#ifndef OR_THREAD_H
#define OR_THREAD_H

#include <pthread.h>
#include <semaphore.h>
#include "surgery.h"

typedef struct {
    int id;                    // OR number (1..3)
    int busy;                  // 0 = free, 1 = busy
    Surgery* current_surgery;  // Surgery being executed
    sem_t start_signal;        // Scheduler signals this when a surgery is assigned
} OperatingRoom;

// Global OR array (size = MAX_ORS)
extern OperatingRoom ors[];

// Initialize OR structures
void init_ors();

// OR thread main function
void* or_thread(void* arg);

#endif
