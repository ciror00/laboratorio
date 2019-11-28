/*
FINAL 07-12-2016 PROFESOR STEINER

se tienen dos listas (con la misma estructura)....
la primera lista tiene que indicar :

apellido del alumno ,nombre, dni, legajo y condicion de regularidad

la condicion de regularidad en la lista 1en principio esta vacia y nosotros lo tenemos que llenar , segun la lista 2

ahora... por otra parte , la lista 2 indica los alumnos de la lista 1 que se quedaron libres .

entonces hay que hacer una funcion que vaya comparando las dos listas y los alumnos que estan en la lista 2 los ponga como
condicion de "no regulares" en la lista 1 y los que no estan en la lista 2 , los pone como "regulares" tambien en la lista 1

ahora... si la lista 2 esta vacia, tiene que poner a todos como condicion de regulares en lista 1

osea que finalmente en la lista 1 van a quedar en que condicion de regularidad quedaron los alumnos.

*/


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define p printf
#define s scanf


typedef struct
{
    char  *apellido;
    char  *nombre;
    int   dni;
    int   legajo;
    char  *condicion_de_regulariad;
}DATOS;

typedef struct _NODO
{
DATOS   *pd;
struct _NODO  *proximo;
}NODO;

typedef struct
{
NODO   *primero;
NODO   *ultimo;
}LISTA;

#define  NIL (NODO  *)0

/////////////////////////////////////

void iniciar_cola (LISTA * pt)
{
pt->primero = NIL;
pt->ultimo = NIL;
return;
}

////////////////////////////////////

void cargar_lista(LISTA *cola , char *apelli , char *nomb , int documento , int lega , char *condi_regulari)
{
NODO *aux;
char *auxstring_1;
char *auxstring_2;
char *auxstring_3;

if((aux=(NODO *)malloc(sizeof(NODO)))== NULL)
{
p("\n sin memoria para nodo");
exit(1);
}

if((aux->pd=(DATOS *)malloc(sizeof(DATOS)))== NULL)
{
p("\n sin memoria para datos");
exit(1);
}

if((auxstring_1=(char *)malloc(strlen(apelli)))== NULL)
{
p("\n sin memoria para strings");
exit(1);
}

if((auxstring_2=(char *)malloc(strlen(nomb)))== NULL)
{
p("\n sin memoria para strings");
exit(1);
}

if((auxstring_3=(char *)malloc(strlen(condi_regulari)))== NULL)
{
p("\n sin memoria para strings");
exit(1);
}

strcpy(auxstring_1 , apelli);
aux->pd->apellido=auxstring_1;

strcpy(auxstring_2 , nomb);
aux->pd->nombre=auxstring_2;

aux->pd->dni=documento;
aux->pd->legajo=lega;

strcpy(auxstring_3 , condi_regulari);
aux->pd->condicion_de_regulariad=auxstring_3;


if(cola->primero==NIL)
cola->primero=aux;
   else
   cola->ultimo->proximo=aux;

cola->ultimo=aux;
aux->proximo=NIL;
return;
}

////////////////////////////////////

void listar_cola (LISTA * cola)
{
NODO * j;

p("apellido:       nombre:         dni:       legajo:     condicion de regularidad:\n\n");
for (j=cola->primero ; j != NIL ; j=j->proximo)
{
p("%-14s  %-10s      %-8d      %-15d  %s\n",j->pd->apellido , j->pd->nombre , j->pd->dni , j->pd->legajo , j->pd->condicion_de_regulariad);
}

return;
}

/////////////////////////////////////

