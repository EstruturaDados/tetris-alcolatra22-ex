#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5

typedef struct {
    char tipo;   // I, O, T, L
    int id;      // ID único
} Peca;

void mostrarFila(Peca fila[], int tamanho) {
    printf("\n=== FILA DE PEÇAS ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("[%c | id:%d] ", fila[i].tipo, fila[i].id);
    }
    printf("\n");
}

char gerarTipoAleatorio() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    return tipos[rand() % 4];
}

void adicionarPeca(Peca fila[], int *tamanho, int *proximoID) {
    if (*tamanho >= MAX_FILA) {
        return; // fila cheia (não deve ocorrer no jogo normal)
    }

    fila[*tamanho].tipo = gerarTipoAleatorio();
    fila[*tamanho].id = (*proximoID)++;
    (*tamanho)++;
}

void removerPeca(Peca fila[], int *tamanho) {
    if (*tamanho == 0) {
        printf("Fila está vazia, nada para remover!\n");
        return;
    }

    printf("\nPeça jogada: Tipo=%c, ID=%d\n",
           fila[0].tipo, fila[0].id);

    // Shift: remove da frente
    for (int i = 0; i < *tamanho - 1; i++) {
        fila[i] = fila[i + 1];
    }

    (*tamanho)--;
}

int main() {
    srand(time(NULL));

    Peca fila[MAX_FILA];
    int tamanho = 0;
    int proximoID = 0; // IDs exclusivos

    // Inicializa a fila com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        adicionarPeca(fila, &tamanho, &proximoID);
    }

    int opcao;

    do {
        printf("\n===== MENU TETRIS (SIMULAÇÃO DE FILA) =====\n");
        printf("1 - Mostrar fila\n");
        printf("2 - Jogar (remover primeira peça)\n");
        printf("3 - Adicionar nova peça automaticamente\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                mostrarFila(fila, tamanho);
                break;

            case 2:
                removerPeca(fila, &tamanho);
                // adiciona automaticamente uma nova peça no final
                adicionarPeca(fila, &tamanho, &proximoID);
                break;

            case 3:
                adicionarPeca(fila, &tamanho, &proximoID);
                printf("Nova peça adicionada!\n");
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
