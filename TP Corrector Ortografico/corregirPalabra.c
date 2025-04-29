#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>
#include "main.h"
#include "corregirPalabra.h"

void intercambiar_par_adyacente(TablaHash tabla_diccionario, char* palabra, TablaHash tabla_palabras, GList lista){
    int len_palabra = lista->len_palabra;
    char* temp = malloc(len_palabra + 1);
    char caracter;
    strcpy(temp, palabra);

    for(int i = 0; i < len_palabra - 1 && lista->cant_sugerencias < 5; i++){
        caracter = temp[i+1];
        temp[i+1] = temp[i];
        temp[i] = caracter;
        lista = agregar_lista_palabras(lista, tabla_diccionario, temp);
        
        if(tabla_palabras != NULL)
            tablahash_insertar(tabla_palabras, temp);
        
        temp[i] = temp[i+1];
        temp[i+1] = caracter;
        if(temp[i] == temp[i+1]) // se saltea la proxima iteracion ya que la palabra generada es la misma
            i++;
    }
    free(temp);
}

void insertar_caracteres_entre_letras(TablaHash tabla_diccionario, char* palabra, TablaHash tabla_palabras, GList lista){
    int len_palabra = lista->len_palabra;
    char* temp = malloc(len_palabra + 2);
    for(int n = 0; n < len_palabra + 1 && lista->cant_sugerencias < 5; n++){
        strncpy(temp, palabra, n);
        strcpy(&temp[n+1], &palabra[n]);
        for(char caracter = 'a'; caracter <= 'z' && lista->cant_sugerencias < 5; caracter++){
            temp[n] = caracter;
            lista = agregar_lista_palabras(lista, tabla_diccionario, temp);

            if(tabla_palabras != NULL)
                tablahash_insertar(tabla_palabras, temp);
        }
    }
    free(temp);
}

void eliminar_caracteres(TablaHash tabla_diccionario, char* palabra, TablaHash tabla_palabras, GList lista){
    int len_palabra = lista->len_palabra;
    char* temp = malloc(len_palabra);
    for(int n = 0; n < len_palabra && lista->cant_sugerencias < 5; n++){
        strncpy(temp, palabra, n);
        strcpy(&temp[n], &palabra[n+1]);

        lista = agregar_lista_palabras(lista, tabla_diccionario, temp);
        if(tabla_palabras != NULL)
            tablahash_insertar(tabla_palabras, temp);
    }
    free(temp);
}

void reemplazar_letra(TablaHash tabla_diccionario, char* palabra, TablaHash tabla_palabras, GList lista){
    int len_palabra = lista->len_palabra;
    char* temp = malloc(len_palabra + 1);
    char local;
    strcpy(temp, palabra);
    for (int i = 0; i < len_palabra && lista->cant_sugerencias < 5; i++){
        local = temp[i];
        for(char c = 'a'; c <= 'z' && lista->cant_sugerencias < 5; c++) {
            if(c == temp[i]) continue;
            temp[i] = c;
            lista = agregar_lista_palabras(lista, tabla_diccionario, temp);
            if(tabla_palabras != NULL)
                tablahash_insertar(tabla_palabras, temp);
        }
        temp[i] = local;
    }
    free(temp);
}

void agregar_espacios(TablaHash tabla_diccionario, char* palabra, GList lista){
    int len_palabra = lista->len_palabra;
    char* primeraParte = malloc(len_palabra + 1);
    char* segundaParte = malloc(len_palabra + 1);

    for(int n = 1; n < len_palabra && lista->cant_sugerencias < 5; n++){
        strncpy(primeraParte, palabra, n);
        primeraParte[n] = '\0';
        strcpy(segundaParte, &palabra[n]);

        if( (buscar_palabra(tabla_diccionario, primeraParte) == 1) && (((buscar_palabra(tabla_diccionario, segundaParte)) == 1 ) ) ){
            char* temp = malloc(len_palabra + 2);
            strcpy(temp, primeraParte);
            temp[n] = ' ';
            temp[n+1] = 0;
            strcat(temp, segundaParte);
            if ( (encontrar_sugerencia_repetida(lista, temp) == 0) && (lista->cant_sugerencias < 5))// palabra completa
                lista->sugerencias[lista->cant_sugerencias++] = temp;
            else
                free(temp);
        }
    }
    free(primeraParte);
    free(segundaParte);
}

GList agregar_lista_palabras(GList lista, TablaHash diccionario, char* palabra){ 
    if( (lista->cant_sugerencias < 5) && (buscar_palabra(diccionario, palabra) == 1) && (encontrar_sugerencia_repetida(lista, palabra) == 0))
        lista->sugerencias[lista->cant_sugerencias++] = strdup(palabra);
    return lista;
}

void corregir_todo(TablaHash tabla_diccionario, char* palabra, TablaHash tabla_palabras, GList lista){ 
    if(lista->cant_sugerencias < 5) intercambiar_par_adyacente(tabla_diccionario, palabra, tabla_palabras, lista);
    if(lista->cant_sugerencias < 5) insertar_caracteres_entre_letras(tabla_diccionario, palabra, tabla_palabras, lista);
    if(lista->cant_sugerencias < 5) eliminar_caracteres(tabla_diccionario, palabra, tabla_palabras, lista);
    if(lista->cant_sugerencias < 5) reemplazar_letra(tabla_diccionario, palabra, tabla_palabras, lista);
    if(lista->cant_sugerencias < 5) agregar_espacios(tabla_diccionario, palabra, lista);
}

void corregir_distancia_2(TablaHash tabla_diccionario, TablaHash tabla_palabras, GList lista){
    TablaHash tabla_palabras_2 = crear_tabla(CAPACITY);
    for(unsigned idx = 0; idx < tabla_palabras->capacidad && lista->cant_sugerencias < 5; ++idx) {
        if(tabla_palabras->palabra[idx] != NULL) {
            corregir_todo(tabla_diccionario, tabla_palabras->palabra[idx], tabla_palabras_2, lista);
        }
    }
    if(lista->cant_sugerencias < 5){ 
        for(unsigned idx = 0; idx < tabla_palabras_2->capacidad && lista->cant_sugerencias < 5; ++idx) {
            if(tabla_palabras_2->palabra[idx] != NULL) {
                corregir_todo(tabla_diccionario, tabla_palabras_2->palabra[idx], NULL, lista);
            }
        }
    }
    destruir_tabla(tabla_palabras_2);
}