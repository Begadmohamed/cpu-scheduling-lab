#include "lab7.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <math.h>

using namespace std;

void Scheduler::execute()
{
    for (int i = 0; i < schedulongPoliceis.size(); i++)
    {
        clearTables();
        if (schedulongPoliceis[i].first == 1)
        {
            FCFS();
            if (type == "trace")
                trace(1, -1);
            else
                stats(1, -1);
        }
        else if (schedulongPoliceis[i].first == 2)
        {
            RR(schedulongPoliceis[i].second);
            if (type == "trace")
                trace(2, schedulongPoliceis[i].second);
            else
                stats(2, schedulongPoliceis[i].second);
        }
        else if (schedulongPoliceis[i].first == 3)
        {
            SPN();
            if (type == "trace")
                trace(3, -1);
            else
                stats(3, -1);
        }
        else if (schedulongPoliceis[i].first == 4)
        {
            SRT();
            if (type == "trace")
                trace(4, -1);
            else
                stats(4, -1);
        }
        else if (schedulongPoliceis[i].first == 5)
        {
            HRRN();
            if (type == "trace")
                trace(5, -1);
            else
                stats(5, -1);
        }
        else if (schedulongPoliceis[i].first == 6)
        {
            FB1();
            if (type == "trace")
                trace(6, -1);
            else
                stats(6, -1);
        }
        else if (schedulongPoliceis[i].first == 7)
        {
            FB2i();
            if (type == "trace")
                trace(7, -1);
            else
                stats(7, -1);
        }
        else if (schedulongPoliceis[i].first == 8)
        {
            AGE(schedulongPoliceis[i].second);
            if (type == "trace")
                trace(8, -1);
        }
    }
}
void Scheduler::trace(int policy, int argument)
{
    if (policy == 1)
    {
        cout << "FCFS  ";
        printHeader();
        cout << '\n';
        printTracing();
        printDashes();
        cout << "\n\n";
    }
    else if (policy == 2)
    {
        if (argument > 10)
            cout << "RR-" << argument << " ";
        else
            cout << "RR-" << argument << "  ";
        printHeader();
        cout << '\n';
        printTracing();
        printDashes();
        cout << "\n\n";
    }
    else if (policy == 3)
    {
        cout << "SPN   ";
        printHeader();
        cout << "\n";
        printTracing();
        printDashes();
        cout << "\n\n";
    }
    else if (policy == 4)
    {
        cout << "SRT   ";
        printHeader();
        cout << '\n';
        printTracing();
        printDashes();
        cout << "\n\n";
    }
    else if (policy == 5)
    {
        cout << "HRRN  ";
        printHeader();
        cout << "\n";
        printTracing();
        printDashes();
        cout << "\n\n";
    }
    else if (policy == 6)
    {
        cout << "FB-1  ";
        printHeader();
        cout << "\n";
        printTracing();
        printDashes();
        cout << "\n\n";
    }
    else if (policy == 7)
    {
        cout << "FB-2i ";
        printHeader();
        cout << "\n";
        printTracing();
        printDashes();
        cout << "\n\n";
    }
    else if (policy == 8)
    {
        cout << "Aging ";
        printHeader();
        cout << "\n";
        printTracing();
        printDashes();
        cout << "\n\n";
    }
}
void Scheduler::stats(int policy, int argument)
{
    if (policy == 1)
    {
        cout << "FCFS" << endl;
        printStats();
        cout << '\n';
    }
    else if (policy == 2)
    {
        cout << "RR-" << argument << endl;
        printStats();
        cout << '\n';
    }
    else if (policy == 3)
    {
        cout << "SPN" << endl;
        printStats();
        cout << '\n';
    }
    else if (policy == 4)
    {
        cout << "SRT" << endl;
        printStats();
        cout << '\n';
    }
    else if (policy == 5)
    {
        cout << "HRRN" << endl;
        printStats();
        cout << '\n';
    }
    else if (policy == 6)
    {
        cout << "FB-1" << endl;
        printStats();
        cout << '\n';
    }
    else if (policy == 7)
    {
        cout << "FB-2i" << endl;
        printStats();
        cout << '\n';
    }
}
void Scheduler::FCFS()
{
    // First Come First Serve Scheduling
    for(int time=0;time<maxSeconds;time++){
        for(int i=0;i<numberOfProcesses;i++){
            if(processes[i].arrivalTime==time){ //process becoms eligible
                readyQueue.push(processes[i]);
            }
        }
        if(!processorBusy && !readyQueue.empty()){ //CPU idle and process ready
            currentProcess=readyQueue.front(); //make first process in ready queue the current process
            readyQueue.pop();
            processorBusy=true; //CPU becomes busy
        }
        if(processorBusy){
            *(processesPrintingArray + currentProcess.id * maxSeconds + time)='*';  
            currentProcess.remainingTime--;
            if(currentProcess.remainingTime==0){
                processorBusy=false;
                currentProcess.finishTime=time+1; //process finishes at the end of this time unit
                currentProcess.turnAroundTime=currentProcess.finishTime - currentProcess.arrivalTime;
                currentProcess.NormTurnTime=currentProcess.turnAroundTime / (float)currentProcess.serveTime;
                processes[currentProcess.id]=currentProcess; //update the process in the process list
            }
            
        }
                queue<Process> tempQueue=readyQueue;
                while(!tempQueue.empty()){
                    int waitingProcessId=tempQueue.front().id; //get the id of the process waiting in ready queue
                    *(processesPrintingArray + waitingProcessId * maxSeconds + time)='.';
                    tempQueue.pop();
                }
    }
}

