// this is the lock server
// the lock client has a similar interface

#ifndef lock_server_h
#define lock_server_h

#include <string>
#include "lock_protocol.h"
#include "lock_client.h"
#include "rpc.h"
#include <pthread.h>

class lock_server {

 protected:
  int nacquire;

 public:
  lock_protocol::status lock_server_grant_lock(int clt, lock_protocol::lockid_t lid, int &, pthread_mutex_t &lock);
  ~lock_server() {};
  lock_protocol::status stat(int clt, lock_protocol::lockid_t lid, int &);
};

#endif 







