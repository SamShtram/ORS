#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <pthread.h>
#include <semaphore.h>
#include "surgery.h"
#include "queue.h"

#define MAX_SURGERIES 200
#define MAX_ORS 3      // Fixed at 3 operating rooms

// Global simulation time
extern int current_time;

// Total surgeries input by user
extern int surgery_count;

// The surgeries array
extern Surgery surgeries[MAX_SURGERIES];

//avaliable ors
extern sem_t or_available;


// Scheduler thread function
void* scheduler_thread(void* arg);

// Initializes scheduler resources (mutexes, semaphores)
void init_scheduler();

// Moves newly arrived surgeries into the ready queue
void check_arrivals();

// Returns 1 when all surgeries are finished
int all_surgeries_completed();

#endif