void funcion_condicion_regularidad(LISTA *cola_1 , LISTA *cola_2)
{
	NODO *i,*j;
	NODO *aux;
	char *auxstr;
	int flag;


	if(cola_1->primero==NIL && cola_2->primero==NIL)
	{
		p("\nlas dos listas estan vacias");
		return;       //vuelve sin hacer nada
	}


	if(cola_1->primero==NIL)
	{
		p("\nla lista de alumnos 1 esta vacia");
		return;      //vuelve sin hacer nada
	}


	if(cola_2->primero==NIL) //si la lista 2 (que indica alumnos libres) esta vacia pone a todos (lista 1) como condicion de regular
	{
		for (aux=cola_1->primero ; aux!=NIL ; aux=aux->proximo)
		{
		  if((auxstr=(char *)malloc(strlen("regular")))== NULL)
		  {
			  p("\n sin memoria para string");
			  exit(1);
		  }

		strcpy(auxstr , "regular");
		aux->pd->condicion_de_regulariad=auxstr;

		}
	return;
	}


	for (i=cola_1->primero ; i!=NIL ; i=i->proximo)
	{
	flag=0;
		 for(j=cola_2->primero ; j!=NIL ; j=j->proximo)
		 {
			 if(i->pd->legajo == j->pd->legajo)
			 {
				if((auxstr=(char *)malloc(strlen("no regular")))== NULL)
				{
					p("\n sin memoria para string");
					exit(1);
				}
				 strcpy(auxstr , "no regular");
				 i->pd->condicion_de_regulariad=auxstr;
				 flag=1;
				 break;  //fuerzo a  salir del for
			 }  //cierro if
		 }  //cierro for


	  if(flag==0)
	  {
			if((auxstr=(char *)malloc(strlen("regular")))== NULL)
			{
			p("\n sin memoria para string");
			exit(1);
			}
	  strcpy(auxstr , "regular");
	  i->pd->condicion_de_regulariad=auxstr;
	  }

	}  //cierro for

	return;
}  //cierro funcion


/////////////////////////////////////

void main (void)
{

////// DATOS QUE SE VAN A CARGAR EN LA LISTA 1
char  *apellido_lista_1[]={"ortega" , "peralta" , "maida", "deluca", "naso", "quintana", "acevedo","*"};
char  *nombre_lista_1[]={"santi" , "maxi" , "gabriel", "guillermo", "florencia", "alejandro", "laura","*"};
int  dni_lista_1[]={4556,2345,457,343,17864,18765,16900,0};
int  legajo_lista_1[]={1, 2, 3, 4, 5, 6, 7, 0};
char  *condicion_regularidad_lista_1[]={"-----" , "-----" , "-----", "-----", "-----", "-----", "-----","*"};



////// DATOS QUE SE VAN A CARGAR EN LA LISTA 2
char  *apellido_lista_2_libre[]={"maida" , "naso" , "acevedo","*"};
char  *nombre_lista_2_libre[]={"gabriel" , "florencia" , "laura"};
int  dni_lista_2_libre[]={457, 17864 , 16900};
int  legajo_lista_2_libre[]={3, 5 , 7};
char  *condicion_regularidad_2_libre[]={"libre" , "libre" , "libre"};


int i;
LISTA *cola1;
LISTA *cola2;

system("cls");

if  (( cola1=(LISTA *)malloc(sizeof(LISTA)))==NULL)
{
p("\n sin memoria para header de lista 1");
exit(1);
}

if  (( cola2=(LISTA *)malloc(sizeof(LISTA)))==NULL)
{
p("\n sin memoria para header de lista 2");
exit(1);
}

/////////////
iniciar_cola (cola1);
iniciar_cola (cola2);
////////////

for (i=0 ; apellido_lista_1[i]!="*" ; i++)
{
cargar_lista(cola1 , apellido_lista_1[i] , nombre_lista_1[i] , dni_lista_1[i] , legajo_lista_1[i] , condicion_regularidad_lista_1[i]);
}

p("\n   ///vemos la primer lista de alumnos///\n\n");
listar_cola(cola1);

////////////


for (i=0 ; apellido_lista_2_libre[i]!="*" ; i++)
{
cargar_lista(cola2 , apellido_lista_2_libre[i] , nombre_lista_2_libre[i] , dni_lista_2_libre[i] , legajo_lista_2_libre[i] , condicion_regularidad_2_libre[i]);
}

p("\n   ///vemos la segunda lista de alumnos que quedaron libres///\n\n");
listar_cola(cola2);


//////////

p("\n///finalmente vemos como quedo la condicion de regularidad en la primera lista de alumnos///\n\n");
funcion_condicion_regularidad(cola1 , cola2);
listar_cola(cola1);


p("\n\n\napretar cualquier tecla para terminar");
getch();
return;
}
