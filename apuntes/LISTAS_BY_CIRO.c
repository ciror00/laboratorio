/*
****************************************************************************************************
    Todos los datos que viene a constinuacion son datos que se repiten siempre en la misma estructura,
    segun la forma de resolcion de Steiner.
    Las librerias y las 3 estructuas basicas.
****************************************************************************************************
*/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>


// Estructura DATOS es el unico set de que cambia. Los elementos internos los dá en el enuncia
typedef struct{
    // Asi se define un elemento del tipo entero
    int integers;
    // Asi se define un elemento del tipo decimal (punto flotante)
    float decimals;
    // Asi se define un String (Haciendo un array de caracteres usando punteros)
    char *phrases;
    char *morePhrases;
} DATOS;

// Elementos de la lista, puntero a DATO
typedef struct _NODO {
    DATOS *pd;
    struct _NODO *proximo;
}NODO;

// Cabecera de la lista
typedef struct{
    NODO *ultimo; // puntero a NODO
    NODO *primero;
} LISTA;

#define NIL (NODO *)0 // Se define un NODO vacio o NODO cargado con 0

void iniciar_cola(LISTA *pt)
{
    pt->primero = NIL;
    pt->ultimo = NIL;  
    return; // No es necesario porque es una funcion "viod", pero funciona
}

/*
****************************************************************************************************
    Despues de estas funciones, comienzan las funciones especificas para el programa.
    Aunque, seguramente se necesiten las siguientes funciones, indiferentemente de la consigna
****************************************************************************************************
*/

// Esta funcion agrega elementos a la lista que inicializamos. 
// Sirve ya que, indiferentemente del enunciado, se requiere cargar datos en la lista, ya que se inicia vacia
// A veces se llama poner_ultimo(), inicializar(), precarga()
// Se agrega como parametros, un valor tipo LISTA y exactamente los mismos elementos que difinimos en DATOS.
// Por ejemplo, colocamos estos paramestros:
void cargar_lista(LISTA *cola, int entero, float decimal, char *cadena, char *otraCadena)
{
    // Se crea un "auxiliar" del tipo NODO para agregar los valores que ingresamos por parametro, dentro de la
    //estructura de la lista, y despues agregar UN AUXILIAR EXTRA POR CADA PARAMETRO STRING de la estructura DATOS.
    NODO *aux;
    char *auxstr1;
    char *auxstr2;

    // Despues se agregan 3 condicionales para "ver si hay memoria"
    // Primero se signa en aux el numero de bytes especificado por el tamañao de NODO. Si eso es igual
    //a un NODO vacio, se puede decir que no hay memoria para otro NODO y se termina la ejecucion
    //como "Ejecucion no exitosa, dado por el exit(1)"
    if ( (aux = (NODO *)malloc(sizeof(NODO))) == NIL){
        printf("Sin memoria para nodo");
        exit(1);
    }
    // Despues se signa en el atributo pd, a traves del operacion ->, el numero de bytes especificado 
    //por el tamañao de DATOS. Eso solo es posible porque en aux cargamos una estructura del tipo NODO. Si lo
    //anterior es igual a NULL, podemos decir que no hay memoria para cargar elementos del tipo DATOS.
    if ((aux->pd = (DATOS *)malloc(sizeof(DATOS))) == NULL){
        printf("Sin memoria para datos");
        exit(1);
    }
    // Finalmente, se le asigna a los otros auxiliares, el numero de bytes especificado por el largo de la oracion
    //pasada por parametros. Se agrega una condicion por cada String que agreguemos y se puede evaluar en el 
    //mismo condicional o en varios.
    // Si lo anterior es igual a NULL, se puede decir que no hay memoria para agregar cadenas de caracteres
    if (((auxstr1 = (char *)malloc(strlen(cadena))) == NULL ||
        ((auxstr2 = (char *)malloc(strlen(otraCadena))) == NULL)))
    {
        printf("Sin memoria para Strings");
        exit(1);
    }

    // Lo siguiente que se hace es agregar en cada atributo de la estructura DATOS, dentro de la estructura NODO,
    // usando los auxiliares que son del tipo NODO, los valore que pasamos por parametro.
    aux->pd->integers = entero;
    aux->pd->decimals = decimal;
    // En al caso de los Strings, ustilizamos la funciona para copiar cadenas de caracteres y los auxiliares extra
    strcpy(auxstr1, cadena);
    strcpy(auxstr2, otraCadena);
    aux->pd->phrases = auxstr1;
    aux->pd->morePhrases = auxstr2;

    // Despues de copiar los datos. Se utiliza otro condicional para diferenciar el caso de que la carga la carga
    //se del primer elemento de la lista, o no.
    // Si el atributo primero (de la lista pasada por parametro) esta vacio, es porque es el primer elemento y
    //se carga aux en el atributo "primero" donde cargamos todos los datos (recordando que aux es del tipo NODO)
    // Si no es el primero, aux se carga en el atributo "proximo".
    if(cola->primero == NIL)
        cola->primero = aux;
    else
        cola->ultimo->proximo = aux;

    // Antes de terminar, se carga en el atributo "ultimo" el nodo auxiliar y el atributo "proximo" del mismo nodo
    // se borra.
    cola->ultimo = aux;
    aux->proximo = NIL;
    return;
}

