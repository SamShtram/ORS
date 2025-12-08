#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "surgery.h"
#include "queue.h"

// Enumeration for scheduling algorithms
typedef enum {
    ALG_FCFS = 1,
    ALG_SJF = 2,
    ALG_PRIORITY = 3
} AlgorithmType;

// Selected algorithm (set in main)
extern AlgorithmType selected_algorithm;

// Dispatch function to choose correct dequeue implementation
Surgery* select_next_surgery(SurgeryQueue* q);

#endif
