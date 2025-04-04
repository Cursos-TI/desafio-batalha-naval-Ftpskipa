#include <stdio.h>
#define MATRIZ_LINHAS 10
#define MATRIZ_COLUNAS 10

int tabuleiro[MATRIZ_LINHAS][MATRIZ_COLUNAS];

void mostrar_tabuleiro()
{
	printf("\n  ");
	for (int i = 0; i < 10; i++)
	{
		printf(" %c", 65 + i);
	}
	printf("\n");

	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		printf("%2d ", i + 1);
		for (int j = 0; j < 10; j++)
		{
			printf("%d ", tabuleiro[i][j]);
		}
		printf("\n");
	}
}

void mover_navio(int navio[], int tamanho)
{
	int tamanhoMax = (MATRIZ_LINHAS * MATRIZ_COLUNAS) - 1;
	int linha;
	int coluna;
	
	for (int i = 0; i < tamanho; i++) // Verificar conteúdo das coordenadas
	{
		linha = navio[i] / 10;
		coluna = navio[i] % 10;
		
		if (navio[i] > tamanhoMax || navio[i] < 0)
		{

			printf("A coordenada (%c%d) excede o tamanho do tabuleiro\n",
					coluna + 65, linha + 1);
			return;
		}

		if (tabuleiro[linha][coluna] != 0)
		{
			printf("\nA coordenada (%c%d) contém parte de outro navio\n",
					coluna + 65, linha + 1);
			return;
		}
	}

	for (int i = 0; i < tamanho; i++) // Inserir o navio no tabuleiro
	{
		linha = navio[i] / 10;
		coluna = navio[i] % 10;
		
		tabuleiro[linha][coluna] = 3;
	}
}

int main()
{
	int navio1[3] = {11, 12, 13}; // Células B2, C2, D2
	int navio2[3] = {16, 26, 36}; // Células G2, G3, G4

	mover_navio(navio1, sizeof(navio1)/sizeof(int));
	mover_navio(navio2, sizeof(navio2)/sizeof(int));
	mostrar_tabuleiro();

	return 0;
}
