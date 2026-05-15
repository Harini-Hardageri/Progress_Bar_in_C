#include <stdio.h>
#include <stdlib.h>  //for system function
#include <unistd.h>  //for sleep function
#include <time.h>    //for seeding random function

const int BAR_LENGTH = 50;
const int MAX_TASKS = 5;

typedef struct {
    int id;
    int progress;
    int step;
} Task;

void print_bar(Task task);
void clear_screen();

int main() {
    Task tasks[MAX_TASKS];
    srand(time(NULL));

    for(int i = 0; i < MAX_TASKS; i++) {
        tasks[i].id = i + 1;
        tasks[i].progress = 0;
        tasks[i].step = rand() % 5 + 1;
    }

    int tasks_incomplete = 1;
    while(tasks_incomplete) {
        tasks_incomplete = 0;
        clear_screen();
        printf("\033[0;32m");
        printf("\t\t\tProgress Bars\n");
        for(int i = 0; i < MAX_TASKS; i++) {
            tasks[i].progress += tasks[i].step;
            if(tasks[i].progress > 100) {
                tasks[i].progress = 100;
            }
            else if(tasks[i].progress < 100) {
                tasks_incomplete = 1;
            }
            print_bar(tasks[i]);
        }
        sleep(1); //Sleep for one second;
    }
    printf("All tasks are completed!\n");
    return 0;
}

void clear_screen() {
    system("cls");
}

void print_bar(Task task) {
    int bars_to_show = (task.progress * BAR_LENGTH) / 100;
    printf("\033[0;32m");   //Changes text color to Green
    printf("Task %d: [", task.id);
    for(int i = 0; i < BAR_LENGTH; i++) {
        if(i < bars_to_show) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %d%%\n", task.progress);
    printf("\033[0m");
}