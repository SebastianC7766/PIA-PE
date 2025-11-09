#include <windows.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct
{
	char user[20];
	char pswd[20];
} user;

typedef struct
{
    long id_zone;
    char zone_name[20];
    int threshold;
    int def_thr;
    int fan_status;
    float current_temp;
} zone;

typedef struct
{ 
    long zone;
    int dia, mes, anio;
    int hora, min, seg;
    float temp;
    int fan;
} evento;

#include "users.c"
#include "zonas.c"
#include "conf.c"
#include "consultas.c"