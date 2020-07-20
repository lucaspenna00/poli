#ifndef _LINEARALGEBRA_H_
#define _LINEARALGEBRA_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

#define MAX_MATRIX 10000
#define EPSLON 0.00001
#define ITMAX 100

using namespace std;

void multiplyMatrices(float firstMatrix[MAX_MATRIX][MAX_MATRIX], float secondMatrix[MAX_MATRIX][MAX_MATRIX], float mult[MAX_MATRIX][MAX_MATRIX],
	/*
	Essa função recebe três matrizes. Multiplica as duas primeiras
	e armazena na terceira matriz
	*/

	int rowFirst, int columnFirst, int rowSecond, int columnSecond)
{
	int i, j, k;

	// Initializing elements of matrix mult to 0.
	for(i = 0; i < rowFirst; ++i)
	{
		for(j = 0; j < columnSecond; ++j)
		{
			mult[i][j] = 0;
		}
	}

	// Multiplying matrix firstMatrix and secondMatrix and storing in array mult.
	for(i = 0; i < rowFirst; ++i)
	{
		for(j = 0; j < columnSecond; ++j)
		{
			for(k=0; k<columnFirst; ++k)
			{
				mult[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
			}
		}
	}
}

void transposeMatrix(float A[MAX_MATRIX][MAX_MATRIX], float A_transpose[MAX_MATRIX][MAX_MATRIX], int num_Rows, int num_Columns){

/* Essa função recebe duas matrizes: a primeira é a original. A segunda é a transposta*/

	for(int i = 0; i < num_Columns; i++){

		for(int j = 0; j < num_Rows; j++){

			A_transpose[i][j] = A[j][i];
		}

	}
}


void rotGivens_Matrix(float W[MAX_MATRIX][MAX_MATRIX], int num_Rows, int num_Columns, int i, int j, float c, float s){

/*Essa função recebe uma matriz e aplica a transformação de Givens nela.
Ref. Enunciado do problema
*/

	float aux;

	for(int n = 0; n < num_Columns; n++){

		aux = c*W[i][n] - s*W[j][n];
		W[j][n] = s*W[i][n] + c*W[j][n];
		W[i][n] = aux;
	}
}

void rotGivens_Vector(float W[MAX_MATRIX][1], int i, int j, float c, float s){
	/*Essa função recebe um vetor e aplica a transformação de Givens nele.
	Ref. Enunciado do problema
	*/
		float aux;

		aux = c*W[i][0] - s*W[j][0];
		W[j][0] = s*W[i][0] + c*W[j][0];
		W[i][0] = aux;
}

void calculateCS(float *c, float *s, float A[MAX_MATRIX][MAX_MATRIX], int i, int j, int k)
{

	/*Essa função calcula os valores de seno e cosseno a serem utilizados na rotação
	de forma a zerar os elementos da matrix A passada como argumento
	Ref. Enunciado do problema.
	*/

	float t;
	float c_linha, s_linha;

	if (fabs(A[i][k]) > fabs(A[j][k])){

		t = -(A[j][k]/A[i][k]);

		*c = 1/(sqrt(1+t*t));

		c_linha = *c;

		*s = c_linha * t;
	}
	else{

		t = -(A[i][k])/(A[j][k]);

		*s = 1/(sqrt(1+t*t));

		s_linha = *s;

		*c = s_linha * t;
	}
}

void normalizeMatrix(float W[MAX_MATRIX][MAX_MATRIX], int num_Rows_W, int num_Columns_W){

	/*Função auxiliar da fatoração WH. Essa função normaliza a matrix baseada na norma de Frobenius
	descrita no enunciado, no item explicativo da tarefa de fatoração WH*/

	float soma;

	//for each column
	for(int j = 0; j < num_Columns_W; j++){

		soma = 0.0;

		for(int n = 0; n < num_Rows_W; n++){

			soma = soma + (W[n][j]*W[n][j]);
		}

			for(int i = 0; i < num_Rows_W; i++){

				//calcular a soma

				W[i][j] = W[i][j]/sqrt(soma);
			}
	}
}

void redefine(float W[MAX_MATRIX][MAX_MATRIX], int num_Rows_W, int num_Columns_W){

	/*
	Essa função pega uma matriz A e retorna ela redefinida. Ou seja, calcula o
	maximo entre Aij e zero.
	*/

	for(int i = 0; i<num_Rows_W; i++){

		for(int j = 0; j<num_Columns_W; j++){

			if(W[i][j] < 0.0){

				W[i][j] = 0.0;

			}
		}
	}
}

void factorizationQR(float A[MAX_MATRIX][MAX_MATRIX], float B[MAX_MATRIX][1], float Result[MAX_MATRIX][1], int num_Rows, int num_Columns)
{

	/*
	Essa função pega uma matriz A e B e resolve o seguinte sistema linear:
	Ax=B, retornando o vetor de raizes Result.
	Essa função utiliza a fatoração de Givens para escalonar triangular superior a matriz A e assim
	resolver o sistema.
	*/

	float c;
	float s;
	int i;
	int column;

	//printf("[ WARN] Comecou a fatoracao");

	//for each column
	for(int k = 0; k < num_Columns; k++){

		//for each row
		for(int j = num_Rows-1; j > k; j--){

			i = j - 1;

			//printf("\n\n");

			//printMatrix(A, num_Rows, num_Columns);

			if(fabs(A[j][k]) > EPSLON){

				//printf("\n[ WARN] Zerando elemento (%d, %d). Elemento: %f)\n", j+1, k+1, A[j][k]);
				calculateCS(&c, &s, A, i, j, k);// CALCULAR C e S para zerar o elemento i,n
				rotGivens_Matrix(A, num_Rows, num_Columns, i, j, c, s);
				rotGivens_Vector(B, i, j, c, s);
			}
		}
	}

	for(int row = num_Rows-1; row >= 0; row--){

		float soma = 0.0;

		for(column = 0; column < num_Columns; column++){

			if(column != row){

				soma = soma + A[row][column] * Result[column][0];

			}
		}

		Result[row][0] = (B[row][0]-soma)/(A[row][row]);

	}
}

void overdetermined_systemQR(float W[MAX_MATRIX][MAX_MATRIX], float A[MAX_MATRIX][MAX_MATRIX],
float H[MAX_MATRIX][MAX_MATRIX], int n, int m, int p)
{
	/*
	Essa função pega uma matriz W e A e resolve os seguintes múltiplos sistemas lineares:
	WH=A, retornando a matriz H de raizes. Note que aqui possuimos p sistemas lineares
	de mesma matriz W e diferentes "vetores independentes". Assim,
	Essa função utiliza a fatoração de Givens para escalonar triangular superior a matriz A e assim
	resolver o sistema.
	*/

	//printf("\n[ WARN] Multiple system function called\n");

	float c;
	float s;
	int i;
	int column;
	float soma;

	// for each column
	for(int k = 0; k < p; k++){

		//for each row
		for(int j = n-1; j > k; j--){

			i = j - 1;

			//printf("\n\n");

			//printMatrix(W, num_Rows_W, num_Columns_W);

			if(fabs(W[j][k]) > EPSLON){

				//printf("\n[ WARN] Zerando elemento (%d, %d). Elemento: %f)\n", j+1, k+1, W[j][k]);

				/* A(n,m)  W(n,p)   H(p,m) */

				calculateCS(&c, &s, W, i, j, k);// CALCULAR C e S para zerar o elemento i,n
				rotGivens_Matrix(W, n, p, i, j, c, s);
				rotGivens_Matrix(A, n, m, i, j, c, s);
			}
		}
	}

	//over determined system
	for(int k = p-1; k>=0; k--){

		for(int j=0; j<m; j++){

			soma = 0.0;

			for(int i=k+1; i<p; i++){

				soma = soma + W[k][i]*H[i][j];

			}

			H[k][j] = (A[k][j] - soma)/W[k][k];

		}
	}

	/* A(n,m)  W(n,p)   H(p,m) */
	/* DEBUG CONSOLE
	printf("[ WARN_MSYS] Matrix A calculated:\n\n");

	printMatrix(A, num_Rows_A, num_Columns_A);

	printf("\n");

	printf("[ WARN_MSYS] Matrix W calculated:\n\n");

	printMatrix(W, num_Rows_W, num_Columns_W);

	printf("\n");

	printf("[ WARN_MSYS] Matrix H calculated:\n\n");

	printMatrix(H, num_Rows_H, num_Columns_H);

	printf("\n");
	*/

}

float erroQuad(float A[MAX_MATRIX][MAX_MATRIX], float W[MAX_MATRIX][MAX_MATRIX], float H[MAX_MATRIX][MAX_MATRIX], int n, int p, int m) {

/*Essa função calcula o erro quadrático, que é critério de parada do algoritmo de fatoração*/

    float wh, soma = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            wh = 0;
            for (int k = 0; k < p; k++) {
                wh += W[i][k] * H[k][j];
            }
            soma += (A[i][j] - wh) * (A[i][j] - wh);
        }
    }
    return soma;
}

