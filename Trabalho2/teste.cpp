#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int main() {
    unsigned seed = time(0);
    int n,i;
    int vetor[15];

    for(i = 0; i < 15; i++){
        vetor[i] = i;
    }
    srand(seed);
    for (i= 14; i > 0; i--){
        int j = rand() % (i+1);
        swap(vetor[i], vetor[j]);
    }

    for(i=0; i<15;i++){
        cout << vetor[i] << endl;
    }
    return 0;
}