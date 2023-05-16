#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//#include <conio.h>

#include "cliente.h"
#include "gestor.h"
#include "meio.h"
#include "grafo.h"

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
	printf("9 - Voltar ao menu. \n");
	scanf("%d", &opcao);
	return (opcao);
}

int menuGestorGestores()
{
	int opcao;
	printf(" ----------------------------\n");
	printf("|    Menu Gestor Gestores    |\n");
	printf(" ----------------------------\n\n\n");
	printf("1 - Adicionar gestor\n");
	printf("2 - Remover gestor\n");
	printf("3 - Alterar dados de um gestor\n");
	printf("4 - Listar gestores na consola\n");
	printf("5 - Adicionar vertice (rua) a um grafo\n");
	printf("6 - Adicionar peso (distancia) entre dois vertices\n");
	printf("7 - Listar adjacentes e peso de um vertice\n");
	printf("9 - Voltar ao menu.\n");
	scanf("%d", &opcao);
	return(opcao);
}

int menuGestorMeios()
{
	int op;
	printf(" -----------------------------\n");
	printf("|      Menu Gestor Meios      |\n");
	printf(" -----------------------------\n\n\n");
	printf("1 - Adicionar meio\n");
	printf("2 - Remover meio\n");
	printf("3 - Listar meios na consola\n");
	printf("4 - Ordenar meios por autonomia\n");
	printf("5 - Procurar meios por determinada localizacao\n");
	printf("9 - Voltar ao menu\n");
	scanf("%d", &op);
	return(op);
}

int menuGestorClientes()
{
	int op;
	printf(" -----------------------------\n");
	printf("|     Menu Gestor Clientes    |\n");
	printf(" -----------------------------\n\n\n");
	printf("1 - Adicionar cliente\n");
	printf("2 - Remover cliente\n");
	printf("3 - Listar clientes na consola\n");
	printf("4 - Adicionar saldo\n");
	printf("5 - Alterar determinado dado de um cliente\n");
	printf("6 - Adicionar cliente a um vertice\n");
	printf("7 - Listar clientes por rua\n");
	printf("9 - Voltar ao menu\n");
	scanf("%d", &op);
	return (op);
}


void clearr()
{
	printf("\033[2J\033[H");

}

