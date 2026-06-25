# Com o objetivo de promover boas práticas de programação, é expressamente proibida a

utilização dos seguintes recursos de programação: comando goto, comando continue, co-
mando break e variáveis globais. É permitido o uso do comando break somente junto ao comando

switch-case. Se você não sabe o que são estes recursos, pode perguntar à professora e/ou aos moni-
tores como eles funcionam, apenas por curiosidade. Também é proibido: o uso do comando #define

para definir uma sequência de comandos, a definição de uma função dentro de outra função, o uso
de laços com condições que são sempre verdadeiras (como while (1) ou while (x == x)) e o uso
de comandos/recursos que não foram vistos em aula. O uso de recursos proibidos acarretará
em nota 0 (zero) no trabalho.

Na versão em que o computador joga sozinho, as jogadas são escolhidas pelo próprio programa. Depois que a Mesa é mostrada na tela, o programa espera a pessoa digitar uma instrução para o computador fazer o próximo movimento. Isso serve para que quem está assistindo consiga acompanhar o que está acontecendo, em vez do jogo acontecer tudo de uma vez.

Primeiro, o computador verifica se vale a pena evitar a Sala. Para fazer isso, ele olha as cartas que estão na Sala e calcula uma estimativa de dano. Ele procura as cartas que são monstros, ou seja, paus e espadas, e vê quanto de vida perderia ao enfrentar esses monstros. Se ele tiver uma arma equipada e essa arma puder ser usada contra o monstro, o dano considerado é o valor do monstro menos o valor da arma. Se esse valor ficar negativo, o dano vira zero. Se a estimativa de dano for maior ou igual à vida atual e ainda for possível evitar a Sala, o computador evita a Sala. Nesse caso, as cartas da Sala vão para o fundo da Masmorra.

Se o computador não evitar a Sala, ele começa a escolher as cartas com que vai interagir. A escolha segue uma ordem de prioridade. Primeiro, ele procura uma poção de copas, mas só usa a poção se a vida estiver menor que 20 e se ainda não tiver usado outra poção naquele turno. Se tiver mais de uma poção disponível, ele escolhe a de maior valor, porque é a que recupera mais vida.

Se não tiver poção útil, o computador procura uma arma de ouros. Ele dá preferência para armas melhores que a arma atual. Então, se aparecer uma arma com valor maior do que a arma equipada, ele escolhe essa nova arma. Quando uma nova arma é equipada, a arma anterior é descartada e o limite da arma volta a ficar sem limite, porque ela ainda não foi usada contra nenhum monstro.

Se não tiver poção útil nem arma melhor, o computador procura um monstro para enfrentar. Nessa parte, ele tenta escolher o monstro que causa o menor dano possível. Para cada monstro da Sala, o programa calcula quanto dano ele receberia lutando sem arma. Depois, se tiver arma equipada e se o valor do monstro for menor que o limite da arma, ele também calcula quanto dano receberia usando a arma. Se usar a arma causar menos dano, ele escolhe usar a arma. Se não compensar, ele luta sem arma.

Depois que o computador escolhe uma carta, o programa resolve a jogada. Se a carta for monstro, ele perde vida de acordo com o combate. Se ele usou arma, o limite da arma passa a ser o valor daquele monstro, porque a partir daí a arma só pode ser usada contra monstros menores. Se a carta for arma, ela vira a nova arma equipada. Se a carta for poção, ela recupera vida, mas sem deixar passar de 20. Se uma poção já tiver sido usada no mesmo turno, a próxima poção é descartada sem curar.

Depois de cada jogada, o programa mostra o que aconteceu e atualiza a Mesa. Então aparecem novamente a vida atual, a arma equipada, o limite da arma, a Sala atual, a Masmorra e se ainda é possível evitar a Sala. Se a vida chegar a 0 ou menos, o computador perde e o jogo acaba. Se a Masmorra acabar e a vida ainda for maior que 0, o computador vence.

Então, resumindo, o computador joga olhando a situação atual da Mesa e escolhendo uma jogada válida. Ele tenta evitar a Sala quando ela parece perigosa demais, usa poções quando precisa curar, equipa armas melhores quando aparecem e enfrenta os monstros tentando receber o menor dano possível.
