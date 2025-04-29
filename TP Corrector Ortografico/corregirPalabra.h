#ifndef __CORREGIR_PALABRA_H__
#define __CORREGIR_PALABRA_H__
#include <stddef.h>
#include "diccionarioHash.h"
#include "glist.h"

void intercambiar_par_adyacente(TablaHash tabla, char* palabra, TablaHash tabla_palabras, GList lista);

void insertar_caracteres_entre_letras(TablaHash tabla, char* palabra, TablaHash tabla_palabras, GList lista);

void eliminar_caracteres(TablaHash tabla, char* palabra, TablaHash tabla_palabras, GList lista);

void reemplazar_letra(TablaHash tabla, char* palabra, TablaHash tabla_palabras, GList lista);

void agregar_espacios(TablaHash tabla, char* palabra, GList lista);

/* 
 * Agrega una sugerencia a la lista de sugerencias si la cantidad es menor a 5,
 * si esta en el diccionario y si no estaba previamente agregada en las sugerencias
*/
GList agregar_lista_palabras(GList lista, TablaHash tabla, char* palabra);

/* 
 * La funcion llama a las funciones que buscan sugerencias
*/
void corregir_todo(TablaHash tabla, char* palabra, TablaHash tabla_palabras, GList lista);

/* 
 * La funcion busca sugerencias a distancia 2 y 3 
*/
void corregir_distancia_2(TablaHash tabla_diccionario, TablaHash tabla_palabras, GList lista);

#endif //__CORREGIR_PALABRAa_H__