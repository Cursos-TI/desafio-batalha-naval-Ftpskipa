#include <stdio.h>
#define TABULEIRO_LINHAS 10
#define TABULEIRO_COLUNAS 10
#define ASCII_A 65
#define HAB_LINHAS 5
#define HAB_COLUNAS 5

#define NAVIO_VALOR 3
#define HABCONE_VALOR 5
#define HABCRU_VALOR 6
#define HABOCT_VALOR 7

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

		if (tabuleiro[linha][coluna] == NAVIO_VALOR)
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
		
		tabuleiro[linha][coluna] = NAVIO_VALOR;
	}	
}

void mostrar_matrizhab(int hab[HAB_LINHAS][HAB_COLUNAS])
{
	for (int i = 0; i < HAB_LINHAS; i++)
	{
		for (int j = 0; j < HAB_COLUNAS; j++)
		{
			printf(" %d", hab[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}

void inicializar_matrizcone(int hab[HAB_LINHAS][HAB_COLUNAS])
{
	int lincentral =  HAB_LINHAS/2;
	int colcentral = HAB_COLUNAS/2;
	
	int antesdepois = 0;
	for (int i = 0; i < HAB_LINHAS; i++)
	{
		for (int j = 0; j < HAB_COLUNAS; j++)
		{
			int distrelativa = (j - colcentral) < 0 ? (colcentral - j) : (j - colcentral);

			if ( distrelativa <= antesdepois || distrelativa == 0)
				hab[i][j] = 1;
		}

		antesdepois++;
	}
}

void inicializar_matrizoctaedro(int hab[HAB_LINHAS][HAB_COLUNAS])
{
	int lincentral =  HAB_LINHAS/2;
	int colcentral = HAB_COLUNAS/2;
	
	int antesdepois = 0;
	for (int i = 0; i < HAB_LINHAS; i++)
	{
		for (int j = 0; j < HAB_COLUNAS; j++)
		{
			int distrelativa = (j - colcentral) < 0 ? (colcentral - j) : (j - colcentral);

			if ( distrelativa <= antesdepois || distrelativa == 0 )
				hab[i][j] = 1;
		}
		
		if (i < lincentral)
			antesdepois++;
		else
			antesdepois--;
	}
}

void inicializar_matrizcruz(int hab[HAB_LINHAS][HAB_COLUNAS])
{
	int lincentral =  HAB_LINHAS/2;
	int colcentral = HAB_COLUNAS/2;
	
	for (int i = 0; i < HAB_LINHAS; i++)
	{
		for (int j = 0; j < HAB_COLUNAS; j++)
		{
			if (i == lincentral || j == colcentral)
				hab[i][j] = 1;
		}
	}
}

void mover_hab(int hab[HAB_LINHAS][HAB_COLUNAS], int origem, int valorhab)
{
	int lincentral =  HAB_LINHAS/2;
	int colcentral = HAB_COLUNAS/2;
	
	int origem_habcone = origem;
	
	int lintabuleiro = origem_habcone / TABULEIRO_COLUNAS;
	int coltabuleiro = origem_habcone % TABULEIRO_COLUNAS;
	
	int inicord = hab[0][0];
	
	int tabuleiro_maxelem = (TABULEIRO_LINHAS * TABULEIRO_COLUNAS) - 1;

	if ( (coltabuleiro - colcentral) < 0 || (coltabuleiro + colcentral) > TABULEIRO_COLUNAS ||
		 (lintabuleiro - lincentral) < 0 || (lintabuleiro + lincentral) > TABULEIRO_LINHAS )
	{
		printf("A matriz de habilidade excede o tamanho do tabuleiro\n");
		return;
	}

	for (int i = 0; i < HAB_LINHAS; i++)
	{
		for (int j = 0; j < HAB_COLUNAS; j++)
		{
			int distanciax = colcentral - j;
			int distanciay = (lincentral - i) * TABULEIRO_COLUNAS;
			int coord  = origem_habcone - (distanciay + distanciax);
			
			int lin = coord / TABULEIRO_COLUNAS;
			int col = coord % TABULEIRO_COLUNAS;

			if (hab[i][j] == 1)
				tabuleiro[lin][col] = valorhab;

			hab[i][j] = coord;
		}
	}
}

int main()
{
	inicializar_tabuleiro(0); // Inicializa os campos de água com valor zero

	int habcone[HAB_LINHAS][HAB_COLUNAS] = 
	{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	};

	int habcruz[HAB_LINHAS][HAB_COLUNAS] = 
	{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	};

	int haboctaedro[HAB_LINHAS][HAB_COLUNAS] = 
	{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	};

	inicializar_matrizcone(habcone);
	inicializar_matrizoctaedro(haboctaedro);
	inicializar_matrizcruz(habcruz);

	mover_hab(habcone, 22, HABCONE_VALOR);
	mover_hab(habcruz, 62, HABCRU_VALOR);
	mover_hab(haboctaedro, 47, HABOCT_VALOR);
	
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
