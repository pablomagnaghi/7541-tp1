#ifndef FUNCIONES_MATRIZ_H_
#define FUNCIONES_MATRIZ_H_
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/*
 * PRE: La matriz de caracteres debe estar inicializada.
 * POS: La matriz de caracteres se carga en base al archivo de configuración.
 *      Se retorna el resultado de la operación.
 *         Se verifica que sólo aparezcan caracteres válidos.
 *         Se verifica que no aparezcan caracteres repetidos.
*/
int cargarMatriz(FILE* archivo, unsigned char matrizDeCaracteres[9][9]);

/*
 * PRE: -
 * POS: Se retorna el resultado de la comprobacion de la validez del caracter dado.
*/
int esCaracterValido(unsigned char caracter);


/*
 * PRE: La matriz de caracteres debe estar inicializada.
 * POS: Se devuelve la posicion del caracter en la matriz de caracteres.
 *      Si el caracter no se encuentra en la matriz, se devuelve la posicion [-1,-1].
 *      La posición se retorna en un puntero a memoria dinámica (dos posiciones de tipo entero),
 *      por lo que el usuario deberá liberar dicha memoria.
*/
int* buscarClave(unsigned char matrizDeCaracteres[9][9], unsigned char a);

/*
 * PRE: La matriz de caracteres debe estar inicializada.
 * POS: Devuelve 1 si los caracteres están en la misma fila y 0 en caso contrario.
*/
int mismaFila(unsigned char matrizDeCaracteres[9][9], unsigned char a, unsigned char b);

/*
 * PRE: La matriz de caracteres debe estar inicializada.
 * POS: Devuelve 1 si los caracteres están en la misma columna y 0 en caso contrario.
*/
int mismaColumna(unsigned char matrizDeCaracteres[9][9], unsigned char a, unsigned char b);

/*
 * PRE: La cadena de caracteres debe estar inicializada.
 * POS: Devuelve 1 si la cantidad de caracteres es un número par y 0 en caso contrario.
*/
int esPar(char* cadena);

/*
 * PRE: La matriz de caracteres debe estar inicializada.
 * POS: Devuelve el caracter que está a la derecha del caracter dado
 *      en la matriz de caracteres.
 *      Si el caracter dado es el último de una fila,
 *      el caracter a devolver será el primero de la fila siguiente.
 *      Si el caracter dado es el último de la última fila,
 *      el caracter a devolver será el primero de la primer fila.
 *      Si el caracter dado no se encuentra en la matriz, se retorna '%'.
*/
unsigned char siguienteHorizontal(unsigned char matrizDeCaracteres[9][9], unsigned char a);

/*
 * PRE: La matriz de caracteres debe estar inicializada.
 * POS: Devuelve el caracter que está a la izquierda del caracter dado
 *      en la matriz de caracteres.
 *      Si el caracter dado es el primero de una fila,
 *      el caracter a devolver será el último de la fila anterior.
 *      Si el caracter dado es el primero de la primer fila,
 *      el caracter a devolver será el último de la última fila.
 *      Si el caracter dado no se encuentra en la matriz, se retorna '%'.
*/
unsigned char anteriorHorizontal(unsigned char matrizDeCaracteres[9][9], unsigned char a);

/*
 * PRE: La matriz de caracteres debe estar inicializada.
 * POS: Devuelve el caracter que está a la izquierda del caracter dado
 *      en la matriz de caracteres.
 *      Si el caracter dado es el último de una columna,
 *      el caracter a devolver será el primero de la columna siguiente.
 *      Si el caracter dado es el último de la última columna,
 *      el caracter a devolver será el primero de la primer columna.
 *      Si el caracter dado no se encuentra en la matriz, se retorna '%'.
*/
unsigned char siguienteVertical(unsigned char matrizDeCaracteres[9][9], unsigned char a);

/*
 * PRE: La matriz de caracteres debe estar inicializada.
 * POS: Devuelve el caracter que está a la izquierda del caracter dado
 *      en la matriz de caracteres.
 *      Si el caracter dado es el primero de una columna,
 *      el caracter a devolver será el último de la columna anterior.
 *      Si el caracter dado es el primero de la primer columna,
 *      el caracter a devolver será el último de la última columna.
 *      Si el caracter dado no se encuentra en la matriz, se retorna '%'.
*/
unsigned char anteriorVertical(unsigned char matrizDeCaracteres[9][9], unsigned char a);

void imprimirMatriz(unsigned char matrizDeCaracteres[9][9]);

#endif /*FUNCIONES_MATRIZ_H_*/
