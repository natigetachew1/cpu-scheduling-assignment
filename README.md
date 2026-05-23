OS Scheduling & Banker's Algorithm Simulator
Overview
This project is a C++ implementation of major CPU Scheduling Algorithms and the Banker's Algorithm used in Operating Systems.
The program simulates:
First Come First Served (FCFS)
Shortest Job First (SJF - Non Preemptive)
Shortest Remaining Time First (SRTF)
Round Robin Scheduling
Banker's Algorithm (Deadlock Avoidance)
---
Features
CPU Scheduling Algorithms
1. FCFS (First Come First Served)
Processes execute in order of arrival.
Non-preemptive scheduling.
2. SJF (Shortest Job First)
Executes process with smallest burst time first.
Non-preemptive scheduling.
3. SRTF (Shortest Remaining Time First)
Preemptive version of SJF.
CPU always executes process with shortest remaining burst time.
4. Round Robin
Time-sharing scheduling algorithm.
Uses fixed time quantum = 2.
---
Banker's Algorithm
Implements deadlock avoidance using:
Allocation Matrix
Max Matrix
Need Matrix
Available Resources
Safe Sequence Detection
The system checks whether the state is:
SAFE
NOT SAFE
---
Technologies Used
Language: C++
Concepts:
CPU Scheduling
Deadlock Avoidance
Queues
Vectors
Sorting Algorithms
---
Compilation
Use g++ compiler:
```bash
g++ os_scheduling_and_bankers.cpp -o os
```
Run program:
```bash
./os
```
Windows:
```bash
os.exe
```
---
Input Format
Process Input
Example:
```text
4

P1 0 5
P2 1 3
P3 2 8
P4 3 6
```
Format:
```text
ProcessID ArrivalTime BurstTime
```
---
Banker's Algorithm Input
Number of Processes and Resources
Example:
```text
5
3
```
Allocation Matrix
Example:
```text
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
```
Max Matrix
Example:
```text
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
```
Available Resources
Example:
```text
3 3 2
```
---
Output
The program displays:
Completion Time (CT)
Turnaround Time (TAT)
Waiting Time (WT)
Average WT
Average TAT
Need Matrix
Safe Sequence
---
Formula Used
Turnaround Time
TAT = CT - AT
Waiting Time
WT = TAT - BT
---
Project Structure
```text
os_scheduling_and_bankers.cpp
README.md
```
---
Learning Objectives
This project helps understand:
CPU Scheduling Concepts
Process Management
Deadlock Avoidance
Safe State Detection
Operating System Simulation
---
Author
Natnael Getachew Mihert  
Student at Bahir Dar University  
Cybersecurity Mentor and Freelance Security Engineer
