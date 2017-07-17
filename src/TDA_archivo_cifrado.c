#include "TDA_archivo_cifrado.h"
#include "funciones_aux.h"

/***ABRE UN ARCHIVO PARA LECTURA O ESCRITURA***/
int TAC_Abrir (TAC *tac, char *archMensaje, char tipoAcceso, char *archConf) 
{
   FILE * archivo;
   
   if ((archivo = fopen(archConf,"r")) == NULL) 
     return (-1); /*devuelve -1 si hubo error al abrir el archivo de configuracion*/

   tac->archivo = fopen(archMensaje,&tipoAcceso);
   if (tac->archivo == NULL)
     return (-2); /*devuelve -2 si hubo error al abrir el archivo del mensaje*/
   else
   {
	   if ((cargarMatriz(archivo,tac->matriz)) == 0) 
		   return (-3); /*devuelve -3 si el archivo de configuración es inválido*/
	   else 
		   return 0; /*devuelve 0 si se pudo abrir*/
   }
}



/****CERRAR EL ARCHIVO*******/
int TAC_Cerrar(TAC *tac)
 {  
    if ( fclose(tac->archivo) != 0 )
    return -1; /*devuelve -1 no puede cerrar el archivo*/
    else 
      return 0; /*devuelve 0 si cerro el archivo*/
 }

/**********LEER LA SIGUIENTE LINEA DEL ARCHIVO CIFRADO*/
int TAC_Leer(TAC *tac, char *mensaje)

{   if (fscanf(tac->archivo,"%[^\n]\n",mensaje) == EOF) 
    return -1; /*si devuelve -1 alcanzo el final del archivo*/
    else 
       {
        if(descifrarLinea(tac,mensaje) == 0)
        return 0; /*devuelve 0 si la linea siguiente del archivo se copio en mensaje*/
        else return (-2);  /*en otro caso devuelve -2*/
       }
}

/************ESCRIBE UNA LINEA EN EL ARCHIVO CIFRADO*/
int TAC_Escribir(TAC *tac, char *mensaje)
{   
	char* cadena = NULL; // Cadena temporal donde se guarda el mensaje descifrado.
	int error;
	
	if ( !esCifrable(mensaje))
		return (-1);
    /*devuelve -1 hubo error por caracteres invalidos en el mensaje*/
    else    
       {
    	cadena = cifrarCadena(mensaje,tac->matriz);

        error = fprintf(tac->archivo,"%s\n",cadena); 
        free(cadena);
/*devuelve 0 escribio en una linea nueva al final de archivo*/
        if (error >= 0)
        return 0;
    	else return (-2); /*otro caso devuelve -2*/
       }
}
