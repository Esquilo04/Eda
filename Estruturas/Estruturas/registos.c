#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "registos.h"

int guardarRegistos(char nome[], int idCliente, int idMeio)
{
	FILE* fp;
	fp = fopen("Registos.txt", "a");

	int dia, mes, hora, minuto;

	// Obter a hora e data atuais
	time_t t = time(NULL);
	struct tm* hora_data = localtime(&t);
	dia = hora_data->tm_mday;
	mes = hora_data->tm_mon + 1;
	hora = hora_data->tm_hour;
	minuto = hora_data->tm_min;

	if (fp != NULL)
	{
		fprintf(fp, "Opcao: %s\nID cliente: %d\nID Meio: %d\nData: %02d/%02d\nHora: %02d:%02d\n\n", nome, idCliente, idMeio, dia,
		mes, hora, minuto);
		fclose(fp);
		return(1);
	}
	else
	{
		return(0);
	}
}
