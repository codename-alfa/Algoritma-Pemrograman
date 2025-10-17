#include <iostream>
#include <vector>
#include <algorithm> // std::swap
#include <string>

using namespace std;

// Fungsi utilitas untuk mencetak vector
void printVector(const std::string& label, const std::vector<int>& vec);

/// TODO 1: Implementasikan fungsi siftdown.
// Fungsi ini harus memperbaiki properti Max-Heap dari sebuah subtree.
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

// TODO 2: Implementasikan fungsi makeheap.
// Fungsi ini mengubah seluruh array menjadi Max-Heap menggunakan pendekatan Bottom-Up.
void makeheap(std::vector<int>& H) {
    int n = static_cast<int>(H.size());
    for (int i = (n / 2) - 1; i >= 0; --i) {
        siftdown(H, i, n);
    }
}

// TODO 3: Implementasikan fungsi heapsort.
// Fungsi ini menggabungkan makeheap dan fase sorting untuk mengurutkan array secara in-place.
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
    std::vector<int> data = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    printVector("Data awal:", data);
    heapsort(data);
    printVector("Data terurut:", data);
    return 0;
}

// Implementasi printVector
void printVector(const std::string& label, const std::vector<int>& vec) {
    std::cout << label << "\t";
    for (int val : vec) { std::cout << val << " "; }
    std::cout << std::endl;
}
