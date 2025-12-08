#include <stdio.h>
#include <pthread.h>
#include "scheduler.h"
#include "or_thread.h"
#include "utils.h"
#include "algorithms.h"
#include "queue.h"

// Global ready queue
SurgeryQueue ready_queue;

// Scheduler and OR threads
pthread_t scheduler_tid;
pthread_t or_tids[MAX_ORS];

int main() {

    // Initialize queue
    init_queue(&ready_queue);

    // Choose scheduling algorithm
    int algo_choice = 0;
    printf("Choose scheduling algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SJF (default)\n");
    printf("3. Priority Scheduling\n");
    printf("Selection: ");
    scanf("%d", &algo_choice);
    getchar(); // consume newline

    switch (algo_choice) {
        case 1:
            selected_algorithm = ALG_FCFS;
            break;
        case 2:
            selected_algorithm = ALG_SJF;
            break;
        case 3:
            selected_algorithm = ALG_PRIORITY;
            break;
        default:
            selected_algorithm = ALG_SJF;
            break;
    }

    // Load surgeries interactively
    load_surgeries_interactive();

    // Initialize scheduler structures
    init_scheduler();

    // Initialize Operating Rooms
    init_ors();

    // Create OR threads
    for (int i = 0; i < MAX_ORS; i++) {
        pthread_create(&or_tids[i], NULL, or_thread, &ors[i]);
    }

    // Create scheduler thread
    pthread_create(&scheduler_tid, NULL, scheduler_thread, NULL);

    // Wait for scheduler to finish
    pthread_join(scheduler_tid, NULL);

    // At this point all surgeries are completed
    printf("\nAll surgeries completed.\n");

    print_summary();

    return 0;
}
