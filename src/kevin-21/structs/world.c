#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "world.h"


World* world_init(int n_countries){
    World* world=malloc(sizeof(World));
    world -> n_countries=n_countries;
    world -> n_regions_countries=malloc(n_countries * sizeof(int));
    world -> people_count=malloc(n_countries*sizeof(int*));
    world->countries=malloc(world -> n_countries*sizeof(Person**));
    //world->countries=malloc(n_countries*sizeof(Person**)); 
    return world;
}
void create_region(World* world,int idx,int amount){
    //printf("numero de pais:%i \n ", idx);
    //printf("numero de cantidad:%i \n ", amount);
    //world ->n_countries=amount;
    //printf("--------------------- \n ");
    world->n_regions_countries[idx]=amount;
    world->people_count[idx]=malloc(amount*sizeof(int));
    world->countries[idx]=malloc(amount*sizeof(Person*));
    for (int x = 0; x < amount ; x++){
        world->countries[idx][x]=person_init(NULL,0,2);
          world->people_count[idx][x]=1;
    }
}



void destroy_node2(Person* current){

    if (current==NULL){
        //free(current);
        //printf("Dead end  \n");
        return;
    }
   // else if (current->id==10 ){
       // if (!current->next &&current->id==0 ){
                //printf("****En el 0: no existe el next %i\n", current->id);
       // }
    //}
    //printf("inico \n");
    //printf("-----En el nodo %i --------\n",current->id);
    while(current!=NULL){
        //printf("Nueva iteracion en %i  \n", current->id);
        destroy_node2(current->head);
        //continue;
        //if (current->head!=NULL){
           // printf("El hijo que acaba de ir es  %i, es hijo de  \n",current->head->id,current->id);
        //}
        //printf("Volvimos a  %i \n",current->id);
        if(!current->next ||current->next==NULL ){
            //printf("en el break \n");
            break;
        }
        current=current->next;
        }
    //if (!current->next ){
        //printf("no existe el next %i\n", current->id);
    //}
    //if ((current->next ==NULL && current->head ==NULL)){
        //printf("next y head null %i\n", current->id);
    //}
    if ((current->next ==NULL && current->head ==NULL)){
        //cambios en este if
    //!current->next ||(current->next ==NULL && current->head ==NULL
        //printf("Borrando a %i \n",current->id);
        if (current -> prev && current -> prev!=NULL){//aca agregue la primera condicion
            Person* prev = current -> prev;
           // printf("Borrando a los anteriores a:%i \n",current->id);
            while(prev)
            {  // printf("Borrando a :%i \n",current->id);

                free(current);
                current = prev;
                prev = current -> prev;
            }
            //printf("Borrando a :%i \n",current->id);
            if (current->parent && current->id==current->parent->head->id){
                //printf("....................Dejando sin cabeza %i \n",current->parent->id);
                current->parent->head=NULL;
            }
            free(current);            
        }
        else{
            if (current->parent && current->id==current->parent->head->id){
               // printf("....................Dejando sin cabeza %i \n",current->parent->id);
               current->parent->head=NULL;
           }
            free(current); 
        }
    }
}

void world_destroy(World* world){    
    for(int x=0;x<world->n_countries;x++){
        for(int y=0;y<world->n_regions_countries[x];y++){
            //borrar nodo
           // printf("LLAMANDO A DESTUIR en el pais: %i y la region %i\n",x,y);
            destroy_node2(world->countries[x][y]);
            //free(world->countries[x][y]);
        }
        free(world->countries[x]);
        free(world->people_count[x]);
    }
    free(world->n_regions_countries);
    free(world->people_count);
    free(world->countries);
    free(world);
}


Person* search(World* world,int idx, int region_idx, int depth, List* list){
    Person* person=world->countries[idx][region_idx];
    if (list->top!=NULL){
        Node* node=list->top;
        //printf("Profundidad: %i \n", depth);
        for (int x=0;x<depth;x++){
           // printf("***iteración en la lista***\n", depth);
           // printf("Buscando a  %i en", node->value);
           // printf(" %i \n", person->id);
            person=search_contact(person,node->value);
            node=node ->next;
        }
    }
    //printf("Se encontró a  %i \n", person->id);
    return person;
}

