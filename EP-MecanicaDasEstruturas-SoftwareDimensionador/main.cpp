#include <iostream>
#include "stdio.h"
#include "Pilar.h"
#include "Viga.h"
#include "Laje.h"

using namespace std;

int main()
{
    Pilar **pilares = new Pilar* [20];
    Viga **vigas = new Viga* [20];
    Laje **lajes = new Laje* [20];

    float dimX, dimY; /*dimensões da área de influência dos pilares*/
    float X, Y; /*dimensões totais*/
    float Xo, Yo, Xf, Yf;
    float x, y; // dimensões da LAJE

    int numPilaresX, numPilaresY;
    int contadorAndares;
    int numAndares = 0;
    int identificacao;
    int numVigas = 0;
    int numLajes = 0;

    char resposta;
    char tipo;

    printf("\n+--------------------------+");
    printf("\n|                          |");
    printf("\n|         PEF              |");
    printf("\n|                          |");
    printf("\n+--------------------------+");

    printf("\n\nBem vindo ao dimensionador de estruturas!");

    printf("\n\n ATENÇÃO: ESSE SOFTWARE SERVE APENAS PARA PRÉ-DIMENSIONAR ESTRUTURAS DE CONCRETO, MODULARES E SIMÉTRICAS.");
    printf("\n ATENÇÃO: Para o dimensionamento das lajes, considera-se que nenhuma está engastada, apenas apoiada nas vigas.");
    printf("\n INFO: fck = 2.5 kN/cm²");

    printf("\n\n\n Primeiramente, informe as dimensões X e Y, respectivamente, totais da edificação: ");
    scanf("%f", &X); scanf("%f", &Y);

    printf("\n Agora, informe o número de Pilares em X e em Y: ");
    scanf("%d", &numPilaresX); scanf("%d", &numPilaresY);

    printf("\n Quantos andares tem a edificação?: ");
    scanf("%d", &numAndares);

    for(contadorAndares = 0; contadorAndares < numAndares+1; contadorAndares++){

        printf("\n Deseja adicionar um andar na edificação? type y or n");

        fflush(stdin);

        scanf(" \n %c", &resposta);

        if( resposta == 'y'){


            printf("\n Agora, vamos adicionar todos os pilares nesse andar.");

            for(int i = 0; i < numPilaresX * numPilaresY; i++){

                //Lampada *l1 = new Lampada;

                printf("\n Digite o tipo de pilar! 'c' = canto, 'e' = extremidade (sem ser canto), 'm' = meio ");

                fflush(stdin);

                scanf("\n %c", &tipo);

                /*Verificar como criar objeto e passar ele para um vetor*/

                /*Pilar listaPilares[i] = new Pilar(numPilaresX, numPilaresY, tipo, X, Y, (numAndares - contadorAndares));*/

                /*Sensor	**sensores =	new	Sensor*[maximo];*/

                pilares[i]	=	new	Pilar(numPilaresX, numPilaresY, tipo, i, X, Y, (numAndares - contadorAndares));

            }

            printf("\n Agora, vamos adicionar todas as vigas! Insira o número total de vigas que se quer adicionar nesse andar: ");
            scanf("%d", &numVigas);

            for(int i = 0; i < numVigas; i++){

                printf("\n Digite as posições iniciais e finais da viga conforme o requerido: (Xo, Yo) e (Xf, Yf).");
                scanf("%f", &Xo);
                scanf("%f", &Xf);
                scanf("%f", &Yo);
                scanf("%f", &Yf);

                printf("\n Digite o tipo de Viga. Tramo interno = 'i'. Balanço = 'b'. Tramo externo = 'e'");

                fflush(stdin);

                scanf("\n%c", &tipo);

                vigas[i]   =  new	Viga(Xo, Yo, Xf, Yf, tipo);
               // Viga listaVigas[i] = new Viga(Xo, Yo, Xf, Yf, tipo)

            }

            printf("\n Agora, vamos adicionar todas as lajes! Insira o número total de lajes que se quer adicionar nesse andar: ");
            scanf("%d", &numLajes);

            for(int i = 0; i < numLajes; i++){

                printf("\n Digite os cumprimentos X e Y, respectivamente, da laje que desejas adicionar nesse andar: ");

                scanf("%f", &x); scanf("%f", &y);

                lajes[i] = new Laje(x, y, i);

            }

        }

        if(resposta == 'n'){

            for(int c = 0; c < numAndares; c++){

            printf("\n\n\n ------------------------- Exibição dos resultados ---------------------");

            printf("\n ------ Exibição do   >>>>> %d andar <<<<<  ---------  " , c);

            printf("\n \n --- PILARES ----");

                for(int i = 0; i < numPilaresX * numPilaresY; i++){

                    printf("\n >> Pilar ( %d ) << de secção quadrada. Dimensão: %f", pilares[i]->identificacao, 10 * pilares[i]->obterDimensao());

                }

            printf("\n \n --- VIGAS ----");

                 for(int i = 0; i < numVigas; i++){

                    printf("\n >> Viga ( %d ) << Cumprimento: %f. Espessura dimensionada: %f", i, vigas[i]->obterComprimento(), vigas[i]->obterEspessura());

                }

            printf("\n \n --- LAJES ----");

                for(int i = 0; i < numLajes; i++){

                    printf("\n >> Laje ( %d ) << Espessura: %f", lajes[i]->identificacao, lajes[i]->obterAltura());

                }

            }

       }

    }

    printf("\n\n\n");

    printf("\n+-------------------------------------------------------+");
    printf("\n|                                                       |");
    printf("\n|         OBRIGADO POR USAR O DIMENSIONADOR             |");
    printf("\n|                                                       |");
    printf("\n+-------------------------------------------------------+");
    printf("\n");

    return 0;
}
