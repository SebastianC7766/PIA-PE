#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

// estructura de usuario
typedef struct
{
	char user[20];
	char pswd[20];
} user;

void val_user();
int find_user();

// funcion principal para validar que el archivo exista y si no, lo crea con un usuario "admin" por defecto
void val_user()
{
	FILE *arch = fopen("users.dat", "rb");
	if (arch == NULL)
	{
		arch = fopen("users.dat", "wb"); // si no existe crea el archivo
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
		Sleep(3000);   // NOTA: esta funcion solo funciona en windows, pendiente: encontrar una forma de que sea portable en linux y windows
		system("cls"); // NOTA: esta funcion solo funciona en windows, pendiente: encontrar una forma de que sea portable en linux y windows
	} // el ciclo se repite mientras la funcion find_user regrese cero
	printf("\nINICIO DE SESION VALIDO, BIENVENIDO\n");
	Sleep(1000);
	system("cls");
}

// funcion para verificar que el usuario existe
int find_user()
{
	FILE *arch = fopen("users.dat", "rb");
	if (arch == NULL)
	{
		printf("Error al acceder al archivo");
	}
	char inuser[20], inpswd[20];
	printf("USUARIO: ");
	scanf(" %19s", inuser); // pide un usuario y contraseña y verifica si estan dentro del archivo
	printf("CONTRASEÑA: ");
	char c;
	int i = 0;
	while ((c = getch()) != '\r')
	{ // Enter = fin de entrada
		if (c == '\b')
		{ // Retroceso
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
	inpswd[i] = '\0'; // Termina la cadena
	user aux;
	while (fread(&aux, sizeof(user), 1, arch))
	{
		if (strcmp(inuser, aux.user) == 0 && strcmp(inpswd, aux.pswd) == 0)
		{
			return 1; // si estan dentro del archiv regresa un 1
		}
	}
	fclose(arch);
	return 0; // si no se enceuntran regresa un 0
}

// funcion para agregar usuario
void add_user()
{
	user nuevo;
	FILE *arch = fopen("users.dat", "ab");
	if (arch == NULL)
	{
		printf("Error al acceder al archivo");
		return;
	}
	printf("Ingrese el nombre de usuario");
	scanf("%s", nuevo.user);
	printf("Ingrese la contraseña");
	scanf("%s", nuevo.pswd);
	fread(&nuevo, sizeof(user), 1, arch);
	fclose(arch);
}
