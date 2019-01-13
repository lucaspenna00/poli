#include <stdio.h>
#include <stdlib.h>
/********************************************************************/
/**                                                                                 **/
/**   Lucas Penna Saraiva         Número USP 9770566   **/
/**   Exercício-Programa 01                                           **/
/**   Professor: Alair                                                      **/
/**   Turma: 03                                                              **/
/**                                                                                **/
/********************************************************************/

int main()
{   int n100, /* nX são as variáveis que armazenam o número de notas x */
        n50,
        n10,
        n5,
        n1,
        nop, /* nop é a variável que armazena o número de operações desejadas pelo usuário*/
        op, /* op é a variável que armazena as operações saque = 0 e depósito = 1 */
        cont, /*cont é a variável que armazena o contador de operações dentro do laço*/
        saq, /*saq é a variável que armazena o valor do saque desejado*/
        dep100, /*depX é a variável que armazena o numero de notas de cada valor que se quer depositar */
        dep50,
        dep10,
        dep5,
        dep1,
        n100saq, /* nXsaq são as variáveis que armazenam o número de notas sacadas */
        n50saq,
        n10saq,
        n5saq,
        n1saq,
        n100i, /* variaveis que armazenam o valor inicial das notas */
        n50i,
        n10i,
        n5i,
        n1i;

    printf("\nDigite a quantidade inicial de notas de 100, 50, 10, 5 e 1 reais: ");
    scanf("%d", &n100);
    scanf("%d", &n50);
    scanf("%d", &n10);
    scanf("%d", &n5);
    scanf("%d", &n1);

    printf("\nBem vindo ao Banco Adelmo! ");
    printf("\n* * * * * * * * * * * * * * * * * * *");
    printf("\nQuantas operacoes deseja realizar?");
    scanf("%d", &nop);

    for (cont=0; cont<nop; cont++) {

            printf("\nQual operacao deseja efetuar? (0=saque, 1=deposito)");
            scanf("\n%d", &op);

            /* inicializadores das variáveis */

            n100saq = 0;
            n50saq = 0;
            n10saq = 0;
            n5saq = 0;
            n1saq = 0;
            n100i = n100;
            n50i = n50;
            n10i = n10;
            n5i = n5;
            n1i = n1;

        if(op == 0) {

                    printf("\nQuantos reais deseja sacar? ");
                    scanf("%d", &saq);

                    /*Aqui começa um série de laços que alterarão as variáveis saq, número de notas sacadas e número de notas disponíveis! */
                    /*Para executar os laços, existem condições iniciais que devem ser obedecidas. Caso as condições não são atendidas,
                    o programa tentará executar o laço seguinte e assim sucessivamente. */

                        while((saq>=100)&&(n100>0)){
                            saq = saq - 100;
                            n100--;
                            n100saq++;}

                        while((saq>=50)&&(n50>0)){
                            saq = saq - 50;
                            n50--;
                            n50saq++;}

                        while((saq>=10)&&(n10>0)){
                            saq = saq - 10;
                            n10--;
                            n10saq++;}

                        while((saq>=5)&&(n5>0)){
                            saq = saq - 5;
                            n5--;
                            n5saq++;}

                        while((saq>=1)&&(n1>0)){
                            saq = saq - 1;
                            n1--;
                            n1saq++;}

                     /*Note que ao final dos laços, se a variável "saq" for igual a zero, significa que houve notas o suficiente para se executar o saque,
                     sendo essa uma condição essencial para sinalizar que o saque foi realizado com sucesso */

                            if(saq != 0){
                                n100 = n100i; /*note que aqui as variáveis que armazenam o número de notas retornam ao seu valor inicial caso a variável saq != 0*/
                                n50 = n50i;
                                n10 = n10i;
                                n5 = n5i;
                                n1 = n1i;
                                printf("Saque nao efetuado!");}

                            else {
                                printf("\nSaque efetuado: %d %d %d %d %d", n100saq, n50saq, n10saq, n5saq, n1saq);
                                printf("\nNotas disponiveis: %d %d %d %d %d", n100, n50, n10, n5, n1);} /*note que aqui as variáveis que armazenam o número de notas tem seu valor alterado, visto que o saque deu certo)*/
        }

        if(op == 1) {

                    printf("\nDigite a quantidade de notas de 100, 50, 10, 5 e 1 sendo depositadas: ");
                    scanf("\n%d", &dep100);
                    scanf("\n%d", &dep50);
                    scanf("\n%d", &dep10);
                    scanf("\n%d", &dep5);
                    scanf("\n%d", &dep1);

                    n100 = n100 + dep100;
                    n50 = n50 + dep50;
                    n10 = n10 + dep10;
                    n5 = n5 + dep5;
                    n1 = n1 + dep1;

                    printf("\nDeposito efetuado! \nNotas disponiveis: %d %d %d %d %d", n100, n50, n10, n5, n1);}
    }
    printf("O Banco Adelmo agradece a sua visita e deseja reve-lo em breve!");
    return 0;
    }
