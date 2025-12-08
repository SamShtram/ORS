#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "scheduler.h"
#include "queue.h"
#include "algorithms.h"
#include "or_thread.h"

// Global simulation clock
int current_time = 0;

// Surgeries
Surgery surgeries[MAX_SURGERIES];
int surgery_count = 0;

// Ready queue (declared in main)
extern SurgeryQueue ready_queue;

// Semaphores
sem_t ready_sem;        // Signals surgeries available
sem_t or_available;     // Signals OR is free

// Completed surgery counter
int completed = 0;

// Initialize scheduler resources
void init_scheduler() {
    sem_init(&ready_sem, 0, 0);
    sem_init(&or_available, 0, MAX_ORS);  // All ORs free initially
}

// Move surgeries into the queue when arrival time matches current_time
void check_arrivals() {
    for (int i = 0; i < surgery_count; i++) {
        if (surgeries[i].arrival_time == current_time) {

            printf("[time %d] Surgery %s arrived\n",
                   current_time, surgeries[i].name);

            enqueue(&ready_queue, &surgeries[i]);
            sem_post(&ready_sem);   // Mark 1 surgery ready
        }
    }
}

int all_surgeries_completed() {
    return (completed == surgery_count);
}

// Scheduler thread
void* scheduler_thread(void* arg) {

    while (!all_surgeries_completed()) {

        sleep(1);
        current_time++;

        // Handle arrivals at this time
        check_arrivals();

        // Assignment loop: assign surgeries as long as conditions allow
        while (!queue_empty(&ready_queue)) {

            // Wait for BOTH: a surgery ready AND an OR free
            sem_wait(&ready_sem);
            sem_wait(&or_available);

            // Select next surgery based on chosen algorithm
            Surgery* next = select_next_surgery(&ready_queue);
            if (next == NULL)
                continue;

            // Find an available OR (safe due to or_available semaphore)
            int assigned = -1;
            for (int i = 0; i < MAX_ORS; i++) {
                if (ors[i].busy == 0) {
                    assigned = i;
                    break;
                }
            }

            if (assigned == -1) {
                // Should never happen because of correct semaphore logic,
                // but we handle it safely.
                enqueue(&ready_queue, next);
                sem_post(&ready_sem);
                continue;
            }

            // Assign surgery
            ors[assigned].current_surgery = next;
            ors[assigned].busy = 1;
            next->start_time = current_time;

            printf("[time %d] Assigned %s to OR %d\n",
                   current_time, next->name, ors[assigned].id);

            // Signal OR thread to begin surgery
            sem_post(&ors[assigned].start_signal);
        }
    }

    return NULL;
}
