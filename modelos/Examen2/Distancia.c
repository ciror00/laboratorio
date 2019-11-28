/*dada una lista de objetos , escribir una funcion que produzca un listado de los objetos de esta lista, 
y si la distancia de algun punto es menor a la especificada sacar la funcion por pantalla

listar_por_dist(lista1,xp,yp,dist) donde xp,yp(punto p de referencia) y dist son enteros */


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define NIL (NODO*)0

typedef struct
{
    int xp;
    int yp;
    char *objeto;
}DATOS;

typedef struct _NODO
{
    DATOS *pd;
    struct _NODO *proximo;

}NODO;
typedef struct
{
     NODO *primero;
     NODO *ultimo;
}LISTA;

/////////////////////
void Inicializar(LISTA *colita1)
    {
    colita1->primero=NIL;
    colita1->ultimo=NIL;
    return;
    }
////////////////////

void precarga( LISTA *cola1, char *obj, int x, int y )
{
NODO *aux;
char *auxstr1;


        if ((aux=(NODO *)malloc(sizeof(NODO)))==NULL)
             {
               printf("Sin memoria para nodos");
               exit(1);
             }
             if ((aux->pd=(DATOS *)malloc(sizeof(DATOS)))==NULL)
             {
               printf("Sin memoria para datos");
               exit(1);
             }
              if ((auxstr1=(char *)malloc(strlen(obj)))==NULL)
             {
               printf("Sin memoria para string");
               exit(1);
             }


             strcpy(auxstr1,obj);
             aux->pd->objeto=auxstr1;
             aux->pd->xp=x;



             aux->pd->yp=y;


             if (cola1->primero == NIL)
             cola1->primero=aux;
                   else
                   cola1->ultimo->proximo=aux;
             cola1->ultimo=aux;
             aux->proximo=NIL;
return;
}

//////////////////////
void mostrar(LISTA *col)
{
NODO *aux;

        for(aux=col->primero;aux!=NIL;aux=aux->proximo)
        {
            printf("%s \ncoord x: %d coord y: %d\n ",aux->pd->objeto,aux->pd->xp,aux->pd->yp);
            printf("\n\n");
        }
return;
}

////////////////////
void calc_dist(LISTA *col, int dist)
{
float distancia;
int xh;
int yh;
int flag=0;
NODO * aux;


      for(aux=col->primero;aux!=NIL;aux=aux->proximo)
      {
      xh=(aux->pd->xp)-600;       //RESTO PUNTOS (600 ES DATO)
      yh=(aux->pd->yp)-400;       //RESTO PUNTOS (400 ES DATO)

      distancia = sqrt((xh*xh)+(yh*yh));   //APLICO FORMULA DE LA RAIZ CUADRADA

           if(distancia < dist)
           {
           printf("\nLa distancia del objeto %s es %f\n", aux->pd->objeto, distancia);
           flag=1;
           }
      }

if(flag==0)
printf("\nno hay ninguna distancia de algun obeto al punto x:600 y:400 que sea menor a: %d (especificada)", dist );

return;
}
///////////////////////

void main(void)
{
char *objetos[]={"objeto1","objeto2","objeto3",0};
int x[]={2,3,4};
int y[]={5,5,5};
int dist=6;
int i;

LISTA *cola1;


if((cola1=(LISTA *)malloc(sizeof(LISTA)))==NULL)
{
  printf("Sin memoria para Header");
  exit(1);
}

Inicializar(cola1);

for (i=0;objetos[i]!=0;i++)
{
  precarga( cola1, objetos[i], x[i], y[i] );
}

mostrar(cola1);

calc_dist(cola1,dist);

printf("\n\n\n\n\n\n\n");

getch();
exit(0);
return;
}
