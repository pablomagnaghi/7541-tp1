#ifndef FUNCIONES_AUX_H
#define FUNCIONES_AUX_H
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "TDA_archivo_cifrado.h"
#include "funciones_matriz.h"

/****************** FUNCIONES PRIMARIAS DE TDA ******************/

/*
 * PRE: Se recibe 3 rutas de archivo.
 * POS: Se normalizan los 3 parametros de ruta. Cambiando en ellos el caracter
 * 		'\' por '/'.
*/
void normalizarRutas(char *p_config,char *p_cifrado,char *p_descifrado);


/*
 * PRE: Se recibe el TDA TAC inicializado.
 * POS: Se ofrece al usuario la oportunidad de ingresar texto por pantalla.
 * 		Si el texto es cifrable se lo guarda en el archivo cifrado 
 * 		perteneciente al TDA.
*/
int cifrarPantallaOutput(TAC *tac);

/*
 * PRE: Se recibe el TDA TAC inicializado y una ruta valida de archivo descifrado.
 * POS: De ser cifrable, se guarda el contenido del archivo descifrado en el
 * 		archivo cifrado perteneciente al TDA.
*/
int cifrarInputOutput(TAC *tac,FILE *descifrado);

/*
 * PRE: Se recibe el TDA TAC inicializado.
 * POS: Se muestra por pantalla el texto descifrado contenido en el archivo cifrado 
 * 		perteneciente al TDA.
*/
int descifrarInputPantalla(TAC *tac);

/*
 * PRE: Se recibe el TDA TAC inicializado y una ruta valida de archivo descifrado.
 * POS: Se guarda el contenido del archivo cifrado perteneciente al TDA en el
 * 		archivo descifrado.
*/
int descifrarInputOutput(TAC *tac,FILE *descifrado);

/*
 * PRE: Se recibe una cadena.
 * POS: Toma la cadena y valida que este compuesta por los caracteres definidos
 * 		como validos para el algoritmo PLAYFAIR II.
*/
int esCifrable(char *mensaje);



/****************** FUNCIONES DE CIFRADO ******************/

/*
 * PRE: La matriz de caracteres debe estar inicializada.
 *      La cadena de caracteres debe ser cifrable por la matriz de caracteres dada.
 * POS: Se devuelve la cadena cifrada según el algoritmo Playfair II
 *      utilizando la matriz de caracteres dada.
 *      Se retorna un puntero a memoria dinámica, por lo que el usuario deberá
 *      liberar dicha memoria.
*/
char* cifrarCadena(char* cadena, unsigned char matrizDeCaracteres[9][9]);

/*
 * PRE: La matriz de caracteres debe estar inicializada.
 *      El par de caracteres debe ser cifrable por la matriz de caracteres dada.
 * POS: Se devuelve el par de caracteres cifrado según el algoritmo Playfair II
 *      utilizando la matriz de caracteres dada.
 *      Se retorna un puntero a memoria dinámica, por lo que el usuario deberá
 *      liberar dicha memoria.
*/
char* cifrarPar(unsigned char parDeCaracteres[2], unsigned char matrizDeCaracteres[9][9]);



/****************** FUNCIONES DE DESCIFRADO ******************/

/// Funcion: Dada una matriz, descifra el mensaje cifrado pasado por parametro
/// Precondicion:
 /*  mensaje_cifrado valido:  El mensaje cifrado tiene que ser descifrable .
      matrizDeCaracteres valido,solo lo predefinido en el tp. */
/// Postcondicion:
 /*  Devuelve la linea cifrada por el parametro mensaje_descifrado. */

void Descifrar(unsigned char matrizDeCaracteres[9][9],unsigned char mensaje_cifrado[MAXBUFFER],unsigned char mensaje_descifrado[MAXBUFFER]);

/// Funcion: Dada la matriz de configuracion,descifra la linea cifrada
/// Precondicion:
 /*  tac valido:  La matriz debe estar cargada y valida.
      mensaje valido: El mensaje debe ser descifrable.. */
/// Postcondicion:
 /*  Devuelve el mensaje descifrado por el parametro mensaje. */

int descifrarLinea(TAC *tac,unsigned char *mensaje);


#endif /*FUNCIONES_AUX_*/
