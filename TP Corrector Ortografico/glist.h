#ifndef __GLIST_H__
#define __GLIST_H__

#define MAX_SUG 5

typedef struct _GNode {
  char *data;
  struct _GNode *next;
  int cant_sugerencias;
  int len_palabra;
  char* sugerencias[MAX_SUG];
} GNode;


typedef GNode *GList;

/*
 * Devuelve una lista vacía.
 */
GNode* glist_crear();

/*
 * Destruccion de la lista.
 * Libera todos los datos almacenados
 */
void glist_destruir(GNode* lista);

/*
 * Determina si la lista es vacía.
 */
int glist_vacia(GNode* lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
GNode* glist_agregar_inicio(GNode* lista, char* data, int len_palabra);

/*
  * Toma una lista y una palabra y devuelve un puntero al nodo con la misma palabra
  * O NULL en caso contrario
*/
GNode* encontrar_elemento(GNode* lista, char* palabra);


/**
 * toma una lista y una palabra y devuelve 1 si la palabra esta en las
 * sugerencias, 0 en caso contrario
*/
int encontrar_sugerencia_repetida(GNode* lista, char* palabra);

#endif /* __GLIST_H__ */
