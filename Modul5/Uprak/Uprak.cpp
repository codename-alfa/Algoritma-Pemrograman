#include <iostream>
#include <vector>

using namespace std;

void selection(vector<int> &data){ // algoritma selection sort
    int n = data.size();
	for(int i = 0; i < (n - 1); i++){
        int min_idx = i;

        for(int j = i + 1; j < n; j++){
            if(data[j] > data[min_idx]){
                min_idx = j;
            }
        }

        int temp = data[min_idx];
        data[min_idx] = data[i];
        data[i] = temp;
    }

    cout << "\nHasil sorting (selection): ";
}

void output(vector<int> data){ // fungsi printout
    for(int i = 0; i < data.size(); i++){
        cout << data[i] << " ";
    }
}


int main(){
    vector<int> data = {5, 1, 11, 8, 19};
    selection(data);
    output(data);
}