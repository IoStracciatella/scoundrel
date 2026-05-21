// TEM QUE MUDAR O NEGÓCIO DE FICAR SEMPRE SOBRANDO UMA CARTA NA SALA
// TEM QUE CONSERTAR O PROBLEMA DE DAR PRA ESCOLHER MAIS DE UMA VEZ A MESMA CARTA NA MESMA SALA
// TEM QUE ADICIONAR UM SISTEMA DE PONTUAÇÃO
// TEM QUE ADICIONAR UM MECANISMO QUE NÃO DEIXE O JOGADOR MATAR UM MONSTRO MAIS FORTE DO QUE O ANTERIOR COM A ARMA
// TEM QUE ADICIONAR UM SISTEMA QUE NÃO DEIXE CURAR 2 VEZES NA MESMA SALA

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void embaralhar(int array[], int tamanho);

int main() {
    struct carta {
        int numero, naipe;
    };

    struct carta cartas[44], cartas_emb[88], cartas_atuais[4];
    struct carta arma;
    arma.numero = 0;

    int indice_carta = 0, cont = 15, game = 0, vida = 20, pos_cartas = 0, indice = 0, fim_bar = 44, pulou = 0, escolha1, escolha2, indices_emb[44];
    int avanco = 4; // Define o tanto de cartas que são retiradas do baralho

    char nome_naipe[10];

    printf("=====================================================\n");
    printf("  ____                            _           _ \n");
    printf(" / ___|  ___ ___  _   _ _ __   __| |_ __ ___| |\n");
    printf(" \\___ \\ / __/ _ \\| | | | '_ \\ / _` | '__/ _ \\ |\n");
    printf("  ___) | (_| (_) | |_| | | | | (_| | | |  __/ |\n");
    printf(" |____/ \\___\\___/ \\__,_|_| |_|\\__,_|_|  \\___|_|\n");
    printf("=====================================================\n");

    //========================= PREENCHENDO A MATRIZ DE CARTAS COM OS NÚMEROS E NAIPES =========================

    for (int i = 0; i < 4; i++) {
        if (i > 1) {
            cont = 11;
        }

        for (int j = 2; j < cont; j++) {
            cartas[indice_carta].numero = j;
            cartas[indice_carta].naipe = i;

            indice_carta++;
        }
    }

    for (int i = 0; i < 44; i++) {
        indices_emb[i] = i;
    }

    embaralhar(indices_emb, 44);

    for (int i = 0; i < 44; i++) {
        cartas_emb[indices_emb[i]] = cartas[i];
    }

    while (game == 0) {

        for (int i = pos_cartas; i < pos_cartas+avanco; i++) {
            // Inserindo as cartas do baralho embaralhado em cartas_atuais
            cartas_atuais[indice] = cartas_emb[i];

            // Mudando o índice do array cartas_atuais
            indice++;
        }

        for (int i = pos_cartas; i < pos_cartas+4; i++) {
            
            // Imprimindo o nome dos naipes de acordo com o valor de 0 a 3
            if (cartas_emb[i].naipe == 0) {
                strcpy(nome_naipe, "Paus");
            } else if (cartas_emb[i].naipe == 1) {
                strcpy(nome_naipe, "Espadas");
            } else if (cartas_emb[i].naipe == 2) {
                strcpy(nome_naipe, "Ouros");
            } else if (cartas_emb[i].naipe == 3) {
                strcpy(nome_naipe, "Copas");
            }

            // Imprimindo a carta
            printf("\n-------------------\n");
            printf("[%d]  %d   %s", indice, cartas_emb[i].numero, nome_naipe);
            printf("\n-------------------\n");
        }

        pos_cartas += avanco; // Avançando no baralho. O array de cartas atuais agora irá conter 4 cartas a frente das que ele continha

        printf("\nVida: %d || Arma: %d\n", vida, arma.numero);
        printf("Digite 1 para permanecer na sala ou 2 para pular: ");
        scanf("%d", &escolha1);

        if (escolha1 == 1) {
            printf("Escolha com quais cartas interagir: ");
            
            for (int i = 0; i < 3; i++) {
                scanf("%d", &escolha2);

                escolha2--; // Para funcionar como índice do array subtraimos 1 (afinal array começa em zero)

                if (escolha2 > 3 || escolha2 < 0) {
                    printf("Escolha um valor valido.");
                    return 1;
                }

                if (cartas_atuais[escolha2].naipe == 0) {
                    if (arma.numero == 0) {
                        vida -= cartas_atuais[escolha2].numero;
                    } else if (arma.numero != 0) {
                        if (cartas_atuais[escolha2].numero - arma.numero >= 0) {
                            vida -= cartas_atuais[escolha2].numero - arma.numero;
                        } else {
                            vida = vida;
                        }
                    }
                } else if (cartas_atuais[escolha2].naipe == 1) {
                    if (arma.numero == 0) {
                        vida -= cartas_atuais[escolha2].numero;
                    } else if (arma.numero != 0) {
                        vida -= cartas_atuais[escolha2].numero - arma.numero;
                    }
                } else if (cartas_atuais[escolha2].naipe == 2) {
                    arma = cartas_atuais[escolha2];
                } else if (cartas_atuais[escolha2].naipe == 3) {
                    vida += cartas_atuais[escolha2].numero;
                }

                if (vida < 1) {
                    printf("Game over :(\n");
                    printf("Pontuação: hdjtfgbdhfghgds");
                }

                cartas_atuais[escolha2].numero = 0; // Pra detectar que a carta foi escolhida
                printf("\nVida: %d || Arma: %d\n", vida, arma.numero);
            }

            pulou = 0; // Define que não pulamos a sala
            avanco = 3; // Define que agora vamos puxar só 3 cartas do deck
            indice = 1; // Fazemos isso pra não sobrescrever a primeira carta em cartas_atuais

            // Definimos que a carta que não foi usada vai pro começo da prox. sala
            for (int i = 0; i < 4; i++) { 
                if (cartas_atuais[i].numero != 0) {
                    cartas_atuais[0] = cartas_atuais[i]; 
                }
            } 
        } else if (escolha1 == 2 && pulou == 0) {
            indice = 0;

            for (int i = fim_bar; i < fim_bar+4; i++) {
                cartas_emb[i] = cartas_atuais[indice];
                indice++;
            }

            fim_bar += 4; // Aumenta o fim do baralho e as cartas que foram retiradas vão para o fim
            pulou = 1; // Define que pulamos a sala
            avanco = 4; // Define que serão retiradas 4 cartas do baralho (afinal jogamos as 4 cartas fora)
        } else  if (escolha1 > 2) {
            printf("\n-----------------------------------------------------------------\n");
            printf("Escolha um valor valido.");
            return 1;
        } else if (pulou == 1) {
            printf("\n-----------------------------------------------------------------\n");
            printf("Nao pode pular essa sala pois a anterior ja foi pulada!");
            return 1;
        }

        indice = 0;
    }

    return 0;
}

// Criando a função que embaralha
void embaralhar(int array[], int tamanho) {
  // Semeando número aleatório
  srand( time(NULL) );
  
  // Trocando de ordem
  for (int i = 0; i < tamanho; i++)
  {
    // Achando aleatoriamente um índice de 0 até "tamanho"
    int troca_indice = rand() % tamanho;
    
    // Troca de posição do que está no índice i com o que está em troca_indice
    int temp = array[i];
    array[i] = array[troca_indice];
    array[troca_indice] = temp;
  }
  
}
