Trabalho desenvolvido por Roberta Samistraro Tomigian (GRR20171631) e Ricardo Carvalho dos Santos(GRR20171598).

O trabalho 1 da disciplina de Algoritmos 2, turma 2018-1, consiste em criar um jogo de pokemon automático.

Para compilar, basta digitar 'make' no terminal dentro da pasta do arquivo ou digitar no terminal: 

gcc -Wall -o nome_do_executavel main.c pokemon.c batalha.c mapa.c
./nome_do_executavel


O programa vai solicitar que voce digite o nome do arquivo onde esta incluso os nomes dos pokemons. Deve-se digitar:
nomedoarquivo.txt 

e clicar enter. 

A quantidade de pokemons presentes no arquivo devem ser 3 ou mais.

O mesmo vai ocorrer com o mapa. Deve-se digitar:
nomemapa.txt

e clicar enter.

O mapa deve ser de 20 linhas por 30 colunas e conter apenas ' ' e '#'.

Vai ser printado na tela o mapa e o caminho do personagem, assim como a descrição de suas batalhas e quando restaura a vida.

O personagem representa o numero 8, a saida é o '=', '.' é o lugar que o personagem passou mas voltou, o '+' é o caminho que o personagem esta fazendo,
o 'x' restaura a vida dos pokemons da mochila do personagem, o '?' é inimigo, ' ' é espaço livre por onde o personagem transita
e '#' é parede.

O personagem começa na primeira posição livre mais a esquerda na região superior do mapa e a saída é inserida na posição livre mais a direita na região 
inferior do mapa.  

Os pontos de restaurar vida 'x' são colocados aleatoriamente e varia de 2 a 10 itens.

Os inimigos são 3 e aleatorizados no mapa.

Após o mapa conter todas as posições: personagem, saída, itens e inimigos, o personagem começa a andar no mapa em direção a saída.

Ao encontrar um 'x' no mapa, a vida de todos os pokemons da mochila do personagem são restauradas.

Ao encontrar um '?' no mapa, se da início a uma batalha onde é escolhido um pokemon da mochila aleatoriamente, caso a vida do pokemon seja 0 ou menos é escolhido outro pokemon.

A batalha é gerida por turnos onde o personagem começa atacando. A probabilidade de acerto do ataque corresponde a 10% da vida atual do pokemon.

Caso o pokemon do personagem perca a batalha é então escolhido um novo pokemon aleatoriamente seguindo os mesmos critérios anteriores.

A batalha tem fim quando o pokemon inimigo é derrotado ou quando atingimos um limite de 6 lutas diferentes(caso hajam pokemons suficientes para tal) onde o personagem não foi capaz de vencer o pokemon inimigo.

É considerado que o personagem fugiu quando ao encontrar um '?' no mapa, o jogador não possua pokemons aptos para lutar(pokemons com vida maior que 0), quando não foi capaz de vencer o inimigo em uma batalha ou ainda se não tiver acesso a saída.

O jogo termina quando o personagem acha a saída, ou não(caso específico citado anteriormente).
