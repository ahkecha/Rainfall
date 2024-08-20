
int main(int ac,char **av)
{
  int ret;
  char *arg;
  uid_t uid;
  gid_t gid;
  
  ret = atoi(av[1]);
  if (ret == 423) {
    arg = strdup("/bin/sh");
    gid = getegid();
    uid = geteuid();
    setresgid(gid,gid,gid);
    setresuid(uid,uid,uid);
    execv("/bin/sh",&arg);
  }
  else {
    fwrite("No !\n",1,5,(FILE *)stderr);
  }
  return 0;
}