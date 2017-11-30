
#include <stdio.h>
#include <string.h>


#define sizeofFigura2D sizeof(void *)

#define CirculoradioOffset sizeof(void *)
#define sizeofCirculo sizeof(void *) + sizeof(int)

#define sizeofEsfera sizeofCirculo
#define rectanguloBaseOffset sizeof(void *)
#define rectanguloAlturaOffset rectanguloBaseOffset + sizeof(int)
#define sizeofRectangulo sizeofFigura2D + rectanguloBaseOffset + rectanguloAlturaOffset

#define getAreaOffset 0
#define imprimrOffset sizeof(void*)


char CirculoVtable[sizeof(void *) * 2];
char EsferaVtable[sizeof(void *) * 2];
char RectanguloVtable[sizeof(void *) * 2];



void Figura2D_Imprimir(char * this)
{

  void *vtable = *((void **)this);
  void (*fnImprimir)(char*);
  fnImprimir = *((void (**)(char *))vtable + imprimrOffset);
  return fnImprimir(this);

}

int Figura2D_GetArea(char * this)
{

  void *vtable = *((void **)this);
  int (*fnGetArea)(char*);
  fnGetArea = *((int (**)(char *))vtable + getAreaOffset);
  return fnGetArea(this);

}

void Circulo_ctor(char *this, int radio)
{
  *((void **)this) = CirculoVtable;
  *((int *)(this + CirculoradioOffset)) = radio;
}


int Circulo_getArea(char *this)
{
  int radio = *((int *)(this + CirculoradioOffset));
  int area = ((3.14) * radio * radio);
  printf("Get Area Circle!: %d\n", area);
  return area;
}



int Circulo_getDiametro(char *this)
{
  int radio = *((int *)(this + CirculoradioOffset));
  printf("Get Diametro Circle!: %d\n", radio * 2);
  return 2 * radio;
}

void Circulo_imprimir(char * this)
{
  int radio = *((int *)(this + CirculoradioOffset));
  printf("Imprimir circulo: radio: %d\n", radio);
  Figura2D_GetArea(this);
  Circulo_getDiametro(this);
}


void Esfera_ctor(char *this, int radio)
{
  Circulo_ctor(this, radio);
  *((void **)this) = EsferaVtable;
}

int Esfera_GetVolumen(char * this)
{
  int radio = *((int *)(this + CirculoradioOffset));
  int volumen = (4/3 * (3.14 * radio * radio * radio) ) ;
  printf("Get Volumen Esfera!: %d\n", volumen);
  return volumen;
}

void Esfera_imprimir(char * this)
{
  int radio = *((int *)(this + CirculoradioOffset));
  printf("Imprimir Esfera radio: %d\n", radio);
  Figura2D_GetArea(this);
  Esfera_GetVolumen(this);
}

void Rectangulo_ctor(char * this, int base, int altura)
{
  *((void **)this) = RectanguloVtable;
  *((int *)(this + rectanguloBaseOffset)) = base;
  *((int *)(this + rectanguloAlturaOffset)) = altura;
}

int Rectangulo_GetArea(char *this)
{
  int base = *((int *)(this + rectanguloBaseOffset));
  int altura = *((int *)(this + rectanguloAlturaOffset));

  printf("Rectangulo get area: %d\n", base * altura);
  return base * altura;
}


void Rectangulo_Imprimir(char * this)
{
  int base = *((int *)(this + rectanguloBaseOffset));
  int altura = *((int *)(this + rectanguloAlturaOffset));
  printf("Iprimir rectangulo base:%d  altura:%d\n", base, altura);
  Figura2D_GetArea(this);
}

int main()
{

  *((void **)CirculoVtable) = &Circulo_getArea;
  *((void **)EsferaVtable) = &Circulo_getArea;
  *((void **)RectanguloVtable) = &Rectangulo_GetArea;

  *((void **)CirculoVtable + sizeof(void*)) = &Circulo_imprimir;
  *((void **)EsferaVtable + sizeof(void*)) = &Esfera_imprimir;
  *((void **)RectanguloVtable + sizeof(void*)) = &Rectangulo_Imprimir;

   char CirculoStack[sizeofCirculo];
   char EsferaStack[sizeofCirculo];
   char RectanguloStack[sizeofCirculo];


   Circulo_ctor(CirculoStack, 10);
   Esfera_ctor(EsferaStack, 20);
   Rectangulo_ctor(RectanguloStack, 30, 40);

   Figura2D_Imprimir(RectanguloStack);
   Figura2D_Imprimir(CirculoStack);
   Figura2D_Imprimir(EsferaStack);

  return 0;
}
