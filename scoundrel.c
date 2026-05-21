#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    struct carta {
        int numero, naipe;
    };

    struct carta cartas[44];
    int indice_carta = 0, cont = 15;

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

    printf("=====================================================\n");
    printf("  ____                            _           _ \n");
    printf(" / ___|  ___ ___  _   _ _ __   __| |_ __ ___| |\n");
    printf(" \\___ \\ / __/ _ \\| | | | '_ \\ / _` | '__/ _ \\ |\n");
    printf("  ___) | (_| (_) | |_| | | | | (_| | | |  __/ |\n");
    printf(" |____/ \\___\\___/ \\__,_|_| |_|\\__,_|_|  \\___|_|\n");
    printf("=====================================================\n");
    printf("     Digite qualquer coisa para iniciar!\n");
    printf("=====================================================\n");
    scanf(" ");

    struct carta cartas_emb[44];
    int indices_emb[44];

    for (int i = 0; i < 44; i++) {
        indices_emb[i] = i;
    }

    embaralhar(indices_emb, 44);

    for (int i = 0; i < 44; i++) {
        cartas_emb[indices_emb[i]] = cartas[i];
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
