#ifndef __DICCIONARIO_HASH_H__
#define __DICCIONARIO_HASH_H__
#include <stddef.h>
#include "glist.h"

#define CAPACITY 1000

struct _TablaHash{
    char** palabra;
    unsigned numElems;
    unsigned capacidad;
};

typedef struct _TablaHash* TablaHash;
/* 
 * Libera los datos de una tabla
*/
void destruir_tabla(TablaHash tabla);

/*
 * Toma un char* y devuelve un valor que se va a utilizar
 * para guardarlo en la tabla hash
*/
unsigned long hash_function(char* s);

/* 
 * Toma un unsigned y devuelve una TablaHash con sus casillas nulas
*/
TablaHash crear_tabla(unsigned capacidad);

/* 
 * Toma una TablaHash y un char* y lo agrega a la tabla, si el elemento ya estaba en la
 * tabla, no lo agrega
*/
void tablahash_insertar(TablaHash tabla, char* palabra);

/* 
 * Rehashea la tabla. Solo se llama cuando la cantidad de elementos es mayor o igual al
 * 70% de la capacidad de la tabla
*/
void rehash(TablaHash tabla);

/* 
 * Toma una TablaHash y un path de un diccionario y guarda todos sus elementos en la
 * tabla hash
*/
TablaHash readfile_diccionario(TablaHash tabla, const char *path);


/*
 * toma una TablaHash y una palabra y devuelve 1 si la palabra
 * esta en la tabla, 0 en caso contrario
*/
int buscar_palabra(TablaHash tabla, char* palabra);

#endif //__DICCIONARIO_HASH_H__