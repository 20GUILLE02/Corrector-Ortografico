#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>
#include "main.h"
#include "diccionarioHash.h"


void destruir_tabla(TablaHash tabla){
    unsigned int capacidad = tabla->capacidad; 
    for(unsigned int idx = 0; idx < capacidad; ++idx){
        free(tabla->palabra[idx]);
    }
    free(tabla->palabra);
    free(tabla);
}

unsigned long hash_function(char* s) {
    unsigned long hash = 5381;
    int c;
    while ((c = *s++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

TablaHash crear_tabla(unsigned capacidad){
    TablaHash tabla = malloc(sizeof (*tabla));
    assert(tabla != NULL);
    tabla->palabra = malloc(capacidad * sizeof (tabla->palabra[0]));
    tabla->capacidad = capacidad;
    tabla->numElems = 0;
  // Inicializamos las casillas con datos nulos.
    for (unsigned idx = 0; idx < capacidad; ++idx) {
        tabla->palabra[idx] = NULL;
    }

    return tabla;
}

void tablahash_insertar(TablaHash tabla, char* palabra) {
    unsigned idx = hash_function(palabra) % tabla->capacidad;

    while (tabla->palabra[idx]){ 
        if(strcmp(tabla->palabra[idx], palabra) == 0) return;
        idx = (idx == tabla->capacidad-1) ? 0 : idx + 1;
    }
    tabla->numElems += 1;
    tabla->palabra[idx] = strdup(palabra);

    if (tabla->numElems * 10 / 7 >= tabla->capacidad)
        rehash(tabla);
}

void rehash(TablaHash tabla){
    unsigned capacidad_viejo = tabla->capacidad;
    tabla->capacidad *= 2;
    int capacidad = tabla->capacidad;
    char** nuevo = malloc(capacidad * sizeof(tabla->palabra[0]));
    for(int idx = 0; idx < capacidad; ++idx) nuevo[idx] = NULL;
    char** viejo = tabla->palabra;
    tabla->palabra = nuevo;
    for(unsigned idx = 0; idx < capacidad_viejo; idx++) {
        if(viejo[idx] != NULL){
            tablahash_insertar(tabla, viejo[idx]);
            free(viejo[idx]);
        }
    }
    free(viejo);
}

TablaHash readfile_diccionario(TablaHash tabla, const char *path) {
    char buf[100];
	FILE *file = fopen(path, "rb");

    if(file == NULL){
        printf("Error al abrir el archivo\n");
        abort();
    }

    while(fgets(buf, sizeof(buf), file) != NULL) {
        if (buf[strlen(buf) - 1] == '\n')
          buf[strlen(buf)-1] = '\0';
        tablahash_insertar(tabla, buf);
    }

	fclose(file);
	return tabla;
}

int buscar_palabra(TablaHash tabla, char* palabra) {
    unsigned int idx = hash_function(palabra) % tabla->capacidad;
    while(tabla->palabra[idx] != NULL) { 
        if (strcmp(tabla->palabra[idx], palabra) == 0)
            return 1;

        idx = (idx == tabla->capacidad - 1) ? 0 : idx + 1;
    }
    return 0;
}
