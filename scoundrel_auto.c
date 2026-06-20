// Caio Brun de Olivera - 17882570
// Lucas Cordeiro Gatti - 15746427
// Re Martins Brant - 17080231

/*

Na versão em que o computador joga sozinho, as jogadas serão escolhidas pelo próprio programa. 
Depois que a Mesa é mostrada na tela, o programa espera o usuário digitar uma instrução para o computador fazer o próximo movimento. Isso servirá para que quem esteja assistindo consiga acompanhar o que está acontecendo, em vez do jogo rodar de uma vez só.
Primeiramente, o nosso algoritmo verificará se é uma boa decisão evitar a Sala. Para fazer isso, ele olha as cartas que estão na Sala e calcula uma estimativa de dano procurando as cartas que são monstros, ou seja, paus e espadas, e vê quanto de vida perderia ao enfrentar esses inimigos. 


Caso ele tenha uma arma equipada e poder usufruí-la contra o monstro, o dano considerado será o valor do monstro subtraído do valor da arma. Se esse valor ficar negativo, o dano será zero. No cenário da estimativa de dano for maior ou igual à vida atual e ainda for possível evitar a Sala, o computador irá evitá-la. 
Nesse caso, as cartas da Sala irão para o fundo da Masmorra.

Se o computador não evitar a Sala, ele começará a escolher as cartas as quais irá interagir. 
A escolha segue uma ordem de prioridade: Primeiro, ele procura uma poção de copas, mas só a usará se sua vida estiver menor que 20 pontos, isso se ainda não tiver usado outra poção naquele turno. 

Caso tenha mais de uma poção disponível, ele escolhe a de maior valor, porque será a mais vantajosa para recuperar vida.

Caso não haja poção útil, o algoritmo procurará uma arma de Ouros. 

Assim, ele dará preferência para armas mais vantajosas que a atual. Então, na jogada em que houver uma arma com valor maior do que a equipada, ele escolherá essa nova arma. 

Quando uma nova arma é equipada, a anterior será descartada e o limite da arma voltará a ficar sem limite, pois ela ainda não foi usada contra nenhum monstro.
Se não obtiver poção útil nem arma melhor, o programa procurará um monstro para enfrentar. Nessa parte, ele tentará escolher um monstro que causará o menor dano possível. 

Para cada monstro da Sala, o computador calculará quanto dano ele receberia se estivesse lutando sem armas. 
Depois, se tiver alguma arma equipada e se o valor do monstro for menor que o limite da arma, ele também terá calculado quanto dano receberia usando a arma. 

No cenário em que usar a arma causa menos dano, ele escolherá usar a arma. Caso não obtiver sucesso, ele lutará sem a arma.

Após o computador escolher uma carta, o algoritmo resolverá a jogada. Se a carta for monstro, ele perderá vida de acordo com o combate. 
Se ele tiver usado a arma, o limite dela passará a ser o valor daquele monstro, isso porque a partir daí a arma só poderá ser usada contra monstros menores. 
No caso da carta for uma arma, ela virará a nova arma equipada. Se a carta for poção, ela recuperará vida, mas sem deixar passar de 20 pontos. 
Se uma poção já tiver sido usada no mesmo turno, a próxima poção será descartada sem curar.

No final de cada jogada, o programa mostrará o que aconteceu e atualiza a Mesa. 
Então aparecerão novamente a vida atual, a arma equipada, o limite da arma, a Sala atual, a Masmorra e a possibilidade de ainda ser possível evitar a Sala. 
Se a vida chegar a um valor nulo ou menos, o algoritmo perde e o jogo acaba. Se a Masmorra acabar e a vida ainda for maior que 0, o algoritmo vence.
Logo, em suma, o computador deve jogar olhando a situação atual da Mesa e escolher uma jogada válida. 
Ele tentará evitar a Sala quando ela parecer perigosa demais, usará poções quando precisar curar, equipará armas mais otimizadas quando aparecerem e enfrentará os monstros tentando receber o menor dano possível.

*/

//NOTA ADICIONAL: utilizamos IA (Claude) para auxiliar na resolução do bug que fazia o programa sortear cartas que não existiam após o fim do jogo.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//struct simples para guardar valor e naipe da carta
struct carta {
    int numero;
    int naipe;
};

void mostrar_titulo();
void montar_baralho(struct carta cartas[]);
void embaralhar(int indices[], int tamanho);
void mostrar_carta(struct carta carta_atual, int indice);
void mostrar_mesa(struct carta sala[], int quantidade_sala, int vida, struct carta arma, int limite_arma, int pode_evitar, int modo_jogo, int pos_masmorra, int fim_masmorra);

