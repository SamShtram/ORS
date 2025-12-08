#ifndef SURGERY_H
#define SURGERY_H

typedef struct {
    char name[50];
    int arrival_time;
    int duration;
    int priority;      // 1 = highest priority
    int start_time;
    int completion_time;
    int finished;
} Surgery;

#endif
