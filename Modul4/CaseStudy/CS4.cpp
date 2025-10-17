#include <iostream>
#include <vector>
#include <fstream>  // Pustaka untuk file input/output
#include <string>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

// --- FUNGSI HELPER UNTUK FILE HANDLING (Telah Disesuaikan untuk String, Tidak Perlu Diubah) ---

// Fungsi untuk membaca data string dari file ke vector.
std::vector<std::string> readNamesFromFile(const std::string& fileName) {
    std::vector<std::string> data;
    std::ifstream inFile(fileName);
    std::string name;

    if (!inFile.is_open()) {
        std::cerr << "Error: Gagal membuka file " << fileName << ". Pastikan file tersebut ada." << std::endl;
        return data;
    }
    // Menggunakan std::getline untuk membaca seluruh baris (termasuk spasi dalam nama)
    while (std::getline(inFile, name)) {
        if (!name.empty()) { // Hanya tambahkan jika baris tidak kosong
            data.push_back(name);
        }
    }
    inFile.close();
    return data;
}

// Fungsi untuk menulis data vector string ke sebuah file.
void writeNamesToFile(const std::string& fileName, const std::vector<std::string>& data) {
    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        std::cerr << "Error: Gagal membuat file output " << fileName << std::endl;
        return;
    }
    for (const std::string& name : data) {
        outFile << name << std::endl;
    }
    outFile.close();
}


// --- IMPLEMENTASI MERGE SORT UNTUK STRING ---
// Function merge untuk ascending
void mergeAscending(std::vector<std::string>& arr, int left, int mid, int right) {
    // TODO (Praktikan): Implementasikan logika merge ASCENDING di sini untuk vector of string.
    // Logikanya sama persis dengan integer, hanya tipe data vector sementaranya adalah string.
    // Gunakan <= untuk perbandingan ascending

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<string> L(n1);
    vector<string> R(n2);

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

// Function merge untuk descending
void mergeDescending(std::vector<std::string>& arr, int left, int mid, int right) {
    // TODO (Praktikan): Implementasikan logika merge DESCENDING di sini untuk vector of string.
    // Sama seperti mergeAscending, tetapi gunakan >= untuk perbandingan descending

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<string> L(n1);
    vector<string> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
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

// Function mergeSort yang bisa ascending atau descending
void mergeSort(std::vector<std::string>& arr, int left, int right, bool ascending = true) {
    // TODO (Praktikan): Implementasikan logika merge sort rekursif di sini.
    // Gunakan parameter 'ascending' untuk menentukan memanggil mergeAscending atau mergeDescending
    // if (ascending) panggil mergeAscending, else panggil mergeDescending
    if (ascending == true){
        if (left >= right) {
            return;
        }
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, ascending);
        mergeSort(arr, mid + 1, right, ascending);
        mergeAscending(arr, left, mid, right);
    } else {
        if (left >= right) {
            return;
        }
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, ascending);
        mergeSort(arr, mid + 1, right, ascending);
        mergeDescending(arr, left, mid, right);
    }
}

