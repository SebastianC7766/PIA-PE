#include<stdio.h>
#include<stdlib.h>
#include <time.h>

//estructura de evento
typedef struct{
	long zone;
	int dia,mes,anio;
	int hora,min,seg;
	int temp;
	int fan;
}events;

events gen_event();
void actual_temp(events **Vevents, zones **Vzones);
void print_event(events *Vevents);
int count_events(int key);
void read_events(events **Vevents);
void fan_mod(zones **Vzones,events **Vevents);
void historial(events *Vevents);

//genera los datos de un nuevo evento
events gen_event(){
	long zone_cons;
	time_t tiempo_actual = time(NULL);
	struct tm *info_tiempo = localtime(&tiempo_actual);
	do{
		printf("INGRESE LA ZONA A CONSULTAR: "); scanf("%ld",&zone_cons);
	}while(val_zone(zone_cons)==0);
	system("cls");
	int min = 0;
	int max = 40;
	int temp = min + rand() % (max - min + 1);
	events event;
	event.temp=temp;
	event.zone=zone_cons;
	event.dia=info_tiempo->tm_mday;
	event.mes=info_tiempo->tm_mon+1;
	event.anio=info_tiempo->tm_year+1900;
	event.hora=info_tiempo->tm_hour;
	event.min=info_tiempo->tm_min;
	event.seg=info_tiempo->tm_sec;
	event.fan=0;
	return event;
}

//imprmir nuevo registro de evento
void actual_temp(events **Vevents, zones **Vzones){
	int i=count_events(0);
	*Vevents=realloc(*Vevents,(i+1)*sizeof(events));
	(*Vevents)[i]=gen_event();
	int j;
	for (j=0;j<contar(0);j++){
		if((*Vevents)[i].zone == (*Vzones)[j].id_zone){
			break;
		}
	}
	if((*Vevents)[i].temp>=(*Vzones)[j].threshold) (*Vzones)[j].fan_status=1;
	else (*Vzones)[j].fan_status=0;
	(*Vevents)[i].fan=(*Vzones)[j].fan_status;
	printf("zona: %ld\nTemperatura actual: %d c\nESTADO DEL VENTILADOR: %s (automatico)\n",
	(*Vevents)[i].zone,(*Vevents)[i].temp,(*Vzones)[j].fan_status==1?"ON":"OFF");
	print_event(&(*Vevents)[i]);
	system("pause");
}

//imprimir eventos en el archivo
void print_event(events *Vevents){
	FILE *arch=fopen("eventos.dat","a+b");
	if(arch==NULL){
		printf("ERROR AL ACCEDER AL ARCHIVO");
		return;
	}
	int i;
	fwrite(Vevents,sizeof(events),1,arch);
	fclose(arch);
}

//funcion para leer todos los registros del archivo eventos en un array
void read_events(events **Vevents){
	FILE *arch=fopen("eventos.dat","rb");
	if(arch==NULL){
		*Vevents=calloc(1,sizeof(events));
		return;
	}
	int acc=count_events(1);
	int i=0;
	*Vevents=calloc(acc,sizeof(events));
	while(fread(&(*Vevents)[i],sizeof(events),1,arch)){
		i++;
	}
	fclose(arch);
}

//cuenta cuantos eventos hay en el archivo
int count_events(int key){
	FILE *arch=fopen("eventos.dat","rb");
	if(arch==NULL){
		return 0;
	}
	int acc;
	fseek(arch, 0, SEEK_END);
	long tam = ftell(arch);
	acc = tam / sizeof(events);
	if(key==1)rewind(arch);
	else fclose(arch);
	return acc;
}

//modificar el ventilador de una zona  NOTA: funciona pero falta optmizar
void fan_mod(zones **Vzones,events **Vevents){
	system("cls");
	time_t tiempo_actual = time(NULL);
	struct tm *info_tiempo = localtime(&tiempo_actual);
	int i=count_events(0);
	*Vevents=realloc(*Vevents,(i+1)*sizeof(events));
	printf("INGRESE EL ID DE LA ZONA: ");
	long idzone;
	scanf("%ld",&idzone);
	int j,k;
	for (j=0;j<contar(0);j++){
		if(idzone == (*Vzones)[j].id_zone){
			break;
		}
	}
	if(j == contar(0)){
	    printf("Zona no encontrada.\n");
	    return;
	}

	int opc;
	printf("seleccione accion: \n 1->encender ventilador\n"
	"2->apagar ventilador\n=> ");
	scanf("%d",&opc);
	int temp=0;
	int status;
	if(opc==2) status=0;
	else status = 1;
	if(status!=(*Vzones)[j].fan_status){
		for(k=count_events(0)-1;k>=0;k--){
			if((*Vevents)[k].zone==idzone){
				temp=(*Vevents)[k].temp;
				break;
			}
		}
		(*Vevents)[i].temp=temp;
		(*Vevents)[i].fan=status;
		(*Vevents)[i].zone=idzone;
		(*Vevents)[i].dia=info_tiempo->tm_mday;
		(*Vevents)[i].mes=info_tiempo->tm_mon+1;
		(*Vevents)[i].anio=info_tiempo->tm_year+1900;
		(*Vevents)[i].hora=info_tiempo->tm_hour;
		(*Vevents)[i].min=info_tiempo->tm_min;
		(*Vevents)[i].seg=info_tiempo->tm_sec;
		print_event(&(*Vevents)[i]);
	}
	(*Vzones)[j].fan_status=status;
}

void historial(events *Vevents){
	system("cls");
	int i;
	for(i=0;i<count_events(0);i++){
		printf("[%d:%d.%d] temperartura: %d - ventilador: %s\n",
		Vevents[i].hora,Vevents[i].min,Vevents[i].seg
		,Vevents[i].temp,Vevents[i].fan==1?"ON":"OFF");
	}
	system("pause");
}
