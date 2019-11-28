/*
Final de Laboratorio de Microprocesadores 27/11/19
1) Declarar los elementos para una lista de libros de una biblioteca. La lista tiene 3 datos: editorial, titulo, peso.
2) Hacer una función que recorra la lista y devuelta el peso total de todos los libros del mismo autor.

Presupuestos: las lista está cargada. La función solo tiene que decir el peso total impreso por pantalla.
Sentencia: void calcular_peso(LISTA *cola, char *editorial);
*/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>


// Esta parte resuelve el punto 1 del examen.
typedef struct{
    char *editorial;
    char *titulo;
    int peso;
} DATOS;

typedef struct _NODO {
    DATOS *pd;
    struct _NODO *proximo;
}NODO;

typedef struct{
    NODO *ultimo; // puntero a NODO
    NODO *primero;
} LISTA;

// Hay que definir el nodo vacio, porque se va a usar mas adelante.
#define NIL (NODO *)0

// Esta funcion no es parte del examen, pero se necesita para que se ejecute el codigo.
void iniciar_lista(LISTA *pt)
{
    pt->primero = NIL;
    pt->ultimo = NIL;  
    return;
}

// Esta funcion no es parte del examen, pero se necesita para que se ejecute el codigo.
void cargar_lista(LISTA *cola, char *edit, char *title, int weight)
{
    NODO *aux; // Inicio puntero aux como una estructura NODO
    char *auxstr1; // Inicio puntero auxstr como char
    char *auxstr2; // Inicio puntero auxstr como char

    if ( (aux =(NODO *)malloc(sizeof(NODO))) == NULL){
        printf("Sin memoria para nodo");
        exit(1);
    }

    if ((aux->pd = (DATOS *)malloc(sizeof(DATOS))) == NULL){
        printf("Sin memoria para datos");
        exit(1);
    }

    if ((auxstr1 = (char *)malloc(strlen(edit))) == NULL){
        printf("Sin memoria para Strings");
        exit(1);
    }

    if ((auxstr2 = (char *)malloc(strlen(title))) == NULL){
        printf("Sin memoria para Strings");
        exit(1);
    }

    strcpy(auxstr1, edit);
    aux->pd->editorial = auxstr1;
    strcpy(auxstr2, title);
    aux->pd->titulo = auxstr2;
    
    aux->pd->peso = weight;

    if(cola->primero == NIL)
        cola->primero = aux;
    else
        cola->ultimo->proximo = aux;

    cola->ultimo = aux;
    aux->proximo = NIL;
    return;
}

// Esta funcion resuelve el punto 2 del examen (mas la definicion de NIL)y seria el examen completo
void calcular_peso(LISTA *list, char* title_book){
    NODO *i;
    unsigned int peso_total = 0;
    float peso_kilo;

    if(list->primero==NIL)
	{
		printf("La lista se encuentra vacia");
		return;
	}

	for (i=list->primero ; i != NIL ; i=i->proximo)
	{
	   if(strcmp(i->pd->editorial, title_book)==0)
	   peso_total = peso_total + i->pd->peso;
	}

    peso_kilo = peso_total/1000;
    printf("El peso total de los libreos es de %f Kg.", peso_kilo);

}

// No es necesario escribir el codigo de ejecucion del programa, porque suponen que las listas estan cargadas
//pero se necesita para que se ejecute el codigo.
void main (void){
    char *editoriales[]={"PLANETA" , "OVNI" , "PLANETA","*"};
    char *titulos[]={"El libro" , "Otro libro" , "Nuevo libro","*"};
    int peso[]={102,170,460,0};

    int i;
    LISTA *cola1;

    if (( cola1=(LISTA *)malloc(sizeof(LISTA)))==NULL){
        printf("Sin memoria para header");
        exit(1);
    }

    for (i=0;peso[i]!=0;i++ ){
        cargar_lista(cola1,editoriales[i], titulos[i], peso[i]);
    }

    printf("Ejecuto funcion para calcular el peso de los libros");
    calcular_peso(cola1, "PLANETA");
    exit(0);
}