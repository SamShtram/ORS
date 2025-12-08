#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "queue.h"

// Initialize queue
void init_queue(SurgeryQueue* q) {
    q->head = NULL;
    q->tail = NULL;
    pthread_mutex_init(&q->lock, NULL);
}

// Add to end of queue (FCFS behavior)
void enqueue(SurgeryQueue* q, Surgery* s) {
    pthread_mutex_lock(&q->lock);

    Node* node = malloc(sizeof(Node));
    node->data = s;
    node->next = NULL;

    if (q->tail == NULL) {
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }

    pthread_mutex_unlock(&q->lock);
}

// Simple FCFS dequeue
Surgery* dequeue(SurgeryQueue* q) {
    pthread_mutex_lock(&q->lock);

    if (q->head == NULL) {
        pthread_mutex_unlock(&q->lock);
        return NULL;
    }

    Node* node = q->head;
    Surgery* s = node->data;

    q->head = node->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }

    free(node);
    pthread_mutex_unlock(&q->lock);
    return s;
}

// SJF: remove surgery with shortest duration
Surgery* dequeue_sjf(SurgeryQueue* q) {
    pthread_mutex_lock(&q->lock);

    if (q->head == NULL) {
        pthread_mutex_unlock(&q->lock);
        return NULL;
    }

    Node* curr = q->head;
    Node* shortest_prev = NULL;
    Node* prev = NULL;
    Node* shortest = q->head;

    while (curr != NULL) {
        if (curr->data->duration < shortest->data->duration) {
            shortest = curr;
            shortest_prev = prev;
        }
        prev = curr;
        curr = curr->next;
    }

    // Remove shortest node
    if (shortest_prev == NULL) {
        q->head = shortest->next;
    } else {
        shortest_prev->next = shortest->next;
    }

    if (shortest == q->tail) {
        q->tail = shortest_prev;
    }

    Surgery* s = shortest->data;
    free(shortest);

    pthread_mutex_unlock(&q->lock);
    return s;
}

// Priority scheduling: lowest priority number wins (1 is highest priority)
Surgery* dequeue_priority(SurgeryQueue* q) {
    pthread_mutex_lock(&q->lock);

    if (q->head == NULL) {
        pthread_mutex_unlock(&q->lock);
        return NULL;
    }

    Node* curr = q->head;
    Node* best_prev = NULL;
    Node* prev = NULL;
    Node* best = q->head;

    while (curr != NULL) {
        if (curr->data->priority < best->data->priority) {
            best = curr;
            best_prev = prev;
        }
        prev = curr;
        curr = curr->next;
    }

    // Remove best node
    if (best_prev == NULL) {
        q->head = best->next;
    } else {
        best_prev->next = best->next;
    }

    if (best == q->tail) {
        q->tail = best_prev;
    }

    Surgery* s = best->data;
    free(best);

    pthread_mutex_unlock(&q->lock);
    return s;
}

int queue_empty(SurgeryQueue* q) {
    pthread_mutex_lock(&q->lock);
    int empty = (q->head == NULL);
    pthread_mutex_unlock(&q->lock);
    return empty;
}

void free_queue(SurgeryQueue* q) {
    pthread_mutex_lock(&q->lock);

    Node* curr = q->head;
    while (curr != NULL) {
        Node* tmp = curr;
        curr = curr->next;
        free(tmp);
    }

    q->head = NULL;
    q->tail = NULL;

    pthread_mutex_unlock(&q->lock);
}
