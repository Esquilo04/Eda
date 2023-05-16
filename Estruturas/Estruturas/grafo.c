#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>

#include "grafo.h"


int criarVertice(Grafo* g, int Id, char geo[])
{
    Grafo novo = malloc(sizeof(struct registo1));
    if (novo != NULL)
    {
        novo->id = Id;
        strcpy(novo->geo, geo);
        novo->meios = NULL;
        novo->clientes = NULL;
        novo->adjacentes = NULL;
        novo->seguinte = *g;
        *g = novo;
        return(1);
    }
    else return(0);
}

int criarAresta(Grafo g, int vOrigem, int vDestino, int peso)
{
    Adjacente novo;
    if (existeVertice(g, vOrigem) && existeVertice(g, vDestino))
    {
        while (g != NULL)
        {
            if (g->id == vOrigem)
            {
                novo = malloc(sizeof(struct registo2));
                if (novo != NULL)
                {
                    novo->id = vDestino;
                    novo->peso = peso;
                    novo->seguinte = g->adjacentes;
                    g->adjacentes = novo;
                    return(1);
                }
                else return(0);
            }
            else
            {
                g = g->seguinte;
            }
        }
    }
    else return(0);
}

int inserirMeio(Grafo g, int id, int codigoMeio)
{
    while ((g != NULL) && (g->id == codigoMeio))
        g = g->seguinte;
    if (g == NULL) return(0);
    else {
        Meios novo = malloc(sizeof(struct registo3));
        novo->codigo = codigoMeio;
        novo->seguinte = g->meios;
        g->meios = novo;
        return(1);
    }
}

int inserircliente(Grafo g, int id, int codigoclient)
{
    while ((g != NULL) && (g->id == codigoclient))
        g = g->seguinte;
    if (g == NULL) return(0);
    else {
        Clientes novo = malloc(sizeof(struct registo3));
        novo->codigo = codigoclient;
        novo->seguinte = g->clientes;
        g->clientes = novo;
        return(1);
    }
}

void listarmeios(Grafo g, int codigomeio)
{
    while ((g != NULL) && (g->id == codigomeio))
    {
        if (g != NULL)
        {
            Meios aux = g->meios;
            if (aux == NULL) printf("sem meios de transporte\n");
            else while (aux != NULL)
            {
                printf("Codigo meio: %d\n", aux->codigo);
                aux = aux->seguinte;
            }
        }
        else printf("codigo inexistente\n");
        g = g->seguinte;
    }
}

void listarAdjacentes(Grafo g, int id)
{
    if (g == NULL) {
        printf("Grafo não inicializado.\n");
        return;
    }

    while (g != NULL && g->id != id)
    {
        g = g->seguinte;
    }

    if (g == NULL) {
        printf("Vertice nao encontrado.\n");
        return;
    }

    if (g->adjacentes == NULL) {
        printf("Sem adjacentes.\n");
        return;
    }

    Adjacente aux = g->adjacentes;
    while (aux != NULL)
    {
        printf("Adjacente: %d Peso: %d\n", aux->id, aux->peso);
                aux = aux->seguinte;
    }
}

int existeVertice(Grafo g, int id)
{
    while (g != NULL)
    {
        if (g->id == id) return(1);
        else g = g->seguinte;
    }
    return(0);
}

char geocodigo(char localizacao[])
{
    int o = 0;
    printf("1 - Castelo\n2 - Hospital\n3 - Shopping\n4 - Penha\n5 - Mercado Municipal\n6 - Rua Paio Galvao\n7 - Estatua D. Afonso Henriques\n8 - Estacao Ferroviria\n9 - Largo do Toural\n");
    scanf("%d", &o);
    if (o == 1)
    {
        strcpy(localizacao, "safra.trenó.massas");
        return(localizacao);
    }
    else if (o == 2)
    {
        strcpy(localizacao, "leiga.telha.valorizo");
        return(localizacao);
    }
    else if (o == 3)
    {
        strcpy(localizacao, "nossas.mobilizações.cegos");
        return(localizacao);
    }
    else if (o == 4)
    {
        strcpy(localizacao, "clarinetistas.acha.papéis");
        return(localizacao);
    }
    else if (o == 5)
    {
        strcpy(localizacao, "massas.movam.sapato");
        return(localizacao);
    }
    else if (o == 6)
    {
        strcpy(localizacao, "caules.rojão.penal");
        return(localizacao);
    }
    else if (o == 7)
    {
        strcpy(localizacao, "crua.desejo.cálcio");
        return(localizacao);
    }
    else if (o == 8)
    {
        strcpy(localizacao, "saem.beleza.canga");
        return(localizacao);
    }
    else if (o == 9)
    {
        strcpy(localizacao, "circo.dama.opondo");
        return(localizacao);
    }
    else
    {
        printf("Insira uma opcao valida!!");
        exit(0);
    }
}

int salvarGrafo(Grafo inicio)
{
    FILE* fp;

    fp = fopen("Grafo.txt", "w");

    if (fp != NULL)
    {
        Grafo novo = inicio;
        while (novo != NULL)
        {
            fprintf(fp, "%d;%s;\n", novo->id, novo->geo);
            novo = novo->seguinte;
        }
        fclose(fp);
        return(1);
    }
    else
    {
        return(0);
    }
}

Grafo* lerGrafo()
{
    FILE* fp;
    Grafo* grafo = NULL; //POR ASTERISCO

    fp = fopen("Grafo.txt", "r");

    if (fp != NULL)
    {
        int id;
        char geo[50];
        while (!feof(fp))
        {
            fscanf(fp, "%d;%[^;]\n", &id, geo);
            criarVertice(grafo, id, geo);
        }
        fclose(fp);
    }
    return(grafo);
}