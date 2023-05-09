#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#include "cliente.h"
#include "gestor.h"
#include "meio.h"

int idLoginCliente = 0;
int menulogin()
{
	int opcao;
	printf(" -------------------------\n");
	printf("|       Menu client       |\n");
	printf(" -------------------------\n\n\n");
	printf("1- Registar novo usuario \n");
	printf("2- Login                 \n");
	printf("0- Sair                  \n");
	printf("O que deseja realizar: ");
	scanf("%d", &opcao);
	return (opcao);
}

int menuCliente()
{
	int opcao;
	printf(" -----------------------\n");
	printf("|       Menu cliente    |\n");
	printf(" -----------------------\n\n\n");
	printf("1 - Reservar meio.\n");
	printf("2 - Alterar determinado dado da conta\n");
	printf("3 - Adicionar saldo na conta\n");
	printf("4 - Entregar meio.\n");
	printf("0 - Voltar ao menu. \n");
	scanf("%d", &opcao);
	return (opcao);
}

int menuGestorGestores()
{
	int opcao;
	printf(" ----------------------------\n");
	printf("|         Menu Gestor        |\n");
	printf(" ----------------------------\n\n\n");
	printf("1 - Adicionar gestor\n");
	printf("2 - Remover gestor\n");
	printf("3 - Alterar dados de um gestor\n");
	printf("4 - Listar gestores na consola\n");
	printf("0 - Voltar ao menu.\n");
	scanf("%d", &opcao);
	return(opcao);
}

int menuGestorMeios()
{
	int op;
	printf(" -----------------------------\n");
	printf("|         Menu Gestor         |\n");
	printf(" -----------------------------\n\n\n");
	printf("1 - Adicionar meio\n");
	printf("2 - Remover meio\n");
	printf("3 - Listar meios na consola\n");
	printf("4 - Ordenar meios por autonomia\n");
	printf("0 - Sair\n");
	scanf("%d", &op);
	return(op);
}

int menuGestorClientes()
{
	int op;
	printf(" -----------------------------\n");
	printf("|         Menu Gestor         |\n");
	printf(" -----------------------------\n\n\n");
	printf("1 - Adicionar cliente\n");
	printf("2 - Remover cliente\n");
	printf("3 - Listar clientes na consola\n");
	printf("4 - Adicionar saldo\n");
	printf("5 - Alterar determinado dado de um cliente\n");
	printf("0 - Sair\n");
	scanf("%d", &op);
	return (op);
}


void clear()
{
	system("@cls || clear");
}

