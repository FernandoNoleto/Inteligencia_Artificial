/**
  * Universidade Federal do Tocantins - Ciência da Computação
  * Trabalho de Inteligência Artificial - Implementação do k-means
  *	Acadêmicos: Fernando Noleto, André Luiz, Gabrielle Granja
  */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <math.h>

using namespace std;

typedef struct{
	int num;
	float x, y, z, a;
}centroide;

typedef struct{
	int num;
	float x, y, z, a;
}objeto;

typedef struct{
	int cent;
	int obj;
	objeto obj_atr;
}classificacao;

float distancia_euclidiana(float x1, float y1, float z1, float a1, float x2, float y2, float z2, float a2){
	return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2) + pow(z1-z2, 2) + pow(a1-a2, 2));
}

int menor(vector<float> v){
	int menor = 0;
	for(int i = 0; i < v.size(); i++){
		if(v[i] < v[menor]){
			menor = i;
		}
	}
	return menor;
}


int main() {
	int qtd_iteracoes = 0;

	//-------------------------------------------------------------------------------//
	//PARTE QUE CAPTURA A QUANTIDADE E OS VALORES DOS CENTRÓIDES
	int qtd_centroides;
	cout << "Digite quantos são os centróides iniciais" << endl;
	cin >> qtd_centroides;

	list<centroide> centroides;
	centroide c;

	for(int i = 0; i < qtd_centroides; i++){
		cout << "Digite o valor de x do centroide " << i << endl;
		cin >> c.x;
		cout << "Digite o valor de y do centroide " << i << endl;
		cin >> c.y;
		cout << "Digite o valor de z do centroide " << i << endl;
		cin >> c.z;
        cout << "Digite o valor de a do centroide " << i << endl;
		cin >> c.a;
		c.num = i;

		centroides.push_back(c);

	}
	system("clear");

	list<centroide>::iterator it;
	//Imprime os valores x, y, z dos centróides
	for(it = centroides.begin(); it != centroides.end(); it++){
		cout << "centroide " << it->num << " x: " << it->x << "; y: " << it->y << "; z: " << it->z << "; a: " << it->a << endl;
	}

	puts("----------------------------------");

	//-------------------------------------------------------------------------------//
	//PARTE QUE CAPTURA A QUANTIDADE E OS VALORES DOS OBJETOS A PARTIR DE UM ARQUIVO TXT
	int qtd_obj;
	FILE* arq = fopen("data.txt", "r");
	fscanf(arq, "%i\n", &qtd_obj);
	cout << "Qtd de objetos: " << qtd_obj << endl;
	list<objeto> objetos;
	list<objeto>::iterator ito;
	objeto obj;

	for(int i = 0; i < qtd_obj; i++){
		fscanf(arq, "%f,%f,%f,%f\n", &obj.x, &obj.y, &obj.z, &obj.a);
		obj.num = i;
		objetos.push_back(obj);
	}
	//Imprime os valores dos atributos de cada objeto
	for(ito = objetos.begin(); ito != objetos.end(); ito++){
		cout << "objeto " << ito->num << ": x = " << ito->x << "; y = " << ito->y << "; z = " << ito->z << "; a = " << ito->a << endl;
	}
	fclose(arq);

	puts("---------------------------------");


	//-------------------------------------------------------------------------------//
	//PARTE ONDE FAZ O CÁLCULO DAS DISTÂNCIAS EUCLIDIANAS E CLASSIFICA OS OBJETOS
	list<classificacao> classificao;
	classificacao cl;
	list<classificacao>::iterator itc;
	vector<float> distancia;
	bool continua = false;
	int m;
	int i = 0;
	float x = 0, y = 0, z = 0, a = 0;
	int count = 0;

	do{
		cout << "-------------------------------------" << endl;
		cout << "Iteração: " << qtd_iteracoes << endl;
		qtd_iteracoes++;

		continua = false;
		for(ito = objetos.begin(); ito != objetos.end(); ito++){
			for(it = centroides.begin(); it != centroides.end(); it++){
				distancia.push_back(distancia_euclidiana(ito->x, ito->y, ito->z, it->a, it->x, it->y, it->z, it->a));
				//Imprime a distância de cada objeto apra cada cluster
				//cout << "Distância do objeto " << ito->num << " para cluster ";
				//cout << it->num << ": " << distancia_euclidiana(ito->x, ito->y, ito->z, it->x, it->y, it->z) << endl;
			}

			m = menor(distancia);
			cl.cent = m;
			cl.obj = ito->num;
			cl.obj_atr.x = ito->x;
			cl.obj_atr.y = ito->y;
			cl.obj_atr.z = ito->z;
            cl.obj_atr.a = ito->a;

			distancia.clear();
			classificao.push_back(cl);
		}

		//Imprime em qual cluster o objeto foi classificado
		for(itc = classificao.begin(); itc != classificao.end(); itc++){
			cout << "Objeto " << itc->obj << " classificado no cluster: " << itc->cent << endl;
			//cout << "X: " << itc->obj_atr.x << "; Y: " << itc->obj_atr.y << "; Z: " << itc->obj_atr.z << endl;
		}
		puts("---------------------------------------");


		centroide novo_cent;
		list<centroide> novos_centroides;
		list<centroide>::iterator it_nc;
		//ito = objetos
		//itc = classificação

		for(it = centroides.begin(); it != centroides.end(); it++){
			for(itc = classificao.begin(); itc != classificao.end(); itc++){
				if(itc->cent == i){
					x += itc->obj_atr.x;
					y += itc->obj_atr.y;
					z += itc->obj_atr.z;
                    a += itc->obj_atr.a;
					count++;
				}
			}
			if(x != 0 && y != 0 && z != 0){
				novo_cent.num = it->num;
				novo_cent.x = x/count;
				novo_cent.y = y/count;
				novo_cent.z = z/count;
                novo_cent.a = a/count;
				count = 0;
				x = 0;
				y = 0;
				z = 0;
				novos_centroides.push_back(novo_cent);
			}
			else{
				c.num = it->num;
				c.x = it->x;
				c.y = it->y;
				c.z = it->z;
                c.a = it->a;
				novos_centroides.push_back(c);
			}
			i++;
		}
		for(it = centroides.begin(); it != centroides.end(); it++){
			cout << "Velho Centroide: " << it->num << " -> X: " << it->x << "; Y: " << it->y << "; Z: " << it->z << "; A: " << it->a << endl;
		}

		puts("----------------------------------");

		for(it_nc = novos_centroides.begin(); it_nc != novos_centroides.end(); it_nc++){
			cout << "Novo Centroide: " << it_nc->num << " -> X: " << it_nc->x << "; Y: " << it_nc->y << "; Z: " << it_nc->z << "; A: " << it_nc->a << endl;
		}

		it_nc = novos_centroides.begin();
		//Comparação do centróide antigo com o novo centróide calculado
		for(it = centroides.begin(); it != centroides.end(); it++){
			if((it->x != it_nc->x) || (it->y != it_nc->y) || (it->z != it_nc->z) || (it->a != it_nc->a)){
				continua = true;
			}
			it_nc++;
		}
		if(continua){
			centroides.clear();
			for(it_nc = novos_centroides.begin(); it_nc != novos_centroides.end(); it_nc++){
				c.num = it_nc->num;
				c.x = it_nc->x;
				c.y = it_nc->y;
				c.z = it_nc->z;
                c.a = it_nc->a;
				centroides.push_back(c);
			}

		}

		novos_centroides.clear();
		classificao.clear();
	}while(continua);


	return 0;
}

