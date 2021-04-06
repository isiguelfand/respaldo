#pragma once
#include "persona.h"
#include "linked_list.h"
struct world;
// Definimos un alias para el struct nodo.
// La sintaxis es "typedef tipo alias"
typedef struct world World;

// Definimos el struct nodo
struct world
{
  /** El valor que guarda el nodo */
  int n_countries;
  int* n_regions_countries;
  int** people_count;
  Person*** countries;
  /** Un puntero al siguiente nodo de la lista */
  
};
World* world_init(int n_countries);
void create_region(World* world,int idx,int amount);
void inform (World* world,int country_idx, int region_idx, FILE *output_file);
void add_contacts(World* world, int country_idx, int region_idx, int depth, List* list, int n_contacts);
Person* add_contact(World* world, Person* person,int new_id );
Person* search(World* world,int idx, int region_idx, int depth, List* list);
void world_destroy(World* world);
//void destroy_node(Person* person);
void destroy_node2(Person* person);
void recovered(World* world, int country_idx, int region_idx, int depth, List* list);
void positive(World* world, int country_idx, int region_idx, int depth, List* list);
void negative_destroy(Person* current, int head);
void negative(World* world,int idx, int region_idx, int depth, List* list);
void correct(World * world, int country_idx, int region_idx, int depth_1, List* list_1, int depth_2, List* list_2);
void statistics(World* world,int country_idx, int region_idx, FILE* file);
int* get_statistics(Person *person, int* array,FILE* file);