int main() {
    struct carta cartas[44], masmorra[200], sala[4], arma, carta_jogada;
    int indices[44];
    int vida = 20;
    int pos_masmorra = 0;
    int fim_masmorra = 44;
    int quantidade_sala = 0;
    int pode_evitar = 1;
    int limite_arma = 15;
    int modo_jogo = 0;
    int modo_valido = 0;
    int jogo_ativo = 1;
    int vitoria = 0;
    int curou_turno = 0;
    int escolha_sala = 0;
    int entrada_valida = 0;
    int carta_escolhida = 0;
    int usar_arma = 0;
    int instrucao = 0;
    int instrucao_valida = 0;
    int jogadas_feitas = 0;
    int cartas_para_resolver = 0;
    int fugir_sala = 0;
    int dano = 0;
    int dano_com_arma = 0;
    int dano_estimado = 0;
    int menor_dano = 0;
    int indice_melhor_carta = 0;
    int achou_carta = 0;
    int maior_valor = 0;
    int pontuacao = 0;
    int i = 0;
    int j = 0;

    //aqui temos o estado inicial do jogo
    arma.numero = 0;
    arma.naipe = 2;

    srand(time(NULL));

    mostrar_titulo();

    //monta o baralho e prepara a Masmorra embaralhada
    montar_baralho(cartas);

    for (i = 0; i < 44; i++) {
        indices[i] = i;
    }

    embaralhar(indices, 44);

    for (i = 0; i < 44; i++) {
        masmorra[i] = cartas[indices[i]];
    }

    while (modo_valido == 0) {
        printf("Escolha o modo de jogo:\n");
        printf("1 - Pessoa joga\n");
        printf("2 - Computador joga sozinho\n");
        printf("Opcao: ");
        scanf("%d", &modo_jogo);

        if (modo_jogo == 1 || modo_jogo == 2) {
            modo_valido = 1;
        } else {
            printf("Escolha um modo valido.\n\n");
        }
    }

    while (jogo_ativo == 1 && vida > 0) {
        //completa a sala até quatro cartas sem passar do fim da Masmorra
        while (quantidade_sala < 4 && pos_masmorra < fim_masmorra) {
            sala[quantidade_sala] = masmorra[pos_masmorra];
            quantidade_sala++;
            pos_masmorra++;
        }

        if (quantidade_sala == 0) {
            jogo_ativo = 0;
            vitoria = 1;
        } else {
            mostrar_mesa(sala, quantidade_sala, vida, arma, limite_arma, pode_evitar, modo_jogo, pos_masmorra, fim_masmorra);

            fugir_sala = 0;

            if (modo_jogo == 1) {
                //messe passo, a pessoa escolhe se vai enfrentar ou evitar a Sala
                entrada_valida = 0;

                while (entrada_valida == 0) {
                    printf("Digite 1 para enfrentar a sala");
                    if (pode_evitar == 1) {
                        printf(" ou 2 para evitar a sala");
                    }
                    printf(": ");
                    scanf("%d", &escolha_sala);

                    if (escolha_sala == 1) {
                        entrada_valida = 1;
                    } else if (escolha_sala == 2 && pode_evitar == 1) {
                        entrada_valida = 1;
                        fugir_sala = 1;
                    } else if (escolha_sala == 2 && pode_evitar == 0) {
                        printf("Voce nao pode evitar duas salas seguidas.\n");
                    } else {
                        printf("Escolha um valor valido.\n");
                    }
                }
            } else {
                //aqui o algoritmo espera uma instrução antes de decidir o movimento
                instrucao_valida = 0;

                while (instrucao_valida == 0) {
                    printf("Digite 1 para o computador fazer o proximo movimento: ");
                    scanf("%d", &instrucao);

                    if (instrucao == 1) {
                        instrucao_valida = 1;
                    } else {
                        printf("Instrucao invalida.\n");
                    }
                }

                dano_estimado = 0;

                for (i = 0; i < quantidade_sala; i++) {
                    if (sala[i].naipe == 0 || sala[i].naipe == 1) {
                        dano = sala[i].numero;

                        if (arma.numero > 0 && sala[i].numero < limite_arma) {
                            dano_com_arma = sala[i].numero - arma.numero;
                            if (dano_com_arma < 0) {
                                dano_com_arma = 0;
                            }

                            if (dano_com_arma < dano) {
                                dano = dano_com_arma;
                            }
                        }

                        dano_estimado = dano_estimado + dano;
                    }
                }

                //o computador evita a Sala se o dano estimado puder mata-lo
                if (dano_estimado >= vida && pode_evitar == 1 && quantidade_sala == 4) {
                    fugir_sala = 1;
                }
            }

            if (fugir_sala == 1) {
                if (fim_masmorra + quantidade_sala <= 200) {
                    for (i = 0; i < quantidade_sala; i++) {
                        masmorra[fim_masmorra + i] = sala[i];
                    }

                    fim_masmorra = fim_masmorra + quantidade_sala;
                    quantidade_sala = 0;
                    pode_evitar = 0;
                    curou_turno = 0;

                    if (modo_jogo == 1) {
                        printf("Voce evitou a sala. As cartas foram para o fundo da Masmorra.\n\n");
                    } else {
                        printf("O computador evitou a sala. As cartas foram para o fundo da Masmorra.\n\n");
                    }
                } else {
                    printf("Nao ha espaco para colocar mais cartas no fim da Masmorra.\n");
                    jogo_ativo = 0;
                }
            } else {
                pode_evitar = 1;
                curou_turno = 0;
                jogadas_feitas = 0;
                cartas_para_resolver = 3;

                if (quantidade_sala < 4) {
                    cartas_para_resolver = quantidade_sala;
                }

                //resolve uma carta por vez e mostra a mesa atualizada
                while (jogadas_feitas < cartas_para_resolver && vida > 0 && quantidade_sala > 0 && jogo_ativo == 1) {
                    carta_escolhida = -1;
                    usar_arma = 0;

                    if (modo_jogo == 1) {
                        entrada_valida = 0;

                        while (entrada_valida == 0) {
                            printf("Escolha uma carta para resolver: ");
                            scanf("%d", &carta_escolhida);
                            carta_escolhida--;

                            if (carta_escolhida >= 0 && carta_escolhida < quantidade_sala) {
                                entrada_valida = 1;
                            } else {
                                printf("Carta invalida. Escolha uma carta que esta na sala.\n");
                            }
                        }

                        if (sala[carta_escolhida].naipe == 0 || sala[carta_escolhida].naipe == 1) {
                            if (arma.numero > 0 && sala[carta_escolhida].numero < limite_arma) {
                                entrada_valida = 0;

                                while (entrada_valida == 0) {
                                    printf("Voce quer usar a arma? 1 para sim, 2 para nao: ");
                                    scanf("%d", &usar_arma);

                                    if (usar_arma == 1 || usar_arma == 2) {
                                        entrada_valida = 1;
                                    } else {
                                        printf("Escolha um valor valido.\n");
                                    }
                                }

                                if (usar_arma == 2) {
                                    usar_arma = 0;
                                }
                            } else if (arma.numero > 0) {
                                printf("Sua arma nao pode combater esse monstro por causa do limite dela.\n");
                            }
                        }
                    } else {
                        instrucao_valida = 0;

                        while (instrucao_valida == 0) {
                            printf("Digite 1 para o computador fazer o proximo movimento: ");
                            scanf("%d", &instrucao);

                            if (instrucao == 1) {
                                instrucao_valida = 1;
                            } else {
                                printf("Instrucao invalida.\n");
                            }
                        }

                        achou_carta = 0;
                        maior_valor = -1;

                        for (i = 0; i < quantidade_sala; i++) {
                            if (sala[i].naipe == 3 && vida < 20 && curou_turno == 0) {
                                if (sala[i].numero > maior_valor) {
                                    maior_valor = sala[i].numero;
                                    indice_melhor_carta = i;
                                    achou_carta = 1;
                                }
                            }
                        }

                        if (achou_carta == 0) {
                            maior_valor = -1;

                            for (i = 0; i < quantidade_sala; i++) {
                                if (sala[i].naipe == 2 && sala[i].numero > arma.numero) {
                                    if (sala[i].numero > maior_valor) {
                                        maior_valor = sala[i].numero;
                                        indice_melhor_carta = i;
                                        achou_carta = 1;
                                    }
                                }
                            }
                        }

                        if (achou_carta == 0) {
                            menor_dano = 100;

                            for (i = 0; i < quantidade_sala; i++) {
                                if (sala[i].naipe == 0 || sala[i].naipe == 1) {
                                    dano = sala[i].numero;
                                    usar_arma = 0;

                                    if (arma.numero > 0 && sala[i].numero < limite_arma) {
                                        dano_com_arma = sala[i].numero - arma.numero;
                                        if (dano_com_arma < 0) {
                                            dano_com_arma = 0;
                                        }

                                        if (dano_com_arma < dano) {
                                            dano = dano_com_arma;
                                            usar_arma = 1;
                                        }
                                    }

                                    if (dano < menor_dano) {
                                        menor_dano = dano;
                                        indice_melhor_carta = i;
                                        achou_carta = 1;
                                    }
                                }
                            }
                        }

                        if (achou_carta == 0) {
                            maior_valor = -1;

                            for (i = 0; i < quantidade_sala; i++) {
                                if (sala[i].naipe == 2) {
                                    if (sala[i].numero > maior_valor) {
                                        maior_valor = sala[i].numero;
                                        indice_melhor_carta = i;
                                        achou_carta = 1;
                                    }
                                }
                            }
                        }

                        if (achou_carta == 0) {
                            indice_melhor_carta = 0;
                            achou_carta = 1;
                        }

                        carta_escolhida = indice_melhor_carta;
                    }

                    //agora a carta escolhida eh resolvida de acordo com o naipe
                    carta_jogada = sala[carta_escolhida];

                    if (carta_jogada.naipe == 0 || carta_jogada.naipe == 1) {
                        if (usar_arma == 1) {
                            dano = carta_jogada.numero - arma.numero;

                            if (dano < 0) {
                                dano = 0;
                            }

                            vida = vida - dano;
                            limite_arma = carta_jogada.numero;

                            if (modo_jogo == 1) {
                                printf("Voce enfrentou um monstro de valor %d usando a arma de valor %d.\n", carta_jogada.numero, arma.numero);
                            } else {
                                printf("O computador enfrentou um monstro de valor %d usando a arma de valor %d.\n", carta_jogada.numero, arma.numero);
                            }

                            printf("Dano recebido: %d.\n", dano);
                        } else {
                            vida = vida - carta_jogada.numero;

                            if (modo_jogo == 1) {
                                printf("Voce enfrentou um monstro de valor %d sem usar arma.\n", carta_jogada.numero);
                            } else {
                                printf("O computador enfrentou um monstro de valor %d sem usar arma.\n", carta_jogada.numero);
                            }

                            printf("Dano recebido: %d.\n", carta_jogada.numero);
                        }
                    } else if (carta_jogada.naipe == 2) {
                        arma = carta_jogada;
                        limite_arma = 15;

                        if (modo_jogo == 1) {
                            printf("Voce equipou uma arma de valor %d.\n", arma.numero);
                        } else {
                            printf("O computador equipou uma arma de valor %d.\n", arma.numero);
                        }
                    } else if (carta_jogada.naipe == 3) {
                        if (curou_turno == 0) {
                            vida = vida + carta_jogada.numero;
                            curou_turno = 1;

                            if (vida > 20) {
                                vida = 20;
                            }

                            if (modo_jogo == 1) {
                                printf("Voce usou uma pocao de valor %d.\n", carta_jogada.numero);
                            } else {
                                printf("O computador usou uma pocao de valor %d.\n", carta_jogada.numero);
                            }
                        } else {
                            if (modo_jogo == 1) {
                                printf("Voce pegou outra pocao no mesmo turno. Ela foi descartada sem curar.\n");
                            } else {
                                printf("O computador pegou outra pocao no mesmo turno. Ela foi descartada sem curar.\n");
                            }
                        }
                    }

                    //remove da sala a carta que acabou de ser resolvida
                    for (j = carta_escolhida; j < quantidade_sala - 1; j++) {
                        sala[j] = sala[j + 1];
                    }

                    quantidade_sala--;
                    jogadas_feitas++;

                    if (vida <= 0) {
                        jogo_ativo = 0;
                        pontuacao = vida;

                        for (i = 0; i < quantidade_sala; i++) {
                            if (sala[i].naipe == 0 || sala[i].naipe == 1) {
                                pontuacao = pontuacao - sala[i].numero;
                            }
                        }

                        for (i = pos_masmorra; i < fim_masmorra; i++) {
                            if (masmorra[i].naipe == 0 || masmorra[i].naipe == 1) {
                                pontuacao = pontuacao - masmorra[i].numero;
                            }
                        }

                        printf("\nGame over :(\n");
                        printf("Pontuacao: %d\n", pontuacao);
                    } else {
                        mostrar_mesa(sala, quantidade_sala, vida, arma, limite_arma, pode_evitar, modo_jogo, pos_masmorra, fim_masmorra);
                    }
                }
            }
        }
    }

    if (vitoria == 1 && vida > 0) {
        printf("Parabens, voce atravessou toda a Masmorra!\n");
        printf("Pontuacao: %d\n", vida);
    }

    return 0;
}

