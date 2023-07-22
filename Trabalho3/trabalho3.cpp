/*
 * Algoritmo de Transformação de Imagem PGM
 *
 * Este projeto tem como objetivo manipular imagens em formato de matrizes
 * implementando funcionalidades que geram novas imagens a partir de imagens
 * lidas de arquivos-texto em formato PGM. O projeto possui um menu de opções
 * que permite ler a imagem de entrada em formato PGM e, para cada
 * funcionalidade implementada, possui outras opções em que, uma vez
 * selecionada, gera um arquivo-texto de mesmo formato PGM.
 *
 * Programa criado em 20 de julho de 2023.
 *
 * Disciplina: AEDS I
 * Professor: Paulo Bressan
 *
 * Alunos
 * Nome: Maria Eduarda Pires    R.A.: 2020.1.08.019
 * Nome: Tiago Costa            R.A.: 2020.1.08.017
 *
 * Universidade Federal de Alfenas
 */

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;
const int MAX_LINHAS = 1000;
const int MAX_COLUNAS = 1000;

typedef int tImagem[MAX_LINHAS][MAX_COLUNAS];

string erro; // variável global

void salvarImagem64x64(const string nomeArquivo, tImagem img_saida, int lin, int col) {
  ofstream arquivo(nomeArquivo);

  if (arquivo.is_open()) {
    // Escreve o cabeçalho do arquivo PGM (tamanho e tons de cinza)
    arquivo << "P2" << endl;
    arquivo << "64 64" << endl;
    arquivo << "255" << endl;

    // Calcula o fator de escala para reduzir a imagem para 64x64
    int fator_escala_linhas = lin / 64;
    int fator_escala_colunas = col / 64;

    // Escreve os dados da imagem 64x64
    for (int i = 0; i < 64; i++) {
      for (int j = 0; j < 64; j++) {
        // Obtém a média dos tons de cinza de cada bloco da imagem original
        int media_tons = 0;
        for (int k = 0; k < fator_escala_linhas; k++) {
          for (int l = 0; l < fator_escala_colunas; l++) {
            media_tons += img_saida[i * fator_escala_linhas + k]
                                   [j * fator_escala_colunas + l];
          }
        }
        media_tons /= fator_escala_linhas * fator_escala_colunas;

        // Escreve o valor médio do bloco na imagem ícone
        arquivo << media_tons << " ";
      }
      arquivo << endl;
    }

    arquivo.close();

  } else {
    cout << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
  }
}

/**
 * Leitura da imagem PGM de entrada.
 *
 * @param nome Nome do arquivo contendo a imagem PGM a ser carregada.
 * @param img Um array bidimensional que representará a imagem carregada.
 * @param lin Ponteiro para uma variável que armazenará o número de linhas da
 *imagem lida.
 * @param col Ponteiro para uma variável que armazenará o número de colunas da
 *imagem lida.
 * @param tons Ponteiro para uma variável que armazenará o número de tons de
 *cinza da imagem lida.
 *
 * @return 0 em caso de sucesso na leitura e carregamento da imagem.
 *         1 em caso de erro ao abrir o arquivo (Arquivo não encontrado).
 *         2 em caso de erro no formato do arquivo (Arquivo não tem formato P2).
 **/
int carregaPGM(string nome, tImagem img, int *col, int *lin, int *tons) {

  string tipo;

  // abrindo o arquivo que contém a imagem PGM a ser utilizada.
  ifstream arquivo(nome);
  if (!arquivo.is_open()) {
    erro = "Erro: Arquivo não encontrado.";
    return 1;
  }

  arquivo >> tipo;
  if (tipo != "P2") {
    erro = "Erro: Arquivo não tem formato P2.";
    return 2;
  }

  arquivo >> *col >> *lin >> *tons;
  for (int i = 0; i < *lin; i++) {
    for (int j = 0; j < *col; j++) {
      arquivo >> img[i][j];
    }
  }
  arquivo.close();
  return 0;
}

