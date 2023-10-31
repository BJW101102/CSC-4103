// Brandon Walton
// Bibhushita Baral
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prioque.h"
#include <stdbool.h>
#include <pthread.h>

int totalProcesses = 0, totalTime = 0, burstTime = 0;
Queue setProcessQueue, readyQueue, terminatedQueue, ioQueue, Q[4];

/*Typedef of Process to store Process information*/
typedef struct Process
{
    int pid, arrival, terminated;
    int cpuburst, ioburst, inQueue, repeat; 
    int copyCPU, copyIO;                    // Keeps track of original copies
    int bad, good;
    int currentQuantum;
    bool potential;                         // Tracks if a process has the potential to promote after consecutive running
    Queue behaviorQueue;                    // Keeps track of a processes' new phase
} Process;

/*Compare Processes*/
int compare_function(const void *e1, const void *e2)
{
    const Process *p1 = (const Process *)e1;
    const Process *p2 = (const Process *)e2;
    return p1->pid - p2->pid;
}

/*Multi Level Feedback Queue Scheduler*/
static void MLFQS()
{
    int clock = 0, currentQueue = 0, totalProcesses = 0;
    bool inCPU = false;    // Ensure that a process remains in the CPU unless its interupted
    bool bypass = false;   // Allow the inside process to burst one more cycle then grab the prempted process
    bool ioBypass = false; // Allow for a check of a higher process from IO
    int totalProcess = queue_length(&readyQueue); //Number of Total Expected Processes
    Process *current = NULL, *inside = NULL, *ioProcess = NULL, *copyInside = NULL;
    /*Running Until the terminatedQueue is full with terminated Processes*/
    while (queue_length(&terminatedQueue) != totalProcess)
    {
        /*IO Handler*/
        if (!empty_queue(&ioQueue))
        {
            ioProcess = pointer_to_current(&ioQueue);
            /*Looping throuh IO Queue to burst all processes in IO*/
            while (ioProcess != NULL)
            {
                ioProcess->bad = 0;
                ioProcess->ioburst--;
                if (ioProcess->ioburst == 0)
                {
                    /*Resetting Process fields to current behavior*/
                    if (ioProcess->repeat >= 1)
                    {
                        ioProcess->repeat--;
                        ioProcess->cpuburst = ioProcess->copyCPU, ioProcess->ioburst = ioProcess->copyIO;
                    }

                    /*Resetting Process fields to new behavior*/
                    if (ioProcess->repeat == 0)
                    {
                        if (!empty_queue(&ioProcess->behaviorQueue))
                        {
                            Process *next = pointer_to_current(&ioProcess->behaviorQueue);
                            ioProcess->cpuburst = next->cpuburst;
                            ioProcess->ioburst = next->ioburst;
                            ioProcess->repeat = next->repeat;
                            ioProcess->copyCPU = next->cpuburst;
                            ioProcess->copyIO = next->ioburst;
                            delete_current(&ioProcess->behaviorQueue);
                        }
                    }
                    /*IO Premption Checker*/
                    if (inside != NULL && inside->inQueue > ioProcess->inQueue)
                    {
                        ioBypass = true;
                    }
                    add_to_queue(&Q[ioProcess->inQueue], ioProcess, 0);
                    delete_current(&ioQueue);
                }

                if (!end_of_queue(&ioQueue))
                {
                    next_element(&ioQueue);
                    ioProcess = pointer_to_current(&ioQueue);
                }
                ioProcess = pointer_to_current(&ioQueue);
            }
            rewind_queue(&ioQueue);
        }

        /*Ready Queue Handler*/
        if (!empty_queue(&readyQueue))
        {
            rewind_queue(&readyQueue);
            current = pointer_to_current(&readyQueue);
            /*Iteratin through entire queue to find all processes with the same arrival time*/
            while (current != NULL && !empty_queue(&readyQueue))
            {
                current->inQueue = 0;
                current->currentQuantum = 0;
                current->terminated = 0;
                current->potential = true;
                if (current->arrival == clock)
                {
                    /*Premption Checker*/
                    if (inside != NULL && inside->inQueue > current->inQueue)
                    {
                        bypass = true;
                    }
                    /*Creating Incoming Processes*/
                    printf("PID: %d, ARRIVAL TIME: %d\n", current->pid, current->arrival);
                    printf("CREATE: Process %d entered the ready queue at time %d.\n", current->pid, clock);
                    current->copyCPU = current->cpuburst, current->copyIO = current->ioburst;
                    add_to_queue(&Q[current->inQueue], current, 0);
                    delete_current(&readyQueue);
                    current = pointer_to_current(&readyQueue);
                }
                else if (!end_of_queue(&readyQueue))
                {
                    next_element(&readyQueue);
                    current = pointer_to_current(&readyQueue);
                }
                else
                {
                    current = NULL;
                    break;
                }
            }
        }

        /*CPU Handler*/
        if (inCPU)
        {
            inside->terminated++;
            inside->cpuburst--;
            inside->currentQuantum++;

            /*Quantum has been exhaused or Process' burst cycle has finished*/
            if (inside->currentQuantum == Q[inside->inQueue].quantum || inside->cpuburst == 0)
            {
                /*Promotion Checker*/
                if (Q[inside->inQueue].quantum - inside->currentQuantum > 0 && inside->potential)
                {
                    copyInside = inside;
                    inside->good++;
                    inside->potential = false;

                    if ((inside->good) == Q[currentQueue].good)
                    {
                        inside->inQueue = currentQueue - 1;
                        inside->currentQuantum = 0;
                        inside->good = 0;
                        inside->bad = 0;
                    }
                }

                /*Demotion Checker*/
                else if (inside->currentQuantum == Q[inside->inQueue].quantum)
                {
                    inside->bad++;
                    if ((inside->bad) == Q[inside->inQueue].bad)
                    {
                        inside->inQueue = currentQueue + 1;
                        inside->currentQuantum = 0;
                        inside->bad = 0;
                    }
                }

                /*Terminated/IO Checker*/
                if (inside->cpuburst == 0)
                {
                    if (inside->repeat == 0 && empty_queue(&inside->behaviorQueue))
                    {
                        printf("FINISHED: Process %d has been finished at time %d.\n", inside->pid, clock);
                        burstTime += inside->terminated;
                        add_to_queue(&terminatedQueue, inside, 0);
                    }
                    else
                    {
                        printf("I/O: Process %d has been blocked for I/O at time %d.\n", inside->pid, clock);
                        inside->currentQuantum = 0;
                        add_to_queue(&ioQueue, inside, 0);
                    }
                }

                /*Requeuing Processes*/
                else
                {
                    printf("QUEUED: Process %d queued at level %d at time %d.\n", inside->pid, inside->inQueue, clock);
                    inside->currentQuantum = 0;

                    add_to_queue(&Q[inside->inQueue], inside, 0);
                }
                delete_current(&Q[currentQueue]);
                inCPU = false;
            }
        }

        /*Grabbing Highest Avaliable Process*/
        if (!inCPU || bypass || ioBypass)
        {
            if (bypass || ioBypass)
            {
                printf("QUEUED: Process %d queued at level %d at time %d\n", inside->pid, inside->inQueue, clock);
                bypass = false;
                ioBypass = false;
            }

            for (int i = 0; i < 4; i++)
            {
                if (!empty_queue(&Q[i]))
                {
                    inside = pointer_to_current(&Q[i]);
                    inside->inQueue = i;
                    currentQueue = i;
                    (i == 0) ? (inside->bad = 0, inside->good = 0) : 0;
                    printf("RUN: Process %d started execution from level %d at time %d; wants to execute for %d ticks\n", inside->pid, inside->inQueue, clock, inside->cpuburst);
                    /*This is used to check if a process is able to promote*/
                    if ((copyInside != NULL && inside != NULL) && copyInside->pid == inside->pid)
                    {
                        inside->potential = true;
                    }
                    inCPU = true;
                    break;
                }
            }
        }
        //Incrementing the clock
        clock++;
    }
    totalTime = clock - 1;
}

