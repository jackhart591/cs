#include <stdio.h>
#include <pthread.h>

int prevCount, myCount = 1;
pthread_mutex_t myMutex;
pthread_cond_t myCond1, myCond2;

void* consumer(void* args) {
   printf("CONSUMER THREAD CREATED\n");

   int i = 0;
   do {

      if (prevCount != myCount) {
         printf("CONSUMER: signaling myCond2\n");
         pthread_cond_signal(&myCond2);
         continue;
      } else if (myCount == 10) { return NULL; }

      pthread_mutex_lock(&myMutex);
      printf("CONSUMER: waiting on myCond1\n");
      pthread_cond_wait(&myCond1, &myMutex);
      printf("CONSUMER: myMutex locked\n");

      myCount = i;  

      pthread_mutex_unlock(&myMutex);
      printf("CONSUMER: myMutex unlocked\n");

      printf("CONSUMER: signaling myCond2\n");
      pthread_cond_signal(&myCond2);

      i++;
   } while (1);
}

int main() {
   pthread_t tid;
   pthread_mutex_init(&myMutex, NULL);
   prevCount = myCount;
   
   printf("PROGRAM START\n");

   pthread_create(&tid, NULL, consumer, NULL);

   int i;
   do {
      if (prevCount == myCount) { 
         printf("PRODUCER: signaling myCond1\n");
         pthread_cond_signal(&myCond1);
         continue; 
      }

      pthread_mutex_lock(&myMutex);
      printf("PRODUCER: myMutex locked\n");
      printf("PRODUCER: waiting on myCond2\n");
      pthread_cond_wait(&myCond2, &myMutex);

      printf("myCount: %d -> %d\n", prevCount, myCount);
      prevCount = myCount;

      pthread_mutex_unlock(&myMutex);
      printf("PRODUCER: myMutex unlocked\n");

      printf("PRODUCER: signaling myCond1\n");
      pthread_cond_signal(&myCond1);

      if (myCount == 10) { break; }

   } while (1);

   pthread_join(tid, NULL);

   pthread_mutex_destroy(&myMutex);
   
   printf("PROGRAM END\n");
   return 0;
}
