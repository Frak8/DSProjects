// the lock server implementation

#include "lock_server.h"
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

/*
lock_server::lock_server():
  nacquire (0)
{
}
*/

lock_protocol::status
lock_server::lock_server_grant_lock(int clt, lock_protocol::lockid_t lid, int &r, pthread_mutex_t &lock) {
  pthread_mutex_lock(&lock);
  lock_protocol::status ret = lock_protocol::OK;
  printf("stat request from lock server %d\n", clt);
  pthread_mutex_unlock(&lock);
  return ret;	
}

lock_protocol::status
lock_server::stat(int clt, lock_protocol::lockid_t lid, int &r)
{
  lock_protocol::status ret = lock_protocol::OK;
  printf("stat request from clt %d\n", clt);
  r = nacquire;
  return ret;
}


