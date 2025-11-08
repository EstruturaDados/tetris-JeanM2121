#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//tamanho da fila e pilha
#define TAM 5    
#define PILHA_MAX 3

// função struct
typedef struct {
    char nome;  
    int id;     
} Peca;

// Fila circular
Peca fila[TAM];
int frente = 0;
int tras = 0;
int contador = 0;

// Pilha reserva
Peca pilha[PILHA_MAX];
int topo = 0; 

// Função para gerar peça aleatória
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I','O','T','L'};
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Funções da fila
void filacheia(Peca p) {
    if(contador == TAM) {
        printf("Fila cheia!\n");
        return;
    }
    fila[tras] = p;
    tras = (tras + 1) % TAM;
    contador++;
}

Peca filavazia() {
    Peca vazia = {'X', -1};
    if(contador == 0) {
        printf("Fila vazia!\n");
        return vazia;
    }
    Peca removida = fila[frente];
    frente = (frente + 1) % TAM;
    contador--;
    return removida;
}

void mostrarFila() {
    printf("Fila atual: ");
    for(int i = 0; i < contador; i++) {
        int idx = (frente + i) % TAM;
        printf("[%c%d] ", fila[idx].nome, fila[idx].id);
    }
    printf("\n");
}

// Funções da pilha
void push(Peca p) {
    if(topo == PILHA_MAX) {
        printf("Pilha cheia!\n");
        return;
    }
    pilha[topo++] = p;
}

Peca pop() {
    Peca vazia = {'X', -1};
    if(topo == 0) {
        printf("Pilha vazia!\n");
        return vazia;
    }
    return pilha[--topo];
}

void mostrarPilha() {
    printf("Pilha reserva: ");
    for(int i = 0; i < topo; i++) {
        printf("[%c%d] ", pilha[i].nome, pilha[i].id);
    }
    printf("\n");
}

// Função principal
int main() {
    srand(time(NULL));
    int id_atual = 1;

    
    for(int i = 0; i < TAM; i++) {
        enqueue(gerarPeca(id_atual++));
    }

    int opcao;

    do {
        printf("\nMenu Tetris Stack\n");
        printf("1- Jogar peça\n");
        printf("2- Reservar peça\n");
        printf("3- Usar peça reservada\n");
        printf("0- Sair\n");
        printf("Escolha alguma opção: \n");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                Peca jogada = filavazia();
                if(jogada.id != -1)
                    printf("Você jogou a peça: %c%d\n", jogada.nome, jogada.id);
                filacheia(gerarPeca(id_atual++));
                break;
            }
            case 2: {
                Peca reservada = filavazia();
                if(reservada.id != -1) {
                    push(reservada);
                    printf("Você reservou a peça: %c%d\n", reservada.nome, reservada.id);
                    filacheia(gerarPeca(id_atual++));
                }
                break;
            }
            case 3: {
                Peca usada = pop();
                if(usada.id != -1) {
                    printf("Você usou a peça reservada: %c%d\n", usada.nome, usada.id);
                }
                break;
            }
            case 0:
                printf("Saindo do jogo.............\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

        mostrarFila();
        mostrarPilha();

    } while(opcao != 0);

    return 0;
}