// La siguiente funciona tiene un funcionamiento similar a la anterior, pero antes de agregar un elemento,
//chequea si hay espacios vacios adentro; y los rellena.
void insertar_elemento(LISTA *cola, int entero, float decimal, char *cadena, char *otraCadena)
{
    // Se crea un "auxiliar" del tipo NODO para agregar los valores que ingresamos por parametro, dentro de la
    //estructura de la lista, y despues agregar UN AUXILIAR EXTRA POR CADA PARAMETRO STRING de la estructura DATOS.
    NODO *aux;
    char *auxstr1;
    char *auxstr2;
    // Se crean dos punteros del tipo NODO como pibotes
    NODO *j, *jant;

    // Primero se signa en aux el numero de bytes especificado por el tamañao de NODO. Si eso es igual
    //a un NODO vacio, se puede decir que no hay memoria para otro NODO y se termina la ejecucion
    //como "Ejecucion no exitosa, dado por el exit(1)"
    if ( (aux = (NODO *)malloc(sizeof(NODO))) == NIL){
        printf("Sin memoria para nodo");
        exit(1);
    }
    // Despues se signa en el atributo pd, a traves del operacion ->, el numero de bytes especificado 
    //por el tamañao de DATOS. Eso solo es posible porque en aux cargamos una estructura del tipo NODO. Si lo
    //anterior es igual a NULL, podemos decir que no hay memoria para cargar elementos del tipo DATOS.
    if ((aux->pd = (DATOS *)malloc(sizeof(DATOS))) == NULL){
        printf("Sin memoria para datos");
        exit(1);
    }
    // Finalmente, se le asigna a los otros auxiliares, el numero de bytes especificado por el largo de la oracion
    //pasada por parametros, y se le suma dos lugares mas.
    // Si lo anterior es igual a NULL, se puede decir que no hay memoria para agregar cadenas de caracteres
    if (((auxstr2 = (char *)malloc(strlen(otraCadena) + 2 )) == NULL))
    {
        printf("Sin memoria para Strings");
        exit(1);
    }

    if (((auxstr1 = (char *)malloc(strlen(cadena) + 2 )) == NULL))
    {
        printf("Sin memoria para Strings");
        exit(1);
    }
    
    // Lo siguiente que se hace es agregar en cada atributo de la estructura DATOS, dentro de la estructura NODO,
    // usando los auxiliares que son del tipo NODO, los valore que pasamos por parametro.
    aux->pd->integers = entero;
    aux->pd->decimals = decimal;
    // En al caso de los Strings, ustilizamos la funciona para copiar cadenas de caracteres y los auxiliares extra
    strcpy(auxstr1, cadena);
    strcpy(auxstr2, otraCadena);
    aux->pd->phrases = auxstr1;
    aux->pd->morePhrases = auxstr2;

    // A partir de aca continua la particularidad de la funcion. Primero se asigna en el pibote, el atributo
    //"primero" de la lista pasada por parametro.
    j = cola->primero;

    if(j == NIL) // Si la lista esta vacio (porque el primer elementoe es vacio)...
    { 
        // Se agrega tanto en "primero" como en "ultimo" el NODO aux donde cargamos los datos. Y
        //se deja el atributo "proximo" vacio
        cola->primero = cola->ultimo = aux;
        aux->proximo = NIL;
    }else if(decimal < j->pd->decimals) // Si un valor pasado por parametro es menor a un atributo
    { 
        // Se agrega el pibote que tiene "primero" dentro del atributo "proximo", y se agrega el NODO auxiliar
        //en el atributo "primero" de la lista.
        aux->proximo = j;
        cola->primero = aux;
    }else if( decimal > cola->ultimo->pd->decimals ) // Si un valor pasado por parametro es mayor a un atributo
    {
        // Se agrega el NODO auxiliar al atributo "proximo", dentro del atributo "ultimo" de la lista. Despues
        //se limpia el atributo "proximo" del NODO auxiliar y se vuelve a agregar el NODO auxiliar (con "proximo"
        //vacío) dentro del atributo "ultimo" de la lista
        cola->ultimo->proximo = aux;
        aux->proximo = NIL;
        cola->ultimo = aux;
    }else // Si todo lo anterior no se cumple, se agrega en cualquier lugar del medio
    {
        while(j->pd->decimals < decimal) // Se realiza un bucle mientras el atributo sea menos al parametro
        {
            // Durante el bucle, se hace backup del pibte y se le asigna el valor del atributo "proximo"
            jant = j;
            j = j->proximo;
        }
        // Cuando sale del bucle, es porque encontró un espacio vacio y se agrega al NODO auxiliar el dato
        //backup del pibote. Despues de tener el NODO re asignado, se agrega la estructura nueva al NODO guardado
        aux->proximo = jant->proximo;
        jant->proximo = aux;
    }
    return;
}

