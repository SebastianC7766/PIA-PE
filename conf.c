
void mod_thr(){
    system("cls");
    FILE *arch = fopen("zonas.dat", "r+b"); // abre el archivo zonas.dat en modo lectura y escritura
	if (arch == NULL){
        return;
    }
    long id;
    int new;
    printf("ingrese el ID de la zona, a modificar el umbral: ");
    scanf("%ld",&id);
    while(val_zone(id)==0){
        printf("PORFAVOR INGRESE UNA ZONA VALIDA\n");
        printf("ingrese el ID de la zona, a modificar el umbral: ");
        scanf("%ld",&id);
    }
    printf("ingrese el nuevo umbral de la zona %ld: ",id);
    scanf("%s",&new);
    zone aux;
    while(fread(&aux,sizeof(zone),1,arch)){
        if(id == aux.id_zone){
            aux.threshold = new;
            fseek(arch, -sizeof(zone), SEEK_CUR);
            fwrite(&aux, sizeof(zone), 1, arch);
            fclose(arch);
        }
    }
    system("pause");
    system("cls");
}

void default_zone(){
    system("cls");
    FILE *arch = fopen("zonas.dat", "r+b"); // abre el archivo zonas.dat en modo lectura y escritura
	if (arch == NULL){
        return;
    }
    long id;
    int new;
    printf("ingrese el ID de la zona: ");
    scanf("%ld",&id);
    while(val_zone(id)==0){
        printf("PORFAVOR INGRESE UNA ZONA VALIDA\n");
        printf("ingrese el ID de la zona, a modificar el umbral: ");
        scanf("%ld",&id);
    }
    zone aux;
    while(fread(&aux,sizeof(zone),1,arch)){
        if(id == aux.id_zone){
            aux.threshold = aux.def_thr;
            aux.threshold = 0;
            fseek(arch, -sizeof(zone), SEEK_CUR);
            fwrite(&aux, sizeof(zone), 1, arch);
            fclose(arch);
        }
    }
    system("pause");
    system("cls");
}