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

/** \brief Carga la estructura desde el archivo csv
 *
 * \param nombreArchivo const char* Nombre del archivo origen
 * \param arrayDeposito ArrayList* ArrayList destino
 * \return int 0 si OK -1 si Error
 *
 */
int deposito_cargarDesdeArchivo(const char* nombreArchivo, ArrayList* arrayDeposito);

/** \brief Parsea los datos de la estructura
 *
 * \param pFile FILE* puntero al archivo origen
 * \param pArrayListDeposito ArrayList* ArrayList destino
 * \return int 0 si OK -1 si Error
 *
 */
int deposito_parser(FILE* pFile, ArrayList* pArrayListDeposito);

/** \brief Constructor de la estructura eProducto
 *
 * \param void
 * \return eProducto* Puntero a la nueva estructura o NULL si Error.
 *
 */
eProducto* producto_new(void);

/** \brief Setter de Codigo de Producto
 *
 * \param this eProducto* Puntero a la estructura eProducto destino
 * \param codProducto int Código de producto a guardar en la estructura
 * \return int 0 si OK -1 si Error
 *
 */
int producto_setCodProducto(eProducto* this, int codProducto);

/** \brief Getter de Codigo de Producto
 *
 * \param this eProducto* Puntero a la estructura eProducto origen
 * \return int Código de producto obtenido de la estructura
 *
 */
int producto_getCodProducto(eProducto* this);

/** \brief Setter de Cantidad
 *
 * \param this eProducto* Puntero a la estructura eProducto destino
 * \param cantidad int Cantidad a guardar en la estructura
 * \return int 0 si OK -1 si Error
 *
 */
int producto_setCantidad(eProducto* this, int cantidad);

/** \brief Getter de Cantidad
 *
 * \param this eProducto* Puntero a la estructura eProducto origen
 * \return int Cantidad obtenida de la estructura
 *
 */
int producto_getCantidad(eProducto* this);

/** \brief Setter de Descripción de Producto
 *
 * \param this eProducto* Puntero a la estructura eProducto destino
 * \param descProducto const char* Descripción de producto a guardar en la estructura
 * \return int 0 si OK -1 si Error
 *
 */
int producto_setDescProducto(eProducto* this, const char* descProducto);

/** \brief Getter de Descripción de Producto
 *
 * \param this eProducto* Puntero a la estructura eProducto origen
 * \return int Descripción de producto obtenido de la estructura
 *
 */
char* producto_getDescProducto(eProducto* this);

/** \brief Convierte Código de Producto desde char a int
 *
 * \param charCodProducto char* Código de Producto como char
 * \return int Código de Producto como int
 *
 */
int charCodProductoToCodProducto(char* charCodProducto);

/** \brief Convierte Cantidad desde char a int
 *
 * \param charCantidad char* Cantidad como char
 * \return int Cantidad como int
 *
 */
int charCantidadToCantidad(char* charCantidad);

/** \brief Imprime un elemento de la estructura eProducto
 *
 * \param this eProducto* Elemento a imprimir
 * \return void
 *
 */
void producto_print(eProducto* this);

/** \brief Lista todos los elementos de un ArrayList de depósito
 *
 * \param arrayDeposito ArrayList* ArrayList a imprimir
 * \return int 0 si OK -1 si Error o no hay elementos a listar
 *
 */
int deposito_listar(ArrayList* arrayDeposito);

/** \brief Busca un Código de Producto en un depósito
 *
 * \param lista ArrayList* ArrayList de depósito
 * \param codProducto int Código de Producto a buscar
 * \return int Indice del elemento en el ArrayList o -1 si no existe el código
 *
 */
int producto_buscar(ArrayList* lista, int codProducto);

/** \brief Mueve un elemento desde un depósito hacia otro, actualizando los archivos .csv
 *
 * \param origen ArrayList* Depósito origen
 * \param destino ArrayList* Depósito destino
 * \param indiceProducto int Indice del elemento a mover
 * \param nombreArchivoOrigen const char* Archivo .csv origen
 * \param nombreArchivoDestino const char* Archivo .csv destino
 * \return int 0 si OK -1 si Error
 *
 */
int producto_mover(ArrayList* origen, ArrayList* destino, int indiceProducto, const char* nombreArchivoOrigen, const char* nombreArchivoDestino);

/** \brief Incrementa o decrementa la cantidad de un producto, dependiendo del factor
 *
 * \param lista ArrayList* ArrayList de depósito
 * \param indiceProducto int Indice del elemento
 * \param cantidad int Cantidad a incrementar o decrementar. Debe ser mayor a cero.
 * \param factor int Admite únicamente 1 para incrementar o -1 para decrementar
 * \param nombreArchivo const char* Archivo .csv
 * \return int 0 si OK -1 si Error
 *
 */
int producto_cambiarCantidad(ArrayList* lista, int indiceProducto, int cantidad, int factor, const char* nombreArchivo);

/** \brief Guarda los cambios en un archivo de texto.
 *
 * \param lista ArrayList* ArrayList de depósito origen
 * \param nombreArchivo const char* Archivo .csv destino, sobreescribe si ya existe.
 * \return int 0 si OK -1 si Error
 *
 */
int deposito_guardarEnArchivo(ArrayList* lista, const char* nombreArchivo);

#endif // DEPOSITOS_H_INCLUDED

