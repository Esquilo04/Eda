#pragma once
#include <stdio.h>


typedef struct gestor {
	int id;
	char username[1000];
	char password[1000];
	int contacto;
	int nif;
	struct gestor* seguinte;
}Gestor;

int loginGestor(char user[], char pass[]);
Gestor* adicionarGestor(Gestor* inicio, int id, char nome[], char password[], int contacto, int nif);
int salvarGestor(Gestor* inicio);
void alterarDadosGestor(Gestor* inicio, int id);
Gestor* lerGestor();
Gestor* removerGestor(Gestor* inicio, int id);
void mostrarGestor(Gestor* inicio);
int existeGestor(Gestor* inicio, int id);
int lerMaiorIdGestor();
