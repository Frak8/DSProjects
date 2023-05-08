// the lock server implementation

#include "lock_server.h"
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <map>
#include <chrono>

using namespace std;

struct Lock{
	bool locked;
	pthread_mutex_t mutex;
};

pthread_mutex_t lock;
std::map<int, Lock> locks;

lock_server::lock_server():
  nacquire (0)
{
	pthread_mutex_init(&lock, NULL);
	Lock clientLock = {false};
	
	for(int i=0; i<10; i++) {
		Lock clientLock = {false};
		pthread_mutex_init(&clientLock.mutex, NULL);
		locks[i] = clientLock;
	}
}

lock_server::~lock_server() {
	pthread_mutex_destroy(&lock);
}

lock_protocol::status
lock_server::lock_server_grant_lock(int clt, lock_protocol::lockid_t lid, int &r) {
	//pthread_mutex_lock(&lock);

	if(locks.find(lid) != locks.end()) {
		pthread_mutex_lock(&locks.find(lid)->second.mutex);
		locks.find(lid)->second.locked = true;
		lock_protocol::status ret = lock_protocol::OK;

		//pthread_mutex_unlock(&lock);
		printf("Lock granted %d\n", lid);

		return ret;
	}

	lock_protocol::status ret = lock_protocol::RETRY;

	//pthread_mutex_unlock(&lock);
	printf("Lock denied %d\n", lid);

	return ret;
}

lock_protocol::status
lock_server::lock_server_release_lock(int clt, lock_protocol::lockid_t lid, int &r) {

	if(locks.find(lid) != locks.end()) {
		pthread_mutex_unlock(&locks.find(lid)->second.mutex);
		locks.find(lid)->second.locked = false;
		lock_protocol::status ret = lock_protocol::OK;
	
		printf("Lock released %d\n", lid);

		return ret;
	}

	lock_protocol::status ret = lock_protocol::RETRY;

	printf("Lock released denied %d\n", lid);

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


