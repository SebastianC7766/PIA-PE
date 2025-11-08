void buscar_eventos(){
    FILE *arch = fopen("eventos.dat", "rb"); // abre el archivo zonas.dat en modo agregar
	if (arch == NULL)
	{
		return ;
	}
    evento aux;
    int opc=0;

    while(opc!=3){
        system("cls");
        printf("1-buscar por rango\n2-buscar por fecha\n3-salir\nELIJA UNA OPCION: ");
        scanf("%d",&opc);
        switch (opc)
        {
        case 1: 
            rewind(arch);
            int min,max;
            printf("minimo: "); scanf("%d",&min);
            printf("maximo: "); scanf("%d",&max);
            while(fread(&aux,sizeof(evento),1,arch)){
                if(aux.temp<max && aux.temp>min){
                    printf("zona: \033[34m%ld\033[0m \033[36m%s%d%s%d]\033[0m temperatura: \033[32m%.2f °C\033[0m -ventilador: %s\n",
                    aux.zone,(aux.hora<10)?"[0":"[",aux.hora,(aux.min<10)?":0":":",aux.min,aux.temp,(aux.fan==1)? "ACTIVADO":"APAGADO");
                }
            }
            system("pause");
            break;
        
        case 2: 
            rewind(arch);
            int d,m,a;
            printf("fecha (dd/mm/aaaa): "); scanf("%d/%d/%d",&d,&m,&a);
            while(fread(&aux,sizeof(evento),1,arch)){
                if(aux.dia==d && aux.mes==m && aux.anio==a){
                    printf("zona: \033[34m%ld\033[0m \033[36m%s%d%s%d]\033[0m temperatura: \033[32m%.2f °C\033[0m -ventilador: %s\n",
                    aux.zone,(aux.hora<10)?"[0":"[",aux.hora,(aux.min<10)?":0":":",aux.min,aux.temp,(aux.fan==1)? "ACTIVADO":"APAGADO");
                }
            }
            system("pause");
            break;
        case 3: 
            fclose(arch);
            break;

        default:
            break;
        }
    }
}

void reporte(){
    system("cls");
    printf("REPORTE ESTADISTICO:\n\n");
    zone *zonas=NULL;
    read_zones(&zonas);
    FILE *arch = fopen("eventos.dat", "rb"); // abre el archivo zonas.dat en modo agregar
	if (arch == NULL)
	{
		return ;
	}
    evento aux;
    float sumat=0,mint=35,maxt=0;
    long zonamin,zonamax;

    for(int i=0;i<contar(0);i++){
        float suma=0;
        int cont=0;
        float min=35,max=0;
        rewind(arch);
        printf("ZONA: %ld\n",zonas[i].id_zone);
         while(fread(&aux,sizeof(evento),1,arch)){
            if(aux.zone == zonas[i].id_zone){
                 if (cont == 0) {
                    min = aux.temp;
                    max = aux.temp;
                }
                cont++;
                suma += aux.temp;
                if (aux.temp > max) max = aux.temp;
                if (aux.temp < min) min = aux.temp;
            }
         }   
        if (cont > 0) {
            float promedio = suma / cont;
            printf("    MAYOR: %.2f\n    MENOR: %.2f\n    PROMEDIO: %.2f\n", max, min, promedio);
            sumat += promedio;
        } else {
            printf("    Sin eventos registrados\n");
        }
        if(max > maxt ){
            maxt=max;
            zonamax=zonas[i].id_zone;
        }
        if(min < mint){
            mint = min;
            zonamin=zonas[i].id_zone ;
        }
    }
    printf("\nZONA MAYOR: %ld con %.2f\nZONA MENOR: %ld con %.2f\nPROMEDIO GENERAL: %.2f\n", zonamax,maxt,zonamin,mint,sumat/contar(0));
    free(zonas);
    fclose(arch);
    system("pause");
    system("cls");
}
    
void historial_csv(){
    FILE *arch = fopen("eventos.dat", "rb"); // abre el archivo zonas.dat en modo agregar
	if (arch == NULL)
	{
		return ;
	}

    FILE *csv = fopen("historial.csv", "w");
    if (csv == NULL) {
        printf("No se pudo crear el archivo CSV.\n");
        fclose(arch);
        return;
    }

    fprintf(csv, "Zona,Hora,Minuto,Temperatura (°C),Ventilador\n");

    evento aux;
    while(fread(&aux,sizeof(evento),1,arch)){
       fprintf(csv, "%ld,%02d,%02d,%.2f,%s\n",
                aux.zone, aux.hora, aux.min, aux.temp, (aux.fan == 1) ? "ACTIVADO" : "APAGADO");
    }

    //system("start EXCEL.EXE historial.csv");  opcional abrirlo al crearlo

    fclose(arch);
    fclose(csv);
    system("pause");
    system("cls");
}