void Scheduler::RR(int quantum)
{
    // Round Robin Scheduling
    for(int time=0;time<maxSeconds;time++){
        for(int i=0;i<numberOfProcesses;i++){
            if(processes[i].arrivalTime==time){ //process becoms eligible
                readyQueue.push(processes[i]);
            }
        }
        if(!processorBusy && !readyQueue.empty()){ //CPU idle and process ready
            currentProcess=readyQueue.front(); //make first process in ready queue the current process
            readyQueue.pop();
            currentProcess.q=0; //reset quantum counter
            processorBusy=true; //CPU becomes busy
        }
        queue<Process> tempQueue=readyQueue;
                while(!tempQueue.empty()){
                    int waitingProcessId=tempQueue.front().id; //get the id of the process waiting in ready queue
                    *(processesPrintingArray + waitingProcessId * maxSeconds + time)='.';
                    tempQueue.pop();
                }
        if(processorBusy){
            *(processesPrintingArray + currentProcess.id * maxSeconds + time)='*';  
            currentProcess.remainingTime--;
            currentProcess.q++; //increment quantum counter
            if(currentProcess.remainingTime==0){
                processorBusy=false;
                currentProcess.finishTime=time+1; //process finishes at the end of this time unit
                currentProcess.turnAroundTime=currentProcess.finishTime - currentProcess.arrivalTime;
                currentProcess.NormTurnTime=currentProcess.turnAroundTime / (float)currentProcess.serveTime;
                processes[currentProcess.id]=currentProcess; //update the process in the process list
            }
            else if(currentProcess.q==quantum){ //quantum expired
                processorBusy=false;
                readyQueue.push(currentProcess); //push back to ready queue
            }
        }
                
    }

}

void Scheduler::SPN()
{ 
    // Shortest Process Next Scheduling
    for(int time=0;time<maxSeconds;time++){
        for(int i=0;i<numberOfProcesses;i++){
            if(processes[i].arrivalTime==time){ //process becoms eligible
                readyPriorityQueue.push(make_pair(-processes[i].serveTime, processes[i].id)); //push with negative service time to make min-heap
            }
        }
        if(!processorBusy && !readyPriorityQueue.empty()){ //CPU idle and process ready
            int processId=readyPriorityQueue.top().second; //get the id of the process with shortest service time
            readyPriorityQueue.pop();
            currentProcess=processes[processId]; //make process with shortest service time the current process
            processorBusy=true; //CPU becomes busy
        }
        if(processorBusy){
            *(processesPrintingArray + currentProcess.id * maxSeconds + time)='*';  
            currentProcess.remainingTime--;
            if(currentProcess.remainingTime==0){
                processorBusy=false;
                currentProcess.finishTime=time+1; //process finishes at the end of this time unit
                currentProcess.turnAroundTime=currentProcess.finishTime - currentProcess.arrivalTime;
                currentProcess.NormTurnTime=currentProcess.turnAroundTime / (float)currentProcess.serveTime;
                processes[currentProcess.id]=currentProcess; //update the process in the process list
            }
            
        }
                priority_queue<pair<float, int>> tempPQ=readyPriorityQueue;
                while(!tempPQ.empty()){
                    int waitingProcessId=tempPQ.top().second; //get the id of the process waiting in ready queue
                    *(processesPrintingArray + waitingProcessId * maxSeconds + time)='.';
                    tempPQ.pop();
                }
    }
}

