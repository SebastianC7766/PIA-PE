#include <stdio.h>
#include <stdlib.h>

void main()
{
    int opcion = 0;

    do
    {
        printf("1.Zonas\n2.Control de temperaturas\n3.Consultas\n4.Configuracion\n5.Salir\nINGRESE UNA OPCION: ");
        scanf(" %i", &opcion);
        system("cls");
        switch (opcion)
        {
        case 1:
            opcion = 0;
            do
            {
                printf("1.Registro de zonas\n2.Salir\nINGRESE UNA OPCION: ");
                scanf(" %i", &opcion);
                system("cls");
                switch (opcion)
                {
                case 1:
                    /* code */
                    break;
                case 2:
                    break;
                default:
                    printf("1.Registro de zonas\n2.Salir\nOPCION INVALIDA, INGRESE UNA OPCION: ");
                    scanf(" %i", &opcion);
                    break;
                }
            } while (opcion != 2);
            break;
        case 2:
            opcion = 0;
            do
            {
                printf("1.Ver temperatura Actual\n2.Activar ventilador manualmente\n3.Ver historial de eventos\n4.Simular monitoreo en tiempo real\n5.Salir\nINGRESE UNA OPCION: ");
                scanf(" %i", &opcion);
                system("cls");
                switch (opcion)
                {
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
                    /* code */
                    break;
                case 5:
                    break;
                default:
                    printf("1.Ver temperatura Actual\n2.Activar ventilador manualmente\n3.Ver historial de eventos\n4.Simular monitoreo en tiempo real\n5.Salir\nOPCION INVALIDA, INGRESE UNA OPCION VALIDA: ");
                    scanf(" %i", &opcion);
                    break;
                }

            } while (opcion != 5);
            break;
        case 3:
            opcion = 0;
            do
            {
                printf("1.Buscar eventos por rango de temperatura o fecha\n2.Generar reporte estadistico\n3.Exportar historial a archivo.csv\n4.Salir\nINGRESE UNA OPCION: ");
                scanf(" %i", &opcion);
                system("cls");
                switch (opcion)
                {
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
                    printf("1.Buscar eventos por rango de temperatura o fecha\n2.Generar reporte estadistico\n3.Exportar historial a archivo.csv\n4.Salir\nOPCION INVALIDA, INGRESE UNA OPCION VALIDA: ");
                    scanf(" %i", &opcion);
                    break;
                }
            } while (opcion != 4);
            break;
        case 4:
            opcion = 0;
            do
            {
                printf("1.Configurar umbral de temperatura por zona\n2.Restaurar configuracion por defecto por zona\n3.Salir\nINGRESE UNA OPCION: ");
                scanf(" %i", &opcion);
                system("cls");
                switch (opcion)
                {
                case 1:
                    /* code */
                    break;
                case 2:
                    /* code */
                    break;
                case 3:
                    break;
                default:
                    printf("1.Configurar umbral de temperatura por zona\n2.Restaurar configuracion por defecto por zona\n3.Salir\nOPCION INVALIDA, INGRESE UNA OPCION VALIDA: ");
                    scanf(" %i", &opcion);
                    break;
                }
            } while (opcion != 3);
            break;
        case 5:
            break;
        default:
            printf("1.Zonas\n2.Control de temperaturas\n3.Consultas\n4.Configuracion\n5.Salir\nOPCION INVALIDA, INGRESE UNA NUEVA: ");
            scanf(" %i", &opcion);
            break;
        }
    } while (opcion != 5);
    system("pause");

    return;
}