#include <stdio.h>
#include "algorithms.h"

// Default selected algorithm (can be changed in main)
AlgorithmType selected_algorithm = ALG_SJF;

// Dispatch to correct dequeue function
Surgery* select_next_surgery(SurgeryQueue* q) {
    switch (selected_algorithm) {
        case ALG_FCFS:
            return dequeue(q);

        case ALG_SJF:
            return dequeue_sjf(q);

        case ALG_PRIORITY:
            return dequeue_priority(q);

        default:
            return dequeue(q);
    }
}
