void mod_thr()
{
    system("cls");
    FILE *arch = fopen("binarios\\zonas.dat", "r+b"); 
    if (arch == NULL)
    {
        return;
    }
    long id;
    int new_thr;
    printf("Ingrese el ID de la zona a modificar el umbral: ");
    scanf("%ld", &id);
    while (val_zone(id) == 0)
    {
        printf("PORFAVOR INGRESE UNA ZONA VALIDA\n");
        printf("Ingrese el ID de la zona a modificar el umbral: ");
        scanf("%ld", &id);
    }
    printf("Ingrese el nuevo umbral de la zona %ld: ", id);
    scanf("%d", &new_thr);
    zone aux;
    while (fread(&aux, sizeof(zone), 1, arch))
    {
        if (id == aux.id_zone)
        {
            aux.threshold = new_thr;
            fseek(arch, -(long)sizeof(zone), SEEK_CUR);
            fwrite(&aux, sizeof(zone), 1, arch);
            fclose(arch);
        }
    }
    system("pause");
    system("cls");
}

void default_zone()
{
    system("cls");
    FILE *arch = fopen("binarios\\zonas.dat", "r+b"); 
    if (arch == NULL)
    {
        return;
    }
    long id;
    printf("Ingrese el ID de la zona: ");
    scanf("%ld", &id);
    while (val_zone(id) == 0)
    {
        printf("PORFAVOR INGRESE UNA ZONA VALIDA\n");
        printf("Ingrese el ID de la zona a modificar el umbral: ");
        scanf("%ld", &id);
    }
    zone aux;
    while (fread(&aux, sizeof(zone), 1, arch))
    {
        if (id == aux.id_zone)
        {
            aux.threshold = aux.def_thr;
            aux.threshold = 0;
            fseek(arch, -(long)sizeof(zone), SEEK_CUR);
            fwrite(&aux, sizeof(zone), 1, arch);
            fclose(arch);
        }
    }
    system("pause");
    system("cls");
}