void subtractMatrix(float A[MAX_MATRIX][MAX_MATRIX], float B[MAX_MATRIX][MAX_MATRIX], float C[MAX_MATRIX][MAX_MATRIX], int m, int n){

/*Função calcula a subtração de matrizes*/

	for(int i = 0; i < m; i++){

		for(int j = 0; j < n; j++){

			C[i][j] = A[i][j] - B[i][j];
		}
	}
}


void factorizationWH(float A[MAX_MATRIX][MAX_MATRIX], float W[MAX_MATRIX][MAX_MATRIX], float H[MAX_MATRIX][MAX_MATRIX],
	int m, int n, int p)
{

		/*
		Essa função recebe a Matriz A é retorna as matrizes W H positivas resultados da fatoração
		Repita os seguintes passos até que a norma do erro se estabilize (diferença entre as normas do erro em
		dois passos consecutivos < epslon (use epslon = 10 −5 no seu programa) ou que um número máximo de iterações
		(itmax, escolha itmax = 100) seja atingido
		Normalize W tal que a norma de cada uma de colunas;
		Resolva o problema de mı́nimos quadrados W H = A, determinando a matriz H (são m sistemas
		simultâneos! Cuidado, pois A é modificada no processo de solução. Na iteração seguinte deve-se usar
		a matriz A original novamente. Por isso armazena-se uma cópia de A!)
		Redefina H, com h i,j = max{0, h i,j }
		Compute a matriz A t (transposta da matriz A original)
		Resolva o problema de mı́nimos quadrados H t W t = A t , determinando a nova matriz W t . (são n
		sistemas simultâneos!)
		Compute a matriz W (transposta de W t )
		Redefina W , com w i,j = max{0, w i,j }

		/* A(n,m)  W(n,p)   H(p,m) */

		float A_copy[MAX_MATRIX][MAX_MATRIX];
		float A_transpose[MAX_MATRIX][MAX_MATRIX];
		float W_transpose[MAX_MATRIX][MAX_MATRIX];
		float H_transpose[MAX_MATRIX][MAX_MATRIX];
		float W_final[MAX_MATRIX][MAX_MATRIX];
		float norma_do_erro;
		int count = 0;
		float a = 1.0;
		float error_rate = 1;

		/* A(n,m)  W(n,p)   H(p,m) */

		// Inicializando W randomicamente c/ valores positivos

		for(int i = 0; i < n; i++){

			for(int j = 0; j < p; j++){

				W[i][j] = rand();
			}
		}

		/* A(n,m)  W(n,p)   H(p,m) */

		// Armazenando uma cópia de A
		for(int i = 0; i < n; i++){

			for(int j = 0; j < m; j++){

				A_copy[i][j] = A[i][j];
			}
		}

		/* A(n,m)  W(n,p)   H(p,m) */

		while(count < ITMAX && error_rate > EPSLON){

			normalizeMatrix(W, n, p);

			// Pegar matriz A original de volta a cada iteração
			for(int i = 0; i < n; i++){

				for(int j = 0; j < m; j++){

					A[i][j] = A_copy[i][j];
				}
			}

			/* A(n,m)  W(n,p)   H(p,m) */

			overdetermined_systemQR(W, A, H, n, m, p);

			redefine(H, p, m);

			transposeMatrix(A_copy, A_transpose, n, m);

			transposeMatrix(H, H_transpose, p, m);

			overdetermined_systemQR(H_transpose, A_transpose, W_transpose, m, n, p); // n, m, p

			transposeMatrix(W_transpose, W, p, n);

			redefine(W, n, p);

			count = count + 1;

			error_rate = erroQuad(A_copy, W, H, n, p, m);
		}

		//printf("\n[ WARN_WH] Matrix W generated\n\n");

		//printMatrix(W, n, p); // n,p

		/*
		printf("\n[ WARN_WH] Matrix H generated\n\n");

		printMatrix(H, p, m); // p,m
		*/
}

