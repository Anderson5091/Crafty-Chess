#include <signal.h>
main() {
  extern void handler(int);

  signal(SIGINT,handler);
  while(1);
  printf("exit\n");
}
void handler(int sig) {
  signal(SIGINT,handler);

  printf("caught a ^C, sig=%d\n",sig);
}
