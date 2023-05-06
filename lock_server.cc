// the lock server implementation

#include "lock_server.h"
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <map>

pthread_mutex_t lock;
std::map<int, bool> locks;

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

	if(locks.find(lid) == locks.end()) {
		lock_protocol::status ret = lock_protocol::OK;

		locks.insert(std::make_pair(lid, true));
     
  	pthread_mutex_unlock(&lock);
  	printf("Lock granted %d\n", lid);

		return ret;
	}
	else {
		lock_protocol::status ret = lock_protocol::RETRY;
     
  	pthread_mutex_unlock(&lock);
  	printf("Lock request denied %d\n", lid);

		return ret;
	}
}

lock_protocol::status
lock_server::lock_server_release_lock(int clt, lock_protocol::lockid_t lid, int &r) {
  pthread_mutex_lock(&lock);

	if(locks.find(lid) != locks.end()) {
		lock_protocol::status ret = lock_protocol::OK;

		locks.erase(locks.find(lid));
     
  	pthread_mutex_unlock(&lock);
  	printf("Lock released %d\n", lid);

		return ret;
	}
	else {
		lock_protocol::status ret = lock_protocol::RETRY;
     
  	pthread_mutex_unlock(&lock);
  	printf("Lock is unheld %d\n", lid);

		return ret;
	}
}

lock_protocol::status
lock_server::stat(int clt, lock_protocol::lockid_t lid, int &r)
{
  lock_protocol::status ret = lock_protocol::OK;
  printf("stat request from clt %d\n", clt);
  r = nacquire;
  return ret;
}


