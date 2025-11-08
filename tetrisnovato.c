#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
  char nome; 
  int id;    
} Peca;

#define MAX 5 

// Função que gera a peça
Peca gerarPeca(int id)
{
  char tipos[] = {'I', 'O', 'T', 'L'};
  Peca p;
  p.nome = tipos[rand() % 4]; 
  p.id = id;
  return p;
}

//mostrar a fila
void mostrarFila(Peca fila[], int tamanho)
{
  if (tamanho == 0)
  {
    printf("Fila vazia.\n");
    return;
  }
  printf("Fila de peças:\n");
  for (int i = 0; i < tamanho; i++)
  {
    printf("[%c %d] ", fila[i].nome, fila[i].id);
  }
  printf("\n");
}
//função main
int main()
{
  srand(time(NULL));

  Peca fila[MAX];     
  int tamanho = 0;    
  int contadorID = 0; 


  for (int i = 0; i < MAX; i++)
  {
    fila[tamanho++] = gerarPeca(contadorID++);
  }

  int opcao;
  do
  {
    printf("\n=== Tetris Stack - Fila de Peças ===\n");
    mostrarFila(fila, tamanho);

    printf("\nOpções:\n");
    printf("1 - Jogar peça (dequeue)\n");
    printf("2 - Inserir nova peça (enqueue)\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    if (opcao == 1)
    {
      // Remove a primeira peça
      if (tamanho == 0)
      {
        printf("A fila está vazia! Não há peça para jogar.\n");
      }
      else
      {
        printf("Peça jogada: [%c %d]\n", fila[0].nome, fila[0].id);
        
        for (int i = 0; i < tamanho - 1; i++)
        {
          fila[i] = fila[i + 1];
        }
        tamanho--;
      }
    }
    else if (opcao == 2)
    {
      // Insere a nova peça
      if (tamanho == MAX)
      {
        printf("A fila está cheia! Não é possível inserir.\n");
      }
      else
      {
        Peca nova = gerarPeca(contadorID++);
        fila[tamanho++] = nova;
        printf("Peça inserida: [%c %d]\n", nova.nome, nova.id);
      }
    }

  } while (opcao != 0);

  printf("Saindo do jogo...\n");
  return 0;
}
