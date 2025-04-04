#include <stdio.h>
#define TABULEIRO_LINHAS 10
#define TABULEIRO_COLUNAS 10
#define ASCII_A 65

int tabuleiro[TABULEIRO_LINHAS][TABULEIRO_COLUNAS];

void inicializar_tabuleiro(int valor)
{
	int count = 0;
	for (int i = 0; i < TABULEIRO_LINHAS; i++)
	{
		for (int j = 0; j < TABULEIRO_COLUNAS; j++)
		{
			tabuleiro[i][j] = valor;
		}
	}
}

void mostrar_tabuleiro()
{
	printf("\n  ");
	for (int i = 0; i < TABULEIRO_COLUNAS; i++)
	{
		printf(" %c", ASCII_A + i);
	}
	printf("\n");

	int count = 0;
	for (int i = 0; i < TABULEIRO_LINHAS; i++)
	{
		printf("%2d ", i + 1);
		for (int j = 0; j < TABULEIRO_COLUNAS; j++)
		{
			printf("%d ", tabuleiro[i][j]);
		}
		printf("\n");
	}
}

void mover_navio(int navio[], int tamanho)
{
	int tamanhoMax = (TABULEIRO_LINHAS * TABULEIRO_COLUNAS) - 1;
	int linha;
	int coluna;
	
	for (int i = 0; i < tamanho; i++) // Verificar conteúdo das coordenadas
	{
		linha = navio[i] / TABULEIRO_COLUNAS;
		coluna = navio[i] % TABULEIRO_COLUNAS;
		
		if (navio[i] > tamanhoMax || navio[i] < 0)
		{
			printf("A coordenada (%c%d) excede o tamanho do tabuleiro\n",
					coluna + ASCII_A, linha + 1);
			return;
		}

		if (tabuleiro[linha][coluna] != 0)
		{
			printf("\nA coordenada (%c%d) contém parte de outro navio\n",
					coluna + ASCII_A, linha + 1);
			return;
		}
	}

	for (int i = 0; i < tamanho; i++) // Inserir o navio no tabuleiro
	{
		linha = navio[i] / TABULEIRO_COLUNAS;
		coluna = navio[i] % TABULEIRO_COLUNAS;
		
		tabuleiro[linha][coluna] = 3;
	}
}

int main()
{
	inicializar_tabuleiro(0); // Inicializa os campos de água com valor zero

	int navio1[3] = {41, 42, 43}; // Células B5, C5, D5
	int navio2[3] = {16, 26, 36}; // Células G2, G3, G4
	int navio3[3] = {66, 75, 84}; // Células G7, F8, E9
	int navio4[3] = {12, 23, 34}; // Células C2, D3, E4

	mover_navio(navio1, sizeof(navio1)/sizeof(int));
	mover_navio(navio2, sizeof(navio2)/sizeof(int));
	mover_navio(navio3, sizeof(navio3)/sizeof(int));
	mover_navio(navio4, sizeof(navio4)/sizeof(int));
	
	mostrar_tabuleiro();

	return 0;
}
