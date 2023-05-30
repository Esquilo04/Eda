#include <stdio.h>
#include <stdlib.h>
#include "meio.h";


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

typedef struct registo2
{
	int id; 
	int peso;
	struct registo2* seguinte;
} *Adjacente;

typedef struct registo1
{
	int id;
	char geo[50];
	Adjacente adjacentes;
	Meios meio;
	Clientes clientes;
	struct registo1* seguinte;
} *Grafo;

int criarVertice(Grafo* g, int id, char geo[]);
int criarAresta(Grafo g, int vOrigem, int vDestino, int peso);
int inserirMeio(Grafo g, Meio* inicio, int id, int codigoMeio);
int inserircliente(Grafo g, int id, int codigoclient);
void listarmeios(Grafo g, int codigomeio);
void listarAdjacentes(Grafo g, int id);
int existeVertice(Grafo g, int id);
char geocodigo(char localizacao[], int o);
void salvarGrafo(Grafo g);
Grafo* lerGrafo();
void salvarMeiosPorId(Grafo g);
Grafo* lerConteudoVertice(Grafo g, Meio* inicio);
int InserirClientes(Grafo g, Cliente* inicio, int idvertice, int idCliente);
void salvarClientesPorId(Grafo g);
int existeVertice2(Grafo g, int id);
char obtergeocodigo(char localizacao[], char geo[]);

void mostrarMeiosPorDistancia(Grafo g, Meio* meio, int idVertice, int raio);
void listarMeiosPorId(Meios meio, Meio* meios);