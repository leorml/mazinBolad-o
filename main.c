#include <stdio.h>
#include <stdlib.h>

// Função para verificar se a matriz é simétrica
int verificar_simetria(int N, char tabela[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (tabela[i][j] != tabela[j][i]) {
        return 0; // Retornar 0 para indicar falso
      }
    }
  }
  return 1; // Retornar 1 para indicar verdadeiro
}

// Função para contar o número de famílias e pessoas por família
void contar_familias(int N, int matriz[N][N], int *num_familias, int pessoas_por_familia[]) {
    int familias[N];
    *num_familias = 0;

    // Inicializar o vetor de famílias com -1 (valor inválido)
    for (int i = 0; i < N; i++) {
        familias[i] = -1;
    }

    // Percorrer cada pessoa na tabela de incidência
    for (int i = 0; i < N; i++) {
        // Verificar se a pessoa já pertence a alguma família contada
        if (familias[i] == -1) {
            familias[i] = (*num_familias); // Atribuir uma nova família à pessoa
            (*num_familias)++; // Atualizar o contador de famílias
        }

        // Percorrer as outras pessoas para verificar se pertencem à mesma família
        for (int j = i + 1; j < N; j++) {
            if (matriz[i][j] == 1) {
                // Marcar ambas as pessoas como pertencentes à mesma família
                familias[j] = familias[i];
            }
        }
    }

    // Contabilizar o número de integrantes em cada família
    for (int i = 0; i < (*num_familias); i++) {
        pessoas_por_familia[i] = 0; // Inicializar o contador de pessoas

        // Percorrer todas as pessoas e contar quantas pertencem à família atual
        for (int j = 0; j < N; j++) {
            if (familias[j] == i) {
                pessoas_por_familia[i]++;
            }
        }
    }
}

// Função principal para analisar a tabela
void analisar_tabela(const char *arquivo) {
    FILE *file = fopen(arquivo, "r"); // Abrir o arquivo em modo de leitura
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n"); // Verificar se ocorreu algum erro ao abrir o arquivo
        return;
    }

    int N;
    fscanf(file, "%d", &N); // Ler o número N de pessoas convidadas

    int matriz[N][N]; // Declaração da matriz para armazenar as relações familiares

    // Preencher a matriz com as relações familiares lidas do arquivo
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char valor;
            fscanf(file, " %c", &valor);
            if (valor == 'V') {
                matriz[i][j] = 1; // Definir valor 1 para indicar conexão entre pessoas
            } else {
                matriz[i][j] = 0; // Definir valor 0 para indicar ausência de conexão
            }
        }
    }

    fclose(file); // Fechar o arquivo

    if (verificar_simetria(N, matriz) == 0) {
        printf("Infelizmente os C(K)aios estavam bêbados.\n");
    } else {
        int num_familias = 0;
        int *pessoas_por_familia = (int *)malloc(N * sizeof(int)); // Alocação dinâmica de memória para armazenar o número de pessoas por família

        contar_familias(N, matriz, &num_familias, pessoas_por_familia);

        printf("%d FAMÍLIAS\n", num_familias);

        for (int i = 0; i < num_familias; i++) {
            printf("FAMÍLIA %d: %d PESSOAS\n", i + 1, pessoas_por_familia[i]);
        }

        free(pessoas_por_familia); // Liberar a memória alocada
    }
}

// Função principal
int main() {
    const char *arquivo = "tabela.txt";
    analisar_tabela(arquivo);

    return 0;
}
