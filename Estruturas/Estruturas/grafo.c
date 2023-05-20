#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>

#include "grafo.h"
#include "meio.h"


int criarVertice(Grafo* g, int id, char geo[], int id2, int peso)
{
    Grafo novo = *g;
    Adjacente adj;

    // Verifica se o vértice com o mesmo ID já existe
    while (novo != NULL)
    {
        if (novo->id == id)
        {
            // Atualiza os valores da aresta existente
            adj = novo->adjacentes;
            while (adj != NULL)
            {
                if (adj->id == id2)
                {
                    adj->peso = peso;
                    return 1;
                }
                adj = adj->seguinte;
            }
        }
        novo = novo->seguinte;
    }

    // Cria um novo vértice se não existir
    novo = malloc(sizeof(struct registo1));
    if (novo != NULL)
    {
        novo->id = id;
        strcpy(novo->geo, geo);
        novo->adjacentes = NULL; // Inicializa o ponteiro adjacentes como NULL
        novo->meio = NULL;
        novo->clientes = NULL;
        novo->seguinte = *g;
        *g = novo;

        // Cria um novo vértice adjacente
        adj = malloc(sizeof(struct registo2));
        if (adj != NULL)
        {
            adj->id = id2;
            adj->peso = peso;
            adj->seguinte = novo->adjacentes;
            novo->adjacentes = adj;
            return 1;
        }
        else
        {
            printf("Erro ao alocar memória para vértice adjacente.\n");
            return 0;
        }
    }
    else
    {
        printf("Erro ao alocar memória para vértice.\n");
        return 0;
    }
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

int InserirMeio(Grafo g, Meio* inicio, int id, int codigoMeio)
{
    Meio* meio = inicio;
    while (g != NULL)
    {
        if (g->id == id)
        {
            while (meio != NULL)
            {
                if (meio->id == codigoMeio)
                {
                    if (strcmp(g->geo, meio->localizacao) == 0)
                    {
                        Meios novo = malloc(sizeof(struct registo3));
                        novo->codigo = codigoMeio;
                        novo->seguinte = g->meio;
                        g->meio = novo;
                        return(1);
                    }
                    else
                    {
                        printf("O geocodigo do veiculo nao e o mesmo do vertice!\n");
                        return(0);
                    }
                }
                else
                {
                    meio = meio->seguinte;
                }
            }
        }
        else
        {
            g = g->seguinte;
        }
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
            Meios aux = g->meio;
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
    Grafo atual = g;
    Adjacente adj;
    int aux = 0;

    // Encontra o vértice com o ID fornecido
    while (atual != NULL)
    {
        if (atual->id == id)
        {
            adj = atual->adjacentes;

            // Verifica se há vértices adjacentes
            if (adj == NULL)
            {
                printf("O vertice %d nao possui vertices adjacentes.\n", id);
                return;
            }

            // Itera pelos vértices adjacentes e imprime seus IDs e pesos
            printf("Vertices adjacentes de %d:\n", id);
            while (adj != NULL)
            {
                if (adj->id != 0 && adj->peso != 0)
                {
                    printf("ID: %d, Peso: %d\n", adj->id, adj->peso);
                    aux++;
                }
                adj = adj->seguinte;
            }
            if (aux<1)
            {
                printf("Nao possui vertices adjacentes.\n");
            }
            return;
        }

        atual = atual->seguinte;
    }

    // Se o vértice com o ID fornecido não for encontrado
    printf("O vertice %d não foi encontrado.\n", id);
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

char geocodigo(char localizacao[], int o)
{
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

void salvarGrafo(Grafo g)
{
    Adjacente adj;
    FILE* fp;

    int id = 0, peso = 0;
    fp = fopen("Grafo.txt", "w");


    if (fp != NULL)
    {
        while (g != NULL)
        {
            adj = g->adjacentes;
            if (adj == NULL)
            {
                fprintf(fp, "%d;%s;%d;%d\n", g->id, g->geo, id, peso);
            }
            else
            {
                while (adj != NULL)
                {
                    fprintf(fp, "%d;%s;%d;%d\n", g->id, g->geo, adj->id, adj->peso);
                    adj = adj->seguinte;

                }
            }
            g = g->seguinte;
        }
        fclose(fp);
    }
    else
    {
        printf("O ficheiro esta corrompido!\n");
    }
}

Grafo* lerGrafo()
{
    FILE* fp;
    Grafo* grafo = NULL; 

    fp = fopen("Grafo.txt", "r");

    if (fp != NULL)
    {
        int id, id2, peso;
        char geo[50];
        while (!feof(fp))
        {
            fscanf(fp, "%d;%[^;];%d;%d\n", &id, geo, &id2, &peso);
            //if (id2 == 0 && peso == 0)
            //{
           //     criarVertice(&grafo, id, geo, 0, 0);
            //}
            //else
            //{
                criarVertice(&grafo, id, geo, id2, peso);
                //criarVertice(&grafo, id2, geo, id, peso);
                //criarAresta(grafo, id, id2, peso);
            //}
        }
        fclose(fp);
    }
    return(grafo);
}


/*void salvarConteudoDeVertice(Grafo g)
{
    Grafo g;
    FILE* fp;

    fp = fopen("Vertice.txt", "w");


    if (fp != NULL)
    {
        while (g != NULL)
        {
            adj = g->adjacentes;
            if (adj == NULL)
            {
                fprintf(fp, "%d;%s;%d;%d\n", g->id, g->geo, id, peso);
            }
            else
            {
                while (adj != NULL)
                {
                    fprintf(fp, "%d;%s;%d;%d\n", g->id, g->geo, adj->id, adj->peso);
                    adj = adj->seguinte;

                }
            }
            g = g->seguinte;
        }
        fclose(fp);
    }
    else
    {
        printf("O ficheiro esta corrompido!\n");
    }
}
*/