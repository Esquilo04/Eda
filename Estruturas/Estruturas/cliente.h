#pragma once
#include <stdio.h>

typedef struct cliente
{
	int id;
	char nome[50];
	char username[50];
	char password[50];
	int contacto;
	int nif;
	int saldo;
	char morada[50];
	struct cliente* seguinte;
}Cliente;

int loginCliente(Cliente* inicio, char username[], char password[]);
Cliente* removerCliente(Cliente* inicio, int id);
Cliente* adicionarCliente(Cliente* inicio, int id, char nome[], char username[], char password[], int contacto, int nif, char morada[], int saldo);
void mostrarCliente(Cliente* inicio);
int existeCliente(Cliente* inicio, int id);
void alterarDadosCliente(Cliente* inicio, int id);
int salvarCliente(Cliente* inicio);
Cliente* lerCliente(inicio);
Cliente* adicionarSaldo(Cliente* inicio, int id, int saldo);
Cliente* removerSaldo(Cliente* inicio, int id, int saldo);
int lerMaiorIdCliente();
int lerIdCliente(Cliente* inicio, char username[]);
int lerSaldoCliente(Cliente* inicio, int id);
int lerIdDisponivel(Cliente* inicio);