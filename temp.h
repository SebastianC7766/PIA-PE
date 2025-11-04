#include "zonas.h"

// Funcion para imprimir TODAS las temperaturas del zonas.dat
void ver_temp_actual()
{
    zone *temp_array = (zone *)calloc(1, sizeof(zone));
    read_zones(&temp_array);
    for (int i = 0; i < contar(0); i++)
    {
        printf("ID: %ld - Nombre: %s - Umbral: %i - Ventilador: %i\n", temp_array[i].id_zone, temp_array[i].zone_name, temp_array[i].threshold, temp_array[i].fan_status);
    }
}