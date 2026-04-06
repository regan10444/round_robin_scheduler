#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int interArrival_times[99];
int arrival_times[100];
int service_times[100];
int process_id[100];
int start_time[100];
int end_time[100];
int initial_wait_times[100];
int totalWaitTimes[100];
int turnaround_times[100];

double averageI;
double averageS;
double averageT;
double averageTW;

void createProcessID() //creates process ids from 0 to 99
{
    for (int i = 0; i < 100; i++)
    {
        process_id[i] = i;
    }
}

//generates random interarrival times between 5 and 10
void createInterarrivalTimes()
{
    for (int i = 0; i < 99; i++)
    {
        interArrival_times[i] = 5 + (rand() % 6);
    }
}

void createArrivalTimes()
{
    arrival_times[0] = 0; //first process arrives at 0
    for (int i = 1; i < 100; i++)
    {
        arrival_times[i] = arrival_times[i - 1] + interArrival_times[i - 1];
    }
}

// generates random service times between 4 and 8
void createServiceTimes()
{
    for (int i = 0; i < 100; i++)
    {
        service_times[i] = 4 + (rand() % 5);
    }
}

void roundRobinScheduling()
{
    int quantum = 2;
    int contextSwitch = 0;
    int clock_time = 0;

    int remaining_times[100];
    int finished[100] = {0};
    int finished_count = 0;

    for (int i = 0; i < 100; i++)
    {
        remaining_times[i] = service_times[i];
        start_time[i] = -1;
        end_time[i] = -1;
    }

    while (finished_count < 100)
    {
        for (int i = 0; i < 100; i++)
        {
            if (finished[i] == 0 && arrival_times[i] <= clock_time)
            {
                if (start_time[i] == -1)
                {
                    start_time[i] = clock_time;
                }

                int executed_time = (remaining_times[i] > quantum) ? quantum : remaining_times[i];

                remaining_times[i] -= executed_time;
                clock_time += executed_time;

                if (remaining_times[i] == 0)
                {
                    end_time[i] = clock_time;
                    finished[i] = 1;
                    finished_count++;
                }
                else
                {
                    clock_time += contextSwitch;
                }
            }
        }

        int process_running = 0;

        for (int i = 0; i < 100; i++)
        {
            if (finished[i] == 0 && arrival_times[i] <= clock_time)
            {
                process_running = 1;
                break;
            }
        }

        if (process_running == 0)
        {
            clock_time++;
        }
    }
}

void createInitialWaitTimes()
{
    for (int i = 0; i < 100; i++)
    {
        initial_wait_times[i] =
            (start_time[i] >= arrival_times[i]) ?
            start_time[i] - arrival_times[i] : 0;
    }
}

void createTurnaroundTimes()
{
    for (int i = 0; i < 100; i++)
    {
        turnaround_times[i] = end_time[i] - arrival_times[i];
    }
}

void createTotalWaitTimes()
{
    for (int i = 0; i < 100; i++)
    {
        totalWaitTimes[i] = turnaround_times[i] - service_times[i];
    }
}

void averageInterarrival()
{
    int sum = 0;
    for (int i = 0; i < 99; i++)
    {
        sum += interArrival_times[i];
    }
    averageI = (double)sum / 99;
}

void averageServiceTime()
{
    int sum = 0;
    for (int i = 0; i < 100; i++)
    {
        sum += service_times[i];
    }
    averageS = (double)sum / 100;
}

void averageTurnaroundTime()
{
    int sum = 0;
    for (int i = 0; i < 100; i++)
    {
        sum += turnaround_times[i];
    }
    averageT = (double)sum / 100;
}

void averageTotalWaitTime()
{
    int sum = 0;
    for (int i = 0; i < 100; i++)
    {
        sum += totalWaitTimes[i];
    }
    averageTW = (double)sum / 100;
}

int main()
{
    srand(time(0));

    createProcessID();
    createInterarrivalTimes();
    createArrivalTimes();
    createServiceTimes();
    roundRobinScheduling();
    createInitialWaitTimes();
    createTurnaroundTimes();
    createTotalWaitTimes();

    printf("Quantum = 2, Context Switch = 0\n");
    printf("Process ID - Start Time - End Time - Initial Wait Time - Total Wait Time - Turnaround Time\n");

    for (int i = 0; i < 100; i++)
    {
        printf("%10d %10d %8d %17d %15d %15d\n",
               process_id[i],
               start_time[i],
               end_time[i],
               initial_wait_times[i],
               totalWaitTimes[i],
               turnaround_times[i]);
    }

    printf("\n");

    averageInterarrival();
    averageServiceTime();
    averageTurnaroundTime();
    averageTotalWaitTime();

    printf("Average interarrival time: %.2f\n", averageI);
    printf("Average service time: %.2f\n", averageS);
    printf("Average turnaround time: %.2f\n", averageT);
    printf("Average total wait time: %.2f\n", averageTW);

    printf("\n");

    return 0;
}