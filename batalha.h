#ifndef BATALHA_H
#define BATALHA_H

extern char mapa[20][30];  

// Calcula % de acerto do pokemon
int taxa_acerto(pokemon_t *pokemon);

// Modulo luta entre pokemons, i = numero da batalha
void luta(pokemon_t *pokemon_personagem, pokemon_t *pokemon_inimigo, int i);

// Seleciona pokemon para a batalha
pokemon_t *seleciona_pokemon_batalha(mochila_t *mochila_personagem);

// Modulo de batalha
void batalha(mochila_t *mochila_personagem, pokemon_t *pokemon_inimigo);

#endif