/**
 * Gera uma imagem no formato PGM e a salva em um arquivo de saída.
 *
 * @param nome O nome do arquivo onde a imagem PGM será salva.
 * @param img Um array bidimensional que representa a imagem a ser salva.
 * @param lin O número de linhas da imagem.
 * @param col O número de colunas da imagem.
 * @param tons O número de tons de cinza da imagem.
 *
 * @return 0 em caso de sucesso ao salvar a imagem PGM.
 *         1 em caso de erro ao abrir o arquivo de saída (Arquivo não
 *encontrado).
 *
 **/
int salvaPGM(string nome, tImagem img, int col, int lin, int tons) {
  ofstream arquivo(nome);
  if (!arquivo.is_open()) {
    erro = "Erro: Arquivo não encontrado.";
    return 1;
  }

  arquivo << "P2" << endl << col << " " << lin << endl << tons << endl;
  for (int i = 0; i < lin; i++) {
    for (int j = 0; j < col; j++) {
      arquivo << img[i][j] << " ";
    }
    arquivo << endl;
  }
  arquivo.close();
  return 0;
}

/**
 * Conversão da imagem de entrada com níveis de cinza para uma imagem com
 *representação binária (dois tons).
 *
 * @param img_entrada A imagem de entrada com níveis de cinza.
 * @param img_saida A imagem binarizada que será gerada.
 * @param lin O número de linhas da imagem.
 * @param col O número de colunas da imagem.
 * @param tons O número de tons de cinza da imagem.
 * @param limiar O valor limiar para a binarização.
 **/
void binarizar(tImagem img_entrada, tImagem img_saida, int col, int lin,
               int tons, int limiar) {
  while (limiar < 0 || limiar > tons) {
    cout << "O valor do limiar é inválido. O valor deve estar no intervalo de "
            "0 a "
         << tons << "." << endl;
    cout << "Por favor, digite o valor do limiar novamente: " << endl;
    cin >> limiar;
  }

  for (int i = 0; i < lin; i++) {
    for (int j = 0; j < col; j++) {
      if (img_entrada[i][j] <= limiar) {
        img_saida[i][j] =
            0; // Abaixo ou igual ao limiar, o pixel vira 0 (preto).
      } else {
        img_saida[i][j] = tons; // Acima do limiar, o pixel vira 1 (branco).
      }
    }
  }
}

/**
 * Transformação da imagem em um ícone, reduzindo-a para uma imagem de 64x64
 *pixels.
 *
 * @param img_entrada matriz bidimensional que representa a imagem de entrada.
 * @param img_saida matriz bidimensional que armazenará a imagem de saída em
 *escala reduzida (ícone).
 * @param col número de colunas da imagem de entrada.
 * @param lin número de linhas da imagem de entrada.
 * @param tons número de tons de cinza da imagem de entrada.
 **/

void iconizar(tImagem img_entrada, tImagem img_saida, int col, int lin,
              int tons) {
  // Determina o tamanho dos blocos em que a imagem será dividida
  int tamanho_bloco_lin = lin / 64;
  int tamanho_bloco_col = col / 64;

  // Percorre os blocos e calcula a média de tons de cada bloco
  for (int i = 0; i < 64; i++) {
    for (int j = 0; j < 64; j++) {
      int soma_tons = 0;

      // Percorre os pixels dentro do bloco e soma seus tons
      for (int k = 0; k < tamanho_bloco_lin; k++) {
        for (int l = 0; l < tamanho_bloco_col; l++) {
          soma_tons +=
              img_entrada[i * tamanho_bloco_lin + k][j * tamanho_bloco_col + l];
        }
      }

      // Calcula a média dos tons do bloco
      int media_tons = soma_tons / (tamanho_bloco_lin * tamanho_bloco_col);

      // Preenche todo o bloco da imagem de saída com a média de tons
      for (int k = 0; k < tamanho_bloco_lin; k++) {
        for (int l = 0; l < tamanho_bloco_col; l++) {
          img_saida[i * tamanho_bloco_lin + k][j * tamanho_bloco_col + l] =
              media_tons;
        }
      }
    }
  }
}

