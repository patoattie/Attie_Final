#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../ArrayList/ArrayList.h"
#include "depositos.h"

int deposito_cargarDesdeArchivo(const char* nombreArchivo, ArrayList* arrayDeposito)
{
    FILE* archivoDeposito;
    int retorno = -1;
    int parseoArchivo;
    int cerroArchivo;
    int arrayEstaVacio = al_isEmpty(arrayDeposito);
    char continua;
    int limpiaArray;
    int confirmaParseo = 1;

    if(arrayEstaVacio == 0)
    {
        do
        {
            printf("La carga de Deposito desde archivo sobreescribira los Productos ya cargados. Continua? (S/N): ");
            fflush(stdin);
            scanf("%c", &continua);
            if(toupper(continua) != 'S' && toupper(continua) != 'N')
            {
                printf("Opcion no valida, debe ingresar S o N. Por favor reingrese\n");
            }
        } while(toupper(continua) != 'S' && toupper(continua) != 'N');

        if(toupper(continua) == 'S')
        {
            limpiaArray = al_clear(arrayDeposito);
            if(limpiaArray < 0)
            {
                printf("Error al limpiar array list\n");
                confirmaParseo = 0; //Error al limpiar arrayList, se cancela
            }
        }
        else
        {
            printf("Parseo cancelado por el usuario\n");
            confirmaParseo = 0; //Cancelado por el usuario
        }
    }
    else if(arrayEstaVacio < 0)
    {
        printf("Array list apunta a NULL\n");
        confirmaParseo = 0; //Cancelado por el usuario
    }

    if(confirmaParseo == 1)
    {
        archivoDeposito = fopen(nombreArchivo, "r");
        if(archivoDeposito != NULL)
        {
            parseoArchivo = deposito_parser(archivoDeposito, arrayDeposito);
            cerroArchivo = fclose(archivoDeposito);

            if(parseoArchivo == 0 && cerroArchivo == 0)
            {
                retorno = 0;
            }
        }
    }

    return retorno;
}

int deposito_parser(FILE* pFile, ArrayList* pArrayListDeposito)
{
    int retorno = -1;
    int cantidadDatosLeidos;
    eProducto* unProducto;
    char charCodProducto[10];
    char charCantidad[10];
    int agregoProducto;
    char cabecera[80];
    char descProducto[TAM_DESC_PRODUCTO];
    int guardoDato;
    int huboError = 0;

    if(pFile != NULL)
    {
        if(TIENE_ENCABEZADO_ARCHIVO_DEPOSITO)
        {
            //descarto la lectura del encabezado
            fgets(cabecera, 80, pFile);
        }

        while(!feof(pFile))
        {
            unProducto = producto_new();
            if(unProducto != NULL)
            {
                cantidadDatosLeidos = fscanf(pFile, MASACARA_ARCHIVO_DEPOSITO, charCodProducto, descProducto, charCantidad);
                if(cantidadDatosLeidos == CANTIDAD_CAMPOS_ARCHIVO_DEPOSITO)
                {
                    guardoDato = producto_setDescProducto(unProducto, descProducto);
                    if(guardoDato < 0)
                    {
                        huboError = 1;
                        break;
                    }

                    guardoDato = producto_setCodProducto(unProducto, charCodProductoToCodProducto(charCodProducto));
                    if(guardoDato < 0)
                    {
                        huboError = 1;
                        break;
                    }

                    guardoDato = producto_setCantidad(unProducto, charCantidadToCantidad(charCantidad));
                    if(guardoDato < 0)
                    {
                        huboError = 1;
                        break;
                    }

                    agregoProducto = al_add(pArrayListDeposito, unProducto);
                    if(agregoProducto < 0) //Hubo error
                    {
                        huboError = 1;
                        break;
                    }
                }
                else //Fin de archivo u otro error
                {
                    huboError = 1;
                    break;
                }
            }
            else //Sin memoria
            {
                huboError = 1;
                break;
            }
        }
    }

    if(huboError == 0)
    {
        retorno = 0;
    }

    return retorno;
}

eProducto* producto_new(void)
{
    eProducto* returnAux;
    returnAux = (eProducto*)malloc(sizeof(eProducto));
    return returnAux;
}

int producto_setCodProducto(eProducto* this, int codProducto)
{
    int retorno = -1;

    if(this != NULL && codProducto > 0)
    {
        this->codProducto = codProducto;
        retorno = 0;
    }

    return retorno;
}