void Scheduler::SRT()
{
    // Shortest Remaining Time Scheduling
    for(int time=0;time<maxSeconds;time++){
        for(int i=0;i<numberOfProcesses;i++){
            if(processes[i].arrivalTime==time){ //process becoms eligible
                readyPriorityQueue.push(make_pair(-processes[i].remainingTime, processes[i].id)); //push with negative service time to make min-heap
            }}

        if(processorBusy && !readyPriorityQueue.empty()){
            float bestRemainingTime=-readyPriorityQueue.top().first;;
            if(currentProcess.remainingTime>bestRemainingTime){ //preempt current process
                readyPriorityQueue.push(make_pair(-currentProcess.remainingTime, currentProcess.id)); //push current process back to ready queue
                processorBusy=false;
            }
        
        }
    
        if(!processorBusy && !readyPriorityQueue.empty()){ //CPU idle and process ready
            int processId=readyPriorityQueue.top().second; //get the id of the process with shortest remaining time
            readyPriorityQueue.pop();
            currentProcess=processes[processId]; //make process with shortest remaining time the current process
            processorBusy=true; //CPU becomes busy
        }
        if(processorBusy){
            *(processesPrintingArray + currentProcess.id * maxSeconds + time)='*';  
            currentProcess.remainingTime--;
            if(currentProcess.remainingTime==0){
                processorBusy=false;
                currentProcess.finishTime=time+1; //process finishes at the end of this time unit
                currentProcess.turnAroundTime=currentProcess.finishTime - currentProcess.arrivalTime;
                currentProcess.NormTurnTime=currentProcess.turnAroundTime / (float)currentProcess.serveTime;
                processes[currentProcess.id]=currentProcess; //update the process in the process list
            }
            
        }
                priority_queue<pair<float, int>> tempPQ=readyPriorityQueue;
                while(!tempPQ.empty()){
                    int waitingProcessId=tempPQ.top().second; //get the id of the process waiting in ready queue
                    *(processesPrintingArray + waitingProcessId * maxSeconds + time)='.';
                    tempPQ.pop();
                }
    }
}

void Scheduler::HRRN()
{
    // Highest Response Ratio Next Scheduling
    // Response Ratio = (Current Time - Arrival Time) / Service Time
    for(int time=0;time<maxSeconds;time++){
        for(int i=0;i<numberOfProcesses;i++){
            if(processes[i].arrivalTime==time){ //process becoms eligible
                readyPriorityQueue.push(make_pair(0.0, processes[i].id)); //initial response ratio is 0
            }
        }
        //update response ratios
        priority_queue<pair<float, int>> tempPQ;
        while(!readyPriorityQueue.empty()){
            int processId=readyPriorityQueue.top().second;
            Process process=processes[processId];
            float responseRatio=(float)(time - process.arrivalTime) / (float)(process.serveTime);
            tempPQ.push(make_pair(responseRatio, processId)); //sort by response ratio
            readyPriorityQueue.pop();
        }
        readyPriorityQueue=tempPQ;

        if(!processorBusy && !readyPriorityQueue.empty()){ //CPU idle and process ready
            int processId=readyPriorityQueue.top().second; //get the id of the process with highest response ratio
            readyPriorityQueue.pop();
            currentProcess=processes[processId]; //make process with highest response ratio the current process
            processorBusy=true; //CPU becomes busy
        }
        if(processorBusy){
            *(processesPrintingArray + currentProcess.id * maxSeconds + time)='*';  
            currentProcess.remainingTime--;
            if(currentProcess.remainingTime==0){
                processorBusy=false;
                currentProcess.finishTime=time+1; //process finishes at the end of this time unit
                currentProcess.turnAroundTime=currentProcess.finishTime - currentProcess.arrivalTime;
                currentProcess.NormTurnTime=currentProcess.turnAroundTime / (float)currentProcess.serveTime;
                processes[currentProcess.id]=currentProcess; //update the process in the process list
            }
            
        }
                priority_queue<pair<float, int>> tempPQ2=readyPriorityQueue;
                while(!tempPQ2.empty()){
                    int waitingProcessId=tempPQ2.top().second; //get the id of the process waiting in ready queue
                    *(processesPrintingArray + waitingProcessId * maxSeconds + time)='.';
                    tempPQ2.pop();
                }
    }
}

