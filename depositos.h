#ifndef DEPOSITOS_H_INCLUDED
#define DEPOSITOS_H_INCLUDED

#define TAM_DESC_PRODUCTO 50
#define TIENE_ENCABEZADO_ARCHIVO_DEPOSITO 0
#define MASACARA_ARCHIVO_DEPOSITO "%[^,],%[^,],%[^\n]\n"
#define CANTIDAD_CAMPOS_ARCHIVO_DEPOSITO 3
#define ARCHIVO_DEP0 "dep0.csv"
#define ARCHIVO_DEP1 "dep1.csv"

typedef struct
{
    int codProducto;
    char descProducto[TAM_DESC_PRODUCTO];
    int cantidad;
} eProducto;

int deposito_cargarDesdeArchivo(const char* nombreArchivo, ArrayList* arrayDeposito);
int deposito_parser(FILE* pFile, ArrayList* pArrayListDeposito);
eProducto* producto_new(void);
int producto_setCodProducto(eProducto* this, int codProducto);
int producto_getCodProducto(eProducto* this);
int producto_setCantidad(eProducto* this, int cantidad);
int producto_getCantidad(eProducto* this);
int producto_setDescProducto(eProducto* this, const char* descProducto);
char* producto_getDescProducto(eProducto* this);
int charCodProductoToCodProducto(char* charCodProducto);
int charCantidadToCantidad(char* charCantidad);
void producto_print(eProducto* this);
int deposito_listar(ArrayList* arrayDeposito);

#endif // DEPOSITOS_H_INCLUDED