int main()
{
	Grafo guimaraes = NULL;
//	guimaraes = lerGrafo();

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
	int bat, aut, cus;
	int opcao = 0, cargo;
	do {
		printf("\nQual o seu cargo?\n\n");
		printf("1 - Gestor.\n");
		printf("2 - Cliente.\n");
		printf("0 - Sair.\n");
		scanf("%d", &cargo);

		if (cargo == 2)
		{
			clearr();
			int opcao2;
			do {
				printf("O que deseja fazer?\n");
				printf("1 - Registar novo usuario.\n");
				printf("2 - Login.\n");
				printf("9 - Sair.\n");
				scanf("%d", &opcao2);
				if (opcao2 == 1)
				{
					cliente = lerCliente();
					clearr();
					idCliente = lerIdDisponivel(cliente);
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
					clearr();
				}
				else if (opcao2 == 2)
				{
					clearr();
					meio = lerMeio();
					char username1[50];
					printf("Qual e o seu nome de utilizador?\n");
					scanf("%s", username1);
					printf("Qual e a sua password?\n");
					scanf("%s", password);

					if (loginCliente(cliente, username1, password) == 1)
					{
						clearr();
						int opcao5;
						printf("Login efetuado com sucesso.\n");
						idLoginCliente = lerIdCliente(cliente, username1);
						int saldo;

						do {
							opcao5 = menuCliente();
							if (opcao5 == 1)
							{
								cliente = lerCliente();
								saldo = lerSaldoCliente(cliente, idLoginCliente);
								int auxx;
								clearr();
								mostrarMeiosDisponiveis(meio);
								printf("Qual o id do meio que deseja reservar?\n");
								scanf("%d", &idMeio);
								clearr();
								meio = reservarMeio(meio, cliente, idMeio, saldo, idLoginCliente);
								int salvarmeio(meio);
								salvarCliente(cliente);
							}
							if (opcao5 == 2)
							{
								clearr();
								alterarDadosCliente(cliente, idLoginCliente);
								salvarCliente(cliente);
							}
							if (opcao5 == 3)
							{
								printf("Quanto saldo pretende adicionar?\n");
								scanf("%d", &saldo);
								clearr();
								cliente = adicionarSaldo(cliente, idLoginCliente, saldo);
								salvarCliente(cliente);
							}
							if (opcao5 == 4)
							{
								clearr();
								meio = lerMeio();
								mostrarMeiosReservados(meio, idLoginCliente);
								printf("\n\nQual o id do meio que deseja entregar?\n");
								scanf("%d", &idMeio);
								clearr();
								meio = entregarMeio(meio, idMeio, idLoginCliente);
							}
							else if (opcao5 == 9)
							{
								clearr();
							}
						} while (opcao5 != 9);
					}
					else {
						clearr();
						printf("\nLogin incorreto.\n\n");
					}
				}
				else if (opcao2 == 9)
				{
					clearr();
				}
			} while (opcao2 != 9);
		}
		else if (cargo == 1)
		{
			clearr();
			gestor = lerGestor();
			printf("Qual e o seu nome de utilizador?\n");
			scanf("%s", username);
			printf("Qual e a sua password?\n");
			scanf("%s", password);
			clearr();
			if (loginGestor(gestor, username, password) == 1)
			{
				int opcao;
				do {
					printf("Escolha uma opcao.\n");
					printf("1 - Gerir dados dos gestores\n");
					printf("2 - Gerir dados dos clientes.\n");
					printf("3 - Gerir dados dos meios.\n");
					printf("9 - Voltar ao menu.\n");
					scanf("%d", &opcao);
					clearr();
					if (opcao == 1)
					{
						clearr();
						int opcao2;
						do {
							opcao2 = menuGestorGestores();
							if (opcao2 == 1)
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
								clearr();
								gestor = adicionarGestor(gestor, idGestor, nomeGestor, passGestor, contactoGestor, nifGestor);
							}
							else if (opcao2 == 2)
							{
								printf("Aqui estao os dados dos gestores:\n\n");
								mostrarGestor(gestor);
								printf("Qual o id do gestor que pretende remover?\n");
								scanf("%d", &idGestor);
								clearr();
								gestor = removerGestor(gestor, idGestor);
							}
							else if (opcao2 == 3)
							{
								printf("Aqui estao os dados dos gestores:\n\n");
								mostrarGestor(gestor);
								printf("Qual e o id?\n");
								scanf("%d", &idGestor);
								clearr();
								alterarDadosGestor(gestor, idGestor);
							}
							else if (opcao2 == 4)
							{
								clearr();
								mostrarGestor(gestor);
							}
							else if (opcao2 == 5)
							{
								clearr();
								int id;
								char geo[50], c;
								do
								{
									printf("Qual o id do vertice (rua)?\n");
									scanf("%d", &id);
									geocodigo(geo);
									criarVertice(&guimaraes, id, geo);
									getchar(); //limpar memoria
									printf("Pretende adicionar mais vertices (ruas) (s/n)?\n");
									scanf("%c", &c);
								} while (c != 'n');
							}
							else if (opcao2 == 6)
							{
								clearr();
								int id, id2, peso;
								char c;
								do
								{
									printf("Qual o id do primeiro vertice (rua)?\n");
									scanf("%d", &id);
									printf("Qual o id do segundo vertice (rua)?\n");
									scanf("%d", &id2);
									printf("Qual o peso (distancia) entre eles?\n");
									scanf("%d", &peso);
									criarAresta(guimaraes, id, id2, peso);
									criarAresta(guimaraes, id2, id, peso); //cria o percurso inverso
									getchar();
									printf("Pretende continuar (s/n)?\n");
									scanf("%c", &c);
								} while (c != 'n');
							}
							else if (opcao2 == 7)
							{
								clearr();
								int id;
								printf("Qual o id do vertice?\n");
								scanf("%d", &id);
								listarAdjacentes(guimaraes, id);
							}
							else if (opcao2 == 9)
							{
								clearr();
							}
						} while (opcao2 != 9);
						salvarGestor(gestor);
						salvarGrafo(guimaraes);
					}
					else if (opcao == 2)
					{
						int opcaoid, opcaosaldo, opcao3;
						do {
						opcao3 = menuGestorClientes();
						cliente = lerCliente(cliente);
						//clear();
						if (opcao3 == 1)
						{
							clearr();
							idCliente = lerIdDisponivel(cliente);
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
							clearr();
							cliente = adicionarCliente(cliente, idCliente, nomeCliente, username, password, contactoCliente, nifCliente, morada, saldo);
							cliente = salvarCliente(cliente);
						}
						else if (opcao3 == 2)
						{
							clearr();
							printf("Aqui estao os dados dos cliente:\n\n");
							mostrarCliente(cliente);
							printf("Introduza o id do cliente a remover: ");
							scanf("%d", &opcaoid);
							clearr();
							cliente = removerCliente(cliente, opcao);
							cliente = salvarCliente(cliente);
						}
						else if (opcao3 == 3)
						{
							cliente = lerCliente();
							clearr();
							mostrarCliente(cliente);
						}
						else if (opcao3 == 4)
						{
							clearr();
							printf("Aqui estao os dados dos cliente:\n\n");
							mostrarCliente(cliente);
							printf("Qual o id do cliente que deseja adicionar saldo?\n");
							scanf("%d", &opcaoid);
							printf("Quanto saldo deseja adicionar?\n");
							scanf("%d", &opcaosaldo);
							clearr();
							cliente = adicionarSaldo(cliente, opcaoid, opcaosaldo);
							cliente = salvarCliente(cliente);
						}
						else if (opcao3 == 5)
						{
							printf("Aqui estao os dados dos cliente:\n\n");
							mostrarCliente(cliente);
							printf("Qual o id do cliente que deseja alterar os dados?\n");
							scanf("%d", &opcaosaldo);
							clearr();
							alterarDadosCliente(cliente, opcaosaldo);
							cliente = salvarCliente(cliente);
						}
						else if (opcao3 == 9)
						{
							clearr();
						}
					} while (opcao3 != 9);

					}
					else if (opcao == 3)
					{
						clearr();
						int opcao4;
						do {
							opcao4 = menuGestorMeios();
							meio = lerMeio();
							int opcaoid2;

							if (opcao4 == 1)
							{
								idMeio = lerMaiorIdMeio() + 1;
								printf("Qual o tipo do meio?\n");
								scanf("%s", meio_);
								printf("Qual e a localizacao do meio?\n");
								geocodigo(loc);
								printf("Quanta bateria tem o meio?\n");
								scanf("%d", &bat);
								printf("Qual e a autonomia do meio?\n");
								scanf("%d", &aut);
								printf("Qual e o custo do meio?\n");
								scanf("%d", &cus);
								clearr();
								meio = lerMeio();
								meio = adicionarMeio(meio, idMeio, meio_, loc, bat, aut, cus, 0, 0);
								meio = salvarMeio(meio);
							}
							else if (opcao4 == 2)
							{
								clearr();
								printf("Aqui estao os dados dos meios:\n\n");
								mostrarMeio(meio);
								printf("Introduza o id do meio a remover: ");
								scanf("%d", &opcaoid2);
								clearr();
								meio = lerMeio();
								meio = removerMeio(meio, opcaoid2);
								meio = salvarMeio(meio);
							}
							else if (opcao4 == 3)
							{
								clearr();
								mostrarMeio(meio);
							}
							else if (opcao4 == 4)
							{
								clearr();
								listarPorAutonomia(meio);
							}
							else if (opcao4 == 5)
							{
								clearr();
								char loc[100];
								printf("Qual a localizacao que deseja procurar meios disponiveis?\n");
								scanf("%s", loc);
								clearr();
								mostrarPorLocalizacao(meio, loc);
							}
							else if (opcao4 == 9)
							{
								clearr();
							}
						} while (opcao4 != 9);
					}
					else if (opcao == 9)
					{
						clearr();
					}
				} while (opcao != 9);
			}
			else { printf("Login incorreto.\n"); }
		}
	} while (cargo != 0);
	return(0);
}