#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

// --- FUNGSI HELPER UNTUK FILE HANDLING (Tidak Perlu Diubah) ---

// Fungsi untuk membaca data dari file ke vector.
vector<int> readDataFromFile(const string& fileName) {
    vector<int> data;
    ifstream inFile(fileName);
    int number;

    if (!inFile.is_open()) {
        cerr << "Error: Gagal membuka file " << fileName << ". Pastikan file tersebut ada." << endl;
        return data;
    }
    while (inFile >> number) {
        data.push_back(number);
    }
    inFile.close();
    return data;
}

// Fungsi untuk menulis data vector ke sebuah file.
void writeDataToFile(const string& fileName, const vector<int>& data) {
    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        cerr << "Error: Gagal membuat file output " << fileName << endl;
        return;
    }
    for (int number : data) {
        outFile << number << endl;
    }
    outFile.close();
}


// --- IMPLEMENTASI MERGE SORT ---
void merge(vector<int>& arr, int left, int mid, int right) {
    // TODO (Praktikan): Implementasikan logika merge di sini.
    // 1. Tentukan ukuran dan buat vector sementara L (dari left ke mid) dan R (dari mid+1 ke right).
    // 2. Salin data dari arr ke vector sementara L dan R.
    // 3. Lakukan proses penggabungan (merge) dari L dan R kembali ke arr.
    // 4. Salin sisa elemen dari L atau R jika ada.

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    // TODO (Praktikan): Implementasikan logika merge sort di sini.
    // 1. Base case: jika left >= right, return (array dengan 0 atau 1 elemen sudah terurut)
    // 2. Tentukan titik tengah (mid)
    // 3. Panggil mergeSort secara rekursif untuk paruh kiri
    // 4. Panggil mergeSort secara rekursif untuk paruh kanan
    // 5. Panggil fungsi merge untuk menggabungkan kedua paruh

    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// --- IMPLEMENTASI QUICK SORT (LOMUTO) ---
int partitionLomuto(vector<int>& arr, int low, int high) {
    // TODO (Praktikan): Implementasikan partisi Lomuto di sini.
    // 1. Pilih pivot (elemen terakhir)
    // 2. Inisialisasi index i (penanda "wall")
    // 3. Lakukan iterasi dari low hingga high-1 (dengan pointer j)
    //      - Jika arr[j] < pivot, geser wall (i++) dan lakukan swap antara arr[i] dan arr[j]
    // 4. Setelah loop, tukar pivot (arr[high]) dengan elemen di posisi i+1
    // 5. Return posisi pivot yang baru (i+1)

    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortLomuto(vector<int>& arr, int low, int high) {
    // TODO (Praktikan): Implementasikan quickSort menggunakan partisi Lomuto.
    // 1. Base case: jika low < high
    // 2. Panggil partisi Lomuto untuk mendapatkan pivot index (pi)
    // 3. Panggil quickSortLomuto secara rekursif untuk sub-array sebelum dan sesudah pivot

    if (low < high) {
        int pi = partitionLomuto(arr, low, high);
        quickSortLomuto(arr, low, pi - 1);
        quickSortLomuto(arr, pi + 1, high);
    }
}

// --- IMPLEMENTASI QUICK SORT (HOARE) ---
int partitionHoare(vector<int>& arr, int low, int high) {
    // TODO (Praktikan): Implementasikan partisi Hoare di sini.
    // 1. Pilih pivot (elemen pertama)
    // 2. Inisialisasi pointer i (dari kiri) dan j (dari kanan)
    // 3. Buat sebuah loop tak terbatas (while true):
    //      - Geser i ke kanan hingga menemukan elemen >= pivot
    //      - Geser j ke kiri hingga menemukan elemen <= pivot
    //      - Jika i >= j, keluar dari loop dan Return j
    //      - Jika tidak, tukar arr[i] dengan arr[j]

    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }

        swap(arr[i], arr[j]);
    }
}

void quickSortHoare(vector<int>& arr, int low, int high) {
    // TODO (Praktikan): Implementasikan quickSort menggunakan partisi Hoare.
    // 1. Base case: jika low < high
    // 2. Panggil partisi Hoare untuk mendapatkan split point (pi)
    // 3. Panggil quickSortHoare secara rekursif. Perhatikan batasnya:
    //      - Panggilan pertama dari low hingga pi
    //      - Panggilan kedua dari pi+1 hingga high

    if (low < high) {
        int pi = partitionHoare(arr, low, high);
        quickSortHoare(arr, low, pi);
        quickSortHoare(arr, pi + 1, high);
    }
}

// MAIN FILE JANGAN DIUBAH, PELAJARI SAJA PARAMETER YANG DIKIRIMKAN

