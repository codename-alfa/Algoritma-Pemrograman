#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> angka = {6, 9, 4, 2, 0};

    cout << "Daftar angka: ";
    for (int n : angka) {
        cout << n << " ";
    }
    cout << endl;

    sort(angka.begin(), angka.end());

    cout << "Setelah diurutkan: ";
    for (int n : angka) {
        cout << n << " ";
    }
    cout << endl;

    return 0;
}