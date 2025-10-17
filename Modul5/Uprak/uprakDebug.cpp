#include <iostream>
#include <vector>
#include <utility> // Untuk std::swap

using namespace std;

int partition(std::vector<int>& arr, int low, int high) { // mengubah 0 menjadi low
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high){
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1); // menambah - 1 setelah pi, dan memasukkan pemanggilan quickSort ke if statement
        quickSort(arr, pi + 1, high);
    }
    
}

int main() {
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    
    // Mencetak array awal secara langsung
    std::cout << "Array Awal: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Memanggil fungsi quick sort
    quickSort(arr, 0, arr.size() - 1);

    // Mencetak array hasil secara langsung
    std::cout << "Array Hasil: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
