// estructura de datos de una zona
typedef struct
{
	long id_zone;
	char zone_name[20];
	int threshold;
	int fan_status;
	float current_temp;
} zone;

void print_file(zone Vzones);
void add_zone(zone **Vzones);
int contar(int key);
void read_zones(zone **Vzones);
int val_zone(long idzone);

// funcion para agregar una zona al array de zonas
void add_zone(zone **Vzones)
{ // Vzones es el vector donde se guardan las zonas
	int i = contar(0);
	*Vzones = (zone *)realloc(*Vzones, (i + 1) * sizeof(zone)); // redimension del array Vzones
	printf("INGRESE EL ID DE LA ZONA: ");
	do
	{
		scanf("%ld", &(*Vzones)[i].id_zone); // ciclo que lee la zona hasta que sea valida
	} while (val_zone((*Vzones)[i].id_zone) == 1);
	printf("INGRESE EL NOMBRE DE LA ZONA: ");
	scanf("%19s", (*Vzones)[i].zone_name);
	printf("INGRESE EL UMBRAL DE LA ZONA: ");
	scanf("%d", &(*Vzones)[i].threshold);
	(*Vzones)[i].fan_status = 0;								   // inicializa el abanico de la zona como apagado
	(*Vzones)[i].current_temp = ((float)(rand() % 1500) / 100.0f) + 20.0f; // REVISAR PQ NO TIENE DECIMALES
	print_file((*Vzones)[i]);
	system("cls");
}

// funcion para leer todos los registros del archivo zonas.dat en un array
void read_zones(zone **Vzones)
{
	FILE *arch = fopen("zonas.dat", "rb"); // abre el archivo donde se guardan las zonas llmado zonas.dat
	if (arch == NULL)
	{
		*Vzones = (zone *)calloc(1, sizeof(zone)); // si el archivo no existe o esta vacio declara el arreglo con 1 solo dato vacio
		return;
	}
	int acc = contar(1);
	int i = 0;
	*Vzones = (zone *)calloc(acc, sizeof(zone)); // si el archivo tiene registros entonces los cuenta y dimensiona el array
	for (i = 0; i < acc; i++)
	{
		fread(&(*Vzones)[i], sizeof(zone), 1, arch);
	}
	fclose(arch);
	return;
}

// funcion para imprimir la nueva zona en el archivo
void print_file(zone Vzones)
{
	FILE *arch = fopen("zonas.dat", "a+b"); // abre el archivo zonas.dat en a+b(agregar y leer), si no existe lo crea
	if (arch == NULL)
	{
		printf("ERROR AL ACCEDER AL ARCHIVO\n");
		return;
	}
	fwrite(&Vzones, sizeof(zone), 1, arch); // escribe en el archivo binario
	fclose(arch);
}

// funcion para contar la cantidad de zonas el argumento key,se usa para cerrar el archivo o solo rebobinarlo
int contar(int key)
{
	FILE *arch = fopen("zonas.dat", "rb"); // abre el archivo zonas.dat en modo lectura
	if (arch == NULL)
	{
		return 0;
	}
	int acc;
	fseek(arch, 0, SEEK_END); // mueve el cursor al final del archivo
	long tam = ftell(arch);	  // cuneta los bits que hay antes del cursor
	acc = tam / sizeof(zone); // hace la cuenta de cuantos registros hay haciendo la division de los bits totales entre los bits de la estructura de una zona
	if (key == 1)
		rewind(arch); // si key es 1 rebobina el archivo si no, lo cierra
	else
		fclose(arch); //(el key sirve por si la funcion es llamada dentro de una funcion que ya abra el archivo.dat)
	return acc;
}

// VALIDAR EL ID DE LA ZONA
int val_zone(long idzone)
{
	int i;		  // pendiente opcional: agregar como argumento el array de zonas principal y quitar el que se
	zone *Vzones; // declara en esta funcion, ademas de modificarlo en las funciones que lo usan
	read_zones(&Vzones);
	int n = contar(0);
	for (i = 0; i < n; i++)
	{
		if (idzone == Vzones[i].id_zone)
		{ // busca si la zona existe dentro del archivo
			free(Vzones);
			return 1;
		}
	}
	free(Vzones);
	return 0;
}
