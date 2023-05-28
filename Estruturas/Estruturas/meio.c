#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include "registos.h"
#include "meio.h"
#include "cliente.h"

Cliente* adicionarSaldo(Cliente* inicio, int id, int saldo);



Meio* adicionarMeio(Meio* inicio, int id, char meio[], char localizacao[], int bat, int autonomia, int custo, int reservado, int idcliente)
{
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
		novo->idcliente = idcliente;
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
			fprintf(fp, "%d;%s;%s;%d;%d;%d;%d;%d\n", meio->id, meio->meio, meio->localizacao, meio->bateria, meio->autonomia, meio->custo, meio->reservado, meio->idcliente);
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
	int i,bat, aut, custo, res, icliente;
	char tipomeio[50], loc[50];

	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;];%[^;];%d;%d;%d;%d;%d\n", &i, tipomeio, loc, &bat, &aut, &custo, &res, &icliente);
			meio = adicionarMeio(meio, i, tipomeio, loc, bat, aut, custo, res, icliente);
		}
		fclose(fp);
	}
	return (meio);
}

int lerIdMeioDisponivel(Meio* inicio)
{
	int aux = 1;
	Meio* meio = inicio;

	while (meio != NULL)
	{
		aux++;
		meio = meio->seguinte;
	}
	return aux;
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

void mostrarMeiosDisponiveis(Meio* inicio)
{
	printf("\nLista dos meios disponiveis.\n\n");
	while (inicio != NULL)
	{
		if (inicio->reservado == 0)
		{
			printf("ID: %d\nMeio: %s\nLocalizacao: %s\nBateria: %d\nAutonomia: %d\nCusto: %d\nEstado: Disponivel\n\n", inicio->id, inicio->meio, inicio->localizacao, inicio->bateria, inicio->autonomia, inicio->custo);
		}
		inicio = inicio->seguinte;
	}
}

void mostrarMeiosReservados(Meio* inicio, int idCliente)
{
	printf("\nLista dos meios reservados por si.\n\n");
	while (inicio != NULL)
	{
		if (inicio->reservado == 1)
		{
			if (inicio->idcliente == idCliente)
			{
				printf("ID: %d\nMeio: %s\nLocalizacao: %s\nBateria: %d\nAutonomia: %d\nCusto: %d\nEstado: A ser utilizado\n\n", inicio->id, inicio->meio, inicio->localizacao, inicio->bateria, inicio->autonomia, inicio->custo);
			}
		}
		inicio = inicio->seguinte;
	}
}

Meio* reservarMeio(Meio* inicio,Cliente* inicioC, int id, int saldo, int idCliente)
{
	Meio* meio = inicio; // Apontar para o início da lista
	Cliente* cliente = inicioC;

	int c, d;
	while (meio != NULL)
	{
		if (id == meio->id)
		{
			if (meio->reservado == 1)
			{
				printf("Meio nao disponivel para reserva.\n");
			}
			else
			{
				if(saldo<meio->custo)
				{
					printf("Nao tem saldo suficiente.\n");
				}
				else
				{
					meio->reservado = 1; // Atualizar o estado de reserva para 0
					meio->idcliente = idCliente; //Atualiza o idcliente de 0 para o respetivo id do cliente
					printf("Meio reservado com sucesso.\n");
					c = salvarMeio(inicio);
					d = guardarRegistos("Entrega", idCliente, id);
					inicioC = removerSaldo(cliente, idCliente, (meio->custo));
					
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
	int c, d;
	int aux;
	aux = idCliente;

	while (meio != NULL)
	{
		if (id == meio->id)
		{
			if (meio->reservado == 1)
			{
				if (meio->idcliente == aux)
				{
					meio->reservado = 0;// Atualizar o estado de reserva para 0
					meio->idcliente = 0; //atualiza o id associado ao meio para 0
					printf("Meio entregue com sucesso.\n");
					c = salvarMeio(inicio);
					d = guardarRegistos("Entrega", idCliente, id);
				}
				else
				{
					printf("Nao e possivel entregar um meio reservado por outra pessoa.\n");
				}
			}
			else
			{
				printf("Nao e possivel entregar um meio que nao esteja reservado.\n");
			}
			return inicio; // Retornar o início da lista após a atualização
		}
		meio = meio->seguinte; // Avançar para o próximo meio na lista
	}
	// Se o meio com o ID especificado não foi encontrado na lista, exibir mensagem de erro
	printf("Meio nao encontrado.\n");
	return inicio;
}

void ordenarPorAutonomia(Meio* inicio) {
	int trocado = 1;
	while (trocado) {
		trocado = 0;
		Meio* anterior = NULL;
		Meio* atual = inicio;
		while (atual->seguinte != NULL) {
			if (atual->autonomia < atual->seguinte->autonomia) {
				Meio* proximo = atual->seguinte;
				atual->seguinte = proximo->seguinte;
				proximo->seguinte = atual;
				if (anterior != NULL) {
					anterior->seguinte = proximo;
				}
				else {
					inicio = proximo;
				}
				anterior = proximo;
				trocado = 1;
			}
			else {
				anterior = atual;
				atual = atual->seguinte;
			}
		}
	}
}

void listarPorAutonomia(Meio* inicio)
{
	if (inicio == NULL) {
		printf("Nenhum transporte registado.\n");
		return;
	}
	ordenarPorAutonomia(inicio);
	while (inicio != NULL) {
		printf("ID: %d\nMeio: %s\nLocalizacao: %s\nBateria: %d\nAutonomia: %d\nCusto: %d\nEstado: %d\n\n", inicio->id, inicio->meio, inicio->localizacao, inicio->bateria, inicio->autonomia, inicio->custo, inicio->reservado);
		inicio = inicio->seguinte;
	}
}

void mostrarPorLocalizacao(Meio* inicio, char loc[])
{
	Meio* meio = inicio; // Apontar para o início da lista
	int i = 0;
	printf("Meios disponiveis na localizacao: %s\n\n", loc);
	while (meio != NULL)
	{
		if (strcmp(meio->localizacao, loc) == 0)
		{
			printf("ID: %d\nMeio: %s\nLocalizacao: %s\nBateria: %d\nAutonomia: %d\nCusto: %d\nEstado: %d\n\n", meio->id, meio->meio, meio->localizacao, meio->bateria, meio->autonomia, meio->custo, meio->reservado);
			i++;
		}
		meio = meio->seguinte;
	}
	if(i==0)
	{
		printf("Nenhum meio disponivel nessa localizacao.\n");
	}
}