// Esta funcion tambien es util, porque hace un print de todos los elementos de la lista
void mostrar_elementos(LISTA *cola)
{
    int n = 0;
    NODO *listado;

    // for( inicialización ; condición ; incremento )
    for(listado = cola->primero; listado != NIL; listado= listado->proximo){
        printf("%d) ", n);
        printf("Numero enterio: %d - ", listado->pd->integers);
        printf("Numero decimal: %f - ", listado->pd->decimals);
        printf("Primera frase: %s - ", listado->pd->phrases);
        printf("Segunda frase: %s - ", listado->pd->morePhrases);
        printf("\n");
        n++;
    }
    return;
}

/*
****************************************************************************************************
    Las funciones a continuacion, son funciones especificas que podrian llegar a ser pedidas
    en el enunciado. Su funcionamiento trata de ser los mas generico posible.
****************************************************************************************************
*/

// Se crea un tipo de datos de enumeracion para trasear mejor el funcionamiento
typedef enum {
    ENTERO,
    DECIMAL,
    FRASE,
    OTRA
}PARAMETRO;

// Esta funcion ordena la lista, segun el parametro que le pasas.
// Se utiliza el algoritmo burbujero para acomodar los elementos de la lista.
void ordenar_lista(LISTA *cola, PARAMETRO x)
{
    NODO *j, *i;
    DATOS *temp;
    for(j= cola->primero; j != NIL; j = j ->proximo)
        for(i = j->proximo; i != NIL; i = i->proximo){
            if((j->pd->integers > i->pd->integers) && x == ENTERO){
                temp = j->pd;
                j->pd = i->pd;
                i->pd = temp;
            }else if((j->pd->decimals > i->pd->decimals) && x == DECIMAL){
                temp = j->pd;
                j->pd = i->pd;
                i->pd = temp;
            }else if((strcmp(j->pd->phrases, i->pd->phrases) > 0) && x == FRASE){
                temp = j->pd;
                j->pd = i->pd;
                i->pd = temp;
            }else if((strcmp(j->pd->morePhrases, i->pd->morePhrases) > 0) && x == OTRA){
                temp = j->pd;
                j->pd = i->pd;
                i->pd = temp;
            }
        }
    return;
}

// En esta funcion, se busca un dato especifico en la lista y se modifica.
// Se pasa por parametro la lista, un indicador para saber en que array se esta buscadndo, el datos a buscar 
//y el datos que se va a reemplazar cuando se encuentre.
// Tambien se podrian modificar los _if_s para que en lugar de reemplazar retorne un True/False, asi se haria
//una funcion buscar.
void reemplazar(LISTA *cola, PARAMETRO x, char *dato_buscar, char *dato_reemplazar){
    NODO *i,*j;
	char *auxstr1;
	char *auxstr2;
    

    if(cola->primero==NIL)
	{
		printf("\nLa lista esta vacía\n");
		return;
	}

    if (((auxstr2 = (char *)malloc(strlen(dato_reemplazar))) == NULL))
    {
        printf("Sin memoria para Strings");
        exit(1);
    }

    //strcpy(auxstr1, dato_buscar);
    //strcpy(auxstr2, dato_reemplazar);

    for (i=cola->primero ; i != NIL ; i=i->proximo)
	{
        if(x == FRASE && (strcmp(i->pd->phrases, dato_buscar)==0)){
            i->pd->phrases= dato_reemplazar;
            //break;
        }else if(x == OTRA && (strcmp(i->pd->morePhrases, dato_buscar)==0)){
            i->pd->morePhrases = dato_reemplazar;
            //break;
        }
	}
    return;
}

