#include <iostream>
#include <string>
using namespace std;

class node{
public:
    string data;
    node* next;
    node* prev;
    node(const string& data){
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

void add(node*& head, const string& data){
    node* new_node = new node(data);
    if (head == nullptr) {
        head = new_node;
        return;
    }
    node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node->prev = temp;
}

void delBeg(node*& head){
    if (head == nullptr) {
        cout << "List anda kosong.\n";
        return;
    }
    node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    delete temp;
}

void delEnd(node*& head){
    if (head == nullptr) {
        cout << "List anda kosong.\n";
        return;
    }
    node* temp = head;
    if (temp->next == nullptr) {
        head = nullptr;
        delete temp;
        return;
    }
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->prev->next = nullptr;
    delete temp;
}

void delPos(node*& head, int pos){
    if (head == nullptr) {
        cout << "List anda kosong.\n";
        return;
    }
    if (pos == 1) {
        delBeg(head);
        return;
    }
    node* temp = head;
    for (int i = 1; temp != nullptr && i < pos; i++) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Posisi lebih besar dari ukuran list\n";
        return;
    }
    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }
    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }
    delete temp;
}

void print(node* head){
    int i = 1;
    node* temp = head;
    cout << "\nList kegiatan: \n";
    while (temp != nullptr) {
        cout << i << ". " << temp->data << "\n";
        temp = temp->next;
        i++;
    }
}

int main() {
    node* head = nullptr;
    int MainOpt = 0;
    string act;
    int pos = 0;
    cout << "=== Activity Organizer ===\n";
    while(MainOpt != 4){
        cout << "\nOpsi tersedia: \n";
        cout << "1. Menambahkan kegiatan baru\n";
        cout << "2. Menghapus kegiatan tertentu\n";
        cout << "3. Menampilkan semua list kegiatan\n";
        cout << "4. Keluar dari program\n";
        cout << "Opsi anda: ";
        cin >> MainOpt;
        switch(MainOpt){
            case 1:
                cout << "\nMasukkan kegiatan yang ingin ditambahkan: ";
                getline(cin >> ws, act);
                if(act.empty()){
                    cout << "Kegiatan kosong, batal menambahkan.\n";
                } else {
                    add(head, act);
                }
                break;
            case 2:
                cout << "\nMasukkan posisi kegiatan yang ingin dihapus: ";
                cin >> pos;
                delPos(head, pos);
                break;
            case 3:
                print(head);
                break;
            case 4:
                cout << "\nKeluar dari program...\n";
                break;
            default:
                cout << "\nOpsi tidak valid!\n";
                break;
        }
    }
    while(head) delBeg(head);
    return 0;
}
