#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc < 2) {
    printf(2, "Usage: waitx command\n");
    exit();
  }

  int pid = fork();
  if(pid == -1) printf(2, "Fork Error\n");
  else if(pid == 0)
  {
    if(exec(argv[1], argv + 1) == -1) printf(2, "No such command\n");
    exit();
  }
  else
  {
    int rtime, wtime;
    waitx(&rtime, &wtime);
    printf(1, "Running Time : %d\nWaiting Time : %d\n", rtime, wtime);
  }

  exit();
}