/**
 * Escurecimento da imagem de entrada diminuindo os valores dos pixels.
 * @param img_entrada A imagem de entrada.
 * @param img_saida A imagem resultante após o escurecimento.
 * @param lin O número de linhas da imagem.
 * @param col O número de colunas da imagem.
 * @param tons O número de tons de cinza da imagem.
 **/
void escurecer(tImagem img_entrada, tImagem img_saida, int col, int lin,
               int tons, int limiar) {

  for (int i = 0; i < lin; i++) {
    for (int j = 0; j < col; j++) {
      int novo_tom = img_entrada[i][j] - limiar;
      img_saida[i][j] =
          max(0, novo_tom); // Certifica-se de que o valor não é menor que 0.
    }
  }
}

/**
 * Clareamento da imagem de entrada aumentando os valores dos pixels.
 *
 * @param img_entrada Imagem de entrada.
 * @param img_saida Imagem resultante após o clareamento.
 * @param lin Número de linhas da imagem.
 * @param col Número de colunas da imagem.
 * @param tons Número de tons de cinza da imagem.
 **/
void clarear(tImagem img_entrada, tImagem img_saida, int col, int lin, int tons,
             int limiar) {
  for (int i = 0; i < lin; i++) {
    for (int j = 0; j < col; j++) {
      int novo_tom = img_entrada[i][j] + limiar;
      img_saida[i][j] = min(
          tons, novo_tom); // Certifica-se de que o valor não é maior que tons.
    }
  }
}

/**
 * Rotação da imagem de entrada para a direita, transpondo a matriz de entrada.
 *
 * @param img_entrada A imagem de entrada.
 * @param img_saida A imagem resultante após a rotação para a direita.
 * @param lin O número de linhas da imagem.
 * @param col O número de colunas da imagem.
 * @param tons O número de tons de cinza da imagem.
 **/
void rotaciona_direita(tImagem img_entrada, tImagem img_saida, int col, int lin, int tons) {
  int coluna, linha;
  linha = lin;
  coluna = col;
  for (int i = 0; i < linha; i++) {
    for (int j = 0; j < coluna; j++) {
      img_saida[j][i] = img_entrada[i][j];
    }
  }

  for (int i = 0; i < linha / 2; i++) {
    for (int j = 0; j < coluna; j++) {
      int temp = img_saida[i][j];
      img_saida[i][j] = img_saida[lin - 1 - i][j];
      img_saida[lin - 1 - i][j] = temp;
    }
  }

  // Reflexão vertical (troca de coordenadas i com lin - 1 - i)
  for (int i = 0; i < linha / 2; i++) {
    for (int j = 0; j < coluna; j++) {
      int temp = img_saida[i][j];
      img_saida[i][j] = img_saida[lin - 1 - i][j];
      img_saida[lin - 1 - i][j] = temp;
    }
  }

  // Transposição da matriz (troca de coordenadas i com j)
  int temp = linha;
  linha = coluna;
  coluna = temp;
}

/**
 * Rotação da imagem de entrada para a esquerda, transpondo a matriz de entrada
 *e, em seguida, refletindo verticalmente.
 *
 * @param img_entrada A imagem de entrada.
 * @param img_saida A imagem resultante após a rotação para a esquerda.
 * @param lin O número de linhas da imagem.
 * @param col O número de colunas da imagem.
 * @param tons O número de tons de cinza da imagem.
 **/
void rotaciona_esquerda(tImagem img_entrada, tImagem img_saida, int col, int lin, int tons) {
  int linha, coluna;
  coluna = col;
  linha = lin;
  for (int i = 0; i < linha; i++) {
    for (int j = 0; j < coluna; j++) {
      img_saida[j][i] = img_entrada[i][j];
    }
  }

  for (int i = 0; i < linha; i++) {
    for (int j = 0; j < coluna / 2; j++) {
      int temp = img_saida[i][j];
      img_saida[i][j] = img_saida[i][coluna - 1 - j];
      img_saida[i][coluna - 1 - j] = temp;
    }
  }

  // Reflexão vertical (troca de coordenadas i com lin - 1 - i)
  for (int i = 0; i < linha / 2; i++) {
    for (int j = 0; j < coluna; j++) {
      int temp = img_saida[i][j];
      img_saida[i][j] = img_saida[linha - 1 - i][j];
      img_saida[linha - 1 - i][j] = temp;
    }
  }

  int temp = linha;
  linha = coluna;
  coluna = temp;
}

