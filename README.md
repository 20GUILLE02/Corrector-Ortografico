# Corrector-Ortografico - Diciembre 2022
El programa es un corrector ortografico basado en el corrector ISPELL
el cual toma un archivo a corregir, un diccionario y un archivo que puede tener
sugerencias previamente calculadas o puede estar vacio.

El programa lee palabra por palabra del archivon a corregir y devuelve en un archivo
salida las palabras mal escritas con 5 sugerncias maximo, si es que existen

Los metodos de correccion son intercambiar un par adyacente de la palabra,
insertar caracteres, eliminar caracteres, reemplazar caracteres y separar la palabra

Las sugerencias son de hasta distancia 3 de la palabra a corregir

Se compila con:
	make
	./main (archivo a corregir) (diccionario) (archivo cache)