void digitClassifier(float A[MAX_MATRIX][MAX_MATRIX], float W[MAX_MATRIX][MAX_MATRIX], float H[MAX_MATRIX][MAX_MATRIX],
	float error[MAX_MATRIX], int digit_predict[MAX_MATRIX],
	int digito, int m, int n, int p){

	/*A cada novo dı́gito testado, obtemos os erros correspondentes a cada imagem. Se o novo valor
	de e j for menor que o anterior, armazenamos este novo valor de erro - mı́nimo até então - e o novo dı́gito
	como o mais provável. Se o erro novo for maior que o erro armazenado, concluı́mos que a imagem j não
	corresponde a este novo dı́gito.*/

	printf("\n[INFO_DIGClass] Testando o digito %d\n", digito);

	/* A(n,m)  W(n,p)   H(p,m) */

	float C[MAX_MATRIX][MAX_MATRIX];
	float WH[MAX_MATRIX][MAX_MATRIX];
	float soma;
	double erro_calculado;

	overdetermined_systemQR(W, A, H, n, m, p);

	readingFile("/home/lucas/Numerical_Methods/dataset/test_images.txt", A, n, m);

	//CALCULAR A - WH

	multiplyMatrices(W, H, WH, n, p, p, m);

	subtractMatrix(A, WH, C, n, m);

	/* CALCULAR MATRIZ RESIDUAL*/

	//for each column:
	for(int j = 0; j < m; j++){

		soma = 0.0;
		// for each row:
		for(int i = 0; i < n; i++){

			soma = soma + C[i][j]*C[i][j];

		}

		erro_calculado = sqrt(soma);

		printf("\n[DEBUG_Digclass] Erro calculado: %f\n", erro_calculado);

		/*VERIFICAR SE ERRO RESIDUAL É MENOR DO QUE OS ANTERIORES P/ TOMAR DECISÃO DE
		CLASSIFICAÇÃO*/

		if(digito == 0){

			error[j] = erro_calculado;
		}

		else{
			if(erro_calculado > error[j]){

			error[j] = erro_calculado;
			digit_predict[j] = digito;

			}
		}
	}
}


