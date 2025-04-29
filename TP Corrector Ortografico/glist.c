#include "glist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

GNode* glist_crear() { return NULL; }

void glist_destruir(GNode* list) {
  GNode *nodo = list;
  GNode *nodoToBeDestroy = list;
  while(nodo != NULL) {
    nodoToBeDestroy = nodo->next;
    for(int i = 0; i < nodo->cant_sugerencias; i++){
      free(nodo->sugerencias[i]);
    }
    free(nodo->data);
    free(nodo);
    nodo = nodoToBeDestroy; 
  }
}

int glist_vacia(GNode* list) { return (list == NULL); }

GNode* glist_agregar_inicio(GNode* lista, char* data, int len_palabra){
  GNode *newNode = malloc(sizeof(GNode));
  newNode->data = data;
  newNode->len_palabra = len_palabra;
  newNode->next = lista;
  newNode->cant_sugerencias = 0;
  return newNode;
}

GNode* encontrar_elemento(GNode* lista, char* palabra){
  if(lista == NULL) return NULL;
  for (GNode* temp = lista; temp != NULL; temp = temp->next)
    if(strcmp(temp->data, palabra) == 0) return temp;
  return NULL;
}

int encontrar_sugerencia_repetida(GNode* lista, char* palabra){
  if(lista->cant_sugerencias == 0) return 0;
  for(int i = 0; i < lista->cant_sugerencias; i++)
    if(strcmp(lista->sugerencias[i], palabra) == 0) return 1;
  return 0;
}