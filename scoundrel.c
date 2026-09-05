/*
Vou explicar de forma breve como o código funciona com um textinho aqui em cima, porque eu me perdi com os comentários (muita coisa pra explicar)

O jogo começa assim: Um struct que define o que uma carta armazena é criado, depois um array desse scruct é criado. Esse array contém as cartas
numeradas de 2 a 14 para paus e espadas, e de 2 a 10 para ouros e copas. Os naipes são definidos por número de 0 a 3, 0 = paus, 1 = espadas, 2 =
ouros, 3 = copas. Em seguida, é criado um array com números aleatórios sem repetição, usando uma função que faz um shuffle no array sem deixar
repetir nenhum número. A função é definida abaixo do int main(). Os números aleatórios contidos nesse array são utilizados como índices para re-
ordenar o array de struct que continha as cartas. Agora vem o loop principal, que vai rodar até que a posição das cartas atuais do baralho seja
maior que o tamanho do baralho em si. Esses índices são definidos por pos_cartas e fim_bar, pos_cartas define em qual posição estamos no baralho
quantas cartas a gente já passou. fim_bar define onde é o fim do baralho. Por padrão, o fim é na carta 44, mas se o jogador pular uma sala, o fim
do baralho é estendido em 4 cartas, afinal elas vão pro fim. No início do loop principal ele verifica se a jogada é válida, usando o valor de 
"correto", em seguida as cartas retiradas do baralho são colocadas na mão do jogador, na primeira vez são retiradas 4 cartas, nas demais vezes, 3
porque sempre sobra uma carta da sala anterior. A não ser que o jogador pule a sala, ai ele vai retirar 4 cartas. Tem a varivael indice que serve
pra sempre variar os valores do indice array que armazena as cartas atuais entre 0 e 3, ou 1 e 3 pra não sobrescrever a carta que fica sobrando.
O código em seguida imprime as cartas e passa para a verificação de valores que o usuário inserir. Se o usuário inserir o índice uma carta que é
um monstro, o programa subtrai a vida do monstro da vida do jogador, se ele tivere uma arma subtrai a arma da vida do monstro. Se a carta for
ouros, ele seleciona a carta como arma. Se for copas, ele soma na vida, tomando cuidado pra não passar de 20. Se a vida for menor que 20, acabou
o jogo. Depois, para sabermos com quais cartas o usuário interagiu, as cartas com as quais o usuário interage tem seu número trocado por 0. Depo-
is o programa seta todas as variáveis necessárias para o funcionamento para o seu devido valor, tipo a variável pos_cartas é incrementada em 4, 
a variável que define se o usuário pulou a sala vira zero etc. E por fim ele identifica quais cartas tem numero zero, a que não tiver é a que o
usuário não interagiu, então ela vai pra proxima sala. Caso o usuário tenha escolhido pular, um loop for varre o array de cartas atuais e coloca
elas no fim do baralho, e estende o fim do baralho. Caso os valores que o usuário inseriu sejam inválidos, o programa vai ficar pedindo pra inse-
rir o valor até ele colocar um valor certo. Se pos_cartas for maior que fim_bar, pronto, o usuário ganhou, porque passou do fim do baralho. 
Quando ele ganha, o programa acaba e a vida do jogador é a pontuação. Esqueci de falar antes, mas caso o jogador perca, o programa varre o bara-
lho para identificar monstros e subtrair a vida de todos eles da vida do usuário. Essa é a pontuação caso você perca.

Como Foi difícil fazer esse trabalho, meu Deus.

Comentário adicional:
O código não ficou tão bom quanto eu gostaria. Mesmo eu dando meu melhor. Só que eu não usei ChatGPT, não usei Gemini, não usei deepseek nem ne-
-nhuma IA. Eu esto falando isso porque acho que esse mérito deveria ser considerado. Boa parte da sala nem vai ler o enunciado, só vai jogar o
PDF da atividade em alguma IA copiar e colar o código que a IA fizer e te entregar. O problema é que esses códigos feitos por IA vão ficar per-
-feitos, super otimizados, indentados perfeitamente, etc. A qualidade do código médio que a sala vai entregar vai subir, MUITO, e meu código,
na contramão, não é perfeito. Comparado a um código feito por IA, ou com ajuda de IA, meu código deve ter ficado tosco. Mas peço que seja consi-
-derado meu esforço. Peço que seja considerado que o código foi feito 100% por um ser humano (eu). Não quero nota adicional por isso, só quero
não perder nota porque o código médio da sala ficou perfeito, porque boa parte das pessoas usou IA.
*/

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
    arma.numero = 0; // Inicializando a arma em zero
    
    int indice_carta = 0, cont = 15, vida = 20, pos_cartas = 0, indice = 0, fim_bar = 44, pulou = 0, escolha1, escolha2, indices_emb[44];
    int avanco = 4; // Define o tanto de cartas que são retiradas do baralho
    int curou = 0; // Bool para verificar se a pessoa acabou de curar
    int correto = 0; // Isso é pra verificar se a pessoa inseriu valores válidos
    int pontuacao = 0;
    int inicio = 1; // Mostra que é o início do jogo
    int monstro = 15; // Define quais monstros o jogador pode matar com a arma

    char nome_naipe[10];

    printf("   _____                           _          _ \n");
    printf("  / ____|                         | |        | |\n");
    printf(" | (___   ___ ___  _   _ _ __   __| |_ __ ___| |\n");
    printf("  \\___ \\ / __/ _ \\| | | | '_ \\ / _` | '__/ _ \\ |\n");
    printf("  ____) | (_| (_) | |_| | | | | (_| | | |  __/ |\n");
    printf(" |_____/ \\___\\___/ \\__,_|_| |_|\\__,_|_|  \\___|_|\n");
    printf("                                                \n");
    printf("========================================================\n");

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

    //========================= CRIANDO INDICES ALEATORIOS E USANDO ELES PARA EMBARALHAR O ARRAY CARTAS_EMB =========================

    for (int i = 0; i < 44; i++) {
        indices_emb[i] = i;
    }

    embaralhar(indices_emb, 44);

    for (int i = 0; i < 44; i++) {
        cartas_emb[indices_emb[i]] = cartas[i];
    }

    //========================= PARTE DO JOGO: LOOP PRINCIPAL =========================

    while (pos_cartas < fim_bar) {

        // esse if correto == 0 serve para verificar se a jogada é válida. Ele só irá imprimiar a sala se a jogada for válida
        if (correto == 0) {

            // Colocando todas as cartas da sala atual em um array
            for (int i = pos_cartas; i < pos_cartas+avanco; i++) {
                // Inserindo as cartas do baralho embaralhado em cartas_atuais
                cartas_atuais[indice] = cartas_emb[i];

                // Mudando o índice do array cartas_atuais
                indice++;
            }

            // Imprimindo o nome dos naipes de acordo com o valor de 0 a 3
            // Imprimindo as cartas
            for (int i = 0; i < 4; i++) {
                if (cartas_atuais[i].naipe == 0) {
                    strcpy(nome_naipe, "Paus");
                } else if (cartas_atuais[i].naipe == 1) {
                    strcpy(nome_naipe, "Espadas");
                } else if (cartas_atuais[i].naipe == 2) {
                    strcpy(nome_naipe, "Ouros");
                } else if (cartas_atuais[i].naipe == 3) {
                    strcpy(nome_naipe, "Copas");
                }

                if (cartas_atuais[i].naipe == 0) {
                    printf(".--------.\n"
                           "| P.--.  |\n"
                           "|  :():  |\n"
                           "|  ()()  |\n"
                           "|  '--'P |\n"
                           "`--------'\n");

                    printf("\n[%d]: %d de %s", i+1, cartas_atuais[i].numero, nome_naipe);
                    printf("\n-------------------\n");
                } else if (cartas_atuais[i].naipe == 1) {
                    printf(".--------.\n"
                           "| E.--.  |\n"
                           "|  :/\\: |\n"
                           "|  (__)  |\n"
                           "|  '--'E |\n"
                           "`--------'\n");

                    printf("\n[%d]: %d de %s", i+1, cartas_atuais[i].numero, nome_naipe);
                    printf("\n-------------------\n");
                } else if (cartas_atuais[i].naipe == 2) {
                    printf(".--------.\n"
                           "| O.--.  |\n"
                           "|  :/\\:  |\n"
                           "|  :\\/:  |\n"
                           "|  '--'O |\n"
                           "`--------'\n");

                    printf("\n[%d]: %d de %s", i+1, cartas_atuais[i].numero, nome_naipe);
                    printf("\n-------------------\n");
                } else if (cartas_atuais[i].naipe == 3) {
                    printf(".--------.\n"
                           "| C.--.  |\n"
                           "|  (\\/)  |\n"
                           "|  :\\/:  |\n"
                           "|  '--'C |\n"
                           "`--------'\n");

                    printf("\n[%d]: %d de %s", i+1, cartas_atuais[i].numero, nome_naipe);
                    printf("\n-------------------\n");
                }
            }

            printf("\nVida: %d || Arma: %d\n", vida, arma.numero);
        }

        printf("=================================================================\n");
        printf("Digite 1 para permanecer na sala ou 2 para pular: ");
        scanf("%d", &escolha1);

        //========================= PEGANDO INPUT DE CARTAS ESCOLHIDAS =========================

        if (escolha1 == 1) {
            printf("=================================================================\n");
            printf("Escolha com quais cartas interagir: ");
            
            for (int i = 0; i < 3; i++) { // 3 iterações pra selecionar 3 cartas
                scanf("%d", &escolha2);
                escolha2--; // Para funcionar como índice do array subtraimos 1 (afinal array começa em zero)

                if (escolha2 >= 0 && escolha2 < 4) {
                    if (cartas_atuais[escolha2].numero == 0) {
                        printf("=================================================================\n");
                        printf("Carta ja selecionada.\n");
                        return 0;
                    } else if (cartas_atuais[escolha2].naipe == 0) {
                        if (arma.numero == 0) {
                            vida -= cartas_atuais[escolha2].numero;
                        } else if (arma.numero != 0) {
                            if (cartas_atuais[escolha2].numero < monstro) {
                                monstro = cartas_atuais[escolha2].numero;

                                if (cartas_atuais[escolha2].numero - arma.numero >= 0) {
                                    vida -= cartas_atuais[escolha2].numero - arma.numero;
                                } else if (cartas_atuais[escolha2].numero - arma.numero < 0) {
                                    vida = vida;
                                }
                            } else {
                                vida -= cartas_atuais[escolha2].numero;
                            }
                        }
                    } else if (cartas_atuais[escolha2].naipe == 1) {
                        if (arma.numero == 0) {
                            vida -= cartas_atuais[escolha2].numero;
                        } else if (arma.numero != 0) {
                            if (cartas_atuais[escolha2].numero < monstro) {
                                monstro = cartas_atuais[escolha2].numero;

                                if (cartas_atuais[escolha2].numero - arma.numero >= 0) {
                                    vida -= cartas_atuais[escolha2].numero - arma.numero;
                                } else if (cartas_atuais[escolha2].numero - arma.numero < 0) {
                                    vida = vida;
                                }
                            } else {
                                vida -= cartas_atuais[escolha2].numero;
                            }
                        }
                    } else if (cartas_atuais[escolha2].naipe == 2) {
                        arma = cartas_atuais[escolha2];
                        monstro = 15;
                    } else if (cartas_atuais[escolha2].naipe == 3) {
                        if (curou == 0) {
                            vida += cartas_atuais[escolha2].numero;
                            curou = 1;
                        } else {
                            vida = vida;
                        }

                        if (vida > 20) {
                            vida = 20;
                        }
                    }
                    
                    // =========================================== Caso o jogador perca =========================================== 
                    if (vida < 1) {
                        pontuacao = vida;
                        
                        printf("Game over :(\n");

                        for (int i = pos_cartas+indice; i < fim_bar; i++) {
                            if (cartas_emb[i].naipe == 0 || cartas_emb[i].naipe == 1) {
                                pontuacao = pontuacao - cartas_emb[i].numero;
                            }
                        } 

                        printf("Pontuação: %d", pontuacao);
                        return 0;
                    }

                    cartas_atuais[escolha2].numero = 0; // Pra detectar que a carta foi escolhida

                    // Printando a vida e a arma do jogador, exceto para a última iteração do loop, porque ficaria repetitivo
                    if (i < 2) {
                        printf("=================================================================\n");
                        printf("Vida: %d || Arma: %d\n", vida, arma.numero);
                    } else {
                        printf("=================================================================\n");
                    }
                } else {
                    i--;
                    printf("=================================================================\n");
                    printf("Escolha um valor valido.\n");
                }
            }

            pulou = 0; // Define que não pulamos a sala

            // Define que agora vamos puxar só 3 cartas do deck
            if (inicio == 1) {
                inicio = 0;
                avanco = 4;
            } else {
                avanco = 3;
            }

            indice = 1; // Fazemos isso pra não sobrescrever a primeira carta em cartas_atuais
            correto = 0;

            // Definimos que a carta que não foi usada vai pro começo da prox. sala
            for (int i = 0; i < 4; i++) { 
                if (cartas_atuais[i].numero != 0) {
                    cartas_atuais[0] = cartas_atuais[i]; 
                }
            }

            curou = 0; // Agora pode curar de novo
            pos_cartas += avanco; // Avançando no baralho. O array de cartas atuais agora irá conter 4 cartas a frente das que ele continha
        } else if (escolha1 == 2 && pulou == 0) {
            indice = 0;

            for (int i = fim_bar; i < fim_bar+4; i++) {
                cartas_emb[i] = cartas_atuais[indice];
                indice++;
            }

            fim_bar += 4; // Aumenta o fim do baralho e as cartas que foram retiradas vão para o fim
            pulou = 1; // Define que pulamos a sala
            avanco = 4; // Define que serão retiradas 4 cartas do baralho (afinal jogamos as 4 cartas fora)

            curou = 0; // Agora pode curar de novo
            pos_cartas += avanco; //Avançando no baralho

            correto = 0; // Mostra que o jogador fez uma escolha válida
            indice = 0;
        } else  if (escolha1 > 2 || escolha1 < 1) {
            printf("=================================================================\n");
            printf("Escolha um valor valido.\n");
            correto = 1;
        } else if (pulou == 1) {
            printf("=================================================================\n");
            printf("Nao pode pular essa sala pois a anterior ja foi pulada!\n");
            correto = 1;
        }
    }

    printf("Parabéns, você ganhou!");
    printf("Pontuacao: %d", vida);

    return 0;
}

// Criando a função que embaralha
void embaralhar(int array[], int tamanho) {
  // Semeando número aleatório
  srand(time(NULL));
  
  // Trocando de ordem
  for (int i = 0; i < tamanho; i++) {
    // Achando aleatoriamente um índice de 0 até "tamanho"
    int troca_indice = rand() % tamanho;
    
    // Troca de posição do que está no índice i com o que está em troca_indice
    int temp = array[i];
    array[i] = array[troca_indice];
    array[troca_indice] = temp;
  }
  
}