/*Initilizing All Processes */
static void init_process(char *filename)
{   /*Opening File*/
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }

    Process *p = malloc(sizeof(Process));
    /*Initializing and sending to setProcessQueue*/
    while (fscanf(fp, "%d %d %d %d %d", &p->arrival, &p->pid, &p->cpuburst, &p->ioburst, &p->repeat) == 5)
    {
        totalProcesses++;
        add_to_queue(&setProcessQueue, p, 0);
        p = malloc(sizeof(Process));
    }

    /*Settin a pointer to the previous and present process in the setProcessQueue*/
    rewind_queue(&setProcessQueue);
    Process *prev = pointer_to_current(&setProcessQueue);
    next_element(&setProcessQueue);
    Process *present = pointer_to_current(&setProcessQueue);
    rewind_queue(&setProcessQueue);

    /*Iterating through setProcessQueue to find similar Process and merge*/
    while (!empty_queue(&setProcessQueue))
    {
        init_queue(&prev->behaviorQueue, sizeof(Process), TRUE, compare_function, FALSE);
        while (present != NULL)
        {   
            /*If Process equal eachother the present processes is being added to the prev processes behaviorQueue to store new behavior*/
            if (prev->pid == present->pid)
            {
                add_to_queue(&prev->behaviorQueue, present, 0);
                delete_current(&setProcessQueue);
            }
            else
            {
                next_element(&setProcessQueue);
            }

            present = pointer_to_current(&setProcessQueue);
            if (present == NULL)
            {
                break;
            }
        }
        /*Moving to the next unique process to renter while loop*/
        add_to_queue(&readyQueue, prev, 0);
        rewind_queue(&setProcessQueue);
        delete_current(&setProcessQueue);

        prev = pointer_to_current(&setProcessQueue);

        if (queue_length(&setProcessQueue) != 0)
        {
            next_element(&setProcessQueue);
            present = pointer_to_current(&setProcessQueue);
        }
    }
    fclose(fp);
}

