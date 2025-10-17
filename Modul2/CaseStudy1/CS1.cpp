#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <vector>
#include <iterator>
#include <limits>

using namespace std;

// Fungsi untuk mendapatkan waktu lokal sekarang
string getCurrentTime() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    char buf[16];
    strftime(buf, sizeof(buf), "%H:%M:%S", ltm);
    return string(buf);
}

// Struktur untuk menyimpan data halaman website
struct WebPage {
    string url;
    string accessTime;

    // Operator perbandingan untuk memudahkan pencarian di list
    bool operator==(const string& other_url) const {
        return url == other_url;
    }
};

// Deklarasi global untuk navigasi dan history
list<WebPage> navigation;
list<WebPage>::iterator current_page;
list<WebPage> history;

// --- FUNGSI-FUNGSI UTAMA ---

void displayCurrentPage() {
    cout << "\n=========================================";
    cout << "\n-> Anda sekarang berada di: " << current_page->url;
    cout << "\n   (Diakses pada: " << current_page->accessTime << ")";
    cout << "\n=========================================\n";
}

// Fungsi untuk menambahkan atau memperbarui URL di history
void updateHistory(const WebPage& page) {
    // Hapus entri lama jika URL sudah ada di history
    history.remove_if([&](const WebPage& p) {
        return p.url == page.url;
    });
    // Tambahkan URL sebagai yang paling baru (di depan list)
    history.push_front(page);
}

void undo() {
    if (current_page == navigation.begin()) {
        cout << "[!] Tidak ada halaman untuk di-undo." << endl;
    } else {
        current_page--;
        cout << "[<] Undo berhasil. Kembali ke halaman sebelumnya." << endl;
    }
}

void redo() {
    // Cek apakah iterator sudah di elemen terakhir
    if (next(current_page) == navigation.end()) {
        cout << "[!] Tidak ada halaman untuk di-redo." << endl;
    } else {
        current_page++;
        cout << "[>] Redo berhasil. Maju ke halaman berikutnya." << endl;
    }
}

void inputNewURL() {
    cout << "Masukkan URL baru: ";
    string new_url;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
    getline(cin, new_url);

    // Jika user undo lalu input URL baru, hapus jejak redo
    if (next(current_page) != navigation.end()) {
        cout << "[!] Jejak redo telah dihapus." << endl;
        navigation.erase(next(current_page), navigation.end());
    }

    WebPage new_page = {new_url, getCurrentTime()};
    navigation.push_back(new_page);
    current_page++; // Pindah ke halaman yang baru ditambahkan

    updateHistory(new_page);
    cout << "[+] URL '" << new_url << "' berhasil ditambahkan." << endl;
}

void viewHistory() {
    if (history.empty()) {
        cout << "[!] History masih kosong." << endl;
        return;
    }

    int sort_choice;
    cout << "\nTampilkan history dari:" << endl;
    cout << "1. Paling Baru" << endl;
    cout << "2. Paling Lama" << endl;
    cout << "Pilihan: ";
    cin >> sort_choice;

    vector<WebPage> temp_history;
    cout << "\n--- HISTORY ---" << endl;

    if (sort_choice == 1) { // Paling Baru
        int index = 1;
        for (const auto& page : history) {
            cout << index++ << ". " << page.url << " (" << page.accessTime << ")" << endl;
            temp_history.push_back(page);
        }
    } else if (sort_choice == 2) { // Paling Lama
        int index = 1;
        for (auto it = history.rbegin(); it != history.rend(); ++it) {
            cout << index++ << ". " << it->url << " (" << it->accessTime << ")" << endl;
            temp_history.push_back(*it);
        }
    } else {
        cout << "[!] Pilihan tidak valid." << endl;
        return;
    }
    cout << "---------------" << endl;

    cout << "\nMasukkan nomor untuk visit URL (atau 0 untuk kembali): ";
    int visit_choice;
    cin >> visit_choice;

    if (visit_choice > 0 && visit_choice <= temp_history.size()) {
        WebPage& selected_page = temp_history[visit_choice - 1];
        
        cout << "[!] Mengunjungi '" << selected_page.url << "' dari history." << endl;
        
        // Buat page baru dengan waktu akses terbaru
        WebPage visited_page = {selected_page.url, getCurrentTime()};

        // Reset jejak undo/redo
        navigation.clear();
        navigation.push_back({"Home", getCurrentTime()});
        navigation.push_back(visited_page);
        current_page = --navigation.end(); // Set iterator ke halaman yang baru dikunjungi
        
        cout << "[!] Jejak undo/redo telah di-reset." << endl;

        // Perbarui history (pindahkan ke paling atas dengan waktu baru)
        updateHistory(visited_page);

    } else if (visit_choice != 0) {
        cout << "[!] Nomor tidak valid." << endl;
    }
}

int main() {
    // Inisialisasi program dengan halaman "Home"
    WebPage home = {"Home", getCurrentTime()};
    navigation.push_back(home);
    current_page = navigation.begin();
    updateHistory(home);

    int choice;
    do {
        displayCurrentPage();

        cout << "\nMENU UTAMA:" << endl;
        cout << "1. Undo" << endl;
        cout << "2. Redo" << endl;
        cout << "3. Input URL Baru" << endl;
        cout << "4. Lihat History" << endl;
        cout << "5. Exit" << endl;
        cout << "Pilihan Anda: ";

        cin >> choice;

        // Cek jika input bukan integer
        if (cin.fail()) {
            cout << "[!] Input tidak valid, mohon masukkan angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0; // Set ke nilai default untuk melanjutkan loop
            continue;
        }

        switch (choice) {
            case 1:
                undo();
                break;
            case 2:
                redo();
                break;
            case 3:
                inputNewURL();
                break;
            case 4:
                viewHistory();
                break;
            case 5:
                cout << "Terima kasih telah menggunakan browser terminal!" << endl;
                break;
            default:
                cout << "[!] Pilihan tidak valid. Silakan coba lagi." << endl;
        }

    } while (choice != 5);

    return 0;
}