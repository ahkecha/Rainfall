
void n(void)
{
  system("/bin/cat /home/user/level7/.pass");
  return;
}

void m()
{
  puts("Nope");
  return;
}

int main(undefined4 param_1,char ** av)
{
  char *dest;
  code **fun;
  
  dest = (char *)malloc(0x40);
  fun = (code **)malloc(4);
  *fun = m;
  strcpy(dest,*(char **)(av[1]));
  (**fun)();
  return;
}