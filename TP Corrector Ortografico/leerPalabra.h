#ifndef __LEERPALABRA__
#define __LEERPALABRA__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>
#include "main.h"
#include "glist.h"

/* 
 * Toma un archivo y guarda en una lista del tipo GNode los datos del
 * archivo
*/
GNode* read_sugerencia(FILE* archivo,  GNode* lista);

#endif /* __LEERPALABRA_H__ */