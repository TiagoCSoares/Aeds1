#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

void printResults(const string& method, const string& vectorType, double time_spent, long long int comparisonCount, long long int swapCount) {
    printf("\nMetodo de ordenacao: %s\n", method.c_str());
    printf("Tipo de vetor: %s\n", vectorType.c_str());
    printf("Tempo gasto: %.6f segundos\n", time_spent);
    printf("Numero de comparacoes: %lld\n", comparisonCount);
    printf("Numero de trocas: %lld\n\n", swapCount);
}

void bubblesort(long long int v[], long long int n, const string& vectorType){
  double time_spent = 0.0;
  int i, j;
  long long int comparisonCount = 0;
  long long int swapCount = 0;
  bool swapped;
  clock_t begin = clock();
  for(i = 0; i < n-1; i++){
    swapped = false;
    for(j = 0; j < n-i-1; j++){
      comparisonCount++;
      if(v[j] > v[j+1]){
        swapCount++;
        swap(v[j], v[j+1]);
        swapped = true;
      }
    }
    if(!swapped) {
        break;
    }
  }

  clock_t end = clock();
  time_spent += (double)(end - begin)/ CLOCKS_PER_SEC;

  printResults("Bubble Sort", vectorType, time_spent, comparisonCount, swapCount);
}

void insertionsort(long long int v[],long long int n, const string& vectorType){
  double time_spent = 0.0;
  int i, j, posicao;
  long long int comparisonCount = 0;
  long long int swapCount = 0;
  clock_t begin = clock();

  for (i = 1; i < n; i++) {
    posicao = v[i];
    j = i - 1;
    while (j >= 0 && v[j] > posicao){
      swapCount++;
      comparisonCount++;
      v[j+1] = v[j];
      j = j-1;
    }
    comparisonCount++;  
    v[j+1] = posicao;
  }

  clock_t end = clock();
  time_spent += (double)(end - begin)/ CLOCKS_PER_SEC;
 
  printResults("Insertion Sort", vectorType, time_spent, comparisonCount, swapCount);
}

void selectionsort(long long int v[],long long int n, const string& vectorType){
  double time_spent = 0.0;   
  int i, j, menor, aux, valor;
  valor = n;
  long long int comparisonCount = 0;
  long long int swapCount = 0;
  clock_t begin = clock();
  
  for (i = 0; i < n-1; i ++) {
    menor = i;
    for ( j= i+1; j < n; j++) {
      comparisonCount++;
      if (v[j] < v[menor]){
        menor = j;
      }
    }
    if (menor != i){
        swapCount++;
        aux = v[i];
        v[i] = v[menor];
        v[menor] = aux;
    }
  }

  clock_t end = clock();
  time_spent += (double)(end - begin)/ CLOCKS_PER_SEC;

  printResults("Selection Sort", vectorType, time_spent, comparisonCount, swapCount);
}

long long int* gera_aleatorio (long long int n) {
  unsigned seed = time(0);
  long long int i;
  long long int* vetor = new long long int[n];

  srand(seed);
  for (i=0; i<n; i++){
    vetor[i] = rand();
  }
  
  return vetor;
}

long long int* gera_ordenado (long long int n) {
  long long int* vetor = new long long int[n];
  int i;
  for(i = 0; i < n; i++){
    vetor[i] = i;
  }
  return vetor;
}

long long int* gera_decrescente (long long int n) {
  long long int* vetor = new long long int[n];
  int i, j;
  for(i = (n-1), j = 0; i >= 0; i--, j++){
    vetor[j] = i;
  }
  return vetor;
}

void saveToFile(long long int v[], long long int n, const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Não foi possível abrir o arquivo para escrita.\n";
        exit(1);
    }
    file << n << "\n";
    for (long long int i = 0; i < n; i++) {
        file << v[i];
        if (i < n - 1) { 
            file << " ";
        }
    }
    file << "\n";
    file.close();
}

