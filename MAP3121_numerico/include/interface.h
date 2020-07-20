#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>

#define MAX_MATRIX 10000

using namespace std;

void printMatrix(float M[MAX_MATRIX][MAX_MATRIX], int m, int n){

	 int lin, col;

	 for (lin=0; lin<m; lin++) {

	    for (col=0; col<n; col++)

	      printf("%f \t", M[lin][col]);

	    	printf("\n");
   }
}

void printVector(float M[MAX_MATRIX][1], int m){

	 int lin;

	 for (lin=0; lin<m; lin++) {

	 printf("%f \t", M[lin][0]);

	 printf("\n");

   }
}

void printVectorV(int M[MAX_MATRIX], int m){

	 int lin;

	 for (lin=0; lin<m; lin++) {

	 printf("%d \t", M[lin]);

	 printf("\n");

   }
}

void readingFile(std::string filepath, float A[MAX_MATRIX][MAX_MATRIX], int n, int m){

	double element;
	int i = 0;

	std::ifstream in(filepath.c_str());

	if(in.is_open()){

		printf("\n[INFO_ReadingFile] File opened succesfully!\n");

		std::string line;

		while(getline(in, line)){

			for(int j = 0; j<m; j++){

				in >> element;

				A[i][j] = element/255.0;

			}
			i++;
		}
	}

	else printf("\n\n[ERROR_ReadingFile] Unable to open the file!\n");

}

void readingLabel(std::string filepath, int A[MAX_MATRIX], int n){

	int element;

	std::fstream file(filepath.c_str(), std::ios::in);

	if(file.is_open()){

		printf("\n[INFO_ReadingFile] File opened succesfully!\n");

		for(int i = 0; i<n; i++){

				file >> element;

				A[i] = element;

		}
	}

	else printf("\n\n[ERROR_ReadingFile] Unable to open the file!\n");

}

#endif
