#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;

int n; // Number of processes

// Function to find the index of the process with the shortest remaining time
int findNextProcess(Process proc[], int current_time) {
    // Set min_time to the maximum possible value
    int min_time = INT_MAX;
    // set index to -1
    int index = -1;
    // loop through all processes
    for (int i = 0; i < n; i++) {
        // if the process is not completed and its remaining time is less than min_time
        if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0 && proc[i].remaining_time < min_time) {
            // update min_time and index
            min_time = proc[i].remaining_time;
            index = i;
        }
    }
    return index;
}

// Function to perform the SRTF scheduling
void srtf(Process proc[]) {
    // Initialize variables for current time, number of completed processes, and previous process
    int current_time = 0;
    int completed = 0;
    int prev = -1;
    
    // Loop through all processes
    for (int i = 0; i < n; i++) {
        // Set remaining time for each process
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].is_completed = 0;
    }
    
    // Loop until all processes are completed
    while (completed != n) {
        // Find the process with the shortest remaining time
        int index = findNextProcess(proc, current_time);
        
        // If no process is found, move to the next time unit
        if (index == -1) {
            current_time++;
            continue;
        }
        //Decrement the remaining time of the process
        proc[index].remaining_time--;
        // If the process is completed
        if (proc[index].remaining_time == 0) {
            // Set is_completed to 1
            proc[index].is_completed = 1;
            // Increment completed and Update waiting time and turnaround time 
            completed++;
            proc[index].turnaround_time = current_time + 1 - proc[index].arrival_time;
            proc[index].waiting_time = proc[index].turnaround_time - proc[index].burst_time;
        }
        // Increment the current time
        current_time++;
    }
}

// Function to print the processes and their details
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    // Calculate the number of processes
    n = sizeof(proc) / sizeof(proc[0]);

    // Check if there are no processes
    if (n <= 0) {
        fprintf(stderr, "Error: No processes to schedule.\n");
        return EXIT_FAILURE;
    }
    

    // Perform the SRTF scheduling
    srtf(proc);
    printProcesses(proc);

    return 0;
}
