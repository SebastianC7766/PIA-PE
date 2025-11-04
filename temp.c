#include <stdio.h>
#include <stdlib.h>
#include "zonas.c"

// Funcion para imprimir TODAS las temperaturas del zonas.dat
void ver_temp_actual()
{
    zone *temp_array = (zone *)calloc(1, sizeof(zone));
    read_zones(&temp_array);
    for (int i = 0; i < contar(0); i++)
    {
        printf("ID: %ld - Nombre: %s - Umbral: %i - Temperatura: %.2f - Ventilador: %i\n", temp_array[i].id_zone, temp_array[i].zone_name, temp_array[i].threshold, temp_array[i].current_temp, temp_array[i].fan_status);
    }
    system("pause");
    system("cls");
}


void activar_desactivar_ventilador()
{
    long id;
    int found = 0;
    printf("Ingrese el ID de la zona para para prender el ventilador: ");
    scanf("%ld", &id);

    zone *temp_array = (zone *)calloc(1, sizeof(zone));
    read_zones(&temp_array);
    for (int i = 0; i < contar(0); i++)
    {
        if (id == temp_array[i].id_zone)
        {
            found = 1;
            if(temp_array[i].fan_status){
                temp_array[i].fan_status=0;
                printf("El ventilador ha sido desactivado.\n");
            }
            else if(temp_array[i].fan_status==0){
                temp_array[i].fan_status=1;
                printf("El ventilador ha sido activado.\n");
            }
            
            // FALTA MODIFICAR EL ARCHIVO zonas.dat

            break;
        }
    }

    if (!found)
    {
        printf("No se encontro la zona con el ID ingresado.\n");
    }

    system("pause");
    system("cls");
}