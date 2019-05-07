#ifndef POKEMON_H
#define POKEMON_H

extern char mapa[20][30];  

// struct do tipo pokemon
typedef struct pokemon{
    int id;
    char nome[20];
    int vida_total;
    int vida;
    float peso;
    float altura;
    int inimigo; //boolean
    int x;
    int y;
    int ataque;
    struct pokemon *prox, *ant;

}pokemon_t;

// struct da mochila
typedef struct{
	int tam, pokemons_disponiveis;
    pokemon_t *inicio, *fim;
    
}mochila_t;

// Inicia a mochila
void inicia(mochila_t* mochi);

// Cria pokemon
pokemon_t *cria_poke(int x);

// Copia valores de um pokemon e retorna a cópia
pokemon_t* copia_poke(pokemon_t* poke);

// Insere pokemons do arquivo na mochila
void inserir_fim(mochila_t *mochi, int x);

// Insere o inimigo no fim da mochila de inimigos
void inserir_fim_poke(mochila_t *mochi, pokemon_t *poke);

// Imprime mochila
void imprime (mochila_t *mochi);

// Restaura vida
void restaura_vida(mochila_t *mochi);

// Le pokemons do arquivo txt e coloca na mochila
void le_arquivo(char nome_arquivo[], mochila_t *mochi);

// Aleatoriza valor entre 1 e tam
int aleatorio(int tam);

// Busca na mochila o mesmo id aleatorizado na função encontra_inimigo
pokemon_t *busca_mochila(pokemon_t *auxiliar, int id);

// Encontra inimigo na mochila de pokemons e copia os valores para a de inimigos
pokemon_t *encontra_inimigo(mochila_t *mochi);

// Verifica se todos os pokemons da mochila são inimigos já
int todos_inimigos(pokemon_t *aux);

// Aleatoriza 3 pokemons distintos da mochila do jogador, e coloca na mochila de inimigos.
void aleatoriza_ini(mochila_t *mochi, mochila_t *mochi_ini);




/*
void inicia(mochila_t* mochi);
pokemon_t *cria_poke(int x);
pokemon_t* copia_poke(pokemon_t* poke);
void inserir_fim(mochila_t *mochi, int x);
void inserir_fim_poke(mochila_t *mochi, pokemon_t *poke);
void imprime (mochila_t *mochi);
void restaura_vida(mochila_t *mochi);
void le_arquivo(char nome_arquivo[], mochila_t *mochi);
void le_mapa(char nome_mapa[]);
coord_t* insere_personagem();
void insere_saida();
void imprime_mapa();
int aleatorio(int tam);
int encontra_coord(mochila_t* mochi_ini, pokemon_t *aux);
void aleat_mapa(mochila_t* mochi_ini);
pokemon_t *busca_mochila(pokemon_t *auxiliar, int id);
pokemon_t *encontra_inimigo(mochila_t *mochi);
int todos_inimigos(pokemon_t *aux);
void aleatoriza_ini(mochila_t *mochi, mochila_t *mochi_ini);
void insere_item();
int taxa_acerto(pokemon_t *pokemon);
pokemon_t *det_poke_ini(int x, int y, mochila_t *mochi_ini);
void luta(pokemon_t *pokemon_personagem, pokemon_t *pokemon_inimigo, int i);
pokemon_t *seleciona_pokemon_batalha(mochila_t *mochila_personagem);
void batalha(mochila_t *mochila_personagem, pokemon_t *pokemon_inimigo);
int encontra_caminho(int x, int y, int xant, int yant,mochila_t *mochila_personagem, mochila_t *mochila_ini);
*/


#endif
