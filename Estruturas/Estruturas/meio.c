#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include "registos.h"
#include "meio.h"
#include "cliente.h"

Cliente* adicionarSaldo(Cliente* inicio, int id, int saldo);



Meio* adicionarMeio(Meio* inicio, int id, char meio[], char localizacao[], int bat, int autonomia, int custo, int reservado)
{
	// Verificar se o meio com o mesmo ID já existe na lista encadeada
	Meio* atual = inicio;
	while (atual != NULL)
	{
		if (atual->id == id)
		{
			// Atualizar os dados do meio existente
			strcpy(atual->meio, meio);
			strcpy(atual->localizacao, localizacao);
			atual->bateria = bat;
			atual->autonomia = autonomia;
			atual->custo = custo;
			atual->reservado = reservado;
			return inicio;
		}
		atual = atual->seguinte;
	}

	// Se o meio não existe, adicionar um novo meio à lista encadeada
	Meio* novo = malloc(sizeof(struct meio));
	if (novo != NULL)
	{
		novo->id = id;
		strcpy(novo->meio, meio);
		strcpy(novo->localizacao, localizacao);
		novo->bateria = bat;
		novo->autonomia = autonomia;
		novo->custo = custo;
		novo->reservado = reservado;
		novo->seguinte = inicio;
		return(novo);
	}
	else
	{
		return(inicio);
	}
}

int salvarMeio(Meio* inicio)
{
	FILE* fp;

	fp = fopen("Meios.txt", "w");

	if (fp != NULL)
	{
		Meio* meio = inicio;
		while (meio != NULL)
		{
			fprintf(fp, "%d;%s;%s;%d;%d;%d;%d\n", meio->id, meio->meio, meio->localizacao, meio->bateria, meio->autonomia, meio->custo, meio->reservado);
			meio = meio->seguinte;
		}
		fclose(fp);
		return(1);
	}
	else
	{
		return(0);
	}
} 

Meio* lerMeio()
{
	FILE* fp;
	Meio* meio = NULL;

	fp = fopen("Meios.txt", "r");
	int i,bat, aut, custo, res;
	char tipomeio[50], loc[50];

	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;];%[^;];%d;%d;%d;%d;%d\n", &i, tipomeio, loc, &bat, &aut, &custo, &res);
			meio = adicionarMeio(meio, i, tipomeio, loc, bat, aut, custo, res);
		}
		fclose(fp);
	}
	return (meio);
}

int lerMaiorIdMeio()
{
	int id, maiorId = 0;
	FILE* fp = fopen("Meios.txt", "r");
	if (fp != NULL)
	{
		while (fscanf(fp, "%d", &id) == 1)
		{
			if (id > maiorId)
			{
				maiorId = id;
			}
		}
		fclose(fp);
	}
	return maiorId;
}

Meio* removerMeio(Meio* inicio, int id)
{
	Meio* atual = inicio, * anterior = NULL, * aux;

	if (atual->id == id)
	{
		aux = atual->seguinte;
		free(atual);
		printf("Meio removido com sucesso.\n");
		return aux;
	}
	else
	{
		while ((atual != NULL) && (atual->id != id))
		{
			anterior = atual;
			atual = atual->seguinte;
		}
		if (atual == NULL)
		{
			printf("Meio nao encontrado.\n");
			return inicio;
		}
		else
		{
			anterior->seguinte = atual->seguinte;
			free(atual);
			printf("Meio removido com sucesso.\n");
			return inicio;
		}
	}
}

void mostrarMeio(Meio* inicio)
{
	printf("\nLista dos meios.\n\n");
	while (inicio != NULL)
	{
		printf("ID: %d\nMeio: %s\nLocalizacao: %s\nBateria: %d\nAutonomia: %d\nCusto: %d\nEstado: %d\n\n", inicio->id, inicio->meio, inicio->localizacao, inicio->bateria, inicio->autonomia, inicio->custo, inicio->reservado);
		inicio = inicio->seguinte;
	}
}

Meio* reservarMeio(Meio* inicio, int id, int saldo, int idCliente)
{
	Meio* meio = inicio; // Apontar para o início da lista
	Cliente* cliente = NULL;

	while (meio != NULL)
	{
		if (id == meio->id)
		{
			if (meio->reservado == 0)
			{
				printf("Meio ja reservado.\n");
			}
			else
			{
				if(saldo<meio->custo)
				{
					printf("Nao tem saldo suficiente");
				}
				else
				{
					meio->reservado = 0; // Atualizar o estado de reserva para 0
					printf("Meio reservado com sucesso.\n");
					cliente = adicionarSaldo(cliente, idCliente, saldo);
					salvarMeio(inicio);
					guardarRegistos("Reserva", idCliente, id);
					
				}
			}
			return inicio; // Retornar o início da lista após a atualização
		}
		meio = meio->seguinte; // Avançar para o próximo meio na lista
	}

	// Se o meio com o ID especificado não foi encontrado na lista, exibir mensagem de erro
	printf("Meio nao encontrado.\n");
	return inicio;
}

Meio* entregarMeio(Meio* inicio, int id, int idCliente)
{
	Meio* meio = inicio; // Apontar para o início da lista

	while (meio != NULL)
	{
		if (id == meio->id)
		{
			if (meio->reservado == 1)
			{
				printf("Nao e possivel entregar um meio que nao esteja reservado por si.\n");
			}
			else
			{
				meio->reservado = 1; // Atualizar o estado de reserva para 0
				printf("Meio entregue com sucesso.\n");
				salvarMeio(inicio);
				guardarRegistos("Entrega", idCliente, id);
			}
			return inicio; // Retornar o início da lista após a atualização
		}
		meio = meio->seguinte; // Avançar para o próximo meio na lista
	}
	// Se o meio com o ID especificado não foi encontrado na lista, exibir mensagem de erro
	printf("Meio nao encontrado.\n");
	return inicio;
}

int aux(int x) //funcao criada para caso seja reservado um meio, funcao retorna 1
{
	int a = x;
	return a;
}