long long int* loadFromFile(const string &filename, long long int &n) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Não foi possível abrir o arquivo.\n";
        exit(1);
    }

    string line;

    getline(file, line);
    istringstream iss(line);
    iss >> n;

    long long int* v = new long long int[n];
    getline(file, line);
    istringstream iss2(line);
    for (long long int i = 0; i < n; i++) {
        iss2 >> v[i];
    }

    file.close();
    return v;
}


int main(int argc, char**argv){
  long long int n;
  int i;

  cout << "Escolha o tamanho do vetor:\n";
  cout << "1. 100\n";
  cout << "2. 200\n";
  cout << "3. 300\n";
  cout << "4. 10000\n";
  cout << "5. 100000\n";
  int choice;
  cin >> choice;

  switch (choice) {
    case 1: n = 100; break;
    case 2: n = 200; break;
    case 3: n = 300; break;
    case 4: n = 10000; break;
    case 5: n = 100000; break;
    default: 
      cerr << "Opção inválida. Saindo...\n";
      return 1;
  }

  long long int* vetor_aleatorio = gera_aleatorio(n);
  saveToFile(vetor_aleatorio, n, "vetor_aleatorio.txt");
  vetor_aleatorio = loadFromFile("vetor_aleatorio.txt", n);

  long long int* vetor_ordenado = gera_ordenado(n);
  saveToFile(vetor_ordenado, n, "vetor_ordenado.txt");
  vetor_ordenado = loadFromFile("vetor_ordenado.txt", n);

  long long int* vetor_decrescente = gera_decrescente(n);
  saveToFile(vetor_decrescente, n, "vetor_decrescente.txt");
  vetor_decrescente = loadFromFile("vetor_decrescente.txt", n);

  bubblesort(vetor_aleatorio, n, "Aleatorio");
  bubblesort(vetor_ordenado, n, "Ordenado");
  bubblesort(vetor_decrescente, n, "Decrescente");

  delete[] vetor_aleatorio;
  delete[] vetor_ordenado;
  delete[] vetor_decrescente;

  vetor_aleatorio = gera_aleatorio(n);
  saveToFile(vetor_aleatorio, n, "vetor_aleatorio.txt");
  vetor_aleatorio = loadFromFile("vetor_aleatorio.txt", n);

  vetor_ordenado = gera_ordenado(n);
  saveToFile(vetor_ordenado, n, "vetor_ordenado.txt");
  vetor_ordenado = loadFromFile("vetor_ordenado.txt", n);

  vetor_decrescente = gera_decrescente(n);
  saveToFile(vetor_decrescente, n, "vetor_decrescente.txt");
  vetor_decrescente = loadFromFile("vetor_decrescente.txt", n);


  insertionsort(vetor_aleatorio, n, "Aleatorio");
  insertionsort(vetor_ordenado, n, "Ordenado");
  insertionsort(vetor_decrescente, n, "Decrescente");

  delete[] vetor_ordenado;
  delete[] vetor_aleatorio;
  delete[] vetor_decrescente;

  vetor_aleatorio = gera_aleatorio(n);
  saveToFile(vetor_aleatorio, n, "vetor_aleatorio.txt");
  vetor_aleatorio = loadFromFile("vetor_aleatorio.txt", n);

  vetor_ordenado = gera_ordenado(n);
  saveToFile(vetor_ordenado, n, "vetor_ordenado.txt");
  vetor_ordenado = loadFromFile("vetor_ordenado.txt", n);

  vetor_decrescente = gera_decrescente(n);
  saveToFile(vetor_decrescente, n, "vetor_decrescente.txt");
  vetor_decrescente = loadFromFile("vetor_decrescente.txt", n);

  selectionsort(vetor_aleatorio, n, "Aleatorio");
  selectionsort(vetor_decrescente, n, "Decrescente");
  selectionsort(vetor_ordenado, n, "Ordenado");
  delete[] vetor_ordenado;
  delete[] vetor_aleatorio;
  delete[] vetor_decrescente;

  return 0;
}
