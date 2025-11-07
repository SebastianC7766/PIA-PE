// Funcion para imprimir TODAS las temperaturas del zonas.dat

void mod_fan_status(long id);
void nueva_temp(long id);
void registrar_evento(long id);

typedef struct
{ // estructura para registrar eventos
    long zone;
    int dia, mes, anio;
    int hora, min, seg;
    float temp;
    int fan;
} evento;

void ver_temp_actual()
{
    system("cls");
    zone *temp_array = NULL;
    read_zones(&temp_array);

    for (int i = 0; i < contar(0); i++)
        nueva_temp(temp_array[i].id_zone);

    read_zones(&temp_array);

    for (int i = 0; i < contar(0); i++)
    {
        printf("ID: %ld - Nombre: %s - Umbral: %d - Temperatura: %.2f - Ventilador: %s\n", temp_array[i].id_zone, temp_array[i].zone_name, temp_array[i].threshold, temp_array[i].current_temp, ((temp_array[i].fan_status == 1) ? "ACTIVADO" : "APAGADO"));
        registrar_evento(temp_array[i].id_zone);
    }
    free(temp_array);
    system("pause");
    system("cls");
}

void activar_desactivar_ventilador()
{
    system("cls");
    long id;
    int found = 0;
    printf("Ingrese el ID de la zona a activar/desactivar el ventilador: ");
    scanf("%ld", &id);
    zone *temp_array = NULL;
    read_zones(&temp_array);
    for (int i = 0; i < contar(0); i++)
    {
        if (id == temp_array[i].id_zone)
        {
            found = 1;
            if (temp_array[i].fan_status == 1)
            {
                temp_array[i].fan_status = 0;
                printf("El ventilador ha sido desactivado.\n");
            }
            else if (temp_array[i].fan_status == 0)
            {
                temp_array[i].fan_status = 1;
                printf("El ventilador ha sido activado.\n");
            }
            mod_fan_status(id);
            registrar_evento(id);
            break;
        }
    }

    if (!found)
    {
        printf("No se encontro la zona con el ID ingresado.\n");
    }
    free(temp_array);
    system("pause");
    system("cls");
}

// Modifica el estado del ventilador en zonas.dat
void mod_fan_status(long id)
{
    FILE *arch = fopen("zonas.dat", "r+b"); // abre el archivo zonas.dat en modo lectura y escritura
    if (arch == NULL)
    {
        printf("Error en la lectura de zonas.dat");
        return;
    }
    zone aux;
    while (fread(&aux, sizeof(zone), 1, arch))
    {
        if (aux.id_zone == id)
        {
            if (aux.fan_status == 1)
                aux.fan_status = 0;
            else
                aux.fan_status = 1;
            fseek(arch, -(long)sizeof(zone), SEEK_CUR);
            fwrite(&aux, sizeof(zone), 1, arch);
            fclose(arch);
            return;
        }
    }
}

// funcion que toma nuevas temperaturas y modifica el zonas.dat
void nueva_temp(long id)
{
    FILE *arch = fopen("zonas.dat", "r+b"); // abre el archivo zonas.dat en modo lectura y escritura
    if (arch == NULL)
    {
        return;
    }
    zone aux;
    while (fread(&aux, sizeof(zone), 1, arch))
    {

        if (aux.id_zone == id)
        {
            aux.current_temp = ((float)(rand() % 1501) / 100.0f) + 20.0f; // Genera un numero aleatorio entre 20 y 35
            if (aux.current_temp > aux.threshold)
                aux.fan_status = 1;
            else
                aux.fan_status = 0;
            fseek(arch, -(long)sizeof(zone), SEEK_CUR);
            fwrite(&aux, sizeof(zone), 1, arch);
            fclose(arch);
            return;
        }
    }
}

// funcion para registrar un evento
void registrar_evento(long id)
{
    FILE *arch = fopen("zonas.dat", "rb"); // abre el archivo zonas.dat en modo lectura
    if (arch == NULL)
    {
        printf("Error en lectura de zonas.dat");
        return;
    }
    time_t tiempo_actual = time(NULL);
    struct tm *info_tiempo = localtime(&tiempo_actual);
    long zone_cons;
    evento nuevo;
    zone aux;
    while (fread(&aux, sizeof(zone), 1, arch))
    {
        if (aux.id_zone == id)
        {
            nuevo.zone = aux.id_zone;
            nuevo.temp = aux.current_temp;
            nuevo.fan = aux.fan_status;
            nuevo.dia = info_tiempo->tm_mday;
            nuevo.mes = info_tiempo->tm_mon + 1;
            nuevo.anio = info_tiempo->tm_year + 1900;
            nuevo.hora = info_tiempo->tm_hour;
            nuevo.min = info_tiempo->tm_min;
            nuevo.seg = info_tiempo->tm_sec;
            break;
        }
    }
    fclose(arch);
    arch = fopen("eventos.dat", "ab"); // abre el archivo zonas.dat en modo agregar
    if (arch == NULL)
    {
        printf("Error en apertura de eventos.dat");
        return;
    }
    fwrite(&nuevo, sizeof(evento), 1, arch);
    fclose(arch);
}

// funcion que muestra el historial de todos los eventos
void historial_eventos()
{
    FILE *arch = fopen("eventos.dat", "rb"); // abre el archivo zonas.dat en modo agregar
    if (arch == NULL)
    {
        return;
    }
    evento aux;
    while (fread(&aux, sizeof(evento), 1, arch))
    {
        printf("Id_Zona: %ld [%d:%d:%d] Temperatura: %.2f °C - Ventilador: %s\n",
               aux.zone, aux.hora, aux.min, aux.seg, aux.temp, (aux.fan == 1) ? "ACTIVADO" : "APAGADO");
    }
    fclose(arch);
    system("pause");
    system("cls");
}

// Funcion para simular una zona en tiempo real
void simular()
{
    system("cls");
    long id;
    FILE *arch = fopen("zonas.dat", "rb"); // abre el archivo zonas.dat en modo lectura
    if (arch == NULL)
    {
        return;
    }

    long pos;
    zone aux;
    printf("INGRESE EL ID DE LA ZONA A SEGUIR: ");
    scanf("%ld", &id);
    while (fread(&aux, sizeof(zone), 1, arch))
    {
        if (aux.id_zone == id)
            pos = ftell(arch) - sizeof(zone);
    }
    fclose(arch);
    printf("OPRIME CUALQUIER TECLA PARA TERMINAR\n");

    while (!kbhit())
    { // kbhit retorna verdadero si una tecla es presionada
        nueva_temp(id);
        arch = fopen("zonas.dat", "rb"); // abre el archivo zonas.dat en modo lectura
        if (arch == NULL)
        {
            return;
        }
        fseek(arch, pos, SEEK_SET);
        fread(&aux, sizeof(zone), 1, arch);
        time_t tiempo_actual = time(NULL);
        struct tm *info_tiempo = localtime(&tiempo_actual);
        printf("[%d:%d:%d] Temperatura: %.2f°C - Ventilador: %s\n",
               info_tiempo->tm_hour, info_tiempo->tm_min, info_tiempo->tm_sec, aux.current_temp, (aux.fan_status == 1) ? "ACTIVADO" : "APAGADO");
        Sleep(3000);
        registrar_evento(id);
    }

    system("pause");
    system("cls");
}