/*
    Manejo de listas, tieneq la funciuon que insrta un datos en una lista oirdeandad por precios
    Debe tener en cuenta las distintas posibilidades

    1) Lista Vacia
    2) Insertar antes del primero
    3) Insertar luego del ultimo
    4) Insertar al medio de la lista

    Tiene funciones para ordenar segun los datos
*/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#define MAX_CHAR 30

// Se crea una estructura DATO, con 3 atributos: "codigo", "precio" y "descripcion"
typedef struct{
    int cod;
    float pre;
    char *descr;
} DATOS;

// Elemento de la lista, es un puntero a DATO
typedef struct _NODO {
    DATOS *pd;
    struct _NODO *proximo;
}NODO;

// Header de la lista
typedef struct{
    NODO *ultimo; // puntero a NODO
    NODO *primero;
} LISTA;

/******************************/

#define NIL (NODO *)0 // Se define un puntero a NODO cargado con cero

// Se define una funcion que incializa la lista como una lista vacia
void iniciar_cola(LISTA *pt)
{
    /*
        Utilizando al operador -> para acceder al atributo del elementos pt, ya que *pt sera un parametro
        tipo LISTA (o sea, que tendra dos atributos; "primero" y "ultimo").
        De la misma forma, iniciamos los atributos en cero, usando la etiqueta NIL
    */
    pt->primero = NIL;
    pt->ultimo = NIL;  
    return;
}

// Se defina una funciona que "agrega" un elemento.
// Recibe como parametro un elemento del tipo LISTA y 3 valores
void poner_ultimo(LISTA *cola, int codi, float preci, char *s)
{
    NODO *aux; // Inicio puntero aux como una estructura NODO
    char *auxstr; // Inicio puntero auxstr como char

    /*
        Se realizan 3 condicionales, son se chequea que el micro tenga memoria.
            malloc() asigna el número bytes que se especifique entre parentesis. pero no lo inicializa
            sizeof() devuelve el tamaño, en bytes, de elementos que se coloque entre parentesis
        
    */
    if ( (aux =(NODO *)malloc(sizeof(NODO))) == NIL){
        printf("Sin memoria para nodo");
        exit(1);
    }

    if ((aux->pd = (DATOS *)malloc(sizeof(DATOS))) == NULL){
        printf("Sin memoria para datos");
        exit(1);
    }

    if ((auxstr = (char *)malloc(strlen(s))) == NULL){
        printf("Sin memoria para Strings");
        exit(1);
    }
    /*
         Se asignan los valores pasados por parametro (codigo, precio, descripcion) a los atribuos
        del elemento de la estructura DATOS, dentro de la estructura NODO, usando el puntero *aux
        para "codigo" y "precio", y se usa el puntero *auxstr como buffer para cargar la descripcion
        pasada por parametro "s"; strcpy() copia s en auxstr
    */
    aux->pd->cod = codi;
    aux->pd->pre = preci;
    strcpy(auxstr, s);
    aux->pd->descr = auxstr;
    /*
         La siguiente logica, realiza el "agregado" del nuevo elementos lista. Porque primero se fija
        que el primer elemento de la "cola" sea cero; si es cero, lo agrega como primero
        y si no es cero lo agrega como siguiente.
         Hay que tener presente que *proximo es una estructura de NODO y *ultimo es una estrcutura de LISTA
        eso significa que usa *proximo como "acumulador" para datos se agregan y despues limpia ese dato para usar
        la funcion.
    */
    if(cola->primero == NIL)
        cola->primero = aux;
    else
        cola->ultimo->proximo = aux;

        cola->ultimo = aux;
        aux->proximo = NIL;
        return;
}


