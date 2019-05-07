#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "pokemon.h"
#include "batalha.h"
#include "mapa.h"

char mapa[20][30];  

int main () {
	//Inicia o processo randomico
	srand(time(NULL));


    char nome_arquivo[20];
	char nome_mapa [20];
	//Le nome do arquivo e do mapa
	printf("%s\n","Entre com o nome do arquivo de pokemons .txt: " );
	scanf("%s", nome_arquivo);
	printf("%s\n","Entre com o nome do arquivo do mapa .txt: " );
	scanf("%s", nome_mapa);

	//Aloca espaço para as mochilas do personagem e dos inimigos
	mochila_t *mochi;
	mochila_t *mochi_ini;
	mochi = (mochila_t *)malloc(sizeof(mochila_t));
	mochi_ini = (mochila_t *)malloc(sizeof(mochila_t));
	inicia(mochi);
	inicia(mochi_ini);

	//Le o arquivo dos pokemons e coloca na mochila
	le_arquivo(nome_arquivo,mochi);
	
	//Le o mapa e coloca na matriz
	le_mapa(nome_mapa);

	//Insere o personagem e a saída
	coord_t *coord = insere_personagem();
	insere_saida();

	//Aleatoriza os inimigos e coloca na mochila de inimigos
	aleatoriza_ini(mochi,mochi_ini);

	//Coloca os inimigos no mapa
	aleat_mapa(mochi_ini);

	//Aleatoriza os itens de restauração de vida e coloca no mapa
	insere_item();

	//Imprime o mapa a cada vez que o personagem caminha
	if (encontra_caminho(coord->x,coord->y,-1,-1, mochi, mochi_ini))
	  	printf("Voce achou a saída!\n");
	else 
	 	printf("Voce está preso!\n");
	
	return 0;
}