/**
 * O método abaixo implementa o filtro passa-baixa, que suaviza a imagem
 * deixando-a mais homogênea. Perde-se nitidez e contraste, mas ganha-se
 *homogeneidade dos elementos da imagem.
 *
 * @param img_entrada A imagem de entrada.
 * @param img_saida A imagem resultante após o filtro passa-baixa.
 * @param lin O número de linhas da imagem.
 * @param col O número de colunas da imagem.
 * @param tons O número de tons de cinza da imagem.
 **/
void passa_baixa(tImagem img_entrada, tImagem img_saida, int col, int lin,
                 int tons) {
  int tamanho_kernel = 3; // Tamanho do kernel (deve ser ímpar)

  // Percorre a imagem, aplicando o filtro passa-baixa em cada pixel
  for (int i = tamanho_kernel / 2; i < lin - tamanho_kernel / 2; i++) {
    for (int j = tamanho_kernel / 2; j < col - tamanho_kernel / 2; j++) {
      int soma_tons = 0;

      // Percorre o kernel e soma os tons dos pixels vizinhos
      for (int k = -tamanho_kernel / 2; k <= tamanho_kernel / 2; k++) {
        for (int l = -tamanho_kernel / 2; l <= tamanho_kernel / 2; l++) {
          soma_tons += img_entrada[i + k][j + l];
        }
      }

      // Calcula a média dos tons dos pixels vizinhos
      int media_tons = soma_tons / (tamanho_kernel * tamanho_kernel);

      // Verifica se a média calculada está dentro do intervalo válido (0 a 255)
      if (media_tons < 0) {
        media_tons = 0;
      } else if (media_tons > 255) {
        media_tons = 255;
      }

      // Atribui a média ajustada ao pixel de saída
      img_saida[i][j] = media_tons;
    }
  }
  for (int i = 0; i < lin; i++) {
    for (int j = 0; j < col; j++) {
      if (img_saida[i][j] > tons) {
        img_saida[i][j] = tons;
      }
    }
  }

  for (int i = 0; i < lin; i++) {
    for (int j = 0; j < col; j++) {
      if (img_saida[i][j] < 0) {
        img_saida[i][j] = 0;
      }
    }
  }
}