void Scheduler::FB1()
{
    // Feedback with Quantum 1 Scheduling
    for(int time=0;time<maxSeconds;time++){
        for(int i=0;i<numberOfProcesses;i++){
            if(processes[i].arrivalTime==time){ //process becoms eligible
                if(FBQueues.size()==0){
                    FBQueues.push_back(queue<Process>()); //create first queue if it doesn't exist
                }
                FBQueues[0].push(processes[i]); //new process goes to highest priority queue
            }
        }
        if(!processorBusy){
            for(int level=0;level<FBQueues.size();level++){
                if(!FBQueues[level].empty()){
                    currentProcess=FBQueues[level].front();
                    FBQueues[level].pop();
                    processorBusy=true;
                    break;
                }
            }
        }
                for(int level=0;level<FBQueues.size();level++){
                    queue<Process> tempQueue=FBQueues[level];
                    while(!tempQueue.empty()){
                        int waitingProcessId=tempQueue.front().id; //get the id of the process waiting in ready queue
                        *(processesPrintingArray + waitingProcessId * maxSeconds + time)='.';
                        tempQueue.pop();
                    }
                }
        if(processorBusy){
            *(processesPrintingArray + currentProcess.id * maxSeconds + time)='*';  
            currentProcess.remainingTime--; //quantum is 1, so decrement by 1
            if(currentProcess.remainingTime==0){
                processorBusy=false;
                currentProcess.finishTime=time+1; //process finishes at the end of this time unit
                currentProcess.turnAroundTime=currentProcess.finishTime - currentProcess.arrivalTime;
                currentProcess.NormTurnTime=currentProcess.turnAroundTime / (float)currentProcess.serveTime;
                processes[currentProcess.id]=currentProcess; //update the process in the process list
            }
            else { //process not finished, move to next lower priority queue
                processorBusy=false;
                int nextLevel=currentProcess.FBLevel + 1;
                currentProcess.FBLevel=nextLevel;
                if(nextLevel>=FBQueues.size()){
                    FBQueues.push_back(queue<Process>()); //create new lower priority queue if it doesn't exist
                }
                FBQueues[nextLevel].push(currentProcess);
            }
        }
                
    }

}

void Scheduler::FB2i()
{
    // Feedback with Increasing Quantum 2^i Scheduling
    for(int time=0; time<maxSeconds; time++){
        for(int i=0;i<numberOfProcesses;i++){
            if(processes[i].arrivalTime==time){ //process becoms eligible
                if(FBQueues.size()==0){
                    FBQueues.push_back(queue<Process>()); //create first queue if it doesn't exist
                }
                FBQueues[0].push(processes[i]); //new process goes to highest priority queue
            }
        }
        if(processorBusy){ //prempeetion check
            for(int level=0;level<currentProcess.FBLevel;level++){
            if(!FBQueues[level].empty()){ // if there is a process in a higher priority queue
                FBQueues[currentProcess.FBLevel].push(currentProcess); //push back current process to its queue
                processorBusy=false;
                break;
            }
          }
        }
        if(!processorBusy){
            for(int level=0;level<FBQueues.size();level++){
                if(!FBQueues[level].empty()){
                    currentProcess=FBQueues[level].front();
                    FBQueues[level].pop();
                    processorBusy=true;
                    currentProcess.q=0; //reset quantum counter
                    break;
                }
            }
        }
        for(int level=0;level<FBQueues.size();level++){
                    queue<Process> tempQueue=FBQueues[level];
                    while(!tempQueue.empty()){
                        int waitingProcessId=tempQueue.front().id; //get the id of the process waiting in ready queue
                        *(processesPrintingArray + waitingProcessId * maxSeconds + time)='.';
                        tempQueue.pop();
                    }
                }
        if(processorBusy){
            *(processesPrintingArray + currentProcess.id * maxSeconds + time)='*';
             currentProcess.remainingTime--;
            currentProcess.q++; //increment quantum counter
            int quantum=(int)pow(2, currentProcess.FBLevel); //quantum is 2^level
            if(currentProcess.remainingTime==0){
                processorBusy=false;
                currentProcess.finishTime=time+1; //process finishes at the end of this time unit
                currentProcess.turnAroundTime=currentProcess.finishTime - currentProcess.arrivalTime;
                currentProcess.NormTurnTime=currentProcess.turnAroundTime / (float)currentProcess.serveTime;
                processes[currentProcess.id]=currentProcess; //update the process in the process list
            }
            else if(currentProcess.q==quantum){ //quantum expired
                processorBusy=false;
                int nextLevel=currentProcess.FBLevel + 1;
                currentProcess.FBLevel=nextLevel;
                if(nextLevel>=FBQueues.size()){
                    FBQueues.push_back(queue<Process>()); //create new lower priority queue if it doesn't exist
                }
                FBQueues[nextLevel].push(currentProcess);
            }
    }
  }
}

