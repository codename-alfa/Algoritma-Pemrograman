#include <iostream>
#include <string>
#include <list>
using namespace std;

int countNodes(const list<string>& acts) {
    return acts.size();
}

void insertAtBeginning(list<string>& acts, const string& data) {
    acts.push_front(data);
}

void insertAtEnd(list<string>& acts, const string& data) {
    acts.push_back(data);
}

void insertAtPosition(list<string>& acts, const string& data, int pos) {
    int count = countNodes(acts);
    if (pos < 1 || pos > count + 1) {
        cout << "Posisi invalid!\n";
        return;
    }
    auto i = acts.begin();
    advance(i, pos - 1);
    acts.insert(i, data);
}

void deleteAtBeginning(list<string>& acts) {
    acts.pop_front();
}

void deleteAtEnd(list<string>& acts) {
    acts.pop_back();
}

void deleteAtPosition(list<string>& acts, int pos) {
    int count = countNodes(acts);
    auto i = acts.begin();
    advance(i, pos - 1);
    acts.erase(i);
}

void printListForward(const list<string>& acts) {
    cout << "\nList kegiatan: \n";
    int i = 1;
    for (const auto& acts : acts) {
        cout << i << ". " << acts << "\n";
        i++;
    }
}

void printListReverse(const list<string>& acts) {
    cout << "\nList kegiatan (terbalik): \n";
    int i = acts.size();
    for (auto j = acts.rbegin(); j != acts.rend(); ++j) {
        cout << i << ". " << *j << "\n";
        i--;
    }
}

int main() {
    list<string> acts;
    int mainOpt = 0, pos = 0, addOpt = 0, delOpt = 0, printOpt = 0, count = 0;
    string act;
    cout << "=== Activity Organizer ===\n";
    do {
        cout << "\nOpsi tersedia: \n";
        cout << "1. Menambahkan kegiatan baru\n";
        cout << "2. Menghapus kegiatan tertentu\n";
        cout << "3. Menampilkan semua list kegiatan\n";
        cout << "4. Keluar dari program\n";
        cout << "\nOpsi anda: ";
        cin >> mainOpt;

        switch (mainOpt) {
            case 1:
                do{
                    cout << "\nOpsi penambahan kegiatan yang tersedia: \n";
                    cout << "1. Awal list\n";
                    cout << "2. Akhir list\n";
                    cout << "3. Pilih posisi custom\n";
                    cout << "\nOpsi anda: ";
                    cin >> addOpt;

                    if(addOpt < 1 || addOpt > 3){
                        cout << "\nOpsi tidak valid!\n";
                    }

                } while(addOpt < 1 || addOpt > 3);

                if (addOpt == 3) {
                    count = countNodes(acts);
                    do {
                        cout << "\nPosisi yang diinginkan: ";
                        cin >> pos;
                        if (pos < 1 || pos > (count + 1)) {
                            cout << "\nPosisi tidak valid!\n";
                            pos = 0;
                        }
                    } while (pos < 1 || pos > (count + 1));
                }

                cout << "\nKegiatan yang ingin ditambahkan: ";
                getline(cin >> ws, act);

                if (act.empty()) {
                    cout << "\nKegiatan kosong, batal menambahkan.\n";
                } else {
                    switch (addOpt) {
                        case 1:
                            insertAtBeginning(acts, act);
                            break;
                        case 2:
                            insertAtEnd(acts, act);
                            break;
                        case 3:
                            insertAtPosition(acts, act, pos);
                            break;
                        default:
                            cout << "Opsi tidak valid!\n";
                            break;
                    }
                }
                break;

            case 2:
                if(acts.empty()){
                    cout << "\nList kosong, tidak ada yang bisa dihapus\n";
                } else{
                    do{
                        cout << "\nOpsi penghapusan kegiatan yang tersedia: \n";
                        cout << "1. Awal list\n";
                        cout << "2. Akhir list\n";
                        cout << "3. Pilih posisi custom\n";
                        cout << "\nOpsi anda: ";
                        cin >> delOpt;

                        if(delOpt < 1 || delOpt > 3){
                            cout << "\nOpsi tidak valid!\n";
                        }
                    } while(delOpt < 1 || delOpt > 3);

                    if (delOpt == 3) {
                        count = countNodes(acts);
                        do {
                            cout << "\nPosisi yang diinginkan: ";
                            cin >> pos;
                            if (pos < 1 || pos > count) {
                                cout << "\nPosisi tidak valid!\n";
                                pos = 0;
                            }
                        } while (pos < 1 || pos > count);
                    }

                    switch (delOpt) {
                        case 1:
                            deleteAtBeginning(acts);
                            break;
                        case 2:
                            deleteAtEnd(acts);
                            break;
                        case 3:
                            deleteAtPosition(acts, pos);
                            break;
                        default:
                            cout << "Opsi tidak valid!\n";
                            break;
                    }
                }

                break;

            case 3:
            if(acts.empty()){
                    cout << "\nList kosong\n";
                } else{
                    do{
                        cout << "\nOpsi tampilan list yang tersedia: \n";
                        cout << "1. Normal\n";
                        cout << "2. Terbalik\n";
                        cout << "\nOpsi yang diinginkan: ";
                        cin >> printOpt;

                        if(printOpt < 1 || printOpt > 2){
                            cout << "\nOpsi tidak valid!\n";
                        }
                    } while(printOpt < 1 || printOpt > 2);

                    switch (printOpt) {
                        case 1:
                            printListForward(acts);
                            break;

                        case 2:
                            printListReverse(acts);
                            break;

                        default:
                            cout << "Opsi tidak valid!\n";
                            break;
                            
                    }
                }

                break;

            case 4:
                cout << "\nKeluar dari program...\n";
                break;

            default:
                cout << "\nOpsi tidak valid!\n";
                break;
        }
    } while (mainOpt != 4);

    acts.clear();
    return 0;
}