int producto_getCodProducto(eProducto* this)
{
    int codProducto = 0;

    if(this != NULL)
    {
        codProducto = this->codProducto;
    }

    return codProducto;
}

int producto_setCantidad(eProducto* this, int cantidad)
{
    int retorno = -1;

    if(this != NULL && cantidad >= 0)
    {
        this->cantidad = cantidad;
        retorno = 0;
    }

    return retorno;
}

int producto_getCantidad(eProducto* this)
{
    int cantidad = 0;

    if(this != NULL)
    {
        cantidad = this->cantidad;
    }

    return cantidad;
}

int producto_setDescProducto(eProducto* this, const char* descProducto)
{
    int retorno = -1;

    if(this != NULL && descProducto != NULL)
    {
        strcpy(this->descProducto, descProducto);
        retorno = 0;
    }

    return retorno;
}

char* producto_getDescProducto(eProducto* this)
{
    char* descProducto = NULL;

    if(this != NULL)
    {
        descProducto = this->descProducto;
    }

    return descProducto;
}

int charCodProductoToCodProducto(char* charCodProducto)
{
    int codProducto;
    codProducto = atoi(charCodProducto);

    return codProducto;
}

int charCantidadToCantidad(char* charCantidad)
{
    int cantidad;
    cantidad = atoi(charCantidad);

    return cantidad;
}

void producto_print(eProducto* this)
{
    printf("%d - %s - %d\n", this->codProducto, this->descProducto, this->cantidad);
}

int deposito_listar(ArrayList* arrayDeposito)
{
    int i;
    int retorno = -1;
    eProducto* unProducto = NULL;

    for(i = 0; i < al_len(arrayDeposito); i++)
    {
        unProducto = (eProducto*)al_get(arrayDeposito, i);
        if(unProducto != NULL)
        {
            producto_print(unProducto);
            retorno = 0;
        }
    }

    return retorno;
}

int producto_buscar(ArrayList* lista, int codProducto)
{
    int retorno = -1;
    eProducto* unProducto = NULL;
    int i;

    if(lista != NULL && codProducto > 0)
    {
        if(al_isEmpty(lista) == 0)
        {
            for(i = 0; i < al_len(lista); i++)
            {
                unProducto = (eProducto*)al_get(lista, i);
                if(unProducto != NULL)
                {
                    if(producto_getCodProducto(unProducto) == codProducto)
                    {
                        retorno = i;
                        break;
                    }
                }
            }
        }
    }

    return retorno;
}

int producto_mover(ArrayList* origen, ArrayList* destino, int indiceProducto, const char* nombreArchivoOrigen, const char* nombreArchivoDestino)
{
    int retorno = -1;
    eProducto* unProducto = NULL;

    if(origen != NULL && destino != NULL && indiceProducto >= 0)
    {
        unProducto = (eProducto*)al_pop(origen, indiceProducto);
        retorno = al_add(destino, unProducto);
        if(retorno == 0)
        {
            retorno = deposito_guardarEnArchivo(origen, nombreArchivoOrigen);
            retorno = deposito_guardarEnArchivo(destino, nombreArchivoDestino);
        }
    }

    return retorno;
}

int deposito_guardarEnArchivo(ArrayList* lista, const char* nombreArchivo)
{
    int retorno = -1;
    FILE* archivo;
    eProducto* unProducto = NULL;
    int i;
    int huboError = 0;

    if(nombreArchivo != NULL)
    {
        archivo = fopen(nombreArchivo, "w");
        if(archivo != NULL)
        {
            //unProducto = producto_new();
            //if(unProducto != NULL)
            //{
                for(i = 0; i < al_len(lista); i++)
                {
                    unProducto = (eProducto*)al_get(lista, i);

                    if(unProducto != NULL)
                    {
                        //cantidadEscrita = fwrite(unProducto, sizeof(eProducto), 1, archivo);
                        fprintf(archivo, "%d,%s,%d\n", producto_getCodProducto(unProducto), producto_getDescProducto(unProducto), producto_getCantidad(unProducto));
                    }
                    else
                    {
                        huboError = 1;
                        break;
                    }
                }

                if(huboError == 0)
                {
                    retorno = 0;
                }
            //}
            fclose(archivo);
        }
    }

    return retorno;
}
