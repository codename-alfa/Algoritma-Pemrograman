#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* next;
    Node* prev;
    Node(const string& data) {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

int countNodes(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

void insertAtBeginning(Node*& head, const string& data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

void insertAtEnd(Node*& head, const string& data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void insertAtPosition(Node*& head, const string& data, int pos) {
    int count = countNodes(head);
    if (pos < 1 || pos > count + 1) {
        cout << "Posisi invalid!\n";
        return;
    }
    if (pos == 1) {
        insertAtBeginning(head, data);
        return;
    }
    Node* newNode = new Node(data);
    Node* temp = head;
    for (int i = 1; temp != nullptr && i < pos - 1; i++) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != nullptr) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

void deleteAtBeginning(Node*& head) {
    Node* temp = head;
    head = head->next;
    if (head != nullptr) head->prev = nullptr;
    delete temp;
}

void deleteAtEnd(Node*& head) {
    Node* temp = head;
    if (temp->next == nullptr) {
        head = nullptr;
        delete temp;
        return;
    }
    while (temp->next != nullptr) temp = temp->next;
    temp->prev->next = nullptr;
    delete temp;
}

void deleteAtPosition(Node*& head, int pos) {
    int count = countNodes(head);
    if (pos == 1) {
        deleteAtBeginning(head);
        return;
    }
    Node* temp = head;
    for (int i = 1; temp != nullptr && i < pos; i++) temp = temp->next;
    if (temp->next != nullptr) temp->next->prev = temp->prev;
    if (temp->prev != nullptr) temp->prev->next = temp->next;
    delete temp;
}

void printListForward(Node* head) {
    int i = 1;
    Node* temp = head;
    cout << "\nList kegiatan: \n";
    while (temp != nullptr) {
        cout << i << ". " << temp->data << "\n";
        temp = temp->next;
        i++;
    }
}

void printListReverse(Node* head) {
    int i = countNodes(head);
    Node* temp = head;
    while (temp->next != nullptr) temp = temp->next;
    cout << "\nList kegiatan (terbalik): \n";
    while (temp != nullptr) {
        cout << i << ". " << temp->data << "\n";
        temp = temp->prev;
        i--;
    }
}

int main() {
    Node* head = nullptr;
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
                    count = countNodes(head);
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
                            insertAtBeginning(head, act);
                            break;
                        case 2:
                            insertAtEnd(head, act);
                            break;
                        case 3:
                            insertAtPosition(head, act, pos);
                            break;
                        default:
                            cout << "Opsi tidak valid!\n";
                            break;
                    }
                }
                break;

            case 2:
                if(head == nullptr){
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
                        count = countNodes(head);
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
                            deleteAtBeginning(head);
                            break;
                        case 2:
                            deleteAtEnd(head);
                            break;
                        case 3:
                            deleteAtPosition(head, pos);
                            break;
                        default:
                            cout << "Opsi tidak valid!\n";
                            break;
                    }
                }

                break;

            case 3:
                if(head == nullptr){
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
                            printListForward(head);
                            break;

                        case 2:
                            printListReverse(head);
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

    while (head) deleteAtBeginning(head);
    return 0;
}
