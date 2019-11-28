/*FINAL LABORATORIO DE MICROPROCESADORES 03/12/2014

1) Definir los typedef para una tienda de ropa en la cual la ropa tenga la marca , el modelo , el precio , el codigo y a que temporada
corresponde (verano, oto�o,invierno, primavera)

2) Hacer que las prendas de ropa que corresponden a oto�o tengan un 20% de    descuento , y sacar de la lista las prenda de verano
*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define p printf
#define s scanf


typedef struct
{
    char  *marca;
    char  *modelo;
    float  precio;
    int    codigo;
    char  *temporada;
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

//////////////////////

void iniciar_cola (LISTA * pt)
{
pt->primero = NIL;
pt->ultimo = NIL;
return;
}

////////////////////////
void poner_ultimo (LISTA * cola , int codi , float preci, char *s)
{
NODO *aux;
char *auxstr;

if((aux=(NODO *)malloc(sizeof(NODO)))== NULL)
{
p("\n   ///apretar boton///\n\n");
exit(1);
}

if((aux->pd=(DATOS *)malloc(sizeof(DATOS)))== NULL)
{
p("\n sin memoria para datos");
exit(1);
}

if((auxstr=(char *)malloc(strlen(s)))== NULL)
{
p("\n sin memoria para strings");
exit(1);
}

aux->pd->codigo=codi;
aux->pd->precio=preci;
strcpy(auxstr , s);
aux->pd->temporada=auxstr;

if(cola->primero==NIL)
cola->primero=aux;
    else
    cola->ultimo->proximo=aux;

cola->ultimo=aux;
aux->proximo=NIL;

return;
}

///////////////////

void listar_cola (LISTA * cola)
{
int n=0;
NODO * l;

p("Temporada:      Cant.:  Codigo:    Precio:\n\n");
for (l=cola->primero ; l != NIL ; l=l->proximo)
{
p("%-15s : %d      %4d      %6.3f\n",l->pd->temporada, n , l->pd->codigo , l->pd->precio);
n++;
}

return;
}

/////////////////////

void modificar_lista(LISTA  *cola)
{
	NODO * i,*j;
	int flag=0;
	int flag2;
	int cont=0;

	if(cola->primero==NIL)
	{
		p("La lista se encuentra vacia");
		return;
	}

	for (i=cola->primero ; i != NIL ; i=i->proximo)
	{
	   if(strcmp(i->pd->temporada,"otono")==0)
	   i->pd->precio=i->pd->precio*0.8;
	}


	flag=0;
	while(flag==0)
	{ 
		i=cola->primero;
		flag=1;
		p("La lista se encuentra vacia");
		if( (strcmp(i->pd->temporada , "verano")==0) && (cola->primero == cola->ultimo) )
		{
			cola->primero=NIL;
			cola->ultimo=NIL;
			return;
		}
		if(strcmp(i->pd->temporada,"verano")==0)
		{
			cola->primero = cola->primero->proximo;
			flag=0;
			break;
		}
	}//cierro while


	flag2=0;
	while(flag2==0)
	{
		flag2=1;

		for (i=cola->primero , j=cola->primero->proximo ;  j!= NIL ; i=i->proximo , j=j->proximo )
		{
			if((strcmp(j->pd->temporada,"verano")==0)&&(j->proximo==NIL))
			{
				i->proximo=NIL;
				cola->ultimo=i;
				return;
			}
			if(strcmp(j->pd->temporada,"verano")==0)
			{
				i->proximo=j->proximo;
				flag2=0;
				break;
			}
		}//cierra el for
	}//cierra el while
	return;
}


////////////////////////////

void main (void)
{

int codi[]={102,170,460,124,152,127,100,0};
float preci[]={10.3, 12.4 , 4.02, 5.7, 2.3, 6.2, 12.5, 0};
char *tempora[]={"verano" , "otono" , "verano", "verano", "otono", "verano", "verano","*"};

int i;
LISTA *cola1;

system("cls");


if  (( cola1=(LISTA *)malloc(sizeof(LISTA)))==NULL)
{
p("\n sin memoria para header");
p("\n   ///apretar boton///\n\n");
getch();
exit(1);
}
iniciar_cola (cola1);


for (i=0;codi[i]!=0;i++ )
{
poner_ultimo(cola1,codi[i],preci[i],tempora[i]);
}

p("\n   ///vemos la lista de ropa///\n\n");
listar_cola(cola1);


modificar_lista(cola1);

p("\n///vemos la lista modificada (ropa de otono con 20 porciento de descuento y se saco la ropa de verano)///\n\n");
listar_cola(cola1);
if(cola1->primero==NIL)
p("La lista modificada se encuentra vacia");


p("\n\n\napretar cualquier tecla para terminar");
getch();
return;
}
