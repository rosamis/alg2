#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include "pokemon.h"
#include "batalha.h"
#include "mapa.h"

static int TRUE = 1;
static int FALSE = 0;

// Imprime o mapa
void imprime_mapa() {
	int i,j;
	for (i=0; i<20; i++){
		for (j=0; j<30; j++){
			printf ("%c", mapa[i][j]); 
		} 
		printf("\n");
	}
}

// Le mapa do arquivo txt e coloca na matriz
void le_mapa(char nome_mapa[]) {
	FILE *fp;
	char c;
	int i,j;
	fp = fopen(nome_mapa, "r");
	if(fp == NULL){
		printf("%s\n","Erro na abertura do arquivo!" );
		exit(1);
	}

	printf("abriu %s\n", nome_mapa);

	for (i=0; i<20; i++){
		for (j=0; j<30; j++){
			c = fgetc(fp);
			if (c == EOF){ /*ERRO*/ }
            mapa[i][j] = c;
		}
		c = fgetc(fp);
		if (c != '\n'){ /*ERRO*/ }
	}
	fclose(fp);
}

// Insere o personagem na primeira posição vazia
coord_t* insere_personagem() {
	coord_t *coord = (coord_t *)malloc(sizeof(coord_t));
	printf("INSERINDO PERSONAGEM\n");
	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 30; j++){
			if (mapa[i][j] == ' '){
				mapa[i][j] = '8';
				coord->x = i;
				coord->y = j;
				printf("aqui x=%d y=%d\n", i,j);
				return coord;
			}	
		} 
	}
	return NULL;
}

// Insere a saída na posição mais a abaixo e a direita do mapa
void insere_saida() {
	int i,j;
	printf("INSERINDO A SAIDA\n");
	for (i = 19; i >= 0; i--) {
		for (j = 29; j >= 0; j--) {
			if (mapa[i][j] == ' ') {
				mapa[i][j] = '=';
				return;
			}	
		} 
	}
	printf("NÃO FOI POSSIVEL INSERIR A SAIDA, TERMINANDO PROGRAMA...\n\n");
	exit(1);
}

// Aleatoriza posição vazia no mapa, coloca inimigo e no inimigo atualiza as coordenadas para guardar onde ele esta no mapa.
int encontra_coord(mochila_t* mochi_ini, pokemon_t *aux) { 
	int lin = aleatorio(20)-1; 
	int col = aleatorio(30)-1;
	if (mapa[lin][col] == ' '){
		aux->x = lin;
		aux->y = col;
		mapa[lin][col] = '?';
		return 1;
	}	
	return encontra_coord(mochi_ini,aux);
}

void aleat_mapa(mochila_t* mochi_ini) {
	pokemon_t *aux = mochi_ini->inicio;
	for (int i=0; i<3; i++) {
		encontra_coord(mochi_ini,aux);
		aux = aux->prox;
	}
}

// Insere de 2 a 10 itens em posições aleatorias no mapa
void insere_item() {
	int itens = aleatorio(9) + 1;
	int i = 0;
	int quebra_loop = 0;
	
	printf("%d ITENS SERÃO INSERIDOS\n", itens);
	do {
		int linha = aleatorio(20) - 1;
		int coluna = aleatorio(30) - 1;

		if(mapa[linha][coluna] == ' ') {
			mapa[linha][coluna] = 'x';
			printf("ITEM %d INSERIDO NA POSIÇÃO [%d, %d]\n", i + 1, linha + 1, coluna + 1);
			i++;
			quebra_loop = 0;
		}

		quebra_loop++;

		if(quebra_loop == 2000)	{
				printf("APOS 2000 TENTATIVAS DE INSERSÃO NÂO ACHAMOS UMA POSIÇÃO LIVRE\n");
				return;
		}
	} while(i != itens);
}

// Verifica a correspondencia das coordenadas do mapa com os pokemons da mochila de inimigos, quando for batalhar
pokemon_t *det_poke_ini(int x, int y, mochila_t *mochi_ini) {
	pokemon_t *aux = mochi_ini->inicio;
	while(aux){
		if (aux->x == x && aux->y == y)
			return aux;
		aux = aux->prox;
	}
	printf ("Não há inimigo\n");
	return NULL;
}

// Mostra no terminal o mapa e o caminho do personagem
int encontra_caminho(int x, int y, int xant, int yant,mochila_t *mochila_personagem, mochila_t *mochila_ini) {
	system("clear");
	imprime_mapa();
	usleep(100 * 1000);
	if ((x < 0 || x > 19) || (y < 0 || y > 29))
		return FALSE;

	if (mapa[x][y] == '=')
		return TRUE;

	if (mapa[x][y] == '.' || mapa[x][y] == '#' || mapa[x][y] == '+')
		return FALSE;

	if (mapa[x][y] == '?'){
		pokemon_t *poke_inimigo = det_poke_ini(x,y,mochila_ini);
		batalha(mochila_personagem, poke_inimigo);
	}

	if (mapa[x][y] == 'x')
		restaura_vida(mochila_personagem);


	mapa[x][y] = '8';

	if (xant >= 0 && yant >= 0)
		mapa[xant][yant] = '+';

	if (encontra_caminho(x+1,y,x,y,mochila_personagem,mochila_ini) == TRUE) // SUL
		return TRUE;
	if (encontra_caminho(x,y+1,x,y,mochila_personagem,mochila_ini) == TRUE) // LESTE
		return TRUE;
	if (encontra_caminho(x-1,y,x,y,mochila_personagem,mochila_ini) == TRUE) // NORTE
		return TRUE;
	if (encontra_caminho(x,y-1,x,y,mochila_personagem,mochila_ini) == TRUE) // OESTE
		return TRUE;
	mapa[xant][yant] = '8';
	mapa[x][y] = '.';
	return FALSE;
}