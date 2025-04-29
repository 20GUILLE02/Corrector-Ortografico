#include "leerPalabra.h"

GNode* read_sugerencia(FILE* archivo, GNode* lista){
    char* palabra = malloc(50);
    char* sugerencia = malloc(50);
    while (!feof(archivo)) {
        char c = fgetc(archivo);
        if(c == EOF) { // Determinar si el archivo cache tiene sugerencias o no
            free(palabra);
            free(sugerencia);
            return lista;
            }
        ungetc(c, archivo);
        int cant;
        fscanf(archivo, "%[^,], %d", palabra, &cant);
        lista = glist_agregar_inicio(lista, strdup(palabra), strlen(palabra));
        if(cant != 0){
            for(int i = 0; i < cant-1; i++){
            fscanf(archivo, ", %[^,]", sugerencia);
            lista->sugerencias[lista->cant_sugerencias++] = strdup(sugerencia);
            lista->len_palabra = strlen(sugerencia);
        }
        fscanf(archivo, ", %[^\n]\n", sugerencia);
        lista->sugerencias[lista->cant_sugerencias++] = strdup(sugerencia);
        }
        else{
            fscanf(archivo, "\n");
        }
    }
    free(palabra);
    free(sugerencia);
    return lista;
}