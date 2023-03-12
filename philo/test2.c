#include <stdio.h>
#include <pthread.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
int is_locked = 0;

void *my_thread_function(void *arg) {
    // Lock the mutex
    pthread_mutex_lock(&my_mutex);

    // Set is_locked to 1 to indicate that the mutex is locked
    is_locked = 1;

    // Do some work while holding the mutex

    // Unlock the mutex
    pthread_mutex_unlock(&my_mutex);

    // Set is_locked back to 0 to indicate that the mutex is not locked
    is_locked = 0;

    pthread_exit(NULL);
}

int main() {
    pthread_t my_thread;

    // Create a thread to lock and unlock the mutex
    pthread_create(&my_thread, NULL, my_thread_function, NULL);

    pthread_detach(my_thread);
    // Check if the mutex is locked
    if (is_locked == 1) {
        printf("The mutex is currently locked\n");
    } else {
        printf("The mutex is currently unlocked\n");
    }

    // Wait for the thread to finish

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct ThreadData {
    Node* node;
    // any other data needed by the thread
} ThreadData;

void* thread_func(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    Node* node = data->node;

    // do something with the node

    return NULL;
}

int main() {
    Node* node = malloc(sizeof(Node));
    node->data = 42;
    node->next = NULL;

    ThreadData* data = malloc(sizeof(ThreadData));
    data->node = node;
    // initialize any other data needed by the thread

    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, (void*)data);

    // do other work in the main thread

    pthread_join(thread, NULL);

    free(data);
    free(node);

    return 0;
}
