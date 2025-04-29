#ifndef __MAIN_H__
#define __MAIN_H__
#include <stddef.h>
#include "glist.h"
#include "diccionarioHash.h"

/* 
 * Lee el archivo a corregir, busca las sugerencias si la palabra no esta en el diccionario y se llama a
 * la funcion de escribir los archivos.
 * Cuando se encuentran las sugerencias (si es que hay), se escriben en el archivo.
*/
void leer_y_buscar (const char *pathArchivo, const char *pathDiccionario, GNode* lista, FILE* archivoCache);

/* 
 * Llama a la funcion que encuentra posibles sugerencias para la palabra a distancia 1, 2 y 3
*/
void encontrar_sugerencias(char* palabra, TablaHash tabla_diccionario, TablaHash tabla_sucesores, GNode* lista);

/* 
 * Escribe el archivo de salida y el archivo Cache segun el formato aclarado en el enunciado
*/
void escribir_archivos(FILE* archivoCache, FILE* archivoSalida, char* palabra, int linea, GNode* lista, int condicion);

#endif //__MAIN_H__
