# Level 0

Disassembling the main function, there is a comparaison on the first command line argument that checks if av[1] is equal to 423, if so it spawns a shell with level1

```gdb
   0x08048ed9 <+25>:    cmp    $0x1a7,%eax
```                                                                                                                                          

We simply run the binary with 423 as the first argument and get the flag:

```bash
level0@RainFall:~$ ./level0 423
$ id
uid=2030(level1) gid=2020(level0) groups=2030(level1),100(users),2020(level0)
$ cd /home/user/level1
$ cat .pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
$ 
```