int main() {
    const string RANDOM_FILE = "random_data.txt";
    const string SORTED_FILE = "sorted_data.txt";
    const string TIME_OUTPUT_FILE = "hasil_waktu_sorting.txt";

    ofstream timeOutputFile(TIME_OUTPUT_FILE);

    // ================================================================
    // Skenario 1: Average Case (Data Acak dari File)
    // ================================================================
    timeOutputFile << "========================================" << endl;
    timeOutputFile << "SKENARIO 1: AVERAGE CASE (DATA ACAK)" << endl;
    timeOutputFile << "========================================" << endl;
    cout << "Membaca data acak dari " << RANDOM_FILE << "..." << endl;

    vector<int> randomData = readDataFromFile(RANDOM_FILE);
    if (!randomData.empty()) {
        vector<int> dataForMergeSort_rand = randomData;
        vector<int> dataForLomuto_rand = randomData;
        vector<int> dataForHoare_rand = randomData;

        //===========================================================
        // --- Proses & Ukur Waktu Merge Sort (Random) ---
        //===========================================================
        auto start_ms_rand = high_resolution_clock::now();
        mergeSort(dataForMergeSort_rand, 0, dataForMergeSort_rand.size() - 1);
        auto end_ms_rand = high_resolution_clock::now();

        duration<double, milli> elapsed_ms_rand = end_ms_rand - start_ms_rand;
        timeOutputFile << "Merge Sort (Random): " << elapsed_ms_rand.count() << " ms" << endl;
        writeDataToFile("sorted_random_mergesort.txt", dataForMergeSort_rand);

        //===========================================================
        // --- Proses & Ukur Waktu Quick Sort Lomuto (Random) ---
        //===========================================================
        auto start_qs_lomuto_rand = high_resolution_clock::now();
        quickSortLomuto(dataForLomuto_rand, 0, dataForLomuto_rand.size() - 1);
        auto end_qs_lomuto_rand = high_resolution_clock::now();

        duration<double, milli> elapsed_qs_lomuto_rand = end_qs_lomuto_rand - start_qs_lomuto_rand;
        timeOutputFile << "Quick Sort Lomuto (Random): " << elapsed_qs_lomuto_rand.count() << " ms" << endl;
        writeDataToFile("sorted_random_lomuto.txt", dataForLomuto_rand);

        //===========================================================
        // --- Proses & Ukur Waktu Quick Sort Hoare (Random) ---
        //===========================================================
        auto start_qs_hoare_rand = high_resolution_clock::now();
        quickSortHoare(dataForHoare_rand, 0, dataForHoare_rand.size() - 1);
        auto end_qs_hoare_rand = high_resolution_clock::now();

        duration<double, milli> elapsed_qs_hoare_rand = end_qs_hoare_rand - start_qs_hoare_rand;
        timeOutputFile << "Quick Sort Hoare (Random): " << elapsed_qs_hoare_rand.count() << " ms" << endl;
        writeDataToFile("sorted_random_hoare.txt", dataForHoare_rand);
    }
    timeOutputFile << endl;

    // ================================================================
    // Skenario 2: Worst Case (Data Terurut dari File)
    // ================================================================
    timeOutputFile << "========================================" << endl;
    timeOutputFile << "SKENARIO 2: WORST CASE (DATA TERURUT)" << endl;
    timeOutputFile << "========================================" << endl;
    cout << "Membaca data terurut dari " << SORTED_FILE << "..." << endl;

    vector<int> sortedData = readDataFromFile(SORTED_FILE);
    if (!sortedData.empty()) {
        vector<int> dataForMergeSort_sorted = sortedData;
        vector<int> dataForLomuto_sorted = sortedData;
        vector<int> dataForHoare_sorted = sortedData;

        //===========================================================
        // --- Proses & Ukur Waktu Merge Sort (Sorted) ---
        //===========================================================
        auto start_ms_sorted = high_resolution_clock::now();
        mergeSort(dataForMergeSort_sorted, 0, dataForMergeSort_sorted.size() - 1);
        auto end_ms_sorted = high_resolution_clock::now();

        duration<double, milli> elapsed_ms_sorted = end_ms_sorted - start_ms_sorted;
        timeOutputFile << "Merge Sort (Sorted): " << elapsed_ms_sorted.count() << " ms" << endl;
        writeDataToFile("sorted_terurut_mergesort.txt", dataForMergeSort_sorted);

        //===========================================================
        // --- Proses & Ukur Waktu Quick Sort Lomuto (Sorted) ---
        //===========================================================
        auto start_qs_lomuto_sorted = high_resolution_clock::now();
        quickSortLomuto(dataForLomuto_sorted, 0, dataForLomuto_sorted.size() - 1);
        auto end_qs_lomuto_sorted = high_resolution_clock::now();

        duration<double, milli> elapsed_qs_lomuto_sorted = end_qs_lomuto_sorted - start_qs_lomuto_sorted;
        timeOutputFile << "Quick Sort Lomuto (Sorted): " << elapsed_qs_lomuto_sorted.count() << " ms" << endl;
        writeDataToFile("sorted_terurut_lomuto.txt", dataForLomuto_sorted);

        //===========================================================
        // --- Proses & Ukur Waktu Quick Sort Hoare (Sorted) ---
        //===========================================================
        auto start_qs_hoare_sorted = high_resolution_clock::now();
        quickSortHoare(dataForHoare_sorted, 0, dataForHoare_sorted.size() - 1);
        auto end_qs_hoare_sorted = high_resolution_clock::now();

        duration<double, milli> elapsed_qs_hoare_sorted = end_qs_hoare_sorted - start_qs_hoare_sorted;
        timeOutputFile << "Quick Sort Hoare (Sorted): " << elapsed_qs_hoare_sorted.count() << " ms" << endl;
        writeDataToFile("sorted_terurut_hoare.txt", dataForHoare_sorted);
    }

    timeOutputFile.close();
    cout << "Pengukuran selesai. Hasil waktu disimpan di " << TIME_OUTPUT_FILE << endl;
    cout << "Hasil array yang terurut disimpan di file .txt terpisah." << endl;

    return 0;
}