void Scheduler::AGE(int quantum)
{
    // Aging Scheduling
    vector <Process>readyList;
    for(int time =0;time<maxSeconds;time++){
        for(int i=0;i<numberOfProcesses;i++){
            if(processes[i].arrivalTime==time){ //process becoms eligible
                readyList.push_back(processes[i]); //add to ready list
            }
        }
        if(!processorBusy && !readyList.empty()){
            int maxPriority=-1;
            int selectedIndex=-1;
            for(int k=0;k<readyList.size();k++){ //iterate through ready list to find highest priority process
                if(readyList[k].currentPriority>maxPriority){
                    maxPriority=readyList[k].currentPriority;
                    selectedIndex=k;
                }
            }
            if(selectedIndex!=-1){ // move selected process to current process
                currentProcess=readyList[selectedIndex];
                readyList.erase(readyList.begin()+selectedIndex); //remove from ready list
                currentProcess.q=0; //reset quantum counter
                processorBusy=true;
            }
        }
        for(int k=0;k<readyList.size();k++){
            int waitingProcessId=readyList[k].id; //get the id of the process waiting in ready list
            *(processesPrintingArray + waitingProcessId * maxSeconds + time)='.';
        }

        if(processorBusy){
            *(processesPrintingArray + currentProcess.id * maxSeconds + time)='*';  
            currentProcess.remainingTime--;
            currentProcess.q++; //increment quantum counter
            if(currentProcess.remainingTime==0){
                processorBusy=false;
                currentProcess.finishTime=time+1; //process finishes at the end of this time unit
                currentProcess.turnAroundTime=currentProcess.finishTime - currentProcess.arrivalTime;
                currentProcess.NormTurnTime=currentProcess.turnAroundTime / (float)currentProcess.serveTime;
                processes[currentProcess.id]=currentProcess; //update the process in the process list
            }
            else if(currentProcess.q==quantum){ //quantum expired
                processorBusy=false;
                currentProcess.currentPriority=currentProcess.priority; //reset priority to base priority
                for(int k=0;k<readyList.size();k++){
                    readyList[k].currentPriority+=1; //increase priority of waiting processes
                }
                readyList.push_back(currentProcess); //push back to ready list
            }
        }
    }
}

