// the lock server implementation

#include "lock_server.h"
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

bool lock_available = true;
int lock_holder_id;
pthread_mutex_t lock;

lock_server::lock_server():
  nacquire (0)
{
  pthread_mutex_init(&lock, NULL);
}

lock_server::~lock_server() {
  pthread_mutex_destroy(&lock);
}


lock_protocol::status
lock_server::lock_server_grant_lock(int clt, lock_protocol::lockid_t lid, int &r) {


printf("Grant request from Client %d for Lock ID %d\n",clt , lid );
lock_protocol::status ret = lock_protocol::OK;
/*  pthread_mutex_lock(&lock);

  if(lock_available) {
    lock_available = false;
    lock_holder_id = lid;

    lock_protocol::status ret = lock_protocol::OK;
     
    pthread_mutex_unlock(&lock);
    printf("Lock granted %d\n", clt);

    return ret;	
  }
  else {
    lock_protocol::status ret = lock_protocol::RETRY;
    pthread_mutex_unlock(&lock);
    printf("Lock request denied %d\n", clt);

    return ret;
  } */	
  r = nacquire;
return ret;
}

lock_protocol::status
lock_server::lock_server_release_lock(int clt, lock_protocol::lockid_t lid, int &r) {
printf("Release request from Client %d for Lock ID %d\n",clt , lid );
lock_protocol::status ret = lock_protocol::OK;

/*  pthread_mutex_lock(&lock);

  if(!lock_available) {
    if(lock_holder_id == lid) {
      lock_available = true;
      lock_holder_id = -111111;	
      lock_protocol::status ret = lock_protocol::OK;
      printf("Lock released %d\n", clt);
     
      pthread_mutex_unlock(&lock);
      return ret;
    }
  }
  else {
    lock_protocol::status ret = lock_protocol::OK;
    pthread_mutex_unlock(&lock);

    return ret;
  } */
  r = nacquire;
return ret;
}

lock_protocol::status
lock_server::stat(int clt, lock_protocol::lockid_t lid, int &r)
{
  printf("Status request from Client %d for Lock ID %d\n",clt , lid );
  lock_protocol::status ret = lock_protocol::OK;
  printf("stat request from clt %d\n", clt);
  r = nacquire;
  return ret;
}