int main(int argc, char **argv) {
  tImagem img_entrada, img_saida;
  int colunas, linhas, tons, limiar, opcao;
  string arquivo_entrada, arquivo_saida;

  // Leitura do arquivo de entrada da imagem.
  cout << "Bem-vindo ao programa de manipulação de imagens! Por favor,";
  cout << " entre com o nome da imagem de entrada: ";
  cin >> arquivo_entrada;
  arquivo_entrada = arquivo_entrada + ".pgm";
  if (carregaPGM(arquivo_entrada, img_entrada, &colunas, &linhas, &tons) != 0) {
    cout << "\n" + erro + "\n";
    return 1;
  }

  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      if (img_entrada[i][j] > tons) {
        img_entrada[i][j] = tons;
      }
    }
  }

  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      if (img_entrada[i][j] < 0) {
        img_entrada[i][j] = 0;
      }
    }
  }

  /**
   * Exibe o menu de opções e realiza chamadas de funções de acordo com a opção
   * selecionada pelo usuário.
   *
   * @return Nenhum valor é retornado.
   */

  do {
    cout << "\n* Menu de operações *" << endl;
    cout << "1 - Escurecer imagem " << endl;
    cout << "2 - Clarear imagem " << endl;
    cout << "3 - Rotacionar imagem à esquerda " << endl;
    cout << "4 - Rotacionar imagem à direita " << endl;
    cout << "5 - Binarizar imagem " << endl;
    cout << "6 - Iconizar imagem " << endl;
    cout << "7 - Aplicar filtro passa-baixa para suavizar a imagem" << endl;
    cout << "0 - Sair" << endl;
    cout << "Digite o número correspondente à opção desejada: ";
    cin >> opcao;

    switch (opcao) {
    case 1:
      cout << "Entre com o valor limiar para escurecimento (entre 0 e " << tons
           << "): ";
      cin >> limiar;
      escurecer(img_entrada, img_saida, colunas, linhas, tons, limiar);
      cout << "Entre com o nome da imagem de saída: ";
      cin >> arquivo_saida;
      arquivo_saida = arquivo_saida + ".pgm";
      salvaPGM(arquivo_saida, img_saida, colunas, linhas, tons);
      cout << "Imagem salva como: " << arquivo_saida << endl;
      break;
    case 2:
      cout << "Entre com o valor limiar para clareamento (entre 0 e " << tons
           << "): ";
      cin >> limiar;
      clarear(img_entrada, img_saida, colunas, linhas, tons, limiar);
      cout << "Entre com o nome da imagem de saída: ";
      cin >> arquivo_saida;
      arquivo_saida = arquivo_saida + ".pgm";
      salvaPGM(arquivo_saida, img_saida, colunas, linhas, tons);
      cout << "Imagem salva como: " << arquivo_saida << endl;
      break;
    case 3:
      rotaciona_esquerda(img_entrada, img_saida, colunas, linhas, tons);
      cout << "Entre com o nome da imagem de saída: ";
      cin >> arquivo_saida;
      arquivo_saida = arquivo_saida + ".pgm";
      salvaPGM(arquivo_saida, img_saida, colunas, linhas, tons);
      cout << "Imagem salva como: " << arquivo_saida << endl;
      break;
    case 4:
      rotaciona_direita(img_entrada, img_saida, colunas, linhas, tons);
      cout << "Entre com o nome da imagem de saída: ";
      cin >> arquivo_saida;
      arquivo_saida = arquivo_saida + ".pgm";
      salvaPGM(arquivo_saida, img_saida, linhas, colunas, tons);
      cout << "Imagem salva como: " << arquivo_saida << endl;
      break;
    case 5:
      cout << "Entre com o valor limiar para binarização (entre 0 e " << tons
           << "): ";
      cin >> limiar;
      binarizar(img_entrada, img_saida, colunas, linhas, tons, limiar);
      cout << " Entre com o nome da imagem de saída: ";
      cin >> arquivo_saida;
      arquivo_saida = arquivo_saida + ".pgm";
      salvaPGM(arquivo_saida, img_saida, colunas, linhas, tons);
      cout << "Imagem salva como: " << arquivo_saida << endl;
      break;
    case 6:
      iconizar(img_entrada, img_saida, colunas, linhas, tons);
      cout << "Entre com o nome da imagem de saída: ";
      cin >> arquivo_saida;
      arquivo_saida = arquivo_saida + ".pgm";
      salvarImagem64x64(arquivo_saida, img_saida, linhas, colunas);
      cout << "Imagem salva como: " << arquivo_saida << endl;
      break;
    case 7:
      passa_baixa(img_entrada, img_saida, colunas, linhas, tons);
      cout << " Entre com o nome da imagem de saída: ";
      cin >> arquivo_saida;
      arquivo_saida = arquivo_saida + ".pgm";
      salvaPGM(arquivo_saida, img_saida, colunas, linhas, tons);
      cout << "Imagem salva como: " << arquivo_saida << endl;
      break;
    case 0:
      cout << "Saindo do menu." << endl;
      break;
    default:
      cout << "\nOpção inválida, por favor digite novamente a opção desejada: ";
    }

  } while (opcao != 0);

  //// Construindo a imagem negativa.
  // for (int i = 0; i < linhas; i++){
  //     for (int j = 0; j < colunas; j++){
  //         img_saida[j][i] = tons - img_entrada[i][j];
  //     }
  // }

//  // Escrita do arquivo de saída da imagem.
//  cout << " Entre com o nome da imagem de saída: ";
//  cin >> arquivo_saida;
//  arquivo_saida = arquivo_saida + ".pgm";
//  if (salvaPGM(arquivo_saida, img_saida, colunas, linhas, tons) != 0) {
//    cout << "\n" + erro + "\n";
//    return 1;
//  }

  return 0;
}
