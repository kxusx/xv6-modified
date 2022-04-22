
#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int priority, pid;
  if(argc < 3){
    //printf(2,"Usage: nice pid priority\n");
    exit(0);
  }
  pid = atoi(argv[2]);
  priority = atoi(argv[1]);
  if (priority < 0 || priority > 100){
    //printf(2,"Invalid priority (0-100)!\n");
    exit(0);
  }
  setpriority(priority, pid);
  exit(0);
}