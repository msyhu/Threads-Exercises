/**
 * There's Always a Slight Duplication of Efforts 2.
 *
 * By walking through this example you’ll learn:
 * - How to preserve consistency.
 * 
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h> 

int stick_this_thread_to_core(int core_id);

#define NUM_THREADS 100
#define NUM_TASKS 100000

static int cnt = 0;
pthread_mutex_t counter;

void* worker(void* arg){
    stick_this_thread_to_core((int)arg);
    int progress;

    for(int i = 0; i < NUM_TASKS; i++){
        // The mutex `counter` should be locked.
        pthread_<?1/>(<?2/>);

        progress = cnt++;

        // The mutex `counter` should be released.
        pthread_<?3/>(<?4/>);
    }
    pthread_exit((void*)progress);
}



int main(int argc, char* argv[]){
    pthread_t tids[NUM_THREADS];
    int status;
    int progress = 0;

    // The mutex `counter` should be initiated.
    pthread_<?5/>(<?6/>, NULL);

    for(int i = 0; i < NUM_THREADS; i++){
        // HINT: The thread that runs `worker` should be created.
        // HINT: The address of variable `i` should be passed when thread created.
        // HINT: Each thread descriptor should be stored appropriately.
        status = pthread_<?7/>(<?8/>);

        if(status != 0){
            printf("WTF?");
            return -1;
        }
    }

    // HINT: The main thread should not be exited until all `worker`s have finished.
    for(<?9/>){
        pthread_<?10/>(<?11/>);
        // HINT: The variable `progress` should not be 0.
        printf("\r%d ", progress);

        fflush(stdout);
        usleep(10*1000); // 10ms
    }

    printf("\nexpectd: %d\n", NUM_THREADS * NUM_TASKS);
    printf("result: %d\n", cnt);

    return 0;
}



int stick_this_thread_to_core(int core_id) {
   int num_cores = sysconf(_SC_NPROCESSORS_ONLN);

   cpu_set_t cpuset;
   CPU_ZERO(&cpuset);
   CPU_SET(core_id % num_cores, &cpuset);

   pthread_t current_thread = pthread_self();    
   return pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
}




/*
Expected output:

9301560 
expectd: 10000000
result: 10000000
*/
