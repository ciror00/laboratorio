
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define p printf
#define s scanf


typedef struct
{
    char  *color_objeto;
    float  dimencion_1;
    float  dimencion_2;
    float  dimencion_3;
    int    identificador;
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

#define  NIL (NODO  *)0
/////////////////////
void Inicializar(LISTA *colita1)
    {
    colita1->primero=NIL;
    colita1->ultimo=NIL;
    return;
    }

/////////////////////

void iniciar_cola (LISTA * pt)
{
pt->primero = NIL;
pt->ultimo = NIL;
return;
}

/////////////////////
void poner_ultimo (LISTA * cola,char *color_obejeto,float dimencio_1,float dimencio_2,float dimencio_3,int identificado_1 )
{
NODO *auxiliar;
char *auxstr1;
char *auxstr2;

if((auxiliar=(NODO *)malloc(sizeof(NODO)))== NULL)
{
p("\n sin memoria para nodo");
exit(1);
}

if((auxiliar->pd=(DATOS *)malloc(sizeof(DATOS)))== NULL)
{
p("\n sin memoria para datos");
exit(1);
}

if((auxstr1=(char *)malloc(strlen(color_obejeto)))== NULL)
{
p("\n sin memoria para strings");
exit(1);
}

strcpy(auxstr1 , color_obejeto);
auxiliar->pd->color_objeto=auxstr1;
auxiliar->pd->dimencion_1=dimencio_1;
auxiliar->pd->dimencion_2=dimencio_2;
auxiliar->pd->dimencion_3=dimencio_3;
auxiliar->pd->identificador=identificado_1;


if(cola->primero==NULL)
cola->primero=auxiliar;
    else
    cola->ultimo->proximo=auxiliar;

cola->ultimo=auxiliar;
auxiliar->proximo=NULL;
return;
}

/////////////////////////////

void listar_cola (LISTA *cola)
{
int contador=1;
NODO *l;
NODO *n;

p("\n COLOR OBJ:  DIMENCION_1:  DIMENCION_2:  DIMENCION_3:  IDENTIFICADOR:   CONTADOR_FILAS");
for (l=cola->primero ; l != NULL ; l=l->proximo)
{
p("\n%-12s %-17f  %-7f   %-18f  %-11d  %d",l->pd->color_objeto, l->pd->dimencion_1, l->pd->dimencion_2, l->pd->dimencion_3, l->pd->identificador, contador);
contador++;
}
return;
}

void main (void)
{

char *color_objeto[]={"rojo" , "verde" , "azul", "amarillo", "violeta", "blanco", "negro","*"};
float dimencion_1 []={43 ,32,3,2,1,5,3};
float dimencion_2 []={50.3, 12.4 , 21.02, 85.7, 42.3, 35.2, 70.5};
float dimencion_3 []={12,5,13,12,2,17,15};
int   identificaion[]={1234,3456,754,234,52343,54545,656565};

int i;

LISTA *CABECERA;

system("cls");

if ((CABECERA=(LISTA *)malloc(sizeof(LISTA)))==NULL)
{
p("\n sin memoria para header");
exit(1);
}

iniciar_cola (CABECERA);


for (i=0; color_objeto[i]!="*"; i++ )
{
poner_ultimo(CABECERA,color_objeto[i],dimencion_1[i],dimencion_2[i],dimencion_3[i],identificaion[i]);
}

p("\n                            ///Lista de mesa///\n");
listar_cola(CABECERA);



return;
}
