void run(void)

{
  fwrite("Good... Wait what?\n",1,0x13,stdout);
  system("/bin/sh");
  return;
}

int main(void)
{
  char buffer[76];
  
  gets(buffer);
  return 0;
}
