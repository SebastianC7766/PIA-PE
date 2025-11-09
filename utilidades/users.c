#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

int find_user()
{
	FILE *arch = fopen("binarios\\users.dat", "rb");
	if (arch == NULL)
	{
		printf("Error al acceder al archivo");
	}
	char inuser[20], inpswd[20];
	printf("USUARIO: ");
	scanf(" %19s", inuser);
	printf("CONTRASEÑA: ");
	char c;
	int i = 0;
	while ((c = getch()) != '\r')
	{ 
		if (c == '\b')
		{ 
			if (i > 0)
			{
				i--;
				printf("\b \b");
			}
		}
		else if (i < sizeof(inpswd) - 1)
		{
			inpswd[i++] = c;
			printf("*");
		}
	}
	inpswd[i] = '\0';
	user aux;
	while (fread(&aux, sizeof(user), 1, arch))
	{
		if (strcmp(inuser, aux.user) == 0 && strcmp(inpswd, aux.pswd) == 0)
		{
			return 1;
		}
	}
	fclose(arch);
	return 0;
}

void val_user()
{
	FILE *arch = fopen("binarios\\users.dat", "rb");
	if (arch == NULL)
	{
		arch = fopen("binarios\\users.dat", "wb");
		user admin;
		strcpy(admin.user, "admin");
		strcpy(admin.pswd, "admin");
		fwrite(&admin, sizeof(user), 1, arch);
		fclose(arch);
	}
	fclose(arch);
	while (find_user() == 0)
	{
		printf("\nCREDENCIALES NO VALIDAS, INTENTELO DE NUEVO EN 3 SEGUNDOS\n");
		Sleep(3000);  
		system("cls");
	} 
	printf("\nINICIO DE SESION VALIDO, BIENVENIDO\n");
	Sleep(1000);
	system("cls");
}

void add_user()
{
	system("cls");
	user nuevo;
	FILE *arch = fopen("binarios\\users.dat", "ab");
	if (arch == NULL)
	{
		printf("Error al acceder al archivo");
		return;
	}
	printf("Ingrese el nombre de usuario: ");
	scanf("%s", nuevo.user);
	printf("Ingrese la contraseña: ");
	scanf("%s", nuevo.pswd);
	fwrite(&nuevo, sizeof(user), 1, arch);
	fclose(arch);
	printf("\nUSUARIO AGREGADO CON EXITO\n");
	system("pause");
	system("cls");
}
