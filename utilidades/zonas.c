

void mod_fan_status(long id);
void nueva_temp(long id);
void registrar_evento(long id);
void print_file(zone Vzones);
void add_zone(zone **Vzones);
int contar(int key);
void read_zones(zone **Vzones);
int val_zone(long idzone);


void add_zone(zone **Vzones)
{ 
    int i = contar(0);
    *Vzones = (zone *)realloc(*Vzones, (i + 1) * sizeof(zone));
    printf("INGRESE EL ID DE LA ZONA: ");
    do
    {
        scanf("%ld", &(*Vzones)[i].id_zone);
    } while (val_zone((*Vzones)[i].id_zone) == 1);
    printf("INGRESE EL NOMBRE DE LA ZONA: ");
    scanf("%19s", (*Vzones)[i].zone_name);
    printf("INGRESE EL UMBRAL DE LA ZONA: ");
    scanf("%d", &(*Vzones)[i].threshold);
    (*Vzones)[i].fan_status = 0; 
    (*Vzones)[i].current_temp = ((float)(rand() % 1500) / 100.0f) + 20.0f; 
    (*Vzones)[i].def_thr = (*Vzones)[i].threshold;
    print_file((*Vzones)[i]);
    system("cls");
}

void read_zones(zone **Vzones)
{
    FILE *arch = fopen("binarios\\zonas.dat", "rb"); 
    if (arch == NULL)
    {
        *Vzones = (zone *)calloc(1, sizeof(zone));
        return;
    }
    int acc = contar(1);
    int i = 0;
    *Vzones = (zone *)calloc(acc, sizeof(zone));
    for (i = 0; i < acc; i++)
    {
        fread(&(*Vzones)[i], sizeof(zone), 1, arch);
    }
    fclose(arch);
    return;
}


void print_file(zone Vzones)
{
    FILE *arch = fopen("binarios\\zonas.dat", "a+b"); 
    if (arch == NULL)
    {
        printf("ERROR AL ACCEDER AL ARCHIVO\n");
        return;
    }
    fwrite(&Vzones, sizeof(zone), 1, arch); 
    fclose(arch);
}

int contar(int key)
{
    FILE *arch = fopen("binarios\\zonas.dat", "rb");
    if (arch == NULL)
    {
        return 0;
    }
    int acc;
    fseek(arch, 0, SEEK_END);
    long tam = ftell(arch);
    acc = tam / sizeof(zone);
    if (key == 1)
        rewind(arch);
    else
        fclose(arch); 
    return acc;
}


int val_zone(long idzone)
{
    int i;
    zone *Vzones;
    read_zones(&Vzones);
    int n = contar(0);
    for (i = 0; i < n; i++)
    {
        if (idzone == Vzones[i].id_zone)
        {
            free(Vzones);
            return 1;
        }
    }
    free(Vzones);
    return 0;
}

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
        printf("ID: %ld - Nombre: %s - Umbral: %d - Temperatura: %.2f - Ventilador: %s\n", temp_array[i].id_zone, temp_array[i].zone_name, temp_array[i].threshold, temp_array[i].current_temp, (temp_array[i].fan_status == 0) ? "APAGADO" : "ACTIVADO");
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
    while (val_zone(id) == 0)
    {
        printf("PORFAVOR INGRESE UNA ZONA VALIDA\n");
        printf("Ingrese el ID de la zona a activar/desactivar el ventilador: ");
        scanf("%ld", &id);
    }
    zone *temp_array = (zone *)calloc(1, sizeof(zone));
    read_zones(&temp_array);
    for (int i = 0; i < contar(0); i++)
    {
        if (id == temp_array[i].id_zone)
        {
            found = 1;
            if (temp_array[i].fan_status)
            {
                printf("El ventilador ha sido desactivado.\n");
            }
            else if (temp_array[i].fan_status == 0)
            {
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

    system("pause");
    system("cls");
}


void nueva_temp(long id)
{
    FILE *arch = fopen("binarios\\zonas.dat", "r+b"); 
    if (arch == NULL)
    {
        return;
    }
    zone aux;
    while (fread(&aux, sizeof(zone), 1, arch))
    {

        if (aux.id_zone == id)
        {
            aux.current_temp = ((float)(rand() % 1500) / 100.0f) + 20.0f;
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

// modifica el estado del ventilador en zonas.dat
void mod_fan_status(long id)
{
    FILE *arch = fopen("binarios\\zonas.dat", "r+b"); // abre el archivo zonas.dat en modo lectura y escritura
    if (arch == NULL)
    {
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

// funcion para registrar un evento
void registrar_evento(long id)
{
    FILE *arch = fopen("binarios\\zonas.dat", "rb"); // abre el archivo zonas.dat en modo lectura
    if (arch == NULL)
    {
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
    arch = fopen("binarios\\eventos.dat", "ab"); // abre el archivo zonas.dat en modo agregar
    if (arch == NULL)
    {
        return;
    }
    fwrite(&nuevo, sizeof(evento), 1, arch);
    fclose(arch);
}

// funcion que muestra el historial de todos los eventos
void historial_eventos()
{
    FILE *arch = fopen("binarios\\eventos.dat", "rb"); // abre el archivo zonas.dat en modo agregar
    if (arch == NULL)
    {
        return;
    }
    evento aux;
    while (fread(&aux, sizeof(evento), 1, arch))
    {
        printf("Zona: \033[34m%ld\033[0m \033[36m%s%d%s%d]\033[0m Temperatura: \033[32m%.2f °C\033[0m - Ventilador: %s\n",
               aux.zone, (aux.hora < 10) ? "[0" : "[", aux.hora, (aux.min < 10) ? ":0" : ":", aux.min, aux.temp, (aux.fan == 1) ? "ACTIVADO" : "APAGADO");
    }
    fclose(arch);
    system("pause");
    system("cls");
}

void simular()
{
    system("cls");
    long id;
    FILE *arch = fopen("binarios\\zonas.dat", "rb");
    if (arch == NULL)
    {
        return;
    }

    long pos;
    zone aux;
    printf("INGRESE EL ID DE LA ZONA A SEGUIR: ");
    scanf("%ld", &id);
    while (val_zone(id) == 0)
    {
        printf("PORFAVOR INGRESE UNA ZONA VALIDA\n");
        printf("INGRESE EL ID DE LA ZONA A SEGUIR: ");
        scanf("%ld", &id);
    }
    while (fread(&aux, sizeof(zone), 1, arch))
    {
        if (aux.id_zone == id)
            pos = ftell(arch) - sizeof(zone);
    }
    fclose(arch);
    printf("OPRIMA CUALQUIER TECLA PARA TERMINAR.\n");

    while (!kbhit())
    { 
        nueva_temp(id);
        arch = fopen("binarios\\zonas.dat", "rb"); 
        if (arch == NULL)
        {
            return;
        }
        fseek(arch, pos, SEEK_SET);
        fread(&aux, sizeof(zone), 1, arch);
        time_t tiempo_actual = time(NULL);
        struct tm *info_tiempo = localtime(&tiempo_actual);
        printf("%s%d%s%d%s%d] Temperatura: %.2f°C - Ventilador: %s\n",
               (info_tiempo->tm_hour < 10) ? "[0" : "[", info_tiempo->tm_hour, (info_tiempo->tm_min < 10) ? ":0" : ":", info_tiempo->tm_min, (info_tiempo->tm_sec < 10) ? ":0" : ":", info_tiempo->tm_sec, aux.current_temp, (aux.fan_status == 1) ? "ACTIVADO" : "APAGADO");
        Sleep(3000);
        registrar_evento(id);
    }

    system("pause");
    system("cls");
}