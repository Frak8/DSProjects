//
// Lock demo
//

#include "lock_protocol.h"
#include "lock_client.h"
#include "rpc.h"
#include <arpa/inet.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

std::string dst;
lock_client *lc;
pthread_mutex_t lock;

int
main(int argc, char *argv[])
{
  int r;
  pthread_mutex_init(&lock, NULL);

  if(argc != 2){
    fprintf(stderr, "Usage: %s [host:]port\n", argv[0]);
    exit(1);
  }

  dst = argv[1];
  lc = new lock_client(dst);
  r = lc->acquire(1);
  printf ("acquare returned %d\n", r);
   r = lc->release(1);
  printf ("release returned %d\n", r);
  r = lc->stat(1);
  printf ("stat returned %d\n", r);
}
