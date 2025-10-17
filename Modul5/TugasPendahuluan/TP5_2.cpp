#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Struktur data kustom
struct Patient {
    std::string name;
    int triage_level; // Level 1 (prioritas tertinggi) ... Level 5 (terendah)
};

// TODO 4: Buat sebuah Functor sebagai custom comparator.
// Functor ini akan digunakan oleh std::priority_queue untuk mengurutkan Patient.
// Ingat, std::priority_queue adalah Max-Heap secara default. Untuk membuatnya
// berperilaku seperti Min-Heap (mengeluarkan prioritas terkecil, yaitu level 1),
// operator() harus mengembalikan 'true' jika prioritas 'a' LEBIH RENDAH dari 'b'.
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

int main() {
    // Membuat priority queue menggunakan Functor yang kalian buat
    std::priority_queue<Patient, std::vector<Patient>, ComparePatients> er_queue;

    // TODO 5: Tambahkan beberapa pasien ke dalam queue.
    // Gunakan er_queue.push(...)
    er_queue.push(Patient{"Alfa", 3});
    er_queue.push(Patient{"Beta", 1});
    er_queue.push(Patient{"Cahyo", 2});
    er_queue.push(Patient{"Delta", 5});
    er_queue.push(Patient{"Epsilon", 4});

    std::cout << "Urutan pasien di Ruang Gawat Darurat (dari prioritas tertinggi):" << std::endl;
    while (!er_queue.empty()) {
        // TODO 6: Ambil pasien dengan prioritas tertinggi, cetak namanya, dan hapus dari queue.
        // Gunakan er_queue.top() dan er_queue.pop()
        Patient p = er_queue.top();
        cout << "Nama: " << p.name << " | level: " << p.triage_level << endl;
        er_queue.pop();
    }

    return 0;
}
