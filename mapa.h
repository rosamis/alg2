#ifndef MAPA_H
#define MAPA_H

extern char mapa[20][30];

typedef struct no {
    int x,y;
    struct no *ant;
}nop_t;

typedef struct{
    int x,y;
}coord_t;

typedef struct{
    int tam;
    nop_t *topo;
}pilha_t;

// Imprime o mapa
void imprime_mapa();

// Le mapa do arquivo txt e coloca na matriz
void le_mapa(char nome_mapa[]);

// Insere o personagem na primeira posição vazia
coord_t* insere_personagem();

// Insere a saída na posição mais a abaixo e a direita do mapa
void insere_saida();

// Aleatoriza posição vazia no mapa, coloca inimigo e no inimigo atualiza as coordenadas para guardar onde ele esta no mapa.
int encontra_coord(mochila_t* mochi_ini, pokemon_t *aux);

void aleat_mapa(mochila_t* mochi_ini);

// Insere de 2 a 10 itens em posições aleatorias no mapa
void insere_item();

// Verifica a correspondencia das coordenadas do mapa com os pokemons da mochila de inimigos, quando for batalhar
pokemon_t *det_poke_ini(int x, int y, mochila_t *mochi_ini);

// Mostra no terminal o mapa e o caminho do personagem
int encontra_caminho(int x, int y, int xant, int yant,mochila_t *mochila_personagem, mochila_t *mochila_ini);

#endif