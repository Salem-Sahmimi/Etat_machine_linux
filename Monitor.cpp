#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>  // pour sleep()
using namespace std;

// Fonction pour lire l'utilisation du CPU
int lirePourcentageCPU() {
    ifstream file;
    string line;
    long user1, nice1, system1, idle1, iowait1, irq1, softirq1, steal1;
    long user2, nice2, system2, idle2, iowait2, irq2, softirq2, steal2;

    // Première lecture
    file.open("/proc/stat");
    if (!file.is_open()) return -1;
    getline(file, line);
    sscanf(line.c_str(), "cpu  %ld %ld %ld %ld %ld %ld %ld %ld",
           &user1, &nice1, &system1, &idle1, &iowait1, &irq1, &softirq1, &steal1);
    file.close();

    sleep(1); // pause 1 seconde

    // Deuxième lecture
    file.open("/proc/stat");
    getline(file, line);
    sscanf(line.c_str(), "cpu  %ld %ld %ld %ld %ld %ld %ld %ld",
           &user2, &nice2, &system2, &idle2, &iowait2, &irq2, &softirq2, &steal2);
    file.close();

    long idleDiff = (idle2 + iowait2) - (idle1 + iowait1);
    long total1 = user1 + nice1 + system1 + idle1 + iowait1 + irq1 + softirq1 + steal1;
    long total2 = user2 + nice2 + system2 + idle2 + iowait2 + irq2 + softirq2 + steal2;
    long totalDiff = total2 - total1;

    return 100 * (totalDiff - idleDiff) / totalDiff;
}

// Fonction pour lire l'utilisation de la RAM
int lirePourcentageRAM() {
    ifstream memfile("/proc/meminfo");
    string line;
    long memTotal = 0, memAvailable = 0;

    if (!memfile.is_open()) return -1;

    while (getline(memfile, line)) {
        if (line.find("MemTotal:") == 0) {
            sscanf(line.c_str(), "MemTotal: %ld kB", &memTotal);
        } else if (line.find("MemAvailable:") == 0) {
            sscanf(line.c_str(), "MemAvailable: %ld kB", &memAvailable);
        }
        if (memTotal && memAvailable) break;
    }
    memfile.close();

    return (memTotal - memAvailable) * 100 / memTotal;
}

int main() {
    cout << "Appuyez sur Ctrl + C pour quitter...\n" << endl;

    while (true) {
        int cpu = lirePourcentageCPU();
        int ram = lirePourcentageRAM();

        cout << "\rCPU : " << cpu << "% | RAM : " << ram << "%" << flush;
    }

    return 0;
}
