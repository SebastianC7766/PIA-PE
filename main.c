#include<stdio.h>
#include"users.c"
#include"zonas.c"
#include"control_temp.c"
#include<stdlib.h>

void main()
{
    srand(time(NULL)); //define rand para la semilla de numeros aleatorios
	val_user(); //funcion para iniciar sesion
    zones *Vzones;  //declaracion del array principal de zonas
	read_zones(&Vzones); //leer zonas del archivo
    events *Vevents; //declaracion del array principal de eventos
	read_events(&Vevents); //leer eventos del archivo
    int opcion = 0;

    do{
		system("cls");
        printf("INGRESE UNA OPCION\n1.Zonas\n2.Control de temperaturas\n3.Consultas\n4.Configuracion\n5.Salir\n=>  ");
        scanf(" %i", &opcion);
		system("cls");
        switch (opcion){
            case 1:
				opcion = 0;
				do{
					system("cls");
					printf("INGRESE UNA OPCION\n1.Registro de zonas\n2.Salir\n=> ");
					scanf(" %i", &opcion);
					system("cls");
					switch (opcion){
						case 1:
							add_zone(&Vzones); //llama a la funcion addzone dentro de zonas.c
							break;
						case 2:
							break;
						default:
							printf("\nPORFAVOR INGRESE UNA OPCION VALIDA");
							system("pause");
							break;
						}
					} while (opcion != 2);
					break;
            case 2:
                opcion = 0;
                do{
					system("cls");
                    printf("INGRESE UNA OPCION:\n1.Ver temperatura Actual\n2.Activar ventilador manualmente\n3.Ver historial de eventos\n4.Simular monitoreo en tiempo real\n5.Salir\n=>");
                    scanf(" %i", &opcion);
                    system("cls");
                    switch (opcion){
                    case 1:
                        actual_temp(&Vevents, &Vzones);
                        break;
                    case 2:
                        fan_mod(&Vzones,&Vevents);
                        break;
                    case 3:
                        historial(Vevents);
                        break;
                    case 4:
                        /* code */
                        break;
                    case 5:
                        break;
                    default:
                        printf("\nPORFAVOR INGRESE UNA OPCION VALIDA");
						system("pause");
                        break;
                    }

                } while (opcion != 5);
                break;
            case 3:
                opcion = 0;
                do{
					system("cls");
                    printf("INGRESE UNA OPCION:\n1.Buscar eventos por rango de temperatura o fecha\n2.Generar reporte estadistico\n3.Exportar historial a archivo.csv\n4.Salir\n=> ");
                    scanf(" %i", &opcion);
                    system("cls");
                    switch (opcion){
                    case 1:
                        /* code */
                        break;
                    case 2:
                        /* code */
                        break;
                    case 3:
                        /* code */
                        break;
                    case 4:
                        break;
                    default:
                        printf("\nPORFAVOR INGRESE UNA OPCION VALIDA");
						system("pause");
                        break;
                    }
                } while (opcion != 4);
                break;
            case 4:
                opcion = 0;
                do{
					system("cls");
                    printf("INGRESE UNA OPCION:\n1.Configurar umbral de temperatura por zona\n2.Restaurar configuracion por defecto por zona\n3.Salir\n=> ");
                    scanf(" %i", &opcion);
                    system("cls");
                    switch (opcion){
                    case 1:
                        /* code */
                        break;
                    case 2:
                        /* code */
                        break;
                    case 3:
                        break;
                    default:
                        printf("\nPORFAVOR INGRESE UNA OPCION VALIDA");
						system("pause");
                        break;
                    }
                } while (opcion != 3);
                break;
            case 5:
                break;
            default:
                printf("\nPORFAVOR INGRESE UNA OPCION VALIDA");
				system("pause");
                break;
            }
    } while (opcion != 5);
    system("pause");
    free(Vzones);
	free(Vevents); //liberar memoria dinamica
    return 0;
}