/*Initilizing All Queues */
static void init_AllQueues(char *filename)
{
    init_queue(&setProcessQueue, sizeof(Process), TRUE, compare_function, FALSE);
    init_queue(&readyQueue, sizeof(Process), TRUE, compare_function, FALSE);
    init_queue(&ioQueue, sizeof(Process), TRUE, compare_function, FALSE);
    init_queue(&terminatedQueue, sizeof(Process), TRUE, compare_function, FALSE);

    Q[0].quantum = 10;
    Q[0].bad = 1;
    Q[0].good = INT_MAX;
    init_queue(&Q[0], sizeof(Process), TRUE, compare_function, FALSE);

    Q[1].quantum = 30;
    Q[1].bad = 2;
    Q[1].good = 1;
    init_queue(&Q[1], sizeof(Process), TRUE, compare_function, FALSE);

    Q[2].quantum = 100;
    Q[2].bad = 2;
    Q[2].good = 2;
    init_queue(&Q[2], sizeof(Process), TRUE, compare_function, FALSE);

    Q[3].quantum = 200;
    Q[3].bad = INT_MAX;
    Q[3].good = 2;
    init_queue(&Q[3], sizeof(Process), TRUE, compare_function, FALSE);
    
    init_process(filename);
}

/*Printing the finalReport for the MLFQS*/
static void finalReport()
{
    int nullTime = (totalTime - burstTime) - 1;

    printf("\nScheduluer shutdown at time %d.\n\n", totalTime);
    printf("Total CPU usage for all processes scheduled:\n");
    printf("Process <<NULL>>:%10d time units\n", nullTime);
    while (!empty_queue(&terminatedQueue))
    {
        Process *p = pointer_to_current(&terminatedQueue);
        printf("Process %d: %12d time units\n", p->pid, p->terminated);
        delete_current(&terminatedQueue);
    }
}

int main()
{
    init_AllQueues("simple copy"); // Change Parameter to File Name
    MLFQS();
    finalReport();
    return 0;
}