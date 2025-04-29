#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>
#include "main.h"
#include "diccionarioHash.h"
#include "corregirPalabra.h"
#include "glist.h"
#include "leerPalabra.h"

void leer_y_buscar (const char* pathArchivo, const char* pathDiccionario, GNode* lista, FILE* archivoCache) {
	int sz = 1024;
	char *buf = malloc(sz);

    TablaHash tabla_diccionario = crear_tabla(CAPACITY);
    tabla_diccionario = readfile_diccionario(tabla_diccionario, pathDiccionario);

    FILE *archivoSalida = fopen("ArchivoSalida.txt", "w+"); // archivo donde se van a escribir las sugerencias

	FILE *file = fopen(pathArchivo, "rb"); // archivo a corregir

    if(file == NULL){
        printf("Error al abrir el diccionario\n");
        abort();
    }

    int linea = 1;
    int i = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        char palabra[100];
        if(isalpha(c)){ 
            c = tolower(c);
            palabra[i++] = c;
        }
        else{
            palabra[i] = '\0';
            if(strlen(palabra) != 0){
            if(buscar_palabra(tabla_diccionario, palabra) == 1);
            else {
                TablaHash sucesor = crear_tabla(CAPACITY); // donde se guardan las palabras a distancia 1 de la palabra
                GNode* temp = encontrar_elemento(lista, palabra); // si la palabra ya esta corregida
                if(temp == NULL) {
                    lista = glist_agregar_inicio(lista, strdup(palabra), strlen(palabra));
                    
                    encontrar_sugerencias(palabra, tabla_diccionario, sucesor, lista);
                    escribir_archivos(archivoCache, archivoSalida, palabra, linea, lista, 1);
                }
                else
                    escribir_archivos(archivoCache, archivoSalida, palabra, linea, temp, 0);
                
                destruir_tabla(sucesor);
                }
            i = 0;
            }
        if(c == '\n') {
            linea += 1;
        }
        }
    }
    glist_destruir(lista);

    destruir_tabla(tabla_diccionario);
    free(buf);
	fclose(file);
    fclose(archivoSalida);
}

void encontrar_sugerencias(char* palabra, TablaHash tabla_diccionario, TablaHash tabla_sucesores, GNode* lista){
    corregir_todo(tabla_diccionario, palabra, tabla_sucesores, lista);
    if(lista->cant_sugerencias < 5)
        corregir_distancia_2(tabla_diccionario, tabla_sucesores, lista);
}

void escribir_archivos(FILE* archivoCache, FILE* archivoSalida, char* palabra, int linea, GNode* lista, int condicion){
    if(condicion)
        fprintf(archivoCache, "%s, ", palabra);

    fprintf(archivoSalida, "Linea %d, \"%s\" no esta en el diccionario\n", linea, palabra);
    if(lista->cant_sugerencias == 0){
        if(condicion)
            fprintf(archivoCache, "0\n");

        fprintf(archivoSalida, "No hay sugerencias validas");
        }
    else {
        fprintf(archivoSalida, "Tal vez quisiste decir: ");
        if(condicion)
            fprintf(archivoCache, "%d", lista->cant_sugerencias);

        fprintf(archivoSalida, "%s", lista->sugerencias[0]); // para que siga el formato del archivo de salida
        if(condicion)
            fprintf(archivoCache, ", %s", lista->sugerencias[0]);

        for(int n = 1; n < lista->cant_sugerencias; n++){
            if(condicion)
                fprintf(archivoCache, ", %s", lista->sugerencias[n]);
            fprintf(archivoSalida, ", %s", lista->sugerencias[n]);
        }
        if(condicion)
            fprintf(archivoCache, "\n");
    }
    fprintf(archivoSalida, "\n\n");
}

int main(int argc, char* argv[]){
    GNode* lista = glist_crear();

    if(argc != 4) {
        printf("Error al leer\n");   
        exit(1);
    }

    FILE* archivoCache = fopen(argv[3], "a+");
    if(archivoCache == NULL){
        printf("Error al abrir el archivo de sugerencias\n");
        abort();
    }

    lista = read_sugerencia(archivoCache, lista);

    leer_y_buscar(argv[1], argv[2], lista, archivoCache);
    fclose(archivoCache);
    return 0;
}