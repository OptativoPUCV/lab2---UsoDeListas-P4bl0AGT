#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "arraylist.h"
#include "stack.h"

//#include "exercises.h"

//Funciones auxiliares que puedes utilizar para debuggear tus ejercicios
//NO MODIFICAR
void imprime_lista(List *L) {
   int *dato;
   dato = (int*)first(L);
   printf("[");
   while(dato != NULL) {
      printf("%d ", *dato);
      dato = (int*)next(L);
   }
   printf("]\n");

}

//Ojo que la pila se vacía al imprimir y se imprime en orden inverso
//NO MODIFICAR
void imprime_y_vacia_pila(Stack *P) {
   void *dato;
   printf("[");
   while((dato = pop(P)) != NULL) {
      printf("%d ", *(int*)dato);
   }
   printf("]\n");
}

/* 
Ejercicio 1.
Crea una Lista y agrega punteros a elementos del 1 al 10.
Recuerda que la lista almacena punteros, por lo que
debes reservar memoria para cada elemento que agregues.
Al finalizar retorna la lista creada.
*/

List* crea_lista() {
  List* L = create_list();
  int *elemento;
  for(int i = 1; i <= 10 ; i++)
  {
    elemento = (int *) malloc(sizeof(int));
    if(elemento == NULL) exit(EXIT_FAILURE);
    *elemento = i;
    pushBack(L, elemento);
  }
  return L;
}

/*
Ejercicio 2.
Crea una función que reciba una lista de enteros (int*) y 
retorne la suma de sus elementos.
*/
int sumaLista(List *L) {
  int size = get_size(L);
  void *elemento = first(L);
  int sum = 0;

  for(int i = 0 ; i < size ; i++)
  {
    sum += *(int *)elemento;
    elemento = next(L);
  }
  return sum;
}

/*
Ejercicio 3.
Crea una función que reciba una lista de punteros a int (int*) y
un entero elem. La función debe eliminar todos los elementos 
de la lista que sean iguales a elem.
Asume que popCurrent luego de eliminar un elemento se
posiciona en el elemento anterior.
*/

void eliminaElementos(List*L, int elem)
{
  int size = get_size(L);
  int *elemento = first(L); 
  for(int i = 0 ; i < size ; i++)
  {
    if( *(int*)elemento == elem)
      popCurrent(L);
    elemento = next(L);
  }
}

/*
Ejercicio 4.
La función copia los punteros de la pila P1 en la pila P2.
El orden de ambas pilas se debe mantener.
Puedes usar una pila auxiliar.
*/

void copia_pila(Stack* P1, Stack* P2)
{
  Stack *pAux = create_stack();
  int *elemento;
  //copiar pila en auxiliar y eliminar dato en p1
  while(top(P1) != NULL)
  {
    elemento = top(P1);
    push(pAux, elemento);
    pop(P1);
  }

  //copiar aux en p1 y p2, ademas de eliminar dato en paux
  while(top(pAux) != NULL)
  {
    elemento = top(pAux);
    push(P1, elemento);
    push(P2, elemento);
    pop(pAux);
  }
}

/*
Ejercicio 5.
La función verifica si la cadena de entrada tiene sus 
paraéntesis balanceados. Retorna 1 si están balanceados,
0 en caso contrario.
*/
int parentesisBalanceados(char *cadena)
{
  Stack *pila = create_stack();
  int cont = 0;

  while((*cadena) != '\0')
  {
    if((*cadena) == '(' || (*cadena) == '{' || (*cadena) == '[')
      push(pila, (void *) &(*cadena));
    
    else
    {
      if(pila == NULL)
        return 0;
      
      if( !((*(char *)top(pila) == '(' && (*cadena) == ')') ||
            (*(char *)top(pila) == '{' && (*cadena) == '}') ||
            (*(char *)top(pila) == '[' && (*cadena) == ']')) )
        return 0;
      pop(pila);
    }
    cadena++;
    cont++;
  }
  if(cont % 2 != 0) return 0;

  return 1;
}