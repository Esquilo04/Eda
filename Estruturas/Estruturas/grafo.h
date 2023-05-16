#include <stdio.h>
#include <stdlib.h>


typedef struct registo3
{
	int codigo;
	struct registo3* seguinte;
} *Meios;

typedef struct registo4
{
	int codigo;
	struct registo4* seguinte;
} *Clientes;

// Representa��o de um grafo orientado e pesado
typedef struct registo2
{
	int id; // geoc�digo what3words
	int peso;
	struct registo2* seguinte;
} *Adjacente;

typedef struct registo1
{
	int id; // geoc�digo what3words
	char geo[50];
	Adjacente adjacentes;
	Meios meios; // Lista ligada com os c�digos dos meios de transporte existente
	Clientes clientes;
	struct registo1* seguinte;
} *Grafo;

int criarVertice(Grafo* g, int Id, char geo[]);
int criarAresta(Grafo g, int vOrigem, int vDestino, int peso);
int inserirMeio(Grafo g, int id, int codigoMeio);
int inserircliente(Grafo g, int id, int codigoclient);
void listarmeios(Grafo g, int codigomeio);
void listarAdjacentes(Grafo g, int id);
int existeVertice(Grafo g, int id);
char geocodigo(char localizacao[]);
int salvarGrafo(Grafo g);
Grafo* lerGrafo();
