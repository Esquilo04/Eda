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

// Representação de um grafo orientado e pesado
typedef struct registo2
{
	int id; // geocódigo what3words
	int peso;
	struct registo2* seguinte;
} *Adjacente;

typedef struct registo1
{
	int id; // geocódigo what3words
	char geo[50];
	Adjacente adjacentes;
	Meios meio; // Lista ligada com os códigos dos meios de transporte existente
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

int numVertices(Grafo g);
void teste(Meio* meio, char loca[], char tipomeio[]);
int obterMenorDistancia(int distancias[], int visitado[], int numVertices);
void imprimirCaminho(Grafo g, int caminho[], int verticeAtual);
void imprimirCaminhoMaisCurto(Grafo g, int caminho[], int distancias[], int inicio, int fim);
void encontrarCaminhoMaisCurto(Grafo g, Meio* teste15, int Vertices, int inicio, int fim, int limite, char tipo[]);
