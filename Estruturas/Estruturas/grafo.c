#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>

#include "grafo.h"
#include "meio.h"
#define INFINITO 99999999


int criarVertice(Grafo* g, int id, char geo[])
{
    Grafo novo = *g;
    Adjacente adj;

    novo = malloc(sizeof(struct registo1));
    if (novo != NULL)
    {
        novo->id = id;
        strcpy(novo->geo, geo);
        novo->adjacentes = NULL;
        novo->meio = NULL;
        novo->clientes = NULL;
        novo->seguinte = *g;
        *g = novo;
        return 1;
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

int inserirMeio(Grafo g, Meio* inicio, int id, int codigoMeio)
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
                    // if (strcmp(g->geo, meio->localizacao) == 0)
                     //{
                    Meios novo = malloc(sizeof(struct registo3));
                    novo->codigo = codigoMeio;
                    novo->seguinte = g->meio;
                    g->meio = novo;
                    return(1);
                    //}
                    //else
                    //{
                      //  printf("O geocodigo do veiculo nao e o mesmo do vertice!\n");
                        //return(0);
                    //}
                }
                meio = meio->seguinte;
            }
        }
        else
        {
            g = g->seguinte;
        }
    }
}

int InserirClientes(Grafo g, Cliente* inicio, int idvertice, int idCliente)
{
    Cliente* cliente = inicio;
    while (g != NULL)
    {
        if (g->id == idvertice)
        {
            while (cliente != NULL)
            {
                if (cliente->id == idCliente)
                {
                    Clientes novo = malloc(sizeof(struct registo4));
                    novo->codigo = idCliente;
                    novo->seguinte = g->clientes;
                    g->meio = novo;
                    return(1);

                }
                cliente = cliente->seguinte;
            }
        }
        else
        {
            g = g->seguinte;
        }
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

    while (atual != NULL)
    {
        if (atual->id == id)
        {
            adj = atual->adjacentes;

            if (adj == NULL)
            {
                printf("O vertice %d nao possui vertices adjacentes.\n", id);
                return;
            }

            printf("Vertices adjacentes de %d:\n", id);
            while (adj != NULL)
            {
                if (adj->id != 0)
                {
                    printf("ID: %d  Peso: %d\n", adj->id, adj->peso);
                    aux++;
                }
                adj = adj->seguinte;
            }
            if (aux < 1)
            {
                printf("Nao possui vertices adjacentes.\n");
            }
            return;
        }
        atual = atual->seguinte;
    }

    printf("O vertice %d nao foi encontrado.\n", id);
}

int existeVertice(Grafo g, int id)
{
    while (g != NULL)
    {
        if (g->id == id)
        {
            return(1);
        }
        else
        {
            g = g->seguinte;
        }
    }
    printf("teste");
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

char obtergeocodigo(char localizacao[], char geo[])
{
    if (strcmp(geo, "safra.trenó.massas") == 0)
    {
        strcpy(localizacao, "Castelo");
        return(localizacao);
    }
    else if (strcmp(geo, "leiga.telha.valorizo") == 0)
    {
        strcpy(localizacao, "Hospital");
        return(localizacao);
    }
    else if (strcmp(geo, "nossas.mobilizações.cegos") == 0)
    {
        strcpy(localizacao, "shopping");
        return(localizacao);
    }
    else if (strcmp(geo, "clarinetistas.acha.papéis") == 0)
    {
        strcpy(localizacao, "Penha");
        return(localizacao);
    }
    else if (strcmp(geo, "massas.movam.sapato") == 0)
    {
        strcpy(localizacao, "Mercado");
        return(localizacao);
    }
    else if (strcmp(geo, "caules.rojão.penal") == 0)
    {
        strcpy(localizacao, "Rua Paio Galvao");
        return(localizacao);
    }
    else if (strcmp(geo, "crua.desejo.cálcio") == 0)
    {
        strcpy(localizacao, "Estatua D. Afonso Henriques");
        return(localizacao);
    }
    else if (strcmp(geo, "saem.beleza.canga") == 0)
    {
        strcpy(localizacao, "Estacao Ferroviaria");
        return(localizacao);
    }
    else if (strcmp(geo, "circo.dama.opondo") == 0)
    {
        strcpy(localizacao, "Toural");
        return(localizacao);
    }
    else
    {
        printf("Insira uma opcao valida!!");
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

int existeVertice2(Grafo g, int id)
{
    int aux = 10;

    while (g != NULL)
    {
        if (g->id == id)
        {
            aux = 11;
            return(aux);
        }
        else
        {
            g = g->seguinte;
        }
    }
    return aux;
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
            if (id2 == 0 && peso == 0)
            {
                criarVertice(&grafo, id, geo);
            }
            else
            {
                if (existeVertice2(grafo, id) == 11)
                {
                    if (existeVertice2(grafo, id2) == 11)
                    {
                        criarAresta(grafo, id, id2, peso);
                    }
                    else
                    {
                        criarVertice(&grafo, id2, geo);
                        criarAresta(grafo, id, id2, peso);
                    }
                }
                else
                {
                    if (existeVertice2(grafo, id2) == 11)
                    {
                        criarVertice(&grafo, id, geo);
                        criarAresta(grafo, id, id2, peso);
                    }
                    else
                    {
                        criarVertice(&grafo, id, geo);
                        criarVertice(&grafo, id2, geo);
                        criarAresta(grafo, id, id2, peso);
                    }
                }
            }
        }
        fclose(fp);
    }
    return(grafo);
}

void salvarMeiosPorId(Grafo g)
{
    Meios meios;
    FILE* fp;

    fp = fopen("Vertice.txt", "w");


    if (fp != NULL)
    {
        while (g != NULL)
        {
            meios = g->meio;

            while (meios != NULL)
            {
                fprintf(fp, "%d;%d\n", g->id, meios->codigo);
                meios = meios->seguinte;
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

void salvarClientesPorId(Grafo g)
{
    Clientes clientes;
    FILE* fp;

    fp = fopen("Vertice.txt", "w");


    if (fp != NULL)
    {
        while (g != NULL)
        {
            clientes = g->clientes;

            while (clientes != NULL)
            {
                fprintf(fp, "%d;%d\n", g->id, clientes->codigo);
                clientes = clientes->seguinte;
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

Grafo* lerConteudoVertice(Grafo g, Meio* inicio)
{
    FILE* fp;
    Meio* meio = inicio;

    fp = fopen("Vertice.txt", "r");
    int id = 0, id2 = 0;

    if (fp != NULL)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%d;%d\n", &id, &id2);
            inserirMeio(g, meio, id, id2);
        }
        fclose(fp);
    }
    return(g);
}

void mostrarMeiosPorDistancia(Grafo g, Meio* meio, int idVertice, int raio)
{
    Grafo vertice = g;
    char geo[50], rua[50];
    while (vertice != NULL)
    {
        if (vertice->id == idVertice)
        {
            geocodigo(geo, idVertice);
            obtergeocodigo(rua, geo);
            printf("------------------------------------------------------------------\n");
            printf("Meios Disponiveis na localizacao %s (localizacao atual):\n", rua);
            listarMeiosPorId(vertice->meio, meio);

            Adjacente adj = vertice->adjacentes;
            while (adj != NULL)
            {
                if (adj->id != 0 && adj->peso < raio)
                {
                    Grafo adjacente = g;
                    while (adjacente != NULL)
                    {
                        if (adjacente->id == adj->id)
                        {
                            break;
                        }
                        adjacente = adjacente->seguinte;
                    }
                    if (adjacente != NULL)
                    {
                        geocodigo(geo, adj->id);
                        obtergeocodigo(rua, geo);
                        printf("\nMeios Disponiveis na localizacao %s (%d metros de distancia):\n", rua, adj->peso);
                        listarMeiosPorId(adjacente->meio, meio);
                    }
                }
                adj = adj->seguinte;
            }
            printf("\n------------------------------------------------------------------\n");

            return;
        }
        vertice = vertice->seguinte;
    }
    printf("O vertice %d nao foi encontrado.\n", idVertice);
}

void listarMeiosPorId(Meios meio, Meio* meios) {
    if (meio == NULL) {
        printf("Nenhum meio disponivel.\n");
        return;
    }

    Meio* meioAtual = meios;

    while (meio != NULL) {
        while (meioAtual != NULL) 
        {
            if (meioAtual->id == meio->codigo) 
            {
                if (meioAtual->reservado == 0)
                {
                    printf("ID do meio: %d | Tipo: %s | Bateria: %d\n", meioAtual->id, meioAtual->meio, meioAtual->bateria);
                }
            }
            meioAtual = meioAtual->seguinte;
        }
        meio = meio->seguinte;
        meioAtual = meios; // Reiniciar a variável para percorrer a lista novamente
    }
}
