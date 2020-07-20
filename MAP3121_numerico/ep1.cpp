/*
Instituto de Matemática e Estatísitca da Universidade de São Paulo
Métodos Numéricos e Aplicações - MAP 3221

Exercício Programa 1 - Machine Learning aplicado à Base MNIST

Autor: Lucas Penna Saraiva

AUMENTAR MEMORIA DA PILHA DE EXECUÇÃO
(RELATORIO)

$ ulimit -s unlimited

DEMORANDO 11:50.8

Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/5/lto-wrapper
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 5.4.0-6ubuntu1~16.04.11' --with-bugurl=file:///usr/share/doc/gcc-5/README.Bugs --enable-languages=c,ada,c++,java,go,d,fortran,objc,obj-c++ --prefix=/usr --program-suffix=-5 --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --with-sysroot=/ --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-libmpx --enable-plugin --with-system-zlib --disable-browser-plugin --enable-java-awt=gtk --enable-gtk-cairo --with-java-home=/usr/lib/jvm/java-1.5.0-gcj-5-amd64/jre --enable-java-home --with-jvm-root-dir=/usr/lib/jvm/java-1.5.0-gcj-5-amd64 --with-jvm-jar-dir=/usr/lib/jvm-exports/java-1.5.0-gcj-5-amd64 --with-arch-directory=amd64 --with-ecj-jar=/usr/share/java/eclipse-ecj.jar --enable-objc-gc --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.11)

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "include/linearalgebra.h"
#include "include/interface.h"
#include "include/tarefas.h"

#define MAX_MATRIX 10000

int main(){

	int key;

	printf("\n[INFO_MAIN] Escola Politecnica da Universidade de Sao Paulo\n[INFO_MAIN] MAP3232-Metodos Numericos e Aplicacoes\n[INFO_MAIN] Exercicio Programa 1: Classificador de Digitos (MNIST Base)\n");

	while(1){

		printf("\n-----------------------------------------------------------\n");
		printf("\n\n[INFO_MAIN] Menu principal de operacoes\nDigite 1 para rodar tarefa 1.a\nDigite 2 para rodar tarefa 1.b\nDigite 3 para rodar tarefa 1.c\nDigite 4 para rodar tarefa 1.d\nDigite 5 para rodar tarefa 2\n\n[INFO_MAIN] Digite 0 para RODAR TAREFA PRINCIPAL (TREINAMENTO + TESTES + ACURÁCIA)\n\n");

		scanf("%d", &key);

		if(key == 1)
			task1a();
		if(key == 2)

			task1b();

		if(key == 3)
			task1c();

		if(key == 4)
		  task1d();

		if(key == 5)
			task2();

		if(key == 0){

			int n, m, p, n_test, key;

			int number0correct, number1correct, number2correct, number3correct, number4correct, number5correct, number6correct, number7correct, number8correct, number9correct;

			float accuracy, digit0accuracy, digit1accuracy, digit2accuracy, digit3accuracy, digit4accuracy, digit5accuracy, digit6accuracy, digit7accuracy, digit8accuracy, digit9accuracy;

		  float H[MAX_MATRIX][MAX_MATRIX];
			float A[MAX_MATRIX][MAX_MATRIX];
			float error[MAX_MATRIX];
			int digit_predict[MAX_MATRIX];
			int digit_correct[MAX_MATRIX];

			float W0[MAX_MATRIX][MAX_MATRIX];
			float W1[MAX_MATRIX][MAX_MATRIX];
			float W2[MAX_MATRIX][MAX_MATRIX];
			float W3[MAX_MATRIX][MAX_MATRIX];
			float W4[MAX_MATRIX][MAX_MATRIX];
			float W5[MAX_MATRIX][MAX_MATRIX];
			float W6[MAX_MATRIX][MAX_MATRIX];
			float W7[MAX_MATRIX][MAX_MATRIX];
			float W8[MAX_MATRIX][MAX_MATRIX];
			float W9[MAX_MATRIX][MAX_MATRIX];

			/* A(n,m)  W(n,p)   H(p,m) */

			printf("[INFO_MAIN] Digite a precisao desejada na tarefa principal (0, 1, 2)\nSe 0: m = 100 e p = 5\nSe 1: m = 1000 e p=10\nSe 2: m = 4000 e p = 15");
			scanf("%d", &key);

			if(key == 0){
				n = 784;
				m = 100;
				p = 5;
				n_test = 10000;
			}

			if(key == 1){
				n = 784;
				m = 1000;
				p = 10;
				n_test = 10000;
			}

			if(key == 2){
				n = 784;
				m = 4000;
				p = 15;
				n_test = 10000;
			}

			/* treinamento */

			/*ETAPA DE TREINAMENTO*/

			/* O TREINAMENTO CONSISTE EM CALCULAR AS MATRIZES WD RESPECTIVAS PARA CADA DIGITO D*/

			printf("\n[INFO_MAIN] Treinando o digito 0: \n");
			readingFile("/home/lucas/Numerical_Methods/dataset/train_dig0.txt", A, n, m);
			factorizationWH(A, W0, H, m, n, p);


			printf("\n[INFO_MAIN] Treinando o digito 1: \n");
			readingFile("/home/lucas/Numerical_Methods/dataset/train_dig1.txt", A, n, m);
			factorizationWH(A, W1, H, m, n, p);


			printf("\n[INFO_MAIN] Treinando o digito 2: \n");
			readingFile("/home/lucas/Numerical_Methods/dataset/train_dig2.txt", A, n, m);
			factorizationWH(A, W2, H, m, n, p);


			printf("\n[INFO_MAIN] Treinando o digito 3: \n");
			readingFile("/home/lucas/Numerical_Methods/dataset/train_dig3.txt", A, n, m);
			factorizationWH(A, W3, H, m, n, p);


			printf("\n[INFO_MAIN] Treinando o digito 4: \n");
			factorizationWH(A, W4, H, m, n, p);
			readingFile("/home/lucas/Numerical_Methods/dataset/train_dig4.txt", A, n, m);


			printf("\n[INFO_MAIN] Treinando o digito 5: \n");
			readingFile("/home/lucas/Numerical_Methods/dataset/train_dig5.txt", A, n, m);
			factorizationWH(A, W5, H, m, n, p);


			printf("\n[INFO_MAIN] Treinando o digito 6: \n");
			readingFile("/home/lucas/Numerical_Methods/dataset/train_dig6.txt", A, n, m);
			factorizationWH(A, W6, H, m, n, p);


			printf("\n[INFO_MAIN] Treinando o digito 7: \n");
			readingFile("/home/lucas/Numerical_Methods/dataset/train_dig7.txt", A, n, m);
			factorizationWH(A, W7, H, m, n, p);


			printf("\n[INFO_MAIN] Treinando o digito 8: \n");
			readingFile("/home/lucas/Numerical_Methods/dataset/train_dig8.txt", A, n, m);
			factorizationWH(A, W8, H, m, n, p);


			printf("\n[INFO_MAIN] Treinando o digito 9: \n");
			readingFile("/home/lucas/Numerical_Methods/dataset/train_dig9.txt", A, n, m);
			factorizationWH(A, W9, H, m, n, p);

			/*  teste   */

			readingFile("/home/lucas/Numerical_Methods/dataset/test_images.txt", A, n, n_test);

			//printMatrix(A, n, n_test);

			/* teste digito 0 */

			/* A(n,m)  W(n,p)   H(p,m) */

			/*ETAPA DE CLASSIFICAÇÃO E TESTES*/

			digitClassifier(A, W0, H, error, digit_predict, 0, n_test, n, p);

			readingFile("/home/lucas/Numerical_Methods/dataset/test_images.txt", A, n, n_test);
			digitClassifier(A, W1, H, error, digit_predict, 1, n_test, n, p);

			readingFile("/home/lucas/Numerical_Methods/dataset/test_images.txt", A, n, n_test);
			digitClassifier(A, W2, H, error, digit_predict, 2, n_test, n, p);

			readingFile("/home/lucas/Numerical_Methods/dataset/test_images.txt", A, n, n_test);
			digitClassifier(A, W3, H, error, digit_predict, 3, n_test, n, p);

			readingFile("/home/lucas/Numerical_Methods/dataset/test_images.txt", A, n, n_test);
			digitClassifier(A, W4, H, error, digit_predict, 4, n_test, n, p);

			readingFile("/home/lucas/Numerical_Methods/dataset/test_images.txt", A, n, n_test);
			digitClassifier(A, W5, H, error, digit_predict, 5, n_test, n, p);

			readingFile("/home/lucas/Numerical_Methods/dataset/test_images.txt", A, n, n_test);
			digitClassifier(A, W6, H, error, digit_predict, 6, n_test, n, p);

			readingFile("/home/lucas/Numerical_Methods/dataset/test_images.txt", A, n, n_test);
			digitClassifier(A, W7, H, error, digit_predict, 7, n_test, n, p);

			readingFile("/home/lucas/Numerical_Methods/dataset/test_images.txt", A, n, n_test);
			digitClassifier(A, W8, H, error, digit_predict, 8, n_test, n, p);

			readingFile("/home/lucas/Numerical_Methods/dataset/test_images.txt", A, n, n_test);
			digitClassifier(A, W9, H, error, digit_predict, 9, n_test, n, p);

			readingLabel("/home/lucas/Numerical_Methods/dataset/test_index.txt", digit_correct, n_test);

			//printVectorV(digit_predict, n_test);

			digit0accuracy = getDigitAccuracy(digit_predict, digit_correct,  n_test, 0);
			digit1accuracy = getDigitAccuracy(digit_predict, digit_correct,  n_test, 1);
			digit2accuracy = getDigitAccuracy(digit_predict, digit_correct,  n_test, 2);
			digit3accuracy = getDigitAccuracy(digit_predict, digit_correct,  n_test, 3);
			digit4accuracy = getDigitAccuracy(digit_predict, digit_correct,  n_test, 4);
			digit5accuracy = getDigitAccuracy(digit_predict, digit_correct,  n_test, 5);
			digit6accuracy = getDigitAccuracy(digit_predict, digit_correct,  n_test, 6);
			digit7accuracy = getDigitAccuracy(digit_predict, digit_correct,  n_test, 7);
			digit8accuracy = getDigitAccuracy(digit_predict, digit_correct,  n_test, 8);
			digit9accuracy = getDigitAccuracy(digit_predict, digit_correct,  n_test, 9);

			number0correct = getDigitAccuracy(digit_predict, digit_correct,  n_test, 0);
			number1correct = getDigitAccuracy(digit_predict, digit_correct,  n_test, 1);
			number2correct = getDigitAccuracy(digit_predict, digit_correct,  n_test, 2);
			number3correct = getDigitAccuracy(digit_predict, digit_correct,  n_test, 3);
			number4correct = getDigitAccuracy(digit_predict, digit_correct,  n_test, 4);
			number5correct = getDigitAccuracy(digit_predict, digit_correct,  n_test, 5);
			number6correct = getDigitAccuracy(digit_predict, digit_correct,  n_test, 6);
			number7correct = getDigitAccuracy(digit_predict, digit_correct,  n_test, 7);
			number8correct = getDigitAccuracy(digit_predict, digit_correct,  n_test, 8);
			number9correct = getDigitAccuracy(digit_predict, digit_correct,  n_test, 9);

			printf("\n\n[INFO_MAIN] Digit 0 training accuracy calculated: %f\n", digit0accuracy);
			printf("\n\n[INFO_MAIN] Digit 1 training accuracy calculated: %f\n", digit1accuracy);
			printf("\n\n[INFO_MAIN] Digit 2 training accuracy calculated: %f\n", digit2accuracy);
			printf("\n\n[INFO_MAIN] Digit 3 training accuracy calculated: %f\n", digit3accuracy);
			printf("\n\n[INFO_MAIN] Digit 4 training accuracy calculated: %f\n", digit4accuracy);
			printf("\n\n[INFO_MAIN] Digit 5 training accuracy calculated: %f\n", digit5accuracy);
			printf("\n\n[INFO_MAIN] Digit 6 training accuracy calculated: %f\n", digit6accuracy);
			printf("\n\n[INFO_MAIN] Digit 7 training accuracy calculated: %f\n", digit7accuracy);
			printf("\n\n[INFO_MAIN] Digit 8 training accuracy calculated: %f\n", digit8accuracy);
			printf("\n\n[INFO_MAIN] Digit 9 training accuracy calculated: %f\n", digit9accuracy);

			printf("\n\n[INFO_MAIN] Number of digit 0 correctly classified: %d\n", number0correct);
			printf("\n\n[INFO_MAIN] Number of digit 1 correctly classified: %d\n", number1correct);
			printf("\n\n[INFO_MAIN] Number of digit 2 correctly classified: %d\n", number2correct);
			printf("\n\n[INFO_MAIN] Number of digit 3 correctly classified: %d\n", number3correct);
			printf("\n\n[INFO_MAIN] Number of digit 4 correctly classified: %d\n", number4correct);
			printf("\n\n[INFO_MAIN] Number of digit 5 correctly classified: %d\n", number5correct);
			printf("\n\n[INFO_MAIN] Number of digit 6 correctly classified: %d\n", number6correct);
			printf("\n\n[INFO_MAIN] Number of digit 7 correctly classified: %d\n", number7correct);
			printf("\n\n[INFO_MAIN] Number of digit 8 correctly classified: %d\n", number8correct);
			printf("\n\n[INFO_MAIN] Number of digit 9 correctly classified: %d\n", number9correct);

			accuracy = getAccuracy(digit_predict, digit_correct, n_test);

			printf("\n\n\n[INFO_MAIN] -- Total training accuracy calculated: %f --\n\n", accuracy);
		}
 }
	return 0;
}
