#pragma once
//Pasar el codigo aqui sin el include de pch.h
//Me da unos problemas y lo intente arreglarlo pero no he podido. 
#pragma once

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<time.h>

using namespace std;


bool pertenece(int numero, int * intercambios, int cantNodos) {
	for (int i = 0; i <= cantNodos; i++) {
		cout << "Intercambios[i] " << intercambios[i] << "numero" << numero << " metodo pertenecee" << endl;
		if (intercambios[i] == numero) {

			return true;
		}
	}
	return false;
}
int * intercambie(int *a, int numNodos) {
	int * intercambiados = new int[numNodos];
	srand(time(NULL)); //Ingresa la semilla del rand
	//recorrer la lista con los elementos de 0...N-1 e imprimir todo sus valores
	for (int i = 0; i <= numNodos; i++) {
		int numRand = rand() % numNodos + 1;
		cout << "numRand:" << numRand << endl;
		if (!pertenece(numRand, intercambiados, numNodos)) {
			intercambiados[i] = numRand;
			cout << "INCLUYE EL NUMERO EN INTERCAMBIOS; numRand:" << numRand << " intercambios[i]:" << intercambiados[i] << endl;
		}
	}
	for (int i = 0; i < numNodos; i++) {
		cout << "Elementos de las intercambios finales:" << intercambiados[i] << "numNodos" << numNodos << endl;

	}
	return intercambiados;
}

void genere(int n) {

	int * valores = new int[n];
	for (int i = 0; i < n; i++) {
		valores[i] = i + 1;
		cout << "Elementos de las listas original" << valores[i] << endl;
	}
	intercambie(valores, n);
}
