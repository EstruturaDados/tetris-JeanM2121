#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura de uma peça
typedef struct
{
  char nome; 
  int id;    
} Peca;

// Definições de capacidade
#define MAX_FILA 5
#define MAX_PILHA 3

// FILA CIRCULAR
typedef struct
{
  Peca elementos[MAX_FILA];
  int frente;
  int tras;
  int tamanho;
} Fila;

void inicializarFila(Fila *f)
{
  f->frente = 0;
  f->tras = -1;
  f->tamanho = 0;
}

int filaCheia(Fila *f) { return f->tamanho == MAX_FILA; }
int filaVazia(Fila *f) { return f->tamanho == 0; }

void inserirFila(Fila *f, Peca p)
{
  if (filaCheia(f))
    return;
  f->tras = (f->tras + 1) % MAX_FILA;
  f->elementos[f->tras] = p;
  f->tamanho++;
}

Peca removerFila(Fila *f)
{
  Peca removida;
  removida.id = -1;
  removida.nome = '?';
  if (filaVazia(f))
    return removida;

  removida = f->elementos[f->frente];
  f->frente = (f->frente + 1) % MAX_FILA;
  f->tamanho--;
  return removida;
}

Peca *primeiroFila(Fila *f)
{
  if (filaVazia(f))
    return NULL;
  return &f->elementos[f->frente];
}

void mostrarFila(Fila *f)
{
  printf("Fila de peças:\t");
  if (filaVazia(f))
  {
    printf("(vazia)\n");
    return;
  }
  int i, indice = f->frente;
  for (i = 0; i < f->tamanho; i++)
  {
    printf("[%c %d] ", f->elementos[indice].nome, f->elementos[indice].id);
    indice = (indice + 1) % MAX_FILA;
  }
  printf("\n");
}

// PILHA 
typedef struct
{
  Peca elementos[MAX_PILHA];
  int topo;
} Pilha;

void inicializarPilha(Pilha *p) { p->topo = -1; }
int pilhaCheia(Pilha *p) { return p->topo == MAX_PILHA - 1; }
int pilhaVazia(Pilha *p) { return p->topo == -1; }

void push(Pilha *p, Peca elem)
{
  if (!pilhaCheia(p))
  {
    p->elementos[++(p->topo)] = elem;
  }
}

Peca pop(Pilha *p)
{
  Peca removida;
  removida.id = -1;
  removida.nome = '?';
  if (pilhaVazia(p))
    return removida;

  removida = p->elementos[p->topo--];
  return removida;
}

Peca *topoPilha(Pilha *p)
{
  if (pilhaVazia(p))
    return NULL;
  return &p->elementos[p->topo];
}

void mostrarPilha(Pilha *p)
{
  printf("Pilha de reserva (Topo -> Base):\t");
  if (pilhaVazia(p))
  {
    printf("(vazia)\n");
    return;
  }
  for (int i = p->topo; i >= 0; i--)
  {
    printf("[%c %d] ", p->elementos[i].nome, p->elementos[i].id);
  }
  printf("\n");
}

// ---------------- GERAR PEÇA ---------------- //
Peca gerarPeca(int id)
{
  char tipos[] = {'I', 'O', 'T', 'L'};
  Peca nova;
  nova.nome = tipos[rand() % 4];
  nova.id = id;
  return nova;
}

// ---------------- TROCAS ---------------- //
void trocarTopoComFrente(Fila *f, Pilha *p)
{
  if (filaVazia(f) || pilhaVazia(p))
  {
    printf("Não é possível trocar: fila ou pilha vazia.\n");
    return;
  }
  Peca *frente = primeiroFila(f);
  Peca *topo = topoPilha(p);
  Peca temp = *frente;
  *frente = *topo;
  *topo = temp;
  printf("Troca realizada entre a frente da fila e o topo da pilha.\n");
}

void trocaMultiplos(Fila *f, Pilha *p)
{
  if (f->tamanho < 3 || p->topo < 2)
  {
    printf("Não é possível realizar a troca múltipla (precisa de pelo menos 3 peças em cada).\n");
    return;
  }

  for (int i = 0; i < 3; i++)
  {
    int indiceFila = (f->frente + i) % MAX_FILA;
    Peca temp = f->elementos[indiceFila];
    f->elementos[indiceFila] = p->elementos[p->topo - i];
    p->elementos[p->topo - i] = temp;
  }
  printf("Troca múltipla realizada entre 3 da fila e 3 da pilha.\n");
}

// FUNÇÃO MAIN
int main()
{
  srand(time(NULL));

  Fila fila;
  Pilha pilha;
  inicializarFila(&fila);
  inicializarPilha(&pilha);

  int contadorID = 0;

  // Inicializa a fila com 5 peças
  for (int i = 0; i < MAX_FILA; i++)
  {
    inserirFila(&fila, gerarPeca(contadorID++));
  }

  int opcao;
  do
  {
    printf("\n=== Tetris Stack - Gerenciamento Mestre ===\n");
    mostrarFila(&fila);
    mostrarPilha(&pilha);

    printf("\nOpções:\n");
    printf("1 - Jogar peça da frente da fila\n");
    printf("2 - Reservar peça da fila\n");
    printf("3 - Usar peça da pilha\n");
    printf("4 - Trocar frente da fila com topo da pilha\n");
    printf("5 - Troca múltipla (3x3)\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    if (opcao == 1)
    {
      Peca jogada = removerFila(&fila);
      if (jogada.id != -1)
      {
        printf("Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
        inserirFila(&fila, gerarPeca(contadorID++));
      }
    }
    else if (opcao == 2)
    {
      if (!filaVazia(&fila) && !pilhaCheia(&pilha))
      {
        Peca reservada = removerFila(&fila);
        push(&pilha, reservada);
        printf("Peça reservada: [%c %d]\n", reservada.nome, reservada.id);
        inserirFila(&fila, gerarPeca(contadorID++));
      }
    }
    else if (opcao == 3)
    {
      Peca usada = pop(&pilha);
      if (usada.id != -1)
      {
        printf("Peça usada da reserva: [%c %d]\n", usada.nome, usada.id);
      }
    }
    else if (opcao == 4)
    {
      trocarTopoComFrente(&fila, &pilha);
    }
    else if (opcao == 5)
    {
      trocaMultiplos(&fila, &pilha);
    }

  } while (opcao != 0);

  printf("Saindo do jogo...\n");
  return 0;
}
