char *auth;
char *service;

int main(int argc, const char **argv)
{
  char s[5];
  char v5[2];
  char v6[129];

  while ( 1 )
  {
    printf("%p, %p \n", auth, (const void *)service);
    if ( !fgets(s, 128, stdin) )
      break;
    if ( !memcmp(s, "auth ", 5u) )
    {
      auth = (char *)malloc(4u);
      *auth = 0;
      if ( strlen(v5) <= 30 )
        strcpy(auth, v5);
    }
    if ( !memcmp(s, "reset", 5u) )
      free(auth);
    if ( !memcmp(s, "service", 6u) )
      service = strdup(v6);
    if ( !memcmp(s, "login", 5u) )
    {
      if (auth[32])
        system("/bin/sh");
      else
        fwrite("Password:\n", 1u, 0xAu, stdout);
    }
  }
  return 0;
}
