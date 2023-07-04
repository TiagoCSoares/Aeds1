#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>


using namespace std;

void bubblesort(int v[], int n){
  double time_spent = 0.0;
  int i, j;
  long long int count = 0;
  bool swapped;
  clock_t begin = clock();
  //for(i = 0; i < n; i++) {
  //    cout << v[i] << " " ;
  //}

  for(i = 0; i < n-1; i++){
    swapped = false;
    for(j = 0; j < n-i-1; j++){
      if(v[j] > v[j+1]){
        count++;
        v[j] = v[j] + v[j+1];
        v[j+1] = v[j] - v[j+1];
        v[j] = v[j] - v[j+1];
        
        swapped = true;
      }
    }
    if(!swapped) {
        break;
    }
  }

  //for(i = 0; i < n; i++) {
  //    cout << v[i] << " " ;
  //}


clock_t end = clock();
time_spent += (double)(end - begin)/ CLOCKS_PER_SEC;

cout << "TEMPO" << endl;
cout <<  time_spent << endl;
cout<< count << endl;
cout << n << endl;
  
}

void insertionsort(int v[], int n){
  double time_spent = 0.0;
  int i, j, posicao;
  long long int count = 0;
  clock_t begin = clock();
  //for(i = 0; i < n; i++) {
  //    cout << v[i] << " " ;
  //}

  for (i = 1; i < n; i++) {
    posicao = v[i];
    j = i - 1;
    while (j >= 0 && v[j] > posicao){
      count++;  
      v[j+1] = v[j];
      j = j-1;
    }
    v[j+1] = posicao;
  }

  //for(i = 0; i < n; i++) {
  //    cout << v[i] << " " ;
  //}

clock_t end = clock();
time_spent += (double)(end - begin)/ CLOCKS_PER_SEC;

cout << "TEMPO" << endl;
cout << time_spent << endl;
cout << count << endl;
cout << n << endl;
}




void selectionsort(int v[], int n){
  double time_spent = 0.0;   
  int i, j, menor, aux, valor;
  valor = n;
  long long int count = 0;
  clock_t begin = clock();

  //for(i = 0; i < valor; i++) {
  //    cout << v[i] << " " ;
  //}


  for (i = 0; i < n-1; i ++) {
    menor = i;
    for ( j= i+1; j < n; j++) {
      if (v[j] < v[menor]){
        menor = j;
      }
      if (menor != i){
        count++;
        aux = v[i];
        v[i] = v[menor];
        v[menor] = aux;
      }
    }
  }

//for(i = 0; i < valor; i++) {
//    cout << v[i] << " ";
//}

clock_t end = clock();
time_spent += (double)(end - begin)/ CLOCKS_PER_SEC;

cout << "tempo" << endl;
cout <<  time_spent << endl;
cout << count << endl;
cout << n << endl;

}


int* gera_aleatorio (int n) {
  unsigned seed = time(0);
  int i;
  int* vetor = new int[n];

  for(i = 0; i < n; i++){
      vetor[i] = i;
  }
  srand(seed);
  for (i= (n-1); i > 0; i--){
      int j = rand() % (i+1);
      swap(vetor[i], vetor[j]);
  }

  return vetor;
}  

int* gera_ordenado (int n) {
  int* vetor = new int[n];
  int i;
  for (i = 0; i < n;i++) {
    vetor[i] = i;
  }
  
  return vetor;
}

int* gera_decrescente (int n) {
  int* vetor = new int[n];
  int i;
  int aux = n;
  for(i = 0;i < aux;i++){
    vetor[i] = n-1;
    n--;
  }
  return vetor;
}

void imprimevetor(int v[], int n){
  for (int i = 0; i < n; i++)
    cout << "  " << v[i];
  cout << endl;
}

