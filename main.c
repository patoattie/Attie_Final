#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../ArrayList/ArrayList.h"
#include "depositos.h"

int main()
{
    ArrayList* arrayDep0 = al_newArrayList();
    ArrayList* arrayDep1 = al_newArrayList();
    char seguir = 's';
    int opcion;
    int puntoMenu;
    int deposito;
    int codProducto;
    int indiceProducto;

    if(arrayDep0 != NULL && arrayDep1 != NULL)
    {
        while(seguir == 's')
        {
            system("cls");

            printf("1. Cargar depositos\n");
            printf("2. Listar productos de deposito\n");
            printf("3. Mover productos a deposito\n");
            printf("4. Descontar productos de deposito\n");
            printf("5. Agregar productos a deposito\n\n");
            printf("6. Salir\n");

            scanf("%d", &opcion);

            switch(opcion)
            {
            case 1:
                puntoMenu = deposito_cargarDesdeArchivo(ARCHIVO_DEP0, arrayDep0);
                if(puntoMenu == 0)
                {
                    printf("Parse del deposito 0 OK\n");
                }
                else
                {
                    printf("ERROR en Parse deposito 0\n");
                }

                puntoMenu = deposito_cargarDesdeArchivo(ARCHIVO_DEP1, arrayDep1);
                if(puntoMenu == 0)
                {
                    printf("Parse del deposito 1 OK\n");
                }
                else
                {
                    printf("ERROR en Parse deposito 1\n");
                }

                break;

            case 2:
                printf("Ingrese deposito a listar (0 o 1): ");
                scanf("%d", &deposito);
                switch(deposito)
                {
                case 0:
                    puntoMenu = deposito_listar(arrayDep0);
                    break;
                case 1:
                    puntoMenu = deposito_listar(arrayDep1);
                    break;
                default:
                    printf("Opcion incorrecta. Debe elegir 0 o 1\n");
                }

                if(puntoMenu < 0)
                {
                    printf("No hay Productos cargados\n");
                }

                break;

            case 3:
                printf("Ingrese deposito origen (0 o 1): ");
                scanf("%d", &deposito);
                switch(deposito)
                {
                case 0:
                    puntoMenu = deposito_listar(arrayDep0);
                    if(puntoMenu < 0)
                    {
                        printf("No hay Productos cargados\n");
                    }
                    else
                    {
                        printf("Ingrese codigo de producto a mover: ");
                        scanf("%d", &codProducto);
                        indiceProducto = producto_buscar(arrayDep0, codProducto);
                        if(indiceProducto < 0)
                        {
                            printf("No existe el producto\n");
                        }
                        else
                        {
                            puntoMenu = producto_mover(arrayDep0, arrayDep1, indiceProducto, ARCHIVO_DEP0, ARCHIVO_DEP1);
                        }
                    }
                    break;
                case 1:
                    puntoMenu = deposito_listar(arrayDep1);
                    if(puntoMenu < 0)
                    {
                        printf("No hay Productos cargados\n");
                    }
                    else
                    {
                        printf("Ingrese codigo de producto a mover: ");
                        scanf("%d", &codProducto);
                        indiceProducto = producto_buscar(arrayDep1, codProducto);
                        if(indiceProducto < 0)
                        {
                            printf("No existe el producto\n");
                        }
                        else
                        {
                            puntoMenu = producto_mover(arrayDep1, arrayDep0, indiceProducto, ARCHIVO_DEP1, ARCHIVO_DEP0);
                        }
                    }
                    break;
                default:
                    printf("Opcion incorrecta. Debe elegir 0 o 1\n");
                }

                if(puntoMenu < 0)
                {
                    printf("Error al mover el producto\n");
                }

                break;

            case 4:
                break;

            case 5:
                break;

            case 6:
                seguir = 'n';
                break;

            default:
                printf("Opcion incorrecta, opciones validas desde 1 hasta 6\n");
            }

            if(seguir == 's')
            {
                system("pause");
            }
        }

    }
    else
    {
        printf("ERROR. No se pueden cargar los depositos. No hay memoria disponible\n");
    }

    return 0;
}
