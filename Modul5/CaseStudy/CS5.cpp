#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

// =================================================================
// TODO 1: PASTE KODE DARI TP KALIAN DI SINI
// - struct Patient
// - struct ComparePatients (Functor)
// - fungsi printVector (jika perlu)
// - fungsi siftdown, makeheap, dan heapsort
// =================================================================

struct Patient {
    std::string name;
    int triage_level; // Level 1 (prioritas tertinggi) ... Level 5 (terendah)
};

struct ComparePatients {
    bool operator()(const Patient& a, const Patient& b) const {
        // Tulis logika perbandingan di sini
        if(a.triage_level > b.triage_level){
            return true;
        } else{
            return false;
        }
    }
};

void printVector(const std::string& label, const std::vector<int>& vec);

void siftdown(std::vector<int>& H, int start_index, int heap_size) {
    int root = start_index;
    bool swapped;

    do {
        swapped = false;
        int left = 2 * root + 1;
        if (left >= heap_size) break;

        int right = left + 1;
        int swap_index = root;

        if (H[swap_index] < H[left]) swap_index = left;
        if (right < heap_size && H[swap_index] < H[right]) swap_index = right;

        if (swap_index != root) {
            swap(H[root], H[swap_index]);
            root = swap_index;
            swapped = true;
        }

    } while (swapped);
}

void makeheap(std::vector<int>& H) {
    int n = static_cast<int>(H.size());
    for (int i = (n / 2) - 1; i >= 0; --i) {
        siftdown(H, i, n);
    }
}

void heapsort(std::vector<int>& H) {
    int n = static_cast<int>(H.size());
    if (n <= 1) return;

    makeheap(H);

    for (int heap_size = n; heap_size > 1; --heap_size) {
        swap(H[0], H[heap_size - 1]); 
        siftdown(H, 0, heap_size - 1);    
    }
}

int main() {
    std::vector<Patient> daily_patients = {
        {"Pasien Patah Kaki", 3}, {"Pasien Serangan Jantung", 1},
        {"Pasien Flu", 5}, {"Pasien Luka Bakar", 2},
        {"Pasien Sakit Kepala", 4}
    };

    // --- TUGAS 1: BATCH SORTING ---
    std::cout << "--- TUGAS 1: LAPORAN AKHIR HARI (BATCH SORTING) ---" << std::endl;
    
    std::vector<Patient> report_data = daily_patients;
    
    // TODO 2: Urutkan vector 'report_data' menggunakan std::sort.
    // Sediakan sebuah LAMBDA EXPRESSION secara langsung sebagai argumen ketiga
    // untuk memberitahu std::sort cara membandingkan dua pasien.
    // Urutkan berdasarkan triage_level dari yang terkecil (prio tertinggi) ke terbesar.
    std::sort(report_data.begin(), report_data.end(), [](const Patient& a, const Patient& b) {return a.triage_level < b.triage_level;});

    std::cout << "Laporan Pasien Terurut (std::sort):" << std::endl;
    for (const auto& p : report_data) {
        std::cout << "  - " << p.name << " (Prio: " << p.triage_level << ")" << std::endl;
    }
    std::cout << std::endl;


    // --- TUGAS 2: REAL-TIME TRIAGE ---
    std::cout << "--- TUGAS 2: SIMULASI ANTRIAN UGD (REAL-TIME) ---" << std::endl;
    
    // TODO 3: Buat sebuah std::priority_queue menggunakan FUNCTOR 'ComparePatients' dari TP kalian.
    // Lalu, simulasikan proses UGD:
    // 1. Masukkan semua pasien dari 'daily_patients' ke dalam queue satu per satu.
    // 2. Proses antrian dengan mengeluarkan pasien satu per satu hingga queue kosong,
    //    dan cetak nama serta prioritasnya.
    
    std::priority_queue<Patient, std::vector<Patient>, ComparePatients> er_queue;

    er_queue.push(Patient{"Pasien Patah Kaki", 3});
    er_queue.push(Patient{"Pasien Serangan Jantung", 1});
    er_queue.push(Patient{"Pasien Flu", 5});
    er_queue.push(Patient{"Pasien Luka Bakar", 2});
    er_queue.push(Patient{"Pasien Sakit Kepala", 4});

    while(!er_queue.empty()){
        Patient p = er_queue.top();
        cout << " - " << p.name << " (Prio: " << p.triage_level << ")" << endl;
        er_queue.pop();
    }

}
