#ifndef _TAREFAS_H_
#define _TAREFAS_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "linearalgebra.h"

#define MAX_MATRIX 10000
#define EPSLON 0.00001
#define ITMAX 100

void task1a() {

		printf("\n\n[INFO_Task1a] Task (1.a running: \n");

		int n = 64;
    int m = 64;

    float W[MAX_MATRIX][MAX_MATRIX], b[MAX_MATRIX][1], x[MAX_MATRIX][1];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j) W[i][j] = 2.0;
            else if (fabs(i - j) == 1) W[i][j] = 2.0;
            else W[i][j] = 0.0;
        }
        b[i][0] = 1.0;
    }

    factorizationQR(W, b, x, n, m);

    printVector(x, n);

}

void task1b() {

		printf("\n\n[INFO_Task1b] Task (1.b running: \n");

    int n = 20;
    int m = 17;

    float W[MAX_MATRIX][MAX_MATRIX], b[MAX_MATRIX][1], x[MAX_MATRIX][1];

		for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            W[i][j] = (abs(i - j) > 4) ? 0.0 : 1.0 / (i + j + 1);
        }
        b[i][0] = float(i) + 1.0;
    }

    factorizationQR(W, b, x, n, m);

    printVector(x, n);

}

void task1c() {

	printf("\n\n[INFO_Task1c] Task (1.C running: \n");

	float A[MAX_MATRIX][MAX_MATRIX], W[MAX_MATRIX][MAX_MATRIX], H[MAX_MATRIX][MAX_MATRIX];

	int n = 64;
	int p = 3;
	int m = 64;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j) W[i][j] = 2.0;
            else if (abs(i - j) == 1) W[i][j] = 2.0;
            else W[i][j] = 0.0;
        }
        A[i][0] = 1.0;
        A[i][1] = float(i) + 1.0;
        A[i][2] = 2.0 * (float(i) + 1.0) - 1.0;
    }

		/* A(n,m)  W(n,p)   H(p,m) */

    overdetermined_systemQR(W, A, H, n, m, p);

    printMatrix(H, p, m);
}

void task1d() {

	printf("\n\n[INFO_Task1d] Task (1.d running: \n");

	float A[MAX_MATRIX][MAX_MATRIX], W[MAX_MATRIX][MAX_MATRIX], H[MAX_MATRIX][MAX_MATRIX];

	int n = 20;
	int p = 3;
	int m = 17;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            W[i][j] = (abs(i - j) > 4) ? 0.0 : 1. / (i + j + 1);
        }
        A[i][0] = 1.0;
        A[i][1] = float(i) + 1.0;
        A[i][2] = 2.0 * (float(i) + 1.0) - 1.0;
    }

		/* A(n,m)  W(n,p)   H(p,m) */

		overdetermined_systemQR(W, A, H, n, m, p);

  	printMatrix(H, p, m);

}

void task2(){

	printf("\n\n[INFO_Task2] Task (2 running: \n");

	float A[MAX_MATRIX][MAX_MATRIX] = {{0.3, 0.6, 0.0}, {0.5, 0.0, 1.0}, {0.4, 0.8, 0}};
	float W[MAX_MATRIX][MAX_MATRIX], H[MAX_MATRIX][MAX_MATRIX];

	/* A(n,m)  W(n,p)   H(p,m) */

	int p = 2;
	int n = 3;
	int m = 3;

	/*factorizationWH(float A, float W[MAX_MATRIX][MAX_MATRIX], float H[MAX_MATRIX][MAX_MATRIX],
		int m, int n, int p)*/

	factorizationWH(A, W, H, m, n, p);

	printf("\n\n[INFO_Task2] Matrix W:\n\n");

	printMatrix(W, n, p);

	printf("\n\n[INFO_Task2] Matrix H:\n\n");

	printMatrix(H, p, m);

}

#endif
