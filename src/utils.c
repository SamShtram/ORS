#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "scheduler.h"

void trim_newline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

void load_surgeries_interactive() {
    char name[50];
    int arrival, duration, priority;

    printf("Enter surgeries (type 'done' as name to finish):\n");

    while (1) {
        printf("\nSurgery name: ");
        fgets(name, sizeof(name), stdin);
        trim_newline(name);

        if (strcmp(name, "done") == 0)
            break;

        printf("Arrival time: ");
        scanf("%d", &arrival);

        printf("Duration: ");
        scanf("%d", &duration);

        printf("Priority (1 = highest): ");
        scanf("%d", &priority);

        getchar(); // consume newline after scanf

        // Store surgery
        Surgery* s = &surgeries[surgery_count];
        strcpy(s->name, name);
        s->arrival_time = arrival;
        s->duration = duration;
        s->priority = priority;
        s->start_time = -1;
        s->completion_time = -1;
        s->finished = 0;

        surgery_count++;
    }
}

void print_summary() {
    printf("\n=== Simulation Summary ===\n");

    for (int i = 0; i < surgery_count; i++) {
        Surgery* s = &surgeries[i];

        int wait = s->start_time - s->arrival_time;

        printf("%s: arrival=%d start=%d end=%d wait=%d priority=%d\n",
               s->name,
               s->arrival_time,
               s->start_time,
               s->completion_time,
               wait,
               s->priority);
    }

    printf("===========================\n");
}