void mostrar_titulo() {
    printf("   _____                           _          _ \n");
    printf("  / ____|                         | |        | |\n");
    printf(" | (___   ___ ___  _   _ _ __   __| |_ __ ___| |\n");
    printf("  \\___ \\ / __/ _ \\| | | | '_ \\ / _` | '__/ _ \\ |\n");
    printf("  ____) | (_| (_) | |_| | | | | (_| | | |  __/ |\n");
    printf(" |_____/ \\___\\___/ \\__,_|_| |_|\\__,_|_|  \\___|_|\n");
    printf("                                                \n");
    printf("========================================================\n");
}

void montar_baralho(struct carta cartas[]) {
    //paus e espadas vão até A, ouros e copas vão até 10
    int indice_carta = 0;
    int naipe = 0;
    int numero = 0;
    int limite = 15;

    for (naipe = 0; naipe < 4; naipe++) {
        if (naipe > 1) {
            limite = 11;
        } else {
            limite = 15;
        }

        for (numero = 2; numero < limite; numero++) {
            cartas[indice_carta].numero = numero;
            cartas[indice_carta].naipe = naipe;
            indice_carta++;
        }
    }
}

void embaralhar(int indices[], int tamanho) {
    //troca posições aleatórias do vetor de índices
    int i = 0;
    int indice_troca = 0;
    int guardar = 0;

    for (i = 0; i < tamanho; i++) {
        indice_troca = rand() % tamanho;
        guardar = indices[i];
        indices[i] = indices[indice_troca];
        indices[indice_troca] = guardar;
    }
}

