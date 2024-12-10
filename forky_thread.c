#include <stdio.h>
#include <stdlib.h>

// Allows for use of wait(), communication of operating system
// and time related functions
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#include "forky.h"

// Function works to allow the process to sleep for a random amount of time
void Random_Sleep_Num() {

    // Setting a seed of rand() by differentiating it's sequence
    srand(time(NULL) ^ (getpid() << 16));

    // Rand() now uses what was made from srand() to get a random sleep number
    int Sleep_Num =  ((rand() % 8)) + 1;
    sleep(Sleep_Num);
}

// Function to create a number of processes
void Fork_Pattern_One(int Num_Things) {
    // fptr works as a regular pointer but points to a function
    FILE *fptr;

    // "a" is used instead of "w" to allow for writing without overwriting
    fptr = fopen("results.txt", "a");

    // Setbuf takes away incorrect outputs sent to the text file
    setbuf(fptr, NULL);

    // Sets the variable Set_Pid to a set process ID
    pid_t Set_Pid;
    
    fprintf(fptr,"Pattern 1:\n** Pattern 1: creating %d processes\n", Num_Things);
    for (int ix = 0; ix <= Num_Things; ix++) {
        Set_Pid = fork();

        // Set_pid receives 0 for successful fork, or -1 for failed fork
        if (Set_Pid == 0) {
            fprintf(fptr, "Process %d (PID: %d) beginning\n", ix, getpid());

            // Call Random_Sleep_Num to stop the process for set amount of time
            Random_Sleep_Num(ix);
            fprintf(fptr, "Process %d (PID: %d) exiting\n", ix, getpid());

            // Exits once it has successfully stated the child processor
            exit(0);

        // failed forking
        } else if (Set_Pid < 0) {
            exit(1);
        }
    }

    // Waits for all the children to exit
    for (int ix = 0; ix <= Num_Things; ix++) {
        wait(NULL);
    }

    fprintf(fptr, "Pattern 1: All children have exited\n\n");

    fclose(fptr);
}

// This pattern allows for creation of processes within child processes
void Fork_Pattern_Two(int amount_of_children_to_create, int process_number) {
    FILE *fptr;
    fptr = fopen("results.txt", "a");
    setbuf(fptr, NULL);

    pid_t pid = fork();

    // Use a created variable from main to keep track of the process number
    process_number = process_number + 1;
    if (pid == 0) {
        if (process_number == 1) {
            fprintf(fptr, "Pattern 2:\n** Pattern 2: creating %d processes\n", amount_of_children_to_create);
        }
        //printf("I am the child\n");
        fprintf(fptr, "Process %d (PID: %d) beginning\n", process_number, getpid());

        // This uses recurssion to allow for creation of processes by child processes
        if (amount_of_children_to_create > 1) {
            fprintf(fptr, "Process %d (PID: %d) started Process %d (PID: %d)\n", process_number, getpid(), process_number + 1, getpid() + 1);
            Fork_Pattern_Two(amount_of_children_to_create - 1, process_number);
        }
        fprintf(fptr, "Process %d (PID: %d) exiting\n", process_number, getpid());
        exit(1);
    }
    return;
}