// --- IMPLEMENTASI QUICK SORT (LOMUTO) UNTUK STRING ---
// Function partition untuk ascending
int partitionLomutoAscending(std::vector<std::string>& arr, int low, int high) {
    // TODO (Praktikan): Implementasikan partisi Lomuto ASCENDING di sini untuk vector of string.
    // Gunakan perbandingan string standar <= untuk ascending (arr[j] <= pivot)

    string pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Function partition untuk descending
int partitionLomutoDescending(std::vector<std::string>& arr, int low, int high) {
    // TODO (Praktikan): Implementasikan partisi Lomuto DESCENDING di sini untuk vector of string.
    // Sama seperti ascending, tetapi gunakan >= untuk descending (arr[j] >= pivot)

    string pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] >= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Function quickSortLomuto yang bisa ascending atau descending
void quickSortLomuto(std::vector<std::string>& arr, int low, int high, bool ascending = true) {
    // TODO (Praktikan): Implementasikan quickSort menggunakan partisi Lomuto.
    // Gunakan parameter 'ascending' untuk menentukan memanggil partitionLomutoAscending atau partitionLomutoDescending
    // if (ascending) panggil partitionLomutoAscending, else panggil partitionLomutoDescending

    if (ascending == true) {
        if (low < high) {
            int pi = partitionLomutoAscending(arr, low, high);
            quickSortLomuto(arr, low, pi - 1, ascending);
            quickSortLomuto(arr, pi + 1, high, ascending);
        }
    } else {
        if (low < high) {
            int pi = partitionLomutoDescending(arr, low, high);
            quickSortLomuto(arr, low, pi - 1, ascending);
            quickSortLomuto(arr, pi + 1, high, ascending);
        }
    }
}

// --- IMPLEMENTASI QUICK SORT (HOARE) UNTUK STRING ---
// Function partition untuk ascending
int partitionHoareAscending(std::vector<std::string>& arr, int low, int high) {
    // TODO (Praktikan): Implementasikan partisi Hoare ASCENDING di sini untuk vector of string.
    // Gunakan perbandingan string standar < dan > untuk ascending
    // while (arr[i] < pivot) dan while (arr[j] > pivot)

    string pivot = arr[low];
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

// Function partition untuk descending
int partitionHoareDescending(std::vector<std::string>& arr, int low, int high) {
    // TODO (Praktikan): Implementasikan partisi Hoare DESCENDING di sini untuk vector of string.
    // Balik perbandingan: while (arr[i] > pivot) dan while (arr[j] < pivot)
    
    string pivot = arr[low];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] > pivot);

        do {
            j--;
        } while (arr[j] < pivot);

        if (i >= j) {
            return j;
        }

        swap(arr[i], arr[j]);
    }
}

// Function quickSortHoare yang bisa ascending atau descending
void quickSortHoare(std::vector<std::string>& arr, int low, int high, bool ascending = true) {
    // TODO (Praktikan): Implementasikan quickSort menggunakan partisi Hoare.
    // Gunakan parameter 'ascending' untuk menentukan memanggil partitionHoareAscending atau partitionHoareDescending
    // if (ascending) panggil partitionHoareAscending, else panggil partitionHoareDescending
    // Perhatikan batas rekursifnya sesuai dengan return value dari partisi Hoare

    if (ascending == true) {
        if (low < high) {
            int pi = partitionHoareAscending(arr, low, high);
            quickSortHoare(arr, low, pi, ascending);
            quickSortHoare(arr, pi + 1, high, ascending);
        }
    } else {
        if (low < high) {
            int pi = partitionHoareDescending(arr, low, high);
            quickSortHoare(arr, low, pi, ascending);
            quickSortHoare(arr, pi + 1, high, ascending);
        }
    }
}

// MAIN FILE JANGAN DIUBAH, PELAJARI SAJA PARAMETER YANG DIKIRIMKAN

