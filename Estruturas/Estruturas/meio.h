#pragma once
#include <stdio.h>
#include "cliente.h"

typedef struct meio {
	int id;
	char meio[50];
	char localizacao[50];
	int bateria;
	int autonomia;
	int custo;
	int reservado;
	struct meio* seguinte;
}Meio;

Meio* adicionarMeio(Meio* inicio, int id, char meio[], char localizacao[], int bat, int autonomia, int custo, int reservado);
Meio* removerMeio(Meio* inicio, int id);
void alterarDadosMeio(Meio* inicio, int id);
int salvarMeio(Meio* inicio);
Meio* lerMeio();
void mostrarMeio(Meio* inicio);
int lerMaiorIdMeio();
Meio* reservarMeio(Meio* inicio, Cliente* inicioC, int id, int saldo, int idCliente);
Meio* entregarMeio();
void ordenarPorAutonomia(Meio* inicio);
void listarPorAutonomia(Meio* inicio);
void mostrarMeiosDisponiveis(Meio* inicio);