// Quitar cualquier elementos de la lista, buscando entre los datos del primer array (en el caso de esta set
//de datos).
// Se podria crear un buscador mas generico, pero seria complejo de explicar el funcionamiento.
NODO *eliminar_elemento(LISTA *cola, char *dato_buscar){
    NODO *i, *j;
	char *auxstr;
    strcpy(auxstr, dato_buscar);

    i=cola->primero;
    if(i == NIL)
	{
		printf("La lista se encuentra vacia");
		return(NIL);
	}
    // Este conficional sirve si el dato esta en primera posicion.
    if((strcmp(i->pd->phrases, dato_buscar) == 0))
    {
        cola->primero = i->proximo;
        cola->ultimo = NIL;
        return(i);
    }
    // Si el elemento esta en cualquier otra posicion, se corre este codigo-
    // El bucle sirve para recorrer la lista e ir haciendo "back ups" de los datos para rearmar la lista
    int bucle = 1;
	while(bucle)
	{
		bucle = 0;
		for (i=cola->primero , j=cola->primero->proximo ;  j!= NIL ; i=i->proximo , j=j->proximo )
		{
			if((strcmp(j->pd->phrases, dato_buscar)==0)&&(j->proximo==NIL))
			{
				i->proximo=NIL;
				cola->ultimo=i;
				return (i);
			}
			if(strcmp(j->pd->phrases, dato_buscar)==0)
			{
				i->proximo=j->proximo;
				bucle = 1;
				break;
			}
		}//cierra el for
	}//cierra el while
    return(i);
}

/*
****************************************************************************************************
    Al final de todo se coloca el main donde se llaman a todas las funciones.
****************************************************************************************************
*/

void main(void){
     // Se crean arrays con todos los datos
    int enteros[] = {1, 0};
    float decimales[] = {76.3, 0};
    char *frases[] = {"AAAA", "*"};
    char *masFrases[] = {"ZZZZ", "*"};
    /*
    int enteros[] = {1, 9, 4, 0};
    float decimales[] = {76.3, 2.1, 10.3, 0};
    char *frases[] = {"AAAA", "BBBB", "CCCC", "*"};
    char *masFrases[] = {"ZZZZ", "XXXX", "YYYY", "*"};
    */

    // Se inicia un puntero del tipo LISTA
    LISTA *cola1;
    LISTA *cola2;

    // Se inicializa una variable
    int i;

    // Se chequea el espacio para comenzar a llenar la lista de elementos de la cola
    if((cola1 = (LISTA *)malloc(sizeof(LISTA))) == NULL){
        printf("Sin memoria para Header");
        exit(1);
    }
    if((cola2 = (LISTA *)malloc(sizeof(LISTA))) == NULL){
        printf("Sin memoria para Header");
        exit(1);
    }

    // Si llego a esta parte, es porque pase el chequeo anterior, entonces llama a la funciona inciar_cola(), 
    //pasando por parametro el puntero cola1; ese puntero tiene toda la estrcutura anterior
    iniciar_cola(cola1);
    iniciar_cola(cola2);
    
    // Esto es solo un bucle que agrega el set de datos que representa cada arrays
    for(i=0; enteros[i] != 0; i++)
    {
        cargar_lista(cola1, enteros[i], decimales[i], frases[i], masFrases[i]);
    }
    for(i = 0; enteros[i] != 0; i++)
    {
        cargar_lista(cola2, enteros[i], decimales[i], frases[i], masFrases[i]);
    }

    printf("\nVemos la lista ...\n");
    mostrar_elementos(cola1);

    printf("\nBusco y reemplazo en el primer tring.\n");
    reemplazar(cola1, FRASE, "AAAA", "PAPA");
    printf("\nBusco y reemplazo en el segundo tring.\n");
    reemplazar(cola1, OTRA, "XXXX", "MAMA");
    mostrar_elementos(cola1);

    printf("\nElimino un elemento\n");
    NODO *eliminar_elemento();
    eliminar_elemento(cola1, "PAPA");
    mostrar_elementos(cola1);

    printf("\nReacomodo por Decimales.\n");
    ordenar_lista(cola1, DECIMAL);
    mostrar_elementos(cola1);
    printf("\nReacomodo por Enteros.\n");
    ordenar_lista(cola1, ENTERO);
    mostrar_elementos(cola1);
    printf("\nReacomodo por Otra Frase.\n");
    ordenar_lista(cola1, OTRA);
    mostrar_elementos(cola1);
    printf("\nReacomodo por Frase.\n");
    ordenar_lista(cola1, FRASE);
    mostrar_elementos(cola1);

    return;
}