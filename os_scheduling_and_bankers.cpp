#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

// ---------------- PROCESS STRUCTURE ----------------
struct Process {
    string id;
    int at, bt;
    int rt; // remaining time
    int ct, tat, wt;
};

// ---------------- PRINT FUNCTION ----------------
void printTable(vector<Process> p) {
    float total_wt = 0, total_tat = 0;

    cout << "\nID\tAT\tBT\tCT\tTAT\tWT\n";

    for (auto &proc : p) {
        total_wt += proc.wt;
        total_tat += proc.tat;

        cout << proc.id << "\t"
             << proc.at << "\t"
             << proc.bt << "\t"
             << proc.ct << "\t"
             << proc.tat << "\t"
             << proc.wt << endl;
    }

    cout << fixed << setprecision(2);

    cout << "\nAverage Waiting Time = "
         << total_wt / p.size() << endl;

    cout << "Average Turnaround Time = "
         << total_tat / p.size() << endl;
}

// ---------------- FCFS ----------------
void fcfs(vector<Process> p) {

    cout << "\n========== FCFS ==========\n";

    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    int current_time = 0;

    for (auto &proc : p) {

        if (current_time < proc.at)
            current_time = proc.at;

        proc.ct = current_time + proc.bt;
        proc.tat = proc.ct - proc.at;
        proc.wt = proc.tat - proc.bt;

        current_time = proc.ct;
    }

    printTable(p);
}

// ---------------- SJF NON PREEMPTIVE ----------------
void sjf(vector<Process> p) {

    cout << "\n===== SJF (Non-Preemptive) =====\n";

    int n = p.size();

    vector<bool> completed(n, false);

    int current_time = 0;
    int done = 0;

    while (done < n) {

        int idx = -1;
        int min_bt = 1e9;

        for (int i = 0; i < n; i++) {

            if (!completed[i] &&
                p[i].at <= current_time &&
                p[i].bt < min_bt) {

                min_bt = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            current_time++;
        }
        else {

            p[idx].ct = current_time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            current_time = p[idx].ct;

            completed[idx] = true;
            done++;
        }
    }

    printTable(p);
}

// ---------------- SRTF ----------------
void srtf(vector<Process> p) {

    cout << "\n========== SRTF ==========\n";

    int n = p.size();

    vector<int> rem(n);

    for (int i = 0; i < n; i++)
        rem[i] = p[i].bt;

    int current_time = 0;
    int completed = 0;

    while (completed < n) {

        int idx = -1;
        int min_rt = 1e9;

        for (int i = 0; i < n; i++) {

            if (p[i].at <= current_time &&
                rem[i] > 0 &&
                rem[i] < min_rt) {

                min_rt = rem[i];
                idx = i;
            }
        }

        if (idx == -1) {
            current_time++;
        }
        else {

            rem[idx]--;
            current_time++;

            if (rem[idx] == 0) {

                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                completed++;
            }
        }
    }

    printTable(p);
}

// ---------------- ROUND ROBIN ----------------
void roundRobin(vector<Process> p, int quantum) {

    cout << "\n===== ROUND ROBIN =====\n";

    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    int n = p.size();

    queue<int> q;

    vector<int> rem(n);
    vector<bool> inQueue(n, false);

    for (int i = 0; i < n; i++)
        rem[i] = p[i].bt;

    int current_time = p[0].at;
    int completed = 0;

    q.push(0);
    inQueue[0] = true;

    while (completed < n) {

        if (q.empty()) {

            current_time++;

            for (int i = 0; i < n; i++) {

                if (!inQueue[i] &&
                    p[i].at <= current_time &&
                    rem[i] > 0) {

                    q.push(i);
                    inQueue[i] = true;
                }
            }

            continue;
        }

        int idx = q.front();
        q.pop();

        int execute = min(quantum, rem[idx]);

        rem[idx] -= execute;
        current_time += execute;

        for (int i = 0; i < n; i++) {

            if (!inQueue[i] &&
                p[i].at <= current_time &&
                rem[i] > 0) {

                q.push(i);
                inQueue[i] = true;
            }
        }

        if (rem[idx] > 0) {
            q.push(idx);
        }
        else {

            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            completed++;
        }
    }

    printTable(p);
}

// ---------------- BANKER'S ALGORITHM ----------------
bool bankers() {

    cout << "\n===== BANKER'S ALGORITHM =====\n";

    int P, R;

    cout << "Enter number of processes: ";
    cin >> P;

    cout << "Enter number of resources: ";
    cin >> R;

    vector<vector<int>> alloc(P, vector<int>(R));
    vector<vector<int>> maxm(P, vector<int>(R));
    vector<vector<int>> need(P, vector<int>(R));

    vector<int> avail(R);

    cout << "\nEnter Allocation Matrix:\n";

    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            cin >> alloc[i][j];

    cout << "\nEnter Max Matrix:\n";

    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            cin >> maxm[i][j];

    cout << "\nEnter Available Resources:\n";

    for (int i = 0; i < R; i++)
        cin >> avail[i];

    // Need Matrix
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = maxm[i][j] - alloc[i][j];
        }
    }

    cout << "\nNeed Matrix:\n";

    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }

    vector<bool> finish(P, false);

    vector<int> safeSeq;

    int count = 0;

    while (count < P) {

        bool found = false;

        for (int i = 0; i < P; i++) {

            if (!finish[i]) {

                bool possible = true;

                for (int j = 0; j < R; j++) {

                    if (need[i][j] > avail[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {

                    for (int j = 0; j < R; j++)
                        avail[j] += alloc[i][j];

                    safeSeq.push_back(i);

                    finish[i] = true;

                    found = true;

                    count++;
                }
            }
        }

        if (!found) {

            cout << "\nSystem is NOT SAFE\n";

            return false;
        }
    }

    cout << "\nSystem is SAFE\n";

    cout << "Safe Sequence: ";

    for (int i : safeSeq)
        cout << "P" << i << " ";

    cout << endl;

    return true;
}

// ---------------- MAIN FUNCTION ----------------
int main() {

    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    cout << "\nEnter Process ID, Arrival Time, Burst Time\n";

    for (int i = 0; i < n; i++) {

        cin >> processes[i].id
            >> processes[i].at
            >> processes[i].bt;

        processes[i].rt = processes[i].bt;
    }

    fcfs(processes);

    sjf(processes);

    srtf(processes);

    roundRobin(processes, 2);

    bankers();

    return 0;
}