Person* add_contact(World* world, Person* person,int new_id ){
   // printf("Agregando contacto %i a la persona %i  \n", person->id, new_id);
    int state;
    if (person->state==2){
        state =1;
    }
    else{
        state=0;
    }
    append_contact(person,new_id,state);
    return person;
}

void add_contacts(World* world, int country_idx, int region_idx, int depth, List* list, int n_contacts){
   // printf("Agregando contactos  \n");
    Person* person=search(world,country_idx,region_idx,depth,list);
    int new_id;
    for (int x=0;x<n_contacts;x++){
            new_id = world->people_count[country_idx][region_idx];

            add_contact(world,person, new_id);
            world->people_count[country_idx][region_idx] += 1;
    }
}

void inform (World* world,int country_idx, int region_idx, FILE *output_file){
    //fprintf(output_file,"INFORM %d %d\n",country_idx,region_idx);
    Person* first =world->countries[country_idx][region_idx];
    recursive_inform(first,0,output_file);
}
void recovered(World* world, int country_idx, int region_idx, int depth, List* list){
    Person* person=search(world,country_idx,region_idx,depth,list);
    person->state=3;
}

void positive(World* world, int country_idx, int region_idx, int depth, List* list){
    Person* person=search(world,country_idx,region_idx,depth,list);

    
    person->state=2;
    if (person->head && person->head!=NULL){
        //printf("Entrando al sospechoso en espera \n");
        person=person->head;
        while(person && person!=NULL){
            //printf("Cambiando a: %i \n", person->id);
            person->state=1;
            person=person->next;
        }
    }
}

void destroy_node(Person* person){
    Person* current = person->head;
    //printf("inico \n");
    while (current!=NULL){
        //printf("while \n");
        destroy_node(current);
        if (current){
            current=current->next;
        }
        
    }
        if (current==NULL && current->parent){
        //printf("if \n");
        //printf("AcA id: %i \n", person->id);
        if (current->parent->prev!=NULL){
            if (current->parent->next!=NULL){
                current->parent->prev->next=current->parent->next;
            }
            else{
                current->parent->prev->next=NULL;
            }
            //printf("Se elimina como next de anterior \n");
        }
        if (current->parent->next!=NULL){
            if (current->parent->prev!=NULL){
                current->parent->next->prev=current->parent->prev;
            }
            else{
                current->parent->next->prev=NULL;
            }
            //printf("Se elimina como anterior de next \n");
        }
        if ( current->parent->parent->head->id ==current->parent->id){
            if (current->parent->next!=NULL){
                current->parent->parent->head=current->parent->next;
            }
            else{
                current->parent->parent->head=NULL;
            }
            //printf("elimina como inicio de lista \n");
        }
        if (current->parent->parent->tail->id ==current->parent->id){
            if (current->parent->prev!=NULL){
                current->parent->parent->tail=current->parent->prev;
            }
            else{
                current->parent->parent->tail=NULL;
            }
            //printf("elimina como fin de lista \n");
        }
        free(current->parent);
    }
}

void negative(World* world,int idx, int region_idx, int depth, List* list){
    Person* person=search(world,idx,region_idx,depth,list);
    //printf("NEGATIVE----------  \n");
    negative_destroy(person,1);
}

