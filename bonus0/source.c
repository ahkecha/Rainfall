char *__cdecl p(char *string_lijay, char *s)
{
  char buf[4104];

  puts(s);
  read(0, buf, 4096);
  *strchr(buf, 10) = 0;
  return strncpy(string_lijay, buf, 20);
}


char *__cdecl pp(char *dest)
{
  char src[20];
  char v3[28];

  p(src, " - ");
  p(v3, " - ");
  strcpy(dest, src);
  dest[strlen(dest)] = ' ';
  return strcat(dest, v3);
}

int __cdecl main(int argc, const char **argv, const char **envp)
{
  char s[42];

  pp(s);
  puts(s);
  return 0;
}

