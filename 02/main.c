/**
 * Basic POSIX Thread (pthread) Usage 2.
 *
 * By walking through this example you’ll learn:
 * - How to pass value to thread when create it.
 * - How to handles multiple threads.
 * - What happens to variables that reside in various scopes.
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#define NUM_THREADS 3

static int global;

void print_addr(void* g, void* m, void* t, void* ts){
    printf("%p\t%p\t%p\t%p\n", g, m, t, ts);
}

void* worker(void* arg){
    int thread;
    static int thread_static;

    print_addr(&global, arg, &thread, &thread_static);

    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    static int main_static;

    pthread_t tids[NUM_THREADS];
    int status;

    printf("global\t\tmain\t\tthread\t\tthread-static\n");
    print_addr(&global, &main, 0, 0);


    for(int i = 0; i < NUM_THREADS; i++){
        // HINT: The thread that runs `worker` should be created.
        // HINT: The address of variable `main_static` should be passed 
        //       when thread created.
        // HINT: Each thread descriptor should be stored appropriately.
        status = pthread_<?1/>(<?2/>);

        if(status != 0){
            printf("WTF?");
            return -1;
        }
    }

    // HINT: The main thread should not be exited until all `worker`s have finished.
    for(<?3/>){
        pthread_<?4/>(<?5/>);
    }

    return 0;
}




/*
Expected output:

global		main		thread		thread-static
0x4dd030	0x4da249	(nil)	(nil)
0x4dd030	0x4dd038	0xb74db34c	0x4dd034
0x4dd030	0x4dd038	0xb6cda34c	0x4dd034
0x4dd030	0x4dd038	0xb7cdc34c	0x4dd034
*/
