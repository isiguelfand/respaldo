#include "persona.h"
////#include <stdlib.h>
//#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


/** Inicializa una lista vacía */
Person* person_init(Person *parent,int id,int state)
{
  Person * person = malloc(sizeof(Person));
  person -> parent = parent;
  person -> id = id;
  person -> state = state;
  person -> next = NULL;
  person -> head= NULL;
  person -> tail = NULL;
  person -> prev = NULL;
  
  return person;
}
void append_contact(Person* parent, int id, int state)

{
    //printf("Haciendo append %i %i\n",parent->id,id);
    Person* new_person=person_init(parent,id,state);
    if (parent==NULL){
        parent ->head =new_person;
    }
    else if (parent->head==NULL){
       parent ->head =new_person; 
    }
    else if (parent->head!=NULL){
        new_person -> prev = parent ->tail;
        parent ->tail ->next = new_person;
        
    }

    parent->tail = new_person;
}

Person* search_contact(Person* person, int id){
    //printf("Search contact %i %i\n",person->id,id);
    //printf("Cabeza %i \n",person->head->id);
    Person * current= person->head;
    while (current!=NULL){
        //printf("Una iteracion\n");
        if (current->id ==id){
            //printf("Encuentra un nodo\n");
            return current;

        }
        current=current->next;
    }
    //printf("retorna nulo\n");
    return NULL;
}

void recursive_inform(Person*person, int depth, FILE *output_file){
    for(int x=0;x<depth;x++){
        fprintf(output_file,"    ");
    }
    fprintf(output_file,"%d:%d\n",person->id,person->state);
    Person* current = person->head;
    while(current!=NULL){
        recursive_inform(current,depth+1,output_file);
        current=current->next;
    }

}

/** Inserta un nuevo elemento al final de la lista */
