# Round Robin Scheduling Simulation (C)

This project is a simulation of the Round Robin CPU scheduling algorithm, implemented in C. It was developed as part of an Operating Systems course in Spring 2025.

## Overview
The program models how an operating system schedules processes using the Round Robin algorithm. It generates a set of processes with random interarrival and service times, then simulates their execution using a fixed time quantum.

## Features
- Simulates 100 processes
- Random interarrival times (5–10 units)
- Random service times (4–8 units)
- Round Robin scheduling with:
  - Time quantum = 2
  - Context switch time = 0
- Calculates key performance metrics:
  - Start time
  - End time
  - Initial wait time
  - Total wait time
  - Turnaround time
- Computes and displays averages:
  - Average interarrival time
  - Average service time
  - Average turnaround time
  - Average total wait time

## How It Works
1. Processes are generated with unique IDs.
2. Interarrival times are randomly assigned and used to compute arrival times.
3. Service times are randomly generated.
4. The Round Robin scheduling algorithm is applied:
   - Each process receives up to the defined time quantum.
   - Processes that are not finished are cycled back into execution.
5. After execution, performance metrics are calculated and displayed.

