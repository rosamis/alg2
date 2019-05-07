#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include "pokemon.h"
#include "batalha.h"
#include "mapa.h"

// Calcula % de acerto do pokemon
int taxa_acerto(pokemon_t *pokemon) {
	int vida, porc;
	float ataqCem, porCem;

	vida = pokemon->vida;
	ataqCem = vida * 0.1;

	porc = aleatorio(100);
	porCem = porc / 100.0;

	if(ataqCem >= porCem)
		return 1;
	else
		return 0;
}

// Modulo luta entre pokemons, i = numero da batalha
void luta(pokemon_t *pokemon_personagem, pokemon_t *pokemon_inimigo, int i) {
	int hit, turno;

	turno = 1;

	printf("BATALHA NUMERO %d INICIADA:\nAliado: %s[%dhp] vs. Adversário: %s[%dhp]\n", i + 1, pokemon_personagem->nome, pokemon_personagem->vida, pokemon_inimigo->nome, pokemon_inimigo->vida);
	usleep(2000 * 1000);
	while((pokemon_personagem->vida > 0) && (pokemon_inimigo->vida > 0)) {
		printf("TURNO %d\n", turno);
		hit = taxa_acerto(pokemon_personagem);
		if(hit) {
			printf("Aliado: %s acertou o ataque! Adversário: %s perdeu %d de hp\n", pokemon_personagem->nome, pokemon_inimigo->nome, pokemon_personagem->ataque);
			pokemon_inimigo->vida -= pokemon_personagem->ataque;
			if(pokemon_inimigo->vida <= 0) {
				printf("Aliado: %s venceu a luta! Adversário: %s está desmaiado(a)\n\n", pokemon_personagem->nome, pokemon_inimigo->nome);
				usleep(2000 * 1000);
				return;
			}

		} else {
			printf("Aliado: %s errou o ataque!\n", pokemon_personagem->nome);
		}
		usleep(2000 * 1000);

		hit = taxa_acerto(pokemon_inimigo);
		if(hit) {
			printf("Adversário: %s acertou o ataque! Aliado: %s perdeu %d de hp\n", pokemon_inimigo->nome, pokemon_personagem->nome, pokemon_inimigo->ataque);
			pokemon_personagem->vida -= pokemon_inimigo->ataque;
			if(pokemon_personagem->vida <= 0) {
				printf("Adversário: %s venceu a luta! Aliado: %s está desmaiado(a)\n\n", pokemon_inimigo->nome, pokemon_personagem->nome);
				usleep(2000 * 1000);
				return;
			}

		} else {
			printf("Adversário: %s errou o ataque!\n", pokemon_inimigo->nome);
		}
		turno++;
		usleep(2000 * 1000);
	}
}

// Seleciona pokemon para a batalha
pokemon_t *seleciona_pokemon_batalha(mochila_t *mochila_personagem) {
	int id_aleat;
	pokemon_t *aux = mochila_personagem->inicio;

	while(1) {
		id_aleat = aleatorio(mochila_personagem->tam);
		for(; aux != NULL; aux = aux->prox) {
			if(aux->id == id_aleat) {
				if(aux->vida > 0)
					return aux;
				else
					break;
			}
		}
		aux = mochila_personagem->inicio;
	}
}

// Modulo de batalha
void batalha(mochila_t *mochila_personagem, pokemon_t *pokemon_inimigo) {
	printf("Entrou batalha!\n");
	if(mochila_personagem->pokemons_disponiveis == 0) {
		printf("NÃO TEMOS POKEMONS DISPONIVEIS PARA BATALHAR, VOCE FUGIU\n");
		usleep(1000 * 1000);
		return;
	}

	int i = 0;
	pokemon_t *pokemon_batalha;

	// i = quantidade de lutas, considerando maximo de 6 pokemons por batalha
	while((mochila_personagem->pokemons_disponiveis > 0) && i < 6) {
		pokemon_batalha = seleciona_pokemon_batalha(mochila_personagem);
		
		luta(pokemon_batalha, pokemon_inimigo, i);

		i++;

		if(pokemon_inimigo->vida <= 0) {
			printf("FINAL DE BATALHA, O ADVERSÁRIO FOI DERROTADO!\n");
			usleep(2000 * 1000);
			return;
		} else {
			mochila_personagem->pokemons_disponiveis--;
		}
	}

	if(mochila_personagem->pokemons_disponiveis == 0) {
		printf("TODOS OS SEUS POKEMONS ESTÃO DESMAIADOS, VOCE FUGIU!\n");
		usleep(2000 * 1000);
		return;
	} else {
		printf("NUMERO MAXIMO DE BATALHAS (%d) ATINGIDO! VOCE FUGIU!\n", i);
		usleep(2000 * 1000);
	}	
}