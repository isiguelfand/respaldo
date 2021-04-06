/*****************************************************************************/
/*                              Lista Ligada                                 */
/*****************************************************************************/
/*                                                                           */
/* Lista simplemente ligada para guardar datos de tipo int. Cada nodo tiene  */
/* un puntero al nodo siguiente en la lista. La estructura principal tiene   */
/* un puntero al primer y ultimo elemento de la lista.                       */
/*****************************************************************************/

// Indica que este archivo solo se debe incluir una vez en la compilación
#pragma once
#include <stdio.h>
#include <stdlib.h>


// Declaramos el struct para un nodo de la lista
struct linked_person;
// Definimos un alias para el struct nodo.
// La sintaxis es "typedef tipo alias"
typedef struct linked_person Person;

// Definimos el struct nodo
struct linked_person
{
  /** El valor que guarda el nodo */
  int id;
  int state;
  /** Un puntero al siguiente nodo de la lista */
  Person* next;
  Person* prev;
  Person* head;
  Person* tail;
  Person* parent;
  
};




Person* person_init(Person * parent, int id, int state);
void append_contact(Person* parent, int id, int state);
Person* search_contact(Person* person, int id);
void recursive_inform(Person*person, int depth, FILE* output_file);
