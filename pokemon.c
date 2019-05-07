#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "pokemon.h"
#include "batalha.h"
#include "mapa.h"

// Inicia a mochila
void inicia(mochila_t* mochi) {
	mochi->inicio=NULL;
	mochi->fim=NULL;
	mochi->tam=0;
	mochi->pokemons_disponiveis = 0;
}

// Cria pokemon
pokemon_t *cria_poke(int x) { 
	pokemon_t* p=(pokemon_t*)malloc(sizeof(pokemon_t));
	p->prox=NULL;
	p->ant=NULL;
	p->id=x;
	p->x = -1;
	p->y = -1;
	return p;
}

// Copia valores de um pokemon e retorna a cópia
pokemon_t* copia_poke(pokemon_t* poke) {
	pokemon_t *copia = cria_poke(poke -> id);
	for (int i=0; i<19; i++){
		copia->nome[i] = poke->nome[i];
	}
	copia->vida_total = poke->vida_total;
	copia->vida = poke->vida;
	copia->peso = poke->peso;
	copia->altura = poke->altura;
	copia->inimigo = poke->inimigo;
	copia->ataque = poke->ataque;
	copia->x = poke->x;
	copia->y = poke->y;
	return copia;
}

// Insere pokemons do arquivo na mochila
void inserir_fim(mochila_t *mochi, int x) {
    pokemon_t* poke = cria_poke(x);
	if(mochi->tam == 0){
		mochi->inicio = poke;
		mochi->fim = poke;
	}else{
		mochi->fim->prox = poke;
		poke->ant = mochi->fim;
		mochi->fim = poke;
	}
    mochi->tam++;
    mochi->pokemons_disponiveis++;
}

// Insere o inimigo no fim da mochila de inimigos
void inserir_fim_poke(mochila_t *mochi, pokemon_t *poke) { 
	if(mochi->tam == 0){
		mochi->inicio = poke;
		mochi->fim = poke;
	}else{
		mochi->fim->prox = poke;
		poke->ant = mochi->fim;
		mochi->fim = poke;
	}
    mochi->tam++;
    mochi->pokemons_disponiveis++;
}

// Imprime mochila
void imprime (mochila_t *mochi) {
	if (mochi->inicio != NULL){	
		pokemon_t *aux = mochi->inicio;
		while(aux != NULL){
			printf("%d,%s,%d,%f,%f,%d\n", aux->id, aux->nome, aux->vida, aux->peso, aux->altura, aux->inimigo);
			aux = aux->prox;
		}
		printf("\n");
	}    
}

// Restaura vida
void restaura_vida(mochila_t *mochi) {
	pokemon_t *aux = mochi->inicio;
	if (mochi->tam == 0)
		return;

	while(aux) {
		if(aux->vida != aux->vida_total) {
			printf("Restaurando a vida de: %s\n", aux->nome);
			usleep(1500 * 1000);
			aux->vida = aux->vida_total;
			aux = aux->prox;
		} else {
			aux = aux->prox;
		}
	}
}

// Le pokemons do arquivo txt e coloca na mochila
void le_arquivo(char nome_arquivo[], mochila_t *mochi) {
	FILE *fp;
	fp = fopen(nome_arquivo, "r");
	if(fp ==	NULL){
		printf("%s\n","Erro na abertura do arquivo!" );
		exit(1);
	}

	printf("abriu %s\n", nome_arquivo);

    int id, vida;
    char nome[20];
    float peso, altura;

	while(!feof(fp)){
		fscanf(fp,"%d,%19[^,],%d,%f,%f", &id, &nome[0], &vida, &peso, &altura);
		inserir_fim(mochi, id);
		for (int i=0; i<19; i++){
			mochi->fim->nome[i] = nome[i];
		}
		mochi->fim->vida = vida;
		mochi->fim->vida_total = vida;
		mochi->fim->peso = peso;
		mochi->fim->altura = altura;
		mochi->fim->ataque = peso / altura;
		
		char c;
		while((c=fgetc(fp)) !='\n' && c != EOF);
	}

	fclose(fp);
}

// Aleatoriza valor entre 1 e tam
int aleatorio(int tam) {
	return 1 + ( rand() % tam );
}

// Busca na mochila o mesmo id aleatorizado na função encontra_inimigo
pokemon_t *busca_mochila(pokemon_t *auxiliar, int id) {
	if (!auxiliar)
		return NULL;
	
	if (auxiliar -> id == id)
		return auxiliar;

	return busca_mochila(auxiliar -> prox,id);
}

// Encontra inimigo na mochila de pokemons e copia os valores para a de inimigos
pokemon_t *encontra_inimigo(mochila_t *mochi) {
	if (todos_inimigos(mochi->inicio))
		return NULL;
	
	int id = aleatorio(mochi->tam);
	pokemon_t *poke = busca_mochila(mochi->inicio, id);
	
	if(poke->inimigo == 0){
		poke->inimigo = 1;
		pokemon_t *ini = copia_poke(poke);
		return ini;
	}
	return encontra_inimigo (mochi);
}

// Verifica se todos os pokemons da mochila são inimigos já
int todos_inimigos(pokemon_t *aux) {
	if (!aux)
		return 1; //todos inimigos
	
	if (aux -> inimigo == 0)
		return 0;

	return todos_inimigos(aux->prox);
}

// Aleatoriza 3 pokemons distintos da mochila do jogador, e coloca na mochila de inimigos.
void aleatoriza_ini(mochila_t *mochi, mochila_t *mochi_ini) {
	for (int i=0; i<3; i++)
		inserir_fim_poke(mochi_ini,encontra_inimigo(mochi));
}