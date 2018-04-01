#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFERSIZE 100
#define TAMINIVET 100

typedef struct {
	int *vet;
	int cap, tam;
} lista;

lista *constroi_lista();
void destroi_lista(lista *l);
int aumenta_lista(lista *l);
int *Selecao(int *v, int a, int b);
int Minimo(int *v, int a, int b);
void Troca(int *v, int a, int b);
void imprime_lista(lista *l);
int *QuickSelect(int *v, int a, int b);
int Particiona(int *v, int a, int b, int pivot);
int *QuickSort(int *v, int a, int b);

void main() {
	lista *lista = NULL;
	char buffer[BUFFERSIZE];

	//Constroi a lista
	lista = constroi_lista();

	//Verifica se foi criada com sucesso
	if (!lista) return;

	//Carrega os dados para a lista
	while (fgets(buffer, BUFFERSIZE , stdin)) {
		//Verifica se precisa aumentar a lista
		if (lista->cap == lista->tam) {
			if (!aumenta_lista(lista)) return;
		}
		lista->vet[lista->tam++] = atoi(buffer);
  	}

  	QuickSelect(lista->vet, 0, lista->tam - 1);

  	imprime_lista(lista);

  	destroi_lista(lista);
}

lista *constroi_lista() {
	lista *l = malloc(sizeof(lista));

	if (!l) return NULL;

	l->cap = l->tam = 0;

	if (l->vet = malloc(TAMINIVET * sizeof(int))) {
		l->cap = TAMINIVET;
	}
	//printf("\nConstruindo a lista.\n");
	return l;
}

void destroi_lista(lista *l) {
	free(l->vet);
	l->vet = NULL;
	free (l);
	l = NULL;
	//printf("\nDestruindo a lista.\n");
}

int aumenta_lista(lista *l) {
	int nova = l->cap * 2;
	int *aum = realloc(l->vet, nova * sizeof(int));

	if (!aum) return 0;
	l->vet = aum;
	l->cap = nova;
	printf("\nAumentando a lista.\n");
	return 1;
}

int *Selecao(int *v, int a, int b) {
	if (a >= b) return v;

	Troca(v, a, Minimo(v, a, b));

	return Selecao(v, a + 1, b);
}

int Minimo(int *v, int a, int b) {
	if (a == b) return a;

	int m = Minimo(v, a, b - 1);

	if (v[b] < v[m]) m = b;

	return m;
}

void Troca(int *v, int a, int b) {
	int aux = v[a];
	v[a] = v[b];
	v[b] = aux;
}


void imprime_lista(lista *l) {
	int i;
  	//printf("\nImprimindo a lista.\n");

  	for (i = 0; i < l->tam; i++) {
  		printf("%d\n", l->vet[i]);
  	}
}

int *QuickSelect(int *v, int a, int b) {
	int k = 9;
	if (b - a + 1 < k) {//0 10
		Selecao(v, a, b);
		return v;
	}

	int m = Particiona(v, a, b, v[b]);//Particiona do professor na sala um pouco diferente do que ta na especificação do trabalho
	QuickSelect(v, a, m - 1);
	QuickSelect(v, m + 1, b);

	return v;
}

int Particiona(int *v, int a, int b, int pivot) {
	int i = a - 1;
	int y;

	for (y = a; y <= b - 1; y++) {
		if (v[y] < pivot) {
			i = i + 1;
			Troca(v, i, y);
		}
	}
	if (v[b] < v[i + 1]) Troca(v, i + 1, b);

	return i + 1;
}

int *QuickSort(int *v, int a, int b) {
	if (a < b) {
		int m = Particiona(v, a, b, v[b]);//Particiona do professor na sala um pouco diferente do que ta na especificação do trabalho
		QuickSort(v, a, m - 1);
		QuickSort(v, m + 1, b);
	}

	return v;
}