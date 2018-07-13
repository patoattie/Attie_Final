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
 * \param codProducto int C�digo de producto a guardar en la estructura
 * \return int 0 si OK -1 si Error
 *
 */
int producto_setCodProducto(eProducto* this, int codProducto);

/** \brief Getter de Codigo de Producto
 *
 * \param this eProducto* Puntero a la estructura eProducto origen
 * \return int C�digo de producto obtenido de la estructura
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

/** \brief Setter de Descripci�n de Producto
 *
 * \param this eProducto* Puntero a la estructura eProducto destino
 * \param descProducto const char* Descripci�n de producto a guardar en la estructura
 * \return int 0 si OK -1 si Error
 *
 */
int producto_setDescProducto(eProducto* this, const char* descProducto);

/** \brief Getter de Descripci�n de Producto
 *
 * \param this eProducto* Puntero a la estructura eProducto origen
 * \return int Descripci�n de producto obtenido de la estructura
 *
 */
char* producto_getDescProducto(eProducto* this);

/** \brief Convierte C�digo de Producto desde char a int
 *
 * \param charCodProducto char* C�digo de Producto como char
 * \return int C�digo de Producto como int
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

/** \brief Lista todos los elementos de un ArrayList de dep�sito
 *
 * \param arrayDeposito ArrayList* ArrayList a imprimir
 * \return int 0 si OK -1 si Error o no hay elementos a listar
 *
 */
int deposito_listar(ArrayList* arrayDeposito);

/** \brief Busca un C�digo de Producto en un dep�sito
 *
 * \param lista ArrayList* ArrayList de dep�sito
 * \param codProducto int C�digo de Producto a buscar
 * \return int Indice del elemento en el ArrayList o -1 si no existe el c�digo
 *
 */
int producto_buscar(ArrayList* lista, int codProducto);

/** \brief Mueve un elemento desde un dep�sito hacia otro, actualizando los archivos .csv
 *
 * \param origen ArrayList* Dep�sito origen
 * \param destino ArrayList* Dep�sito destino
 * \param indiceProducto int Indice del elemento a mover
 * \param nombreArchivoOrigen const char* Archivo .csv origen
 * \param nombreArchivoDestino const char* Archivo .csv destino
 * \return int 0 si OK -1 si Error
 *
 */
int producto_mover(ArrayList* origen, ArrayList* destino, int indiceProducto, const char* nombreArchivoOrigen, const char* nombreArchivoDestino);

/** \brief Incrementa o decrementa la cantidad de un producto, dependiendo del factor
 *
 * \param lista ArrayList* ArrayList de dep�sito
 * \param indiceProducto int Indice del elemento
 * \param cantidad int Cantidad a incrementar o decrementar. Debe ser mayor a cero.
 * \param factor int Admite �nicamente 1 para incrementar o -1 para decrementar
 * \param nombreArchivo const char* Archivo .csv
 * \return int 0 si OK -1 si Error
 *
 */
int producto_cambiarCantidad(ArrayList* lista, int indiceProducto, int cantidad, int factor, const char* nombreArchivo);

/** \brief Guarda los cambios en un archivo de texto.
 *
 * \param lista ArrayList* ArrayList de dep�sito origen
 * \param nombreArchivo const char* Archivo .csv destino, sobreescribe si ya existe.
 * \return int 0 si OK -1 si Error
 *
 */
int deposito_guardarEnArchivo(ArrayList* lista, const char* nombreArchivo);

#endif // DEPOSITOS_H_INCLUDED

