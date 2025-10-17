#include <bits/stdc++.h>

using namespace std;

void bubble(vector<int> & vektor){
    for(int i = 0; i < (vektor.size() - 1); i++){
        bool swapped = 0;
        for(int j = 0; j < (vektor.size() - i - 1); j++){
            if(vektor[j] > vektor[j+1]){
                int t = vektor[j];
                vektor[j] = vektor[j+1];
                vektor[j+1] = t;
                swapped = 1;
            }
        }
        if (swapped == 0){break;}
    }
}

void insertion(vector<int> & vektor){
    for(int i = 1; i < vektor.size(); i++){
        int key = vektor[i];
        int j = i - 1;

        while(j >= 0 && vektor[j] > key){
            vektor[j+1] = vektor[j];
            j--;
        }
        vektor[j+1] = key;
    }
}

void selection(vector<int> & vektor){
    for(int i = 0; i < (vektor.size() - 1); i++ ){
        int index = i;

        for(int j = i + 1; j < vektor.size(); j++){
            if(vektor[j] < vektor[index]){
                index = j;
            }
        }
        int t = vektor[index];
        vektor[index] = vektor[i];
        vektor[i] = t;
    }
}

void output(vector<int> & vektor){
    for(int i = 0; i < vektor.size(); i++){
        cout << vektor[i] << " ";
    }
}

int main(){
    vector<int> vektor = {4, 7, 7, 3, 9, 1, 5};
    bubble(vektor);
}