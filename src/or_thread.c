#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "or_thread.h"
#include "scheduler.h"

// Global OR array
OperatingRoom ors[MAX_ORS];

// Reference to global completed counter
extern int completed;

// Initialize OR metadata and semaphores
void init_ors() {
    for (int i = 0; i < MAX_ORS; i++) {
        ors[i].id = i + 1;
        ors[i].busy = 0;
        ors[i].current_surgery = NULL;
        sem_init(&ors[i].start_signal, 0, 0);
    }
}

// OR worker thread
void* or_thread(void* arg) {

    OperatingRoom* or = (OperatingRoom*)arg;

    while (1) {

        // Wait for scheduler to assign a surgery
        sem_wait(&or->start_signal);

        Surgery* s = or->current_surgery;

        if (s == NULL)
            continue;

        printf("[time %d] OR %d started surgery %s\n",
               current_time, or->id, s->name);

        // Execute surgery (duration is in real-time seconds)
        sleep(s->duration);

        s->completion_time = current_time + s->duration;
        s->finished = 1;
        completed++;

        printf("[time %d] OR %d completed surgery %s\n",
               s->completion_time, or->id, s->name);

        // Mark OR free
        or->busy = 0;
        or->current_surgery = NULL;

        // Signal scheduler that an OR is free
        sem_post(&or_available);
    }

    return NULL;
}
