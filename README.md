# 🖥️ CPU Scheduling Simulator

A high-performance CPU scheduling simulator written in **C++**. This project implements and compares various operating system scheduling policies, providing detailed visualizations (tracing) and performance analytics (statistics).

## 🚀 Features

### Supported Scheduling Algorithms
* **FCFS** (First Come First Serve)
* **RR** (Round Robin) with configurable quantum
* **SPN** (Shortest Process Next)
* **SRT** (Shortest Remaining Time)
* **HRRN** (Highest Response Ratio Next)
* **FB-1** (Feedback with $q=1$)
* **FB-2i** (Feedback with increasing quantum $2^i$)
* **Aging** (Xinu-style priority aging)

### Operational Modes
* **Tracing Mode:** A visual timeline showing process execution (`*`), waiting states (`.`), and idle time.
* **Statistics Mode:** Detailed performance metrics including **Finish Time**, **Turnaround Time**, and **Normalized Turnaround Time** ($W/S$).

---

## 🛠️ Tech Stack
* **Language:** C++11
* **Build Tool:** Makefile
* **Containerization:** Docker (GCC-based environment)

---

## 📦 Getting Started

### Using Docker (Recommended)
To run the simulator in a containerized environment:

1. **Build the image:**
   ```bash
   docker build -t cpu-scheduler .
   ```
2. Run the simulator:
    ```bash
    docker run -it cpu-scheduler
    ```
    
## Local Execution
1. Compile the project:
    ```bash
     make
    ```
2. Run with an input file:
    ```bash
     ./lab7 < testcases/input_file.txt
    ```
