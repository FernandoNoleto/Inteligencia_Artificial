#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <math.h>

using namespace std;

typedef struct{
	int x, y;
}values;

typedef struct{
	int cent;
	int obj;
}classificacao;

float distancia_euclidiana(float x1, float y1, float x2, float y2){
	return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}


int main() {

	//PARTE QUE CAPTURA A QUANTIDADE E OS VALORES DOS CENTRÓIDES

	int qtd_centroides, x, y;
	cout << "Digite quantos são os centróides iniciais" << endl;
	cin >> qtd_centroides;

	int** centroides = (int**) malloc (qtd_centroides * sizeof(int*));

	for(int i = 0; i < qtd_centroides; i++){
		cout << "Digite o valor de x do centroide " << i << endl;
		cin >> x;
		cout << "Digite o valor de y do centroide " << i << endl;
		cin >> y;

		centroides[i] = (int*) malloc (2 * sizeof(int));
		centroides[i][0] = x;
		centroides[i][1] = y;
	}
	system("clear");

	for(int i = 0; i < qtd_centroides; i++){
		cout << "centroide " << i << ": " << "x = " << centroides[i][0] << " y = " << centroides[i][1] << endl;
	}

	puts("-----------------------");

	//PARTE QUE CAPTURA A QUANTIDADE E OS VALORES DOS OBJETOS A PARTIR DE UM ARQUIVO TXT

	int qtd_obj;
	FILE* arq = fopen("/home/fernando/Qt-Projects/kmeans/data.txt", "r");
	fscanf(arq, "%i\n", &qtd_obj);
	cout << "Qtd de objetos: " << qtd_obj << endl;

	int** objetos = (int**) malloc (qtd_obj * sizeof(int*));
	for(int i = 0; i < qtd_obj; i++){
		objetos[i] = (int*) malloc(2 * sizeof(int));
		fscanf(arq, "%i %i\n", &x, &y);
		objetos[i][0] = x;
		objetos[i][1] = y;

		cout << "objeto " << i << ": x = " << objetos[i][0] << " y = " << objetos[i][1] << endl;
	}
	fclose(arq);

	puts("-----------------------");

	//PARTE ONDE É CALCULADO AS DISTÂNCIAS DOS OBJETOS PARA OS CENTRÓIDES
	//E TAMBÉM JÁ É FEITO AS CLASSIFICAÇÕES
	list<classificacao> l;
	classificacao cl;

	float distancias[qtd_centroides];
	for(int i = 0; i < qtd_obj; i++){
		for(int j = 0; j < qtd_centroides; j++){
			distancias[j] = distancia_euclidiana(objetos[i][0], objetos[i][1], centroides[j][0], centroides[j][1]);
			//Cálculo das distâncias
			cout << "d(obj" << i << ", cl" << j << ") = " << distancias[j] << endl;
		}
		if(distancias[0] < distancias[1] && distancias[0] < distancias[2]){
			cl.cent = 0;
			cl.obj = i;
		}
		else if(distancias[1] < distancias[0] && distancias[1] < distancias[2]){
			cl.cent = 1;
			cl.obj = i;
		}
		else{
			cl.cent = 2;
			cl.obj = i;
		}
		l.push_back(cl);
		puts("-----------------------");
	}

	for(int i = 0; i < qtd_obj; i++){
		cout << "Objeto " << l.front().obj << " no cluster " << l.front().cent << endl;
		l.pop_front();
	}



	return 0;
}