float getAccuracy(int digit_predict[MAX_MATRIX], int digit_correct[MAX_MATRIX], int n_test){

	//Essa função calcula a acurácia de treino do modelo;

	float count_correct_prediction = 0.0;


	for(int i = 0; i < n_test; i++){
		if (digit_predict[i] == digit_correct[i]){

			count_correct_prediction++;
		}
	}

	return (count_correct_prediction/n_test)*100;

}

float getDigitAccuracy(int digit_predict[MAX_MATRIX], int digit_correct[MAX_MATRIX], int n_test, int digit){

	//Essa função calcula a acurácia de treino para cada dígito;

	float count_correct_prediction = 0;
	int element;
	int number_of_digit = 0;

	for(int i=0; i<n_test; i++){

		element = digit_correct[i];

		if(element == digit){

			number_of_digit++;

			if(digit_predict[i] == digit_correct[i]){

				count_correct_prediction++;

			}
		}
	}

	return (count_correct_prediction/number_of_digit)*100;

}

int getNumberOfCorrectPredictions(int digit_predict[MAX_MATRIX], int digit_correct[MAX_MATRIX], int n_test, int digit){

	//Essa função calcula a quantidade de digitos predictos corretamente;

	int count_correct_prediction = 0;
	int element;
	int number_of_digit = 0;

	for(int i=0; i<n_test; i++){

		element = digit_correct[i];

		if(element == digit){

			number_of_digit++;

			if(digit_predict[i] == digit_correct[i]){

				count_correct_prediction++;

			}
		}
	}

	return count_correct_prediction;

}

#endif
