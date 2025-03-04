#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    //set variables to keep track of the time
    int time = 0;
    printf("Execution Order: ");
    while (1) {
        //create a variable to check if all processes are done
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (proc[i].burst_time <= 0) {
                fprintf(stderr, "Error: Invalid burst time for process %d.\n", proc[i].process_id);
                return;
            }
            
            //check if the process is not done
            if (proc[i].remaining_time > 0) {
               
                done = 0;
                //print the process
                printf("P%d ", proc[i].process_id);
                //check if the process is done
                if (proc[i].remaining_time > quantum) {
                    //add the quantum to the time
                    time += quantum;
                    //subtract the quantum from the remaining time
                    proc[i].remaining_time -= quantum;
                //if the process is done
                } else {
                    //add the remaining time to the time
                    time += proc[i].remaining_time;
                    //set the waiting time
                    proc[i].waiting_time = time - proc[i].arrival_time - proc[i].burst_time;
                    //set the turnaround time
                    proc[i].turnaround_time = time - proc[i].arrival_time;
                    //set the remaining time to zero to indicate that the process is done
                    proc[i].remaining_time = 0;
                    //increment the done variable
                    
                }
            }
        }
        //check if all processes are done if so break out of the loop
        if (done) break;
    }
    printf("\n");
}

// Function to calculate turnaround times for all processes
void calculateTurnaroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

// Function to perform the round-robin scheduling
void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
    calculateTurnaroundTime(proc, n);
}

// Function to print the processes and their details
void printProcesses(Process proc[], int n) {
    // Check if the number of processes is invalid
    if (n <= 0) {
        fprintf(stderr, "Error: Invalid number of processes.\n");
        return;
    }
    // Print the processes
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    // Set the number of processes
    int n = sizeof(proc) / sizeof(proc[0]); 
    // Set the time quantum
    int quantum = 4; 
    
    // Check if the number of processes or quantum time is invalid
    if (n <= 0 || quantum <= 0) {
        fprintf(stderr, "Error: Invalid number of processes or quantum time.\n");
        return EXIT_FAILURE;
    }

    // Set the remaining time for each process
    for (int i = 0; i < n; i++) proc[i].remaining_time = proc[i].burst_time;
    
    //run the program and print the processes
    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}
