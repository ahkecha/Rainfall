char c[68];

void m()
{
  time_t tVar1;
  
  tVar1 = time((time_t *)NULL);
  printf("%s - %d\n",c,tVar1);
  return;
}

int main(int ac,char** av)
{
  int *puVar1;
  void *pvVar2;
  int *puVar3;
  FILE *__stream;
  
  puVar1 = (int *)malloc(8);
  *puVar1 = 1;
  pvVar2 = malloc(8);
  puVar1[1] = pvVar2;
  puVar3 = (int *)malloc(8);
  *puVar3 = 2;
  pvVar2 = malloc(8);
  puVar3[1] = pvVar2;
  strcpy((char *)puVar1[1],*(char **)(av[1]));
  strcpy((char *)puVar3[1],*(char **)(av[2]));
  __stream = fopen("/home/user/level8/.pass","r");
  fgets(c, 68, __stream);
  puts("~~");
  return 0;
}