void mostrar_carta(struct carta carta_atual, int indice) {
    if (carta_atual.naipe == 0) {
        printf(".--------.\n");
        printf("| P.--.  |\n");
        printf("|  :():  |\n");
        printf("|  ()()  |\n");
        printf("|  '--'P |\n");
        printf("`--------'\n");
    } else if (carta_atual.naipe == 1) {
        printf(".--------.\n");
        printf("| E.--.  |\n");
        printf("|  :/\\:  |\n");
        printf("|  (__)  |\n");
        printf("|  '--'E |\n");
        printf("`--------'\n");
    } else if (carta_atual.naipe == 2) {
        printf(".--------.\n");
        printf("| O.--.  |\n");
        printf("|  :/\\:  |\n");
        printf("|  :\\/:  |\n");
        printf("|  '--'O |\n");
        printf("`--------'\n");
    } else if (carta_atual.naipe == 3) {
        printf(".--------.\n");
        printf("| C.--.  |\n");
        printf("|  (\\/)  |\n");
        printf("|  :\\/:  |\n");
        printf("|  '--'C |\n");
        printf("`--------'\n");
    }

    printf("[%d]: ", indice + 1);

    if (carta_atual.numero == 11) {
        printf("J");
    } else if (carta_atual.numero == 12) {
        printf("Q");
    } else if (carta_atual.numero == 13) {
        printf("K");
    } else if (carta_atual.numero == 14) {
        printf("A");
    } else {
        printf("%d", carta_atual.numero);
    }

    if (carta_atual.naipe == 0) {
        printf(" de Paus");
    } else if (carta_atual.naipe == 1) {
        printf(" de Espadas");
    } else if (carta_atual.naipe == 2) {
        printf(" de Ouros");
    } else if (carta_atual.naipe == 3) {
        printf(" de Copas");
    }

    printf("\n-------------------\n");
}