int main() {
    // Definisi nama file
    const std::string RANDOM_FILE = "daftar_acak.txt";
    const std::string SORTED_FILE = "daftar_terurut.txt";
    const std::string TIME_OUTPUT_FILE = "hasil_waktu_sorting_nama.txt";

    std::ofstream timeOutputFile(TIME_OUTPUT_FILE);

    // ================================================================
    // Skenario 1: Average Case (Data Nama Acak dari File) - ASCENDING
    // ================================================================
    timeOutputFile << "========================================" << std::endl;
    timeOutputFile << "SKENARIO 1: AVERAGE CASE (NAMA ACAK) - ASCENDING" << std::endl;
    timeOutputFile << "========================================" << std::endl;
    std::cout << "Membaca daftar nama acak dari " << RANDOM_FILE << " untuk sorting ascending..." << std::endl;

    std::vector<std::string> randomNames = readNamesFromFile(RANDOM_FILE);
    if (!randomNames.empty()) {
        std::vector<std::string> namesForMergeSort_rand = randomNames;
        std::vector<std::string> namesForLomuto_rand = randomNames;
        std::vector<std::string> namesForHoare_rand = randomNames;

        // --- Proses & Ukur Waktu Merge Sort (Random) ---
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(namesForMergeSort_rand, 0, namesForMergeSort_rand.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        timeOutputFile << "Merge Sort Ascending (Random): " << elapsed.count() << " ms" << std::endl;
        writeNamesToFile("sorted_acak_mergesort_asc.txt", namesForMergeSort_rand);

        // --- Proses & Ukur Waktu Quick Sort Lomuto (Random) ---
        start = std::chrono::high_resolution_clock::now();
        quickSortLomuto(namesForLomuto_rand, 0, namesForLomuto_rand.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        timeOutputFile << "Quick Sort Lomuto Ascending (Random): " << elapsed.count() << " ms" << std::endl;
        writeNamesToFile("sorted_acak_lomuto_asc.txt", namesForLomuto_rand);
        
        // --- Proses & Ukur Waktu Quick Sort Hoare (Random) ---
        start = std::chrono::high_resolution_clock::now();
        quickSortHoare(namesForHoare_rand, 0, namesForHoare_rand.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        timeOutputFile << "Quick Sort Hoare Ascending (Random): " << elapsed.count() << " ms" << std::endl;
        writeNamesToFile("sorted_acak_hoare_asc.txt", namesForHoare_rand);
    }
    timeOutputFile << std::endl;

    // ================================================================
    // Skenario 1b: Average Case (Data Nama Acak dari File) - DESCENDING
    // ================================================================
    timeOutputFile << "========================================" << std::endl;
    timeOutputFile << "SKENARIO 1b: AVERAGE CASE (NAMA ACAK) - DESCENDING" << std::endl;
    timeOutputFile << "========================================" << std::endl;
    std::cout << "Sorting daftar nama acak untuk descending..." << std::endl;

    if (!randomNames.empty()) {
        std::vector<std::string> namesForMergeSortDesc_rand = randomNames;
        std::vector<std::string> namesForLomutoDesc_rand = randomNames;
        std::vector<std::string> namesForHoareDesc_rand = randomNames;

        // --- Proses & Ukur Waktu Merge Sort Descending (Random) ---
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(namesForMergeSortDesc_rand, 0, namesForMergeSortDesc_rand.size() - 1, false);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        timeOutputFile << "Merge Sort Descending (Random): " << elapsed.count() << " ms" << std::endl;
        writeNamesToFile("sorted_acak_mergesort_desc.txt", namesForMergeSortDesc_rand);

        // --- Proses & Ukur Waktu Quick Sort Lomuto Descending (Random) ---
        start = std::chrono::high_resolution_clock::now();
        quickSortLomuto(namesForLomutoDesc_rand, 0, namesForLomutoDesc_rand.size() - 1, false);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        timeOutputFile << "Quick Sort Lomuto Descending (Random): " << elapsed.count() << " ms" << std::endl;
        writeNamesToFile("sorted_acak_lomuto_desc.txt", namesForLomutoDesc_rand);
        
        // --- Proses & Ukur Waktu Quick Sort Hoare Descending (Random) ---
        start = std::chrono::high_resolution_clock::now();
        quickSortHoare(namesForHoareDesc_rand, 0, namesForHoareDesc_rand.size() - 1, false);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        timeOutputFile << "Quick Sort Hoare Descending (Random): " << elapsed.count() << " ms" << std::endl;
        writeNamesToFile("sorted_acak_hoare_desc.txt", namesForHoareDesc_rand);
    }
    timeOutputFile << std::endl;

    // ================================================================
    // Skenario 2: Best/Worst Case (Data Nama Terurut dari File) - ASCENDING
    // ================================================================
    timeOutputFile << "========================================" << std::endl;
    timeOutputFile << "SKENARIO 2: BEST/WORST CASE (NAMA TERURUT) - ASCENDING" << std::endl;
    timeOutputFile << "========================================" << std::endl;
    std::cout << "Membaca daftar nama terurut dari " << SORTED_FILE << " untuk sorting ascending..." << std::endl;

    std::vector<std::string> sortedNames = readNamesFromFile(SORTED_FILE);
    if (!sortedNames.empty()) {
        std::vector<std::string> namesForMergeSort_sorted = sortedNames;
        std::vector<std::string> namesForLomuto_sorted = sortedNames;
        std::vector<std::string> namesForHoare_sorted = sortedNames;

        // --- Proses & Ukur Waktu Merge Sort (Sorted) ---
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(namesForMergeSort_sorted, 0, namesForMergeSort_sorted.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        timeOutputFile << "Merge Sort Ascending (Sorted): " << elapsed.count() << " ms" << std::endl;
        writeNamesToFile("sorted_terurut_mergesort_asc.txt", namesForMergeSort_sorted);

        // --- Proses & Ukur Waktu Quick Sort Lomuto (Sorted) ---
        start = std::chrono::high_resolution_clock::now();
        quickSortLomuto(namesForLomuto_sorted, 0, namesForLomuto_sorted.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        timeOutputFile << "Quick Sort Lomuto Ascending (Sorted): " << elapsed.count() << " ms" << std::endl;
        writeNamesToFile("sorted_terurut_lomuto_asc.txt", namesForLomuto_sorted);

        // --- Proses & Ukur Waktu Quick Sort Hoare (Sorted) ---
        start = std::chrono::high_resolution_clock::now();
        quickSortHoare(namesForHoare_sorted, 0, namesForHoare_sorted.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        timeOutputFile << "Quick Sort Hoare Ascending (Sorted): " << elapsed.count() << " ms" << std::endl;
        writeNamesToFile("sorted_terurut_hoare_asc.txt", namesForHoare_sorted);
    }
    timeOutputFile << std::endl;

    // ================================================================
    // Skenario 2b: Best/Worst Case (Data Nama Terurut dari File) - DESCENDING
    // ================================================================
    timeOutputFile << "========================================" << std::endl;
    timeOutputFile << "SKENARIO 2b: BEST/WORST CASE (NAMA TERURUT) - DESCENDING" << std::endl;
    timeOutputFile << "========================================" << std::endl;
    std::cout << "Sorting daftar nama terurut untuk descending..." << std::endl;

    if (!sortedNames.empty()) {
        std::vector<std::string> namesForMergeSortDesc_sorted = sortedNames;
        std::vector<std::string> namesForLomutoDesc_sorted = sortedNames;
        std::vector<std::string> namesForHoareDesc_sorted = sortedNames;

        // --- Proses & Ukur Waktu Merge Sort Descending (Sorted) ---
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(namesForMergeSortDesc_sorted, 0, namesForMergeSortDesc_sorted.size() - 1, false);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        timeOutputFile << "Merge Sort Descending (Sorted): " << elapsed.count() << " ms" << std::endl;
        writeNamesToFile("sorted_terurut_mergesort_desc.txt", namesForMergeSortDesc_sorted);

        // --- Proses & Ukur Waktu Quick Sort Lomuto Descending (Sorted) ---
        start = std::chrono::high_resolution_clock::now();
        quickSortLomuto(namesForLomutoDesc_sorted, 0, namesForLomutoDesc_sorted.size() - 1, false);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        timeOutputFile << "Quick Sort Lomuto Descending (Sorted): " << elapsed.count() << " ms" << std::endl;
        writeNamesToFile("sorted_terurut_lomuto_desc.txt", namesForLomutoDesc_sorted);

        // --- Proses & Ukur Waktu Quick Sort Hoare Descending (Sorted) ---
        start = std::chrono::high_resolution_clock::now();
        quickSortHoare(namesForHoareDesc_sorted, 0, namesForHoareDesc_sorted.size() - 1, false);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        timeOutputFile << "Quick Sort Hoare Descending (Sorted): " << elapsed.count() << " ms" << std::endl;
        writeNamesToFile("sorted_terurut_hoare_desc.txt", namesForHoareDesc_sorted);
    }

    timeOutputFile.close();
    std::cout << "Pengukuran selesai. Hasil waktu disimpan di " << TIME_OUTPUT_FILE << std::endl;
    std::cout << "Hasil daftar nama yang terurut disimpan di file .txt terpisah:" << std::endl;
    std::cout << "- File ascending: *_asc.txt" << std::endl;
    std::cout << "- File descending: *_desc.txt" << std::endl;

    return 0;
}
