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

int
main(int argc, char *argv[])
{
  int r;

  if(argc != 2){
    fprintf(stderr, "Usage: %s [host:]port\n", argv[0]);
    exit(1);
  }

  dst = argv[1];
  lc = new lock_client(dst);
  r = lc->acquire(2);	
  r = lc->acquire(2);
  r = lc->release(2);
  r = lc->acquire(2);
  r = lc->acquire(3);
  r = lc->acquire(4);
  r = lc->acquire(4);		
  printf ("stat returned %d\n", r);
}