int main(int argc, char**argv){
  int n = 100;
  int i;
  cout << endl << "Vetor aleatório tamanho" << n << ":" << endl;

  int* vetor_aleatorio;
  int* vetor_ordenado;
  int* vetor_decrescente;


  for(n = 100000; n < 100001; n += 100) {
  //long long int *vetor_aux;
  //vetor_aux = (long long int *)malloc(n * sizeof(int));
  //for( i = 0; i < n; i++){
  //  vetor_aux[i] = vetor_aleatorio[i];
  //}
  

  //cout << endl << "[";
  //for(i=0; i<n; i++) {
  //  cout << vetor_aleatorio[i] << ",";
  //}
  //cout << "]" << endl;
//
//
  //cout << endl << "[";
  //for(i=0; i<n; i++) {
  //  cout << vetor_ordenado[i] << ",";
  //}
  //cout << "]"<< endl;
//
  //cout << endl << "[";
  //for(i=0; i<n; i++) {
  //  cout << vetor_decrescente[i] << ",";
  //}
  //cout << "]"<< endl;
//
//
  //cout << endl << " Métodos de Ordenação" << endl << endl;
//
  vetor_aleatorio = gera_aleatorio(n);
  vetor_ordenado = gera_ordenado(n);
  vetor_decrescente = gera_decrescente(n);
  cout << "Bubble Sort, vetor aleatorio: " << endl;

  //imprimevetor(vetor_aleatorio, n);
  bubblesort(vetor_aleatorio, n);
  //imprimevetor(vetor_aleatorio, n);
  cout << endl << endl;

  cout << "Bubble Sort, vetor ordeando: " << endl;
  //imprimevetor(vb1, 10);
  bubblesort(vetor_ordenado, n);
  //imprimevetor(vb1, 10);
//
  cout << endl << endl;

  cout << "Bubble Sort, vetor em ordem inversa: " << endl;
  //imprimevetor(vb2, 10);
  bubblesort(vetor_decrescente, n);
  //imprimevetor(vb2, 10);
  cout << endl << endl;
  delete[] vetor_aleatorio;
  delete[] vetor_ordenado;
  delete[] vetor_decrescente;



  //for( i = 0; i < n; i++){
  //  vetor_aleatorio[i] = vetor_aux[i];
  //}

  vetor_aleatorio = gera_aleatorio(n);
  vetor_ordenado = gera_ordenado(n);
  vetor_decrescente = gera_decrescente(n);

  cout << "Selection Sort, vetor aleatorio: " << endl;
  //imprimevetor(vetor_aleatorio, n);
  selectionsort(vetor_aleatorio, n);
  //imprimevetor(vetor_aleatorio, n);
  cout << endl << endl;

  cout << "Selection Sort, vetor ordenado: " << endl;
  //imprimevetor(vb1, 10);
  selectionsort(vetor_ordenado, n);
  //imprimevetor(vb1, 10);
//
  cout << endl << endl;

  cout << "Selection Sort, vetor em ordem inversa: " << endl;
  //imprimevetor(vb2, 10);
  selectionsort(vetor_decrescente, n);
  //imprimevetor(vb2, 10);
  cout << endl << endl;
  delete[] vetor_aleatorio;
  delete[] vetor_ordenado;
  delete[] vetor_decrescente;





  vetor_aleatorio = gera_aleatorio(n);
  vetor_ordenado = gera_ordenado(n);
  vetor_decrescente = gera_decrescente(n);
  cout << "insertion Sort, vetor aleatorio: " << endl;
  //imprimevetor(vetor_aleatorio, n);
  insertionsort(vetor_aleatorio, n);
  //imprimevetor(vetor_aleatorio, n);
  cout << endl << endl;

  cout << "insertion Sort, vetor ordenado: " << endl;
  //imprimevetor(vb1, 10);
  insertionsort(vetor_ordenado, n);
  //imprimevetor(vb1, 10);
//
  cout << endl << endl;

  cout << "insertion Sort, vetor em ordem inversa: " << endl;
  //imprimevetor(vb2, 10);
  insertionsort(vetor_decrescente, n);
  //imprimevetor(vb2, 10);
  cout << endl << endl;
  delete[] vetor_aleatorio;
  delete[] vetor_ordenado;
  delete[] vetor_decrescente;
  }
  return 0;
}