void Scheduler::printTracing()
{
    for (int process = 0; process < numberOfProcesses; process++)
    {
        cout << processes[process].processName << "     |";
        for (int time = 0; time < maxSeconds; time++)
            cout << *(processesPrintingArray + process * maxSeconds + time) << '|';
        cout << " \n";
    }
}
void Scheduler::printStats()
{
    float sum, mean, sum2;
    cout << "Process    |";
    for (int i = 0; i < numberOfProcesses; i++)
        cout << "  " << processes[i].processName << "  |";
    cout << endl;
    cout << "Arrival    |";
    for (int i = 0; i < numberOfProcesses; i++)
    {
        if (processes[i].arrivalTime < 10)
            cout << "  " << processes[i].arrivalTime << "  |";
        else
            cout << " " << processes[i].arrivalTime << "  |";
    }
    cout << endl;
    cout << "Service    |";
    for (int i = 0; i < numberOfProcesses; i++)
    {
        if (processes[i].arrivalTime < 10)
            cout << "  " << processes[i].serveTime << "  |";
        else
            cout << " " << processes[i].serveTime << "  |";
    }
    cout << " Mean|" << endl;
    cout << "Finish     |";
    for (int i = 0; i < numberOfProcesses; i++)
    {
        if (processes[i].finishTime >= 10)
            cout << " " << processes[i].finishTime << "  |";
        else
            cout << "  " << processes[i].finishTime << "  |";
    }
    cout << "-----|" << endl;
    cout << "Turnaround |";
    for (int i = 0; i < numberOfProcesses; i++)
    {

        if (processes[i].turnAroundTime >= 10)
            cout << " " << (int)processes[i].turnAroundTime << "  |";
        else
            cout << "  " << (int)processes[i].turnAroundTime << "  |";
        sum += processes[i].turnAroundTime;
    }
    cout << fixed;
    cout << setprecision(2);
    mean = (sum * 1.0) / numberOfProcesses;
    if (mean >= 10)
        cout << mean << "|";
    else
        cout << " " << mean << "|";
    cout << endl;
    cout << "NormTurn   |";
    sum2 = 0;
    for (int i = 0; i < numberOfProcesses; i++)
    {
        if (processes[i].NormTurnTime > 10)
            cout << processes[i].NormTurnTime << "|";
        else
            cout << " " << processes[i].NormTurnTime << "|";
        sum2 += (processes[i].NormTurnTime * 1.0);
    }

    mean = (sum2 * 1.0) / numberOfProcesses;
    if (mean > 10)
        cout << mean << "|";
    else
        cout << " " << mean << "|";
    cout << endl;
}
void Scheduler::clearTables()
{

    for (int i = 0; i < numberOfProcesses; i++)
    {
        for (int j = 0; j < maxSeconds; j++)
            *(processesPrintingArray + i * maxSeconds + j) = ' ';
    }
    for (int i = 0; i < numberOfProcesses; i++)
    {
        processes[i].finishTime = 0;
        processes[i].turnAroundTime = 0;
        processes[i].NormTurnTime = 0;
        processes[i].processState = ' ';
        processes[i].remainingTime = processes[i].serveTime;
    }
    processorBusy = false;
    while (!readyQueue.empty())
        readyQueue.pop();
    while (!readyPriorityQueue.empty())
        readyPriorityQueue.pop();
}
void Scheduler::splitPolicyAndParameter(string str)
{
    string w = "";
    pair<int, int> policies;
    bool parameterExists = false;
    policies.second = -1;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '-')
        {
            parameterExists = true;
            policies.first = stoi(w);
            w = "";
        }
        else if (str[i] == ',')
        {
            if (parameterExists)
                policies.second = stoi(w);
            else
            {
                policies.first = stoi(w);
                policies.second = -1;
            }
            w = "";
            schedulongPoliceis.push_back(policies);
            parameterExists = false;
        }
        else
            w = w + str[i];
    }
    if (parameterExists)
        policies.second = stoi(w);
    else
        policies.first = stoi(w);
    schedulongPoliceis.push_back(policies);
}
void Scheduler::splitPrcoessAndTimes(string str, int id)
{
    Process process;
    string w = "";
    process.processName = str[0];
    for (int i = 2; i < str.length(); i++)
    {
        if (str[i] == ',')
        {
            process.arrivalTime = stoi(w);
            w = "";
        }
        else
            w = w + str[i];
    }
    processorBusy = false;
    process.processState = ' ';
    if (schedulongPoliceis[0].first == 8)
    {
        process.priority = stoi(w);
        process.currentPriority = stoi(w);
    }
    else
        process.serveTime = stoi(w);
    process.remainingTime = process.serveTime;
    process.waitingTime = 0;
    process.id = id;
    processes.push_back(process);
}
void Scheduler::readFile()
{
    processorBusy = false;
    string temp1, temp2;
    cin >> type;
    cin >> temp1;
    splitPolicyAndParameter(temp1);
    cin >> maxSeconds;
    cin >> numberOfProcesses;

    for (int i = 0; i < numberOfProcesses; i++)
    {
        cin >> temp2;
        splitPrcoessAndTimes(temp2, i);
    }
    processesPrintingArray = new char[numberOfProcesses * maxSeconds];
    currentProcess.processName = 0;
    currentProcess.q = 0;
    clearTables();
}
void Scheduler::printHeader()
{
    for (int i = 0; i < maxSeconds + 1; i++)
        cout << i % 10 << ' ';
    cout << "\n";
    printDashes();
}
void Scheduler::printDashes()
{
    cout << "------------------------------------------------";
}
int main(void)
{
    Scheduler scheduler;
    scheduler.readFile();
    scheduler.execute();
    return 0;
}