int main()
{
	Cliente* cliente = NULL;
	cliente = lerCliente();
	int idCliente, contactoCliente, nifCliente, idRemover, idLoginCliente;;
	int saldo = 0;
	char nomeCliente[50], username[50], morada[50], password[50];

	Gestor* gestor = NULL;
	gestor = lerGestor();
	char nomeGestor[50], passGestor[50];
	int idGestor, contactoGestor, nifGestor;
	Meio* meio = NULL;

	int idMeio;
	char meio_[50], loc[50];
	int bat, aut, cus, res;
	int opcao = 0, cargo;
	do {
		printf("\nQual o seu cargo?\n\n");
		printf("1 - Gestor.\n");
		printf("2 - Cliente.\n");
		printf("0 - Sair.\n");
		scanf("%d", &cargo);

		if (cargo == 2)
		{
			int opcao2;
			do {
				clear();
				printf("O que deseja fazer?\n");
				printf("1 - Registar novo usuario.\n");
				printf("2 - Login.\n");
				printf("3 - Voltar ao menu.\n");
				scanf("%d", &opcao2);
				if (opcao2 == 1)
				{
					idCliente = lerMaiorIdCliente() + 1;
					idLoginCliente = idCliente;
					printf("Escreva o seu nome.\n");
					scanf("%s", nomeCliente);
					printf("Escreva o seu nome de utilizador.\n");
					scanf("%s", username);
					printf("Escreva a sua password.\n");
					scanf("%s", password);
					printf("Escreva o seu contacto.\n");
					scanf("%d", &contactoCliente);
					printf("Escreva o seu NIF.\n");
					scanf("%d", &nifCliente);
					printf("Escreva a sua morada.\n");
					scanf("%*c");
					scanf("%s", morada);
					printf("Quanto saldo pretende adicionar na conta?\n");
					scanf("%d", &saldo);
					cliente = adicionarCliente(cliente, idCliente, nomeCliente, username, password, contactoCliente, nifCliente, morada, saldo);
					salvarCliente(cliente);
					clear();
				}
				else if (opcao2 == 2)
				{
					meio = lerMeio();
					char username1[50];
					printf("Qual e o seu nome de utilizador?\n");
					scanf("%s", username1);
					printf("Qual e a sua password?\n");
					scanf("%s", password);

					if (loginCliente(cliente, username1, password) == 1)
					{
						idLoginCliente = lerIdCliente(cliente, username1);
						clear();
						int saldo;

						do {
							opcao = menuCliente();
							if (opcao == 1)
							{
								cliente = lerCliente();
								saldo = lerSaldoCliente(cliente, idLoginCliente);
								int auxx;
								clear();
								printf("Aqui estao os meios existentes:\n\n");
								mostrarMeio(meio);
								printf("\n\nQual o id do meio que deseja reservar?\n");
								scanf("%d", &idMeio);
								clear();
								meio = reservarMeio(meio, cliente, idMeio, saldo, idLoginCliente);
								salvarCliente(cliente);
							}
							if (opcao == 2)
							{
								clear();
								alterarDadosCliente(cliente, idLoginCliente);
								salvarCliente(cliente);
							}
							if (opcao == 3)
							{
								printf("Quanto saldo pretende adicionar?\n");
								scanf("%d", &saldo);
								clear();
								cliente = adicionarSaldo(cliente, idLoginCliente, saldo);
								salvarCliente(cliente);
							}
							if (opcao == 4)
							{
								clear();
								printf("Aqui estao os meios existentes:\n\n");
								mostrarMeio(meio);
								printf("\n\nQual o id do meio que deseja entregar?\n");
								scanf("%d", &idMeio);
								clear();
								meio = entregarMeio(meio, idMeio, idLoginCliente);
							}
						} while (opcao != 0);
					}
					else {
						printf("\nLogin incorreto.\n\n");
					}
				}
				else if (opcao2 == 3)
				{
					clear();
				}
			} while (opcao2 != 3);
		}
		else if (cargo == 1)
		{
			clear();
			gestor = lerGestor();
			printf("Qual e o seu nome de utilizador?\n");
			scanf("%s", username);
			printf("Qual e a sua password?\n");
			scanf("%s", password);
			clear();
			if (loginGestor(gestor, username, password) == 1)
			{
				do {
					int opcao;
					printf("Escolha uma opcao.\n");
					printf("1 - Gerir dados dos gestores\n");
					printf("2 - Gerir dados dos clientes.\n");
					printf("3 - Gerir dados dos meios.\n");
					printf("0 - Voltar ao menu.\n");
					scanf("%d", &opcao);
					clear();
					if (opcao == 1)
					{
						clear();
						do {
							opcao = menuGestorGestores();
							if (opcao == 1)
							{
								idGestor = lerMaiorIdGestor() + 1;
								printf("Qual e o seu nome?\n");
								scanf("%s", nomeGestor);
								printf("Qual e a sua password?\n");
								scanf("%s", passGestor);
								printf("Qual e o seu contacto?\n");
								scanf("%d", &contactoGestor);
								printf("Qual e o seu NIF?\n");
								scanf("%d", &nifGestor);
								clear();
								gestor = adicionarGestor(gestor, idGestor, nomeGestor, passGestor, contactoGestor, nifGestor);
							}
							else if (opcao == 2)
							{
								printf("Aqui estao os dados dos gestores:\n\n");
								mostrarGestor(gestor);
								printf("Qual o id do gestor que pretende remover?\n");
								scanf("%d", &idGestor);
								clear();
								gestor = removerGestor(gestor, idGestor);
							}
							else if (opcao == 3)
							{
								printf("Aqui estao os dados dos gestores:\n\n");
								mostrarGestor(gestor);
								printf("Qual e o id?\n");
								scanf("%d", &idGestor);
								clear();
								alterarDadosGestor(gestor, idGestor);
							}
							else if (opcao == 4)
							{
								clear();
								mostrarGestor(gestor);
							}
							else if (opcao == 0)
							{
								clear();
							}
						} while (opcao != 0);
						salvarGestor(gestor);
					}
					else if (opcao == 2)
					{
						int opcao1, opcao2;
						do {
						opcao = menuGestorClientes();
						cliente = lerCliente(cliente);
						clear();
						if (opcao == 1)
						{
							idCliente = lerMaiorIdCliente() + 1;
							printf("Qual o nome do cliente?\n");
							scanf("%s", nomeCliente);
							printf("Qual e o nome de usuario do cliente?\n");
							scanf("%s", username);
							printf("Qual e a password?\n");
							scanf("%s", password);
							printf("Qual e o contacto?\n");
							scanf("%d", &contactoCliente);
							printf("Qual e o NIF?\n");
							scanf("%d", &nifCliente);
							printf("Introduza a morada do cliente.\n");
							scanf("%s", morada);
							printf("Quanto saldo pretende adicionar na conta?\n");
							scanf("%d", &saldo);
							clear();
							cliente = adicionarCliente(cliente, idCliente, nomeCliente, username, password, contactoCliente, nifCliente, morada, saldo);
							cliente = salvarCliente(cliente);
						}
						else if (opcao == 2)
						{
							printf("Aqui estao os dados dos cliente:\n\n");
							mostrarCliente(cliente);
							printf("Introduza o id do cliente a remover: ");
							scanf("%d", &opcao);
							clear();
							cliente = removerCliente(cliente, opcao);
							cliente = salvarCliente(cliente);
						}
						else if (opcao == 3)
						{
							cliente = lerCliente();
							clear();
							mostrarCliente(cliente);
						}
						else if (opcao == 4)
						{
							clear();
							printf("Aqui estao os dados dos cliente:\n\n");
							mostrarCliente(cliente);
							printf("Qual o id do cliente que deseja adicionar saldo?\n");
							scanf("%d", &opcao1);
							printf("Quanto saldo deseja adicionar?\n");
							scanf("%d", &opcao2);
							clear();
							cliente = adicionarSaldo(cliente, opcao1, opcao2);
							cliente = salvarCliente(cliente);
						}
						else if (opcao == 5)
						{
							printf("Aqui estao os dados dos cliente:\n\n");
							mostrarCliente(cliente);
							printf("Qual o id do cliente que deseja alterar os dados?\n");
							scanf("%d", &opcao2);
							clear();
							alterarDadosCliente(cliente, opcao2);
							cliente = salvarCliente(cliente);
						}
						else if (opcao == 0)
						{
							clear();
						}
					} while (opcao != 0);

					}
					else if (opcao == 3)
					{
						clear();
						do {
							opcao = menuGestorMeios();
							meio = lerMeio();
							int opcao1;

							if (opcao == 1)
							{
								idMeio = lerMaiorIdMeio() + 1;
								printf("Qual o tipo do meio?\n");
								scanf("%s", meio_);
								printf("Qual e a localizacao do meio?\n");
								scanf("%s", loc);
								printf("Quanta bateria tem o meio?\n");
								scanf("%d", &bat);
								printf("Qual e a autonomia do meio?\n");
								scanf("%d", &aut);
								printf("Qual e o custo do meio?\n");
								scanf("%d", &cus);
								clear();
								res = 1;
								meio = lerMeio();
								meio = adicionarMeio(meio, idMeio, meio_, loc, bat, aut, cus, res);
								meio = salvarMeio(meio);
							}
							else if (opcao == 2)
							{
								clear();
								printf("Aqui estao os dados dos meios:\n\n");
								mostrarMeio(meio);
								printf("Introduza o id do meio a remover: ");
								scanf("%d", &opcao1);
								clear();
								meio = lerMeio();
								meio = removerMeio(meio, opcao1);
								meio = salvarMeio(meio);
							}
							else if (opcao == 3)
							{
								clear();
								mostrarMeio(meio);
							}
							else if (opcao == 4)
							{
								clear();
								listarPorAutonomia(meio);
							}
							else if (opcao == 0)
							{
								clear();
							}
						} while (opcao != 0);
					}
					else if (opcao == 0)
					{
						clear();
					}
				} while (opcao != 0);
			}
			else { printf("Login incorreto.\n"); }
		}
	} while (cargo != 0);
	return(0);
}