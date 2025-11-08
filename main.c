#include "utilidades/utilidades.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8); // salida utf-8
    SetConsoleCP(CP_UTF8);       // entrada utf-8

    // inicio de sesion
    val_user(); // defaul user: admin pswd: admin
    // Variables
    srand(time(NULL));
    int opcion = 0;
    zone *zonas = NULL;
    read_zones(&zonas); // esta funcion declara el tamaño del arreglo de zonas, y si hay zonas anteriores las lee

    do
    {
        printf("MENU\n1.Zonas\n2.Control de temperaturas\n3.Consultas\n4.Configuracion\n5.Salir\nINGRESE UNA OPCION: ");
        scanf(" %i", &opcion);
        system("cls");
        switch (opcion)
        {
        case 1:
            opcion = 0;
            do
            {
                printf("SUBMENU: ZONAS\n1.Registro de zona.\n2.Salir.\nINGRESE UNA OPCION: ");
                scanf(" %i", &opcion);
                system("cls");
                switch (opcion)
                {
                case 1:
                    add_zone(&zonas);
                    break;
                case 2:
                    break;
                default:
                    printf("OPCION INVALIDA INGRESE UNA CORRECTA\n");
                    system("pause");
                    system("cls");
                    break;
                }
            } while (opcion != 2);
            break;
        case 2:
            opcion = 0;
            do
            {
                printf("SUBMENU: CONTROL DE TEMPERATURAS\n1.Ver temperatura actual.\n2.Activar/Desactivar ventilador manualmente.\n3.Ver historial de eventos.\n4.Simular monitoreo en tiempo real.\n5.Salir.\nINGRESE UNA OPCION: ");
                scanf(" %i", &opcion);
                system("cls");
                switch (opcion)
                {
                case 1:
                    ver_temp_actual();
                    break;
                case 2:
                    activar_desactivar_ventilador();
                    break;
                case 3:
                    historial_eventos();
                    break;
                case 4:
                    simular();
                    break;
                case 5:
                    break;
                default:
                    printf("OPCION INVALIDA INGRESE UNA CORRECTA\n");
                    system("pause");
                    system("cls");
                    break;
                }
            } while (opcion != 5);
            opcion = 0;
            break;
        case 3:
            opcion = 0;
            do
            {
                printf("SUBMENU: CONSULTAS\n1.Buscar eventos por rango de temperatura o fecha.\n2.Generar reporte estadistico.\n3.Exportar historial a archivo .csv.\n4.Salir.\nINGRESE UNA OPCION: ");
                scanf(" %i", &opcion);
                system("cls");
                switch (opcion)
                {
                case 1:
                    buscar_eventos();
                    break;
                case 2:
                    reporte();
                    break;
                case 3:
                    historial_csv();
                    break;
                case 4:
                    break;
                default:
                    printf("OPCION INVALIDA INGRESE UNA CORRECTA\n");
                    system("pause");
                    system("cls");
                    break;
                }
            } while (opcion != 4);
            break;
        case 4:
            opcion = 0;
            do
            {
                printf("SUBMENU: CONFIGURACION\n1.Configurar umbral de temperatura por zona.\n2.Restaurar configuracion por defecto por zona.\n3.Salir.\nINGRESE UNA OPCION: ");
                scanf(" %i", &opcion);
                system("cls");
                switch (opcion)
                {
                case 1:
                    mod_thr();
                    break;
                case 2:
                    default_zone();
                    break;
                case 3:
                    break;
                default:
                    printf("OPCION INVALIDA INGRESE UNA CORRECTA\n");
                    system("pause");
                    system("cls");
                    break;
                }
            } while (opcion != 3);
            break;
        case 5:
            free(zonas);
            break;
        default:
            printf("OPCION INVALIDA INGRESE UNA CORRECTA\n");
            system("pause");
            system("cls");
            break;
        }
    } while (opcion != 5);

    system("cls");
    return 0;
}
