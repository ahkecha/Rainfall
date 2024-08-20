void p(void)
{
  unsigned int unaff_retaddr;
  char buffer [76];
  
  fflush(stdout);
  gets(buffer);
  if ((unaff_retaddr & 0xb0000000) == 0xb0000000) {
    printf("(%p)\n",unaff_retaddr);
    exit(1);
  }
  puts(buffer);
  strdup(buffer);
  return;
}

int main(void)
{
  p();
  return 0;
}
