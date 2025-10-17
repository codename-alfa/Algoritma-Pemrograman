#include <iostream>
#include <vector>

using namespace std;

void arr(){
    cout << "===ARRAY===\n\n";

    //deklarasi
    int array[5] = {1,2,3,4,5}; //ukuran statis, yaitu 5

    //menampilkan elemen ke output
    int size = sizeof(array) / sizeof(array[0]); //size perlu disimpan ke sebuah variabel yang akan digunakan pada parameter for loop
    cout << "Isi array: ";
    for(int i = 0; i < size; i++){ //perhatikan parameter for loop
        cout << array[i] << " ";
    }
    cout << endl << endl;

    //akses elemen
    cout << "array elemen ke-2: " << array[1]; 
    cout<< endl << endl;

    //penambahan elemen
    cout << "tidak bisa menambahkan elemen pada array ini.\n\n"; //elemen array ini harus di-copy ke array baru dengan elemen baru yang telah ditambahkan

    //pengurangan elemen
    cout << "tidak bisa mengurangi elemen pada array ini.\n\n"; //elemen array ini harus di-copy ke array baru dengan elemen yang telah dihilangkan
}

void vektor(){
    cout << "===VECTOR===\n\n";
    //deklarasi
    vector<int> vektor = {1,2,3,4,5}; //ukuran dinamis, saat ini 5 namun bisa diubah

    //menampilkan elemen ke output
    cout << "isi vector: ";
    for(int i:vektor){ //perhatikan parameter for loop
        cout << i << " ";
    }
    cout << endl << endl;

    //akses elemen
    cout << "vektor elemen ke-2: " << vektor.at(1);
    cout << endl << endl;

    //penambahan elemen 6 ke akhir vector
    cout << "menambahkan elemen 6 ke akhir vektor...\n";
    vektor.push_back(6);
    cout << "isi vector setelah penambahan elemen: ";
    for(int i:vektor){
        cout << i << " ";
    }
    cout << endl << endl;

    //pengurangan elemen terakhir
    cout << "mengurangi elemen terakhir vektor...\n";
    vektor.pop_back();
    cout << "isi vector setelah pengurangan elemen: ";
    for(int i:vektor){
        cout << i << " ";
    }
    cout << endl << endl;
    
}

int main(){
    arr();
    cout << "---------------------------------------------------\n\n";
    vektor();
}