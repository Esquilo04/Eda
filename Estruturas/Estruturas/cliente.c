#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cliente.h"


int existeCliente(Cliente* inicio, int id)
{
	while (inicio != NULL)
	{
		if (inicio->id == id)
		{
			return(1);
		}
		inicio = inicio->seguinte;
	}
	return(0);
}

Cliente* adicionarCliente(Cliente* inicio, int id, char nome[], char username[], char password[], int contacto, int nif, char morada[], int saldo)
{
	Cliente* novo = malloc(sizeof(struct cliente));
	if (novo != NULL)
	{
		novo->id = id;
		strcpy(novo->nome, nome);
		strcpy(novo->username, username);
		strcpy(novo->password, password);
		novo->contacto = contacto;
		novo->nif = nif;
		strcpy(novo->morada, morada);
		novo->saldo = saldo;
		novo->seguinte = inicio;
		return(novo);
	}
	else
	{
		return(inicio);
	}
}

void mostrarCliente(Cliente* inicio)
{
	printf("\nLista dos clientes.\n\n");
	while (inicio != NULL)
	{
		printf("ID: %d\nNome: %s\nUtilizador: %s\nPassword: %s\nContacto: %d\nNIF: %d\nMorada: %s\nSaldo: %d\n\n", inicio->id, inicio->nome, inicio->username, inicio->password, inicio->contacto, inicio->nif, inicio->morada, inicio->saldo);
		inicio = inicio->seguinte;
	}
}

int salvarCliente(Cliente* inicio)
{
	FILE* fp;

	fp = fopen("Clientes.txt", "w");

	if (fp != NULL)
	{
		Cliente* novo = inicio;
		while (novo != NULL)
		{
			fprintf(fp, "%d;%s;%s;%s;%d;%d;%s;%d\n", novo->id, novo->nome, novo->username, novo->password, novo->contacto, novo->nif, novo->morada, novo->saldo);
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

Cliente* lerCliente()
{
	FILE* fp;
	Cliente* cliente = NULL;

	fp = fopen("Clientes.txt", "r");
	int n = 0, i = 0, c = 0, s = 0;
	char no[50], p[50], u[50], m[50];

	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;];%[^;];%[^;];%d;%d;%[^;];%d\n", &i, &no, &u, &p, &c, &n, &m, &s);
			cliente = adicionarCliente(cliente, i, no, u, p, c, n, m, s);
		}
		fclose(fp);
	}
	return (cliente);
}

Cliente* removerCliente(Cliente* inicio, int id)
{
	Cliente* atual = inicio, * anterior = inicio, * aux;

	if (inicio == NULL)
	{
		return(NULL);
	}
	else if (atual->id == id)
	{
		aux = atual->seguinte;
		free(atual);
		printf("Cliente removido com sucesso.\n");
		return (aux);
	}
	else
	{
		while ((atual != NULL) && (atual->id != id))
		{
			anterior = atual;
			atual = atual->seguinte;
		}
		if (atual == NULL)return(inicio);
		else
		{
			anterior->seguinte = atual->seguinte;
			free(atual);
			printf("Cliente removido com sucesso.\n");
			return(inicio);
		}
	}
}

int loginCliente(Cliente* inicio, char username[], char password[])
{
	Cliente* cliente = inicio;
	while (cliente != NULL)
	{
		if (strcmp(cliente->username, username) == 0 && strcmp(cliente->password, password) == 0)
		{
			return 1;
		}
		cliente = cliente->seguinte;
	}
	return 0;
}

int lerIdCliente(Cliente* inicio, char username[])
{
	Cliente* cliente = inicio;
	int aux = -1; // Inicializar com valor inválido
	while (cliente != NULL)
	{
		if (strcmp(cliente->username, username) == 0)
		{
			aux = cliente->id;
			break; // Encontrou o cliente, sair do loop
		}
		cliente = cliente->seguinte;
	}
	return aux; // Retornar o valor de aux após percorrer toda a lista
}

void alterarDadosCliente(Cliente* inicio, int id)
{
	Cliente* anterior = inicio;
	char novonome[50], morada[50], username[50], password[50];
	int nif = 0, contacto = 0, opcao = 0;
	while (inicio != NULL)
	{
		if (inicio->id == id)
		{
			printf("Que dado deseja alterar?\n");
			printf("1 - Nome\n2 - Nome de Utilizador\n3 - Palavra passe\n4 - Morada\n5 - NIF\n6 - Contacto\n");
			scanf("%d", &opcao);
			switch (opcao)
			{
			case 1:
				printf("Digite o nome para a qual deseja alterar: ");
				scanf("%s", novonome);
				strcpy(anterior->nome, novonome);
				return(inicio);
				break;
			case 2:
				printf("Digite o novo nome de utilizador: ");
				scanf("%s", username);
				strcpy(inicio->username, username);
				return(inicio);
				break;
			case 3:
				printf("Digite a nova palavra passe: ");
				scanf("%s", password);
				strcpy(inicio->password, password);
				return(inicio);
				break;
			case 4:
				printf("Digite a nova morada: ");
				scanf("%s", morada);
				strcpy(inicio->morada, morada);
				return(inicio);
				break;
			case 5:
				printf("Digite o novo NIF para a qual deseja alterar: ");
				scanf("%d", &nif);
				inicio->nif = nif;
				return(inicio);
				break;
			case 6:
				printf("Digite o novo contacto: ");
				scanf("%d", &contacto);
				inicio->contacto = contacto;
				return(inicio);
				break;
			}
		}
		else
		{
			inicio = inicio->seguinte;
		}


	}
}

Cliente* adicionarSaldo(Cliente* inicio, int id, int saldo)
{
	while (inicio != NULL)
	{
		if (inicio->id == id)
		{
			inicio->saldo += saldo;
			printf("Saldo adicionado com sucesso.\n\n");
			return(inicio);
		}
		else
		{
			inicio = inicio->seguinte;
		}

	}
}

Cliente* removerSaldo(Cliente* inicio, int id, int saldo)
{
	while (inicio != NULL)
	{
		if (inicio->id == id)
		{
			inicio->saldo -= saldo;
			return(inicio);
		}
		else
		{
			inicio = inicio->seguinte;
		}

	}
}

int lerMaiorIdCliente()
{
	int id, maiorId = 0;
	FILE* fp = fopen("clientes.txt", "r");
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

int lerSaldoCliente(Cliente* inicio, int id)
{
	Cliente* cliente = inicio;
	int aux;

	while (cliente != NULL)
	{
		if (id == cliente->id)
		{
			aux = cliente->saldo;
			return aux;
		}
		cliente = cliente->seguinte;
	}
	return -1;
}


