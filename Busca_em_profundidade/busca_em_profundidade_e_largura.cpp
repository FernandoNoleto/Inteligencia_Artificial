/*
 * Grupo: André Luiz, Fernando Noleto, Gabrielle Azevedo, Mateus Ferreira
 * Inteligência Artificial - Busca em profundidade e Busca em largura
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <queue>
#include <string>

using namespace std;


//Estrutura da árvore AVL com dados de nome, email e idade
struct no{
	int info;
	string nome;
	string email;
	int idade;
	struct no* esq;
	struct no* dir;
};

typedef struct no tavl;

void inserir(tavl**, int);
void preOrdem(tavl*);
void ordem(tavl*);
void posOrdem(tavl*);
void inserir_balanceado(tavl**, int, string, string, int);
void RD(tavl**);
void RE(tavl**);
void RDD(tavl**);
void RDE(tavl**);
int altura(tavl*);
int fator_balanceamento(tavl*);
tavl* verificar_arvore(tavl*);
void remover(tavl**, int);
tavl* maiorDireita(tavl**);
void imprimir_por_nivel(tavl*);
void busca_em_profundidade(stack<tavl>*, int, tavl*, bool*);
void busca_em_largura(int, tavl*, bool*);

void menu();


int main(){

	menu();

	return 0;
}



void inserir(tavl** t, int x){

	if(*t == NULL){
		tavl* novo = (tavl*) malloc (sizeof(tavl));
		novo->info = x;
		novo->dir = NULL;
		novo->esq = NULL;
		*t = novo;
	}else{
		tavl* aux = *t;
		if(x < aux->info) inserir(&(aux->esq), x);
		else inserir(&(aux->dir), x);
	}

}

void preOrdem(tavl* t){

	if(t != NULL){
		printf("%i\n", t->info);
		preOrdem(t->esq);
		preOrdem(t->dir);
	}

}

void ordem(tavl *t){
	if(t){
		ordem(t->esq);
		printf("%i\n", t->info);
		ordem(t->dir);
	}
}

void posOrdem(tavl* t){
	if(t!=NULL){
		posOrdem(t->esq);
		posOrdem(t->dir);
		printf("%i\n", t->info);
	}
}

void inserir_balanceado(tavl** t, int x, string nome, string email, int idade){
	if(*t == NULL){
		tavl* novo = (tavl*) malloc(sizeof(tavl));
		novo->info = x;
		novo->nome = nome;
		novo->email = email;
		novo->idade = idade;
		novo->dir = NULL;
		novo->esq = NULL;
		*t = novo;
	}else{
		tavl* aux = *t;
		if(x < aux->info) inserir_balanceado(&(aux->esq), x, nome, email, idade);
		else inserir_balanceado(&(aux->dir), x, nome, email, idade);
	}

	*t = verificar_arvore(*t);

}

//Rotação à direita
void RD(tavl** t){
	tavl* u;
	u = (*t)->esq;
	(*t)->esq = u->dir;
	u->dir = (*t);
	(*t) = u;
}

//Rotação à esquerda
void RE(tavl** t){
	tavl* u;
	u = (*t)->dir;
	(*t)->dir = u->esq;
	u->esq = (*t);
	(*t) = u;
}

//Rotação dupla à direita
void RDD(tavl** t){
	tavl* u = (*t)->esq;
	tavl* v = u->dir;

	u->dir = v->esq;
	v->esq = u;
	(*t)->esq = v->dir;
	v->dir = (*t);
	(*t) = v;

}

//Rotação dupla à esquerda
void RDE(tavl** t){
	tavl* u = (*t)->dir;
	tavl* v = u->esq;

	u->esq = v->dir;
	v->dir = u;
	(*t)->dir = v->esq;
	v->esq = (*t);

	(*t) = v;
}

//Verifica altura do nó
int altura(tavl* t){
	int lh, rh;
	if (t == NULL) return 0;
	else{
		lh = altura (t->esq);
		rh = altura (t->dir);
		if (lh > rh)
			return (lh+1);
		else
			return (rh+1);
	}
}

int fator_balanceamento(tavl* t){
	if(!t) return 0;
	return (altura(t->esq) - altura(t->dir));
}

//Função usada para verificar balanceamento da árvore a cada inserção ou remoção
tavl* verificar_arvore(tavl* t){

	if(t != NULL){

		int fbt = fator_balanceamento(t);
		int fbe = fator_balanceamento(t->esq);
		int fbd = fator_balanceamento(t->dir);


		if(fbt < -1){
			if(fbd == -1){
				RE(&t);
				return t;
			}
			if(fbd == 1){
				RDE(&t);
				return t;
			}
		}

		if(fbt > 1){

			if(fbe == 1){
				RD(&t);
				return t;
			}
			if(fbe == -1){
				RDD(&t);
				return t;
			}
		}
		verificar_arvore(t->dir);
		verificar_arvore(t->esq);
	}

	return t;
}

//Função de remover sem recursividade
void remover(tavl **t, int x){
   if (*t != NULL){
	  if (x < (*t)->info)
		 remover(&((*t)->esq),x);
	  else if (x > (*t)->info)
		 remover(&((*t)->dir),x);
	  else{
		 tavl *pAux;
		 pAux = *t;

		 if ( (*t)->esq == NULL && (*t)->dir == NULL){
			free(pAux);
			(*t) = NULL;
		 }

		 else if ((*t)->esq == NULL){
			(*t) = (*t)->dir;
			pAux->dir = NULL;
			free(pAux);
		 }

		 else if ((*t)->dir == NULL){
			(*t) = (*t)->esq;
			pAux->esq = NULL;
			free(pAux);
		 }

		 else{
			pAux = maiorDireita(&(*t)->esq);
			pAux->esq = (*t)->esq;
			pAux->dir = (*t)->dir;
			(*t)->esq = (*t)->dir;
			free((*t));
			*t = pAux;
		 }
	  }
   }
   *t = verificar_arvore(*t);
}

tavl* maiorDireita(tavl** t){

	tavl* pAux;
	if((*t)->dir != NULL)
		return maiorDireita(&((*t)->dir));
	else{
		//tavl *pAux;
		pAux = *t;

		if ((*t)->esq != NULL)
				 *t = (*t)->esq;
			  else
				 *t = NULL;
	}
	return pAux;
}

//Imprimir arvore por nivel usando fila
void imprimir_por_nivel(tavl* t){
	if(!t)
		return;
	else{
		queue<tavl*> q;
		q.push(t);
		tavl* aux;

		while (!q.empty()) {

			aux = q.front();
			cout << aux->info << endl;
			q.pop();


			if(aux->esq)
				q.push(aux->esq);
			if(aux->dir)
				q.push(aux->dir);

		}
	}
}

void busca_em_profundidade(stack<tavl>* s, int x, tavl* t, bool* flag){

	if(*flag){
		if(t != NULL)
			s->push(*t);
		else
			return;

		tavl aux = s->top();
		cout << "-----------------" << endl;
		cout << "ID:" << aux.info << endl;
		cout << "Nome:" << aux.nome << endl;
		cout << "Email:" << aux.email << endl;
		cout << "Idade:" << aux.idade << endl;
		cout << "-----------------" << endl;

		if(x == aux.info) {
			s->pop();
			*flag = false;
			return;
		}
		else {
			s->pop();

			busca_em_profundidade(s, x, t->esq, flag);
			busca_em_profundidade(s, x, t->dir, flag);

		}
	}

}

void busca_em_largura(int x, tavl* t, bool* flag){

	if(*flag){
		if(!t)
			return;
		else{
			queue<tavl*> q;
			q.push(t);
			tavl* aux;

			while (!q.empty()) {

				aux = q.front();
				cout << "-----------------" << endl;
				cout << "ID:" << aux->info << endl;
				cout << "Nome:" << aux->nome << endl;
				cout << "Email:" << aux->email << endl;
				cout << "Idade:" << aux->idade << endl;
				cout << "-----------------" << endl;
				q.pop();

				if(x == aux->info){
					*flag = false;
					return;
				}

				if(aux->esq)
					q.push(aux->esq);
				if(aux->dir)
					q.push(aux->dir);

			}
		}
	}
}


void menu(){
	int opc;
	tavl* t = NULL;
	stack<tavl> s;
	bool continuar = true;
	srand(time(NULL));
	string nome;
	string email;
	int idade;
	int id;

	do{
		cout << "0 - Sair" << endl;
		cout << "1 - Adicionar contato" << endl;
		cout << "2 - Excluir contato" << endl;
		cout << "3 - Listar contatos usando busca em profundidade" << endl;
		cout << "4 - Listar contatos usando busca em largura" << endl;
		cin >> opc;
		switch (opc) {
		case 0:
			system("clear");
			cout << "FLW!!" << endl;
			break;
		case 1:
			system("clear");
			cout << "Qual o nome do contato?" << endl;
			cin >> nome;

			cout << "Qual o email do contato?" << endl;
			cin >> email;

			cout << "Qual a idade do contato?" << endl;
			cin >> idade;

			inserir_balanceado(&t, rand() % 10000, nome, email, idade);
			cout << "Contato adicionado" << endl;

			break;
		case 2:
			system("clear");
			cout << "Qual o id do contato que vc quer remover?" << endl;
			cin >> id;
			remover(&t, id);
			break;
		case 3:
			system("clear");
			cout << "Qual o id do contato que você quer buscar?" << endl;
			cout << "Digite -1 se quiser listar todos" << endl;
			cin >> id;
			system("clear");
			if(!t)
				cout << "Não há contatos adicionados" << endl;
			busca_em_profundidade(&s, id, t, &continuar);
			break;
		case 4:
			system("clear");
			cout << "Qual o id do contato que você quer buscar?" << endl;
			cout << "Digite -1 se quiser listar todos" << endl;
			cin >> id;
			system("clear");
			if(!t)
				cout << "Não há contatos adicionados" << endl;
			busca_em_largura(-1, t, &continuar);
			break;
		default:
			system("clear");
			cout << "Digite uma opção entre 0 e 4" << endl;
			break;
		}
		continuar = true;


	}while(opc != 0);
}


