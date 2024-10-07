#include <stdio.h>
#include <stdlib.h>

// These are new inclusion specifically forking
// And threading
// The inclusion of functions within the pthread library
#include <pthread.h>
// This allows for the use wait()
#include <sys/wait.h>
// Allows for communication with the operating systme itself
#include <unistd.h>
// Allows for use of time related function to modify or get it
#include <time.h>

#include "forky.h"

void Random_Sleep_Num() {
    // Setting a seed of rand() by differentiating it's sequence
    // Getpid grabs the ID of the process while shifting the bit to the left
    // By 16
    // Time(NULL) gets a newly elapsed time
    srand(time(NULL) ^ (getpid() << 16));

    // Now that rsand() has set it's seed the data of
    // Rand() will differentiate as well
    int Sleep_Num =  ((rand() % 8)) + 1;

    // Sleep_Num is placed in sleep that pauses for the amount that was
    // Caclulated by last statment
    sleep(Sleep_Num);
}

void Fork_Pattern_One(int Num_Things) {
    // fptr works as a regular pointer but points to a function
    FILE *fptr;
    fptr = fopen("results.txt", "w");

    // Sets the variable Set_Pid to a set process ID
    pid_t Set_Pid;
    
    fprintf(fptr,"Pattern 1:\n** Pattern 1: creating %d processes\n", Num_Things);
    // printf("Pattern 1:\n** Pattern 1: creating %d processes\n", Num_Things);

    // A for loop is used to reprsent the number of processes created
    // By the amount Num_Things is
    for (int ix = 0; ix <= Num_Things; ix++) {

        // Creates a new processes using fork() which is then reprsented
        // By an ID
        Set_Pid = fork();

        // The result of Set_Pid bieng 0 indicates that a new
        // Child processes was sucessfully created
        if (Set_Pid == 0) {
            
            // Outputs that new process has begun while 
            // Displaying it's process ID
            // Later inserted in the results.txt file
            fprintf(fptr, "Process %d (PID: %d) beginning\n", ix, getpid());
            // printf("Process %d (PID: %d) beginning\n", ix, getpid());

            // Call Random_Sleep_Num to stop the process for set amount of time
            Random_Sleep_Num(ix);

            // Out puts the processing existing out with
            // the same process ID and process number
            // Also inserted in the results.txt file
            fprintf(fptr, "Process %d (PID: %d) exiting\n", ix, getpid());
            // printf("Process %d (PID: %d) exiting\n", ix, getpid());

            // Exits once it has successfully stated the child processor
            exit(0);

        // This checks to see if Set_Pid is a less than 0
        // Since a failed forking results in a negative number
        } else if (Set_Pid < 0) {
            exit(1);
        }
        // If the number set by Set_Pid is positive then it is indicated
        // To be the parent process
    }
    
    // Go through a loop with the number of things
    // Wait(NULL) waits for the child process to be terminated

    fprintf(fptr, "** Pattern 1: All processes created\n");

    for (int ix = 1; ix <= Num_Things; ix++) {
        wait(NULL);
    }

    fprintf(fptr, "Pattern 1: All children have exited\n\n");

    fclose(fptr);
}

void Fork_Pattern_Two(int Num_Things) {
    // Stardard pointer
    FILE *ptr;
    ptr = fopen("results.txt", "w");

    // Create a variable of the ID for the processor
    pid_t Set_Pid;

    fprintf(ptr, "Pattern 2:\n** Pattern 2: creating %d processes\n", Num_Things);

    // Same method as of pattern one in creating number of processes
    for (int ix = 0; ix < Num_Things; ix++) {
        
        // Create a new process and set value of fork onto Set_Pid
        Set_Pid = fork();

        // Checks to see if fork was successful with 0
        if (Set_Pid == 0) {

            // Prints the process which is beginning
            fprintf(ptr, "Process %d (PID: %d) beginning\n", ix, getpid());

            // Gets the random number to sleep and stop the processes
            Random_Sleep_Num(ix);

            // Chekcs to see if ix is less than the number of things
            if (ix < Num_Things) {

                // Print that process is beginning the process next to it
                fprintf(ptr, "Process %d (PID: %d) started Process %d (PID: %d)\n", ix, getpid(), ix + 1, getpid() + 1);
            }
        } else if (Set_Pid < 0) {
            // Exits if the fork has failed
            exit(1);

        // If the process isn't 0 or -1 then it's the parent process
        } else {

            // Waits until the child process has been terminated
            wait(NULL);

            // Prints that process has been terminated
            fprintf(ptr, "Process %d (PID: %d) exiting\n", ix, getpid());
            
            // Exits successfully with a 0
            exit(0);
        }
    }

    fclose(ptr);

}