void mostrar_mesa(struct carta sala[], int quantidade_sala, int vida, struct carta arma, int limite_arma, int pode_evitar, int modo_jogo, int pos_masmorra, int fim_masmorra) {
    //mostra tudo que a pessoa precisa saber para acompanhar a partida
    int i = 0;

    printf("\n========================= MESA =========================\n");

    if (modo_jogo == 1) {
        printf("Jogador atual: Pessoa\n");
    } else {
        printf("Jogador atual: Computador\n");
    }

    printf("Vida: %d\n", vida);
    printf("Cartas restantes na Masmorra: %d\n", fim_masmorra - pos_masmorra);

    if (arma.numero == 0) {
        printf("Arma equipada: nenhuma\n");
        printf("Limite da arma: nenhum\n");
    } else {
        printf("Arma equipada: %d de Ouros\n", arma.numero);

        if (limite_arma == 15) {
            printf("Limite da arma: sem limite\n");
        } else {
            printf("Limite da arma: monstros menores que %d\n", limite_arma);
        }
    }

    if (pode_evitar == 1) {
        printf("Pode evitar a sala: sim\n");
    } else {
        printf("Pode evitar a sala: nao\n");
    }

    printf("\nSala atual:\n");

    if (quantidade_sala == 0) {
        printf("Sala vazia.\n");
    }

    for (i = 0; i < quantidade_sala; i++) {
        mostrar_carta(sala[i], i);
    }

    printf("========================================================\n\n");
}