// La siguiente funcion es la "segunda parte" del final
// Se declara una funcion del tipo NODO que recibe como parametro un puntero del tipo LISTA
NODO *sacar_primero(LISTA *cola)
{
    /*
        En esta funcion hay que tener cuidado con los condicionales ya que en la fotocopia esta mal identado.
        El parametro *cola es del tipo LISTA y se pasa por funcion
    */
    NODO *msg;  // Inicio puntero msg como una estructura NODO
    // Se chequea que el atributo *primero de la "cola" no sea cero. Si es cero, retorna la funcion
    // Se accede al atributo *primero de la lista "cola" y se le asigna a *msg
    // Se accede al atributo *proximo de msg (que deberia ser cero) y asi "sacar el primero" 
    // Se chequea que el atributo *ultimo de la lista no quede con "basura". Si tiene algo, lo limpia
    if(cola->primero == NIL)
    return(NIL);

    msg = cola->primero;
    cola->primero = msg->proximo;

    if(cola->ultimo == msg)
        cola->ultimo = NIL;

    return(msg); // retorna el elemento msg
}

// Esta funcion imprimer por pantalla todo los elementos de una lista. No tiene mucho sentido explicar
void listar_cola(LISTA *cola)
{
    int n = 0;
    NODO *l;

    for(l = cola->primero; l != NIL; l= l->proximo){
        printf("%-15s: %d   %4d %6.2f\n",l->pd->descr, n, l->pd->cod, l->pd->pre);
        n++;
    }
    return;
}

/*
    Las siguientes funciones solo ordenen la lista, implementadno el algoritmo de burbujeo.
    No tiene mucho sentido explicar, porque generalemten este tipo de funciones se "copian y pegan".
    Solo hay que tener en vista que utilizan punteros (*i *j) del tipo NODO y punteros (*temp) del tipo DATOS
    Los primeros para hacer el bucle, y los segundos para ir acomodando los elementos, porque utiliza el atributo
    corrspondiente dentro de cada if; el atributo "pre" para podenar por precio, el atributo "cod" para precio y
    el atributo "descr" para descripcion
*/

// Esta funciona ordena la lista y los imprime en orden de precio.
void ord_lista_pre(LISTA *cola){
    NODO *j, *i;
    DATOS *temp;
    for(j= cola->primero; j != NIL; j = j ->proximo)
        for(i=j->proximo; i != NIL; i = i->proximo)
            if(j->pd->pre > i->pd->pre){
                temp = j->pd;
                j->pd = i->pd;
                i->pd = temp;
            }
    return;
}

// Esta funciona ordena la lista y los imprime en orden de codigo.
void ord_list_cod(LISTA *cola)
{
    NODO *j, *i;
    DATOS *temp;
    for(j= cola->primero; j != NIL; j = j ->proximo)
        for(i = j->proximo; i != NIL; i = i->proximo)
            if(j->pd->cod > i->pd->cod){
                temp = j->pd;
                j->pd = i->pd;
                i->pd = temp;
            }
    return;
}

// Esta funciona ordena la lista y los imprime en orden de descripcion.
void ord_list_descr(LISTA *cola)
{
    NODO *j, *i;
    DATOS *temp;
    for(j= cola->primero; j != NIL; j = j ->proximo)
        for(i = j->proximo; i != NIL; i = i->proximo)
            if(strcmp(j->pd->descr, i->pd->descr) > 0){
                temp = j->pd;
                j->pd = i->pd;
                i->pd = temp;
            }
    return;
}