void negative_destroy(Person* current, int head){
    //printf("LLAMANDO E NEGATIVE DESTROY \n");
    if (current==NULL){
        free(current);
        //printf("Dead end  \n");
        return;
    }
    //printf("inico \n");
   // printf("-----En el nodo %i --------\n",current->id);
    while(current!=NULL){
       // printf("Nueva iteracion en ****************%i  \n", current->id);
        negative_destroy(current->head,0);
        if (head){
            if(!current->head || current->head ==NULL ){
                if (current->prev && current->prev!=NULL){
                    if (current->next&&current->next!=NULL){
                        current->prev->next=current->next;
                    }
                    else{
                        current->prev->next=NULL;
                        }
                   // printf("Se elimina como next de anterior %i\n", current->id);
                }
                if (current->next && current->next!=NULL){
                    if (current->prev&&current->prev!=NULL){
                        current->next->prev=current->prev;
                    }       
                    else{
                        current->next->prev=NULL;
                        }
               // printf("Se elimina como anterior de next %i\n", current->id);
                }
                if ( current->parent && current->parent!=NULL  && current->parent->head->id ==current->id){
                    if (current->next && current->next!=NULL){
                        current->parent->head=current->next;
                    }
                    else{
                        current->parent->head=NULL;
                    }
               // printf("elimina como inicio de lista %i\n", current->id);
                }
                if (current->parent && current->parent!=NULL && current->parent->tail->id ==current->id){
                    if (current->prev && current->prev!=NULL){
                        current->parent->tail=current->prev;
                    }
                    else{
                        current->parent->tail=NULL;
                    }
                   // printf("elimina como fin de lista %i\n", current->id);
                }
                    }
        break;
        }
        
       // printf("Volvimos a  %i \n",current->id);
        if(!current->next ||current->next==NULL ){
           // printf("en el break \n");
            break;
            
        }
        current=current->next;
    }
    if (( head!=1 && current->next ==NULL && current->head ==NULL)){
       // printf("Borrando a %i \n",current->id);
        if (current -> prev!=NULL){
            Person* prev = current -> prev;
           // printf("Borrando a los anteriores a:%i \n",current->id);
            while(prev)
            {  //printf("Borrando a :%i \n",current->id);
                free(current);
                current = prev;
                prev = current -> prev;
            }
           // printf("Borrando a :%i \n",current->id);
            if (current->parent && current->id==current->parent->head->id){
                //printf("....................Dejando sin cabeza %i \n",current->parent->id);
                current->parent->head=NULL;
            }
            free(current);   
        }
        else{
            //printf("Estaba solo %i \n",current->id);
            if (current->parent && current->parent->head&& current->id==current->parent->head->id){
               current->parent->head=NULL;
           }
            free(current); 
        }
  }
  else if (head==1){
      //printf("Elimina el negativo %i \n",current->id);
      free(current);
  }
}

void correct(World * world, int country_idx, int region_idx, int depth_1, List* list_1, int depth_2, List* list_2){
    //printf("Con profundidaes   %i  y %i\n",depth_1, depth_2);
    Person* person_1=search(world,country_idx,region_idx,depth_1,list_1);
    Person* person_2=search(world,country_idx,region_idx,depth_2,list_2);

    Person* head_2 = person_2->head;
    Person* tail_2 = person_2->tail;
    for(Person* current = person_1->head; current; current = current -> next){
            current->parent=person_2;
            if (person_2->state==2 && current->state==0){
                current->state=1;
            }
           // printf("Cambiando a %i de %i a %i\n",current->id, person_1->id,person_2->id);
    }

    for(Person* current = person_2->head; current; current = current -> next){
            current->parent=person_1;
            if (person_1->state==2 && current->state==0){
                current->state=1;
            }
           // printf("Cambiando a %i de %i a %i\n",current->id, person_2->id,person_1->id);
    }
    person_2->head=person_1->head;
    person_1->head=head_2;
    person_2->tail=person_1->tail;
    person_1->tail=tail_2;
    //printf("La ceabeza del segundo %i  \n",person_2->head->id);
    //printf("La ceabeza del primero %i  i\n",person_1->head->id);

}

void statistics(World* world,int country_idx, int region_idx, FILE* file){
  //  printf("STADISTICS \n");
    int stat[]  ={0,0,0,0};
    Person* person=world->countries[country_idx][region_idx];
    int* array = get_statistics( person, stat,file);
    fprintf(file,"0:%d\n1:%d\n2:%d\n3:%d\n",array[0],array[1],array[2],array[3]);

}
int* get_statistics(Person *person, int* array,FILE* file){
    //printf("****llamndo a función en %i\n", person->id);
    //fprintf(file,"%d:%d\n",person->id,person->state);
    array[person->state]+=1;
    Person* current = person->head;
    while(current!=NULL){
        //printf("****iterando sobre %i\n", current->id);
        get_statistics(current,array,file);
        current=current->next;
    }

    return array;
}