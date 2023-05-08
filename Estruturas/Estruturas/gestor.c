#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>

#include "gestor.h"


int loginGestor(Gestor* inicio, char username[], char password[])
{
	Gestor* gestor = inicio;
	while (gestor != NULL)
	{
		if (strcmp(gestor->username, username) == 0 && strcmp(gestor->password, password) == 0)
		{
			printf("\nLogin efetuado com sucesso!\n\n");
			return 1;
		}
		gestor = gestor->seguinte;

	}
	return 0;

}


int existeGestor(Gestor* inicio, int id)
{
	while (inicio != NULL)
	{
		if (inicio->id = id)
		{
			return(1);
		}
		inicio = inicio->seguinte;
	}
	return(0);
}

Gestor* adicionarGestor(Gestor* inicio, int id, char username[], char password[], int contacto, int nif)
{
	Gestor* novo = malloc(sizeof(struct gestor));
	if (novo != NULL)
	{
		novo->id = id;
		strcpy(novo->username, username);
		strcpy(novo->password, password);
		novo->contacto = contacto;
		novo->nif = nif;
		novo->seguinte = inicio;
		return(novo);
	}
	else
	{
		return(inicio);
	}
}

Gestor* removerGestor(Gestor* inicio, int id)
{
	Gestor* atual = inicio, * anterior = inicio, * aux;

	if (inicio == NULL)
	{
		return(NULL);
	}
	else if (atual->id == id)
	{
		aux = atual->seguinte;
		free(atual);
		printf("Gestor removido com sucesso.\n");
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
			printf("Gestor removido com sucesso.\n");
			return(inicio);
		}
	}
}

void mostrarGestor(Gestor* inicio)
{

	printf("\nLista dos gestores.\n\n");
	while (inicio != NULL)
	{
		printf("ID: %d\nNome: %s\nPassword: %s\nContacto: %d\nNIF: %d\n\n", inicio->id, inicio->username, inicio->password, inicio->contacto, inicio->nif);
		inicio = inicio->seguinte;
	}
}

void alterarDadosGestor(Gestor* inicio, int id)
{
	Gestor* atual = inicio;
	int nif = 0, contacto = 0, opcao = 0;
	char nome[50], password[50];
	while (inicio != NULL)
	{
		if (inicio->id == id)
		{
			printf("Que dado pretende alterar?\n");
			printf("1 - Nome de utilizador\n2 - Palavra passe\n3 - Contacto\n4 - NIF\n");
			scanf("%d", &opcao);
			switch (opcao)
			{
			case 1:
				printf("Digite o novo nome de utilizador.\n");
				scanf("%s", nome);
				strcpy(atual->username, nome);
				return(inicio);
				break;
			case 2:
				printf("Digite a nova palavra passe.\n");
				scanf("%s", password);
				strcpy(inicio->password, password);
				return(inicio);
				break;
			case 3:
				printf("Digite o novo contacto.\n");
				scanf("%d", &contacto);
				inicio->contacto = contacto;
				return(inicio);
				break;
			case 4:
				printf("Digite o novo NIF.\n");
				scanf("%d", &nif);
				inicio->nif = nif;
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

int salvarGestor(Gestor* inicio)
{
	FILE* fp;

	fp = fopen("Gestor.txt", "w");

	if (fp != NULL)
	{
		Gestor* gestor = inicio;
		while (gestor != NULL)
		{
			fprintf(fp, "%d;%s;%s;%d;%d\n", gestor->id, gestor->username, gestor->password, gestor->contacto, gestor->nif);
			gestor = gestor->seguinte;
		}
		fclose(fp);
		return(1);
	}
	else
	{
		return(0);
	}
}

Gestor* lerGestor()
{
	FILE* fp;
	Gestor* gestor = NULL;

	fp = fopen("Gestor.txt", "r");

	if (fp != NULL)
	{
		int id, contacto, nif;
		char username[1000], password[1000];
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;];%[^;];%d;%d\n", &id, username, password, &contacto, &nif);
			gestor = adicionarGestor(gestor, id, username, password, contacto, nif);
		}
		fclose(fp);
	}
	return(gestor);
}

int lerMaiorIdGestor()
{
	int id, maiorId = 0;
	FILE* fp = fopen("gestor.txt", "r");
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
