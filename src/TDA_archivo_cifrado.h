#ifndef TDA_ARCHIVO_CIFRADO_H_
#define TDA_ARCHIVO_CIFRADO_H_
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAXBUFFER 255
#define N 9

typedef struct 
     {
     unsigned char matriz [N][N]; // Clave del algoritmo Playfair
     FILE *archivo;
     }TAC;

/***ABRE UN ARCHIVO PARA LECTURA O ESCRITURA***/
int TAC_Abrir (TAC *tac, char *archMensaje, char tipoAcceso, char *archConf);

/****CERRAR EL ARCHIVO*******/
int TAC_Cerrar(TAC *tac);

/**********LEER LA SIGUIENTE LINEA DEL ARCHIVO CIFRADO*/
int TAC_Leer(TAC *tac, char *mensaje);

/************ESCRIBE UNA LINEA EN EL ARCHIVO CIFRADO*/
int TAC_Escribir(TAC *tda, char *mensaje);

#endif /*TDA_ARCHIVO_CIFRADO_H_*/
