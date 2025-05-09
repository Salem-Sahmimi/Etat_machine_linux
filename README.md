# System Resource Monitor with C++

This C++ program continuously monitors and displays the CPU and RAM usage on a Linux system. It reads the relevant statistics from the `/proc/stat` and `/proc/meminfo` files, calculates the usage percentage, and updates the display every second. The program runs in an infinite loop, updating the values until interrupted by the user.

## Features

* **CPU Usage:** Displays the current CPU usage percentage, based on user, system, and idle times.
* **RAM Usage:** Displays the current RAM usage percentage, based on total memory and available memory.

## Requirements

* **Operating System:** Linux (since the program reads data from `/proc/stat` and `/proc/meminfo`, which are specific to Linux systems).
* **C++ Compiler:** Any standard C++ compiler (e.g., `g++`).

## How to Compile and Run

1. **Clone the repository or copy the code** into a C++ file (e.g., `system_monitor.cpp`).
2. **Compile the program** using `g++`:

   ```bash
   g++ -o system_monitor system_monitor.cpp
   ```
3. **Run the program**:

   ```bash
   ./system_monitor
   ```

The program will start displaying the CPU and RAM usage, updating every second. To stop the program, press `Ctrl + C`.

## Program Flow

1. The program first reads the CPU statistics from `/proc/stat` and calculates the difference in the CPU times between two consecutive reads (separated by 1 second).
2. It then calculates the percentage of CPU usage by subtracting the idle time from the total time and dividing by the total time.
3. Similarly, it reads the memory statistics from `/proc/meminfo` to determine the total memory and available memory, and computes the percentage of memory used.
4. These values are displayed in the terminal as:

   ```
   CPU : <cpu_usage>% | RAM : <ram_usage>%
   ```

   The program continues updating these values every second.

## Example Output

```
Appuyez sur Ctrl + C pour quitter...

CPU : 15% | RAM : 60%
```

## Notes

* The program uses `sleep(1)` to pause for 1 second between readings.
* The CPU and RAM usage values are updated continuously in the terminal.
* The program terminates when `Ctrl + C` is pressed.

## Troubleshooting

* **"Permission denied" when reading `/proc/stat` or `/proc/meminfo`:** This can happen if the program doesn't have the correct permissions. Make sure you have the necessary read permissions to access these files.
* **Accuracy:** The CPU usage is calculated over a 1-second interval. If your system is under heavy load, the values might fluctuate.
