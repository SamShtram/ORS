#ifndef QUEUE_H
#define QUEUE_H

#include "surgery.h"
#include <pthread.h>

// Node for linked-list queue
typedef struct Node {
    Surgery* data;
    struct Node* next;
} Node;

// Queue structure with mutex protection
typedef struct {
    Node* head;
    Node* tail;
    pthread_mutex_t lock;
} SurgeryQueue;

// Initialize queue
void init_queue(SurgeryQueue* q);

// Add surgery to queue
void enqueue(SurgeryQueue* q, Surgery* s);

// Remove first surgery from queue (used by FCFS)
Surgery* dequeue(SurgeryQueue* q);

// Remove shortest-job from queue (SJF)
Surgery* dequeue_sjf(SurgeryQueue* q);

// Remove highest-priority surgery (priority scheduling)
Surgery* dequeue_priority(SurgeryQueue* q);

// Check if queue is empty
int queue_empty(SurgeryQueue* q);

// Free all remaining nodes
void free_queue(SurgeryQueue* q);

#endif