/* 
    Esta fucion, mal llamada, inserta un elemento a una lista. Es la forma de agregar elementos, una vez que se
    inicio la lista vacia.
    Usa el mismo chequeo de "poner_ultimo()", pero por alguna razon al atributo "descripcion" le da dos bits mas
    de espacio.
    Despues, hace la misma logica de asignarlos los valores por parametro a los atributos del elemento NODO.
*/
void insertar_precio(LISTA *cola, int co, float pr, char *sn)
{
    NODO *j, *jant;
    NODO *aux;
    char *auxstr;

    if ( (aux =(NODO *)malloc(sizeof(NODO))) == NIL){
        printf("Sin memoria para nodo");
        exit(1);
    }

    if ((aux->pd = (DATOS *)malloc(sizeof(DATOS))) == NULL){
        printf("Sin memoria para datos");
        exit(1);
    }

    if ((auxstr = (char *)malloc(strlen(sn) + 2)) == NULL){
        printf("Sin memoria para Strings");
        exit(1);
    }
    
    // Asigna los valore pasado por parametros a cada atributo del elemento NODO contenido en *auxs
    aux->pd->cod = co;
    aux->pd->pre = pr;
    strcpy(auxstr, sn);
    aux->pd->descr = auxstr;

    /*
        La siguiente logica, se usa para chequear si la lista tiene algun elemento.
        Si hay un elemento en la lista, lo agrega primero, si no hay lo agrega en el proximo espacio.
    */
    j = cola->primero;

    if(j == NIL){ /* lista vacia */
        cola->primero = cola->ultimo = aux;
        aux->proximo = NIL;
    }else if(pr < j->pd->pre){ /* Insertar al principio */
        aux->proximo = j;
        cola->primero = aux;
    }else if( pr > cola->ultimo->pd->pre ){ /* Insertar al final */
        cola->ultimo->proximo = aux;
        aux->proximo = NIL;
        cola->ultimo = aux;
    }else{  /* Insertar al medio */
        while(j->pd->pre < pr){
            jant = j;
            j = j->proximo;
        }
        aux->proximo = jant->proximo;
        jant->proximo = aux;
    }
    return;
}

// Es es el cuerpo del programa, donde se ejecutan toda las funciones anteriores
void main(void){
     // Se crea un array con codigos
    int codigo[] = {102, 103, 133, 124, 152, 127, 100, 0};
     // Se crea un array con precios
    float precio[] = {10.3, 12.4, 4.02, 5.7, 2.3, 6.2, 12.5, 0};
    // Se crea un array con descripciones
    char *descrip[] = {"Mecha", "Calibre", "Guias", "M01", "G7", "Sep", "Motro", "*"}; 

    // Se inicializa una variable
    int i;
    // Se crea un puntero del tipo NODO
    NODO *ptr;
    // Se inicia una funciona como puntero del tipo NODO
    NODO *sacar_primero();
    // Se inicia un puntero del tipo LISTA
    LISTA *cola1;

    //clrscr(); // Esta funciona se supone que es para limpiar la pantalla pero no es nativa de C

    // Se chequea el espacio para comenzar a llenar la lista de elementos de la cola
    if((cola1 = (LISTA *)malloc(sizeof(LISTA))) == NULL){
        printf("Sin memoria para Header");
        exit(1);
    }
    // Si llego a esta parte, es porque pase el chequeo anterior, entonces llama a la funciona inciar_cola(), 
    //pasando por parametro el puntero cola1; ese puntero tiene toda la estrcutura anterior
    iniciar_cola(cola1);

    // Esto es solo un bucle que agrega el set de datos que representa cada arrays
    for(i=0; codigo[i] != 0; i++){
        poner_ultimo(cola1, codigo[i], precio[i], descrip[i]);
    }

    // Aca se llaman a todas las funciones ver el funcionamiento
    printf("Vemos la lista ...\n\n");
    listar_cola(cola1);
    ord_lista_pre(cola1);
    printf("\nLista ordenada por precio...:\n\n");
    listar_cola(cola1);
    ord_list_cod(cola1);
    printf("\nLista ordenada por codigo...:\n\n");
    listar_cola(cola1);
    ord_list_descr(cola1);
    printf("\nLista ordenada por precio...:\n\n");
    listar_cola(cola1);
    
    printf("\nSacamos el primero y agregamos ordenado por precio: \n\n");
    sacar_primero(cola1);
    insertar_precio(cola1, 323, 7.55, "Nuevo1");
    insertar_precio(cola1, 444, 1.55, "Nuevo2");
    insertar_precio(cola1, 883, 27.55, "Nuevo3");
    listar_cola(cola1);

    // Esto agrego yo, rapidamente, para ver que el codigo ejecutado
    int t = 5000;
    while(t < 0){
        t--;
    }
    printf("\nFin del programa\n\n");
    exit(-1);
    return;
}