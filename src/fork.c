#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
main()
{
  int i;
  void sighand(int);
  if (i=fork()) {
    signal(SIGCHLD,sighand);
    printf("parent process looping...\n");
    while(1);
    exit(0);
  }
  else {
    printf("child process sleeping...\n");
    sleep(10);
    printf("child process exiting...\n");
    exit(-1);
  }
}
void sighand(int i)
{
  int status;
  printf("caught a signal %d\n",i);
  waitpid (0, &status, 0);
  printf("exit status of child=%d\n",status);
  printf("back to parent loop...\n");
/*
  printf("parent process exiting...\n");
  exit(0);
*/
}
