// the lock server implementation

#include "lock_server.h"
#include <sstream>
#include <list>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

bool lock_available = true;
int lock_holder_id;
pthread_mutex_t lock;
std::list<int> locks;

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
  pthread_mutex_lock(&lock);

    for(int i : locks) {
      printf("Lock %d\n", lid);
      if(i == lid) {
        printf("Lock is held %d\n", lid);
        lock_available = false;
      }
    }    

  if(lock_available) {
    printf("Lock available %d\n", lid);
    //lock_available = false;
    lock_holder_id = clt;

    locks.push_front(lid);

    /* 
    for(int i : locks) {
      printf("Lock %d\n", i);
    }
    */

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
  }	
}

lock_protocol::status
lock_server::lock_server_release_lock(int clt, lock_protocol::lockid_t lid, int &r) {
  pthread_mutex_lock(&lock);

   /*	
   for(int i : locks) {
     if(i == lid) {
       printf("Lock released %d\n", lid);
       locks.remove(i);
       //lock_available = true;
     }
   }     
   */
  lock_protocol::status ret = lock_protocol::OK;
  pthread_mutex_unlock(&lock);

  return ret;

  /*
  if(!lock_available) {
    //lock_available = true;	
    lock_protocol::status ret = lock_protocol::OK;
    printf("Lock released %d\n", clt);
     
    pthread_mutex_unlock(&lock);
    return ret;
  }
  else {
    lock_protocol::status ret = lock_protocol::OK;
    pthread_mutex_unlock(&lock);

    return ret;
  }
  */
}

lock_protocol::status
lock_server::stat(int clt, lock_protocol::lockid_t lid, int &r)
{
  lock_protocol::status ret = lock_protocol::OK;
  printf("stat request from clt %d\n", clt);
  r = nacquire;
  return ret;
}


