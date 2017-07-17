#include "funciones_aux.h"


/*Recibe un path o ruta, y lo devuelve intercambiando '\' por '/'.*/
void normalizarPath(char *path)
{
	int i;
	int longitud = strlen(path);
/* Se toma el largo de la cadena y se la recorre buscando el caracter "\".*/	
	for(i=0;i<longitud; i++)
	{
/* Si se lo encuentra se lo cambia por el caracter '/'.*/		
		if ( path[i] == '\\' )
			path[i] = '/';
	}
}

/* Se normalizan los 3 parametros de ruta. Cambiando en ellos el caracter
 * '\' por '/'.*/
void normalizarRutas(char *p_config,char *p_cifrado,char *p_descifrado)
{
/* Se normalizan las 3 rutas pasadas por parametro. Cambiando '\' por '/'.
 * Previamente se valida que la ruta no este vacia.*/	
	if(p_config[0] != '\0') normalizarPath(p_config);
	if(p_cifrado[0] != '\0') normalizarPath(p_cifrado);
	if(p_descifrado[0] != '\0') normalizarPath(p_descifrado);
}


int textoConsola(FILE *archivo)
{
	char cadena[MAXBUFFER];

/* Se pide al usuario que ingrese el texto a cifrar. */	
	printf("\n <----- INGRESE TEXTO A CIFRAR ----->:\n\n");
/* Se guarda en archivo siempre y cuando no sea una linea vacia.*/
	gets(cadena);
	while (cadena[0] != '\0')
	{
		fprintf(archivo,"%s\n",cadena);
		gets(cadena);
	}
	return 0;
}

int cifrarPantallaOutput(TAC *tac)
{
	FILE *temp; //Archivo temporal de texto tomado de consola.
	int error = 0;
	
	if ((temp = fopen("C:/temp.txt","w")) != NULL)
	{
/* Se toma texto ingresado por consola por el usuario.*/	
	error = textoConsola(temp);
	fclose(temp);
/* Si se pudo tomar correctamente el texto de consola, se procede a cifrar
 * el contenido del archivo temporal y se gaurda en el archivo de cifrado.*/	
	if(!error)
	{	
/* si lo puede abrir continua.*/		
		if((temp = fopen("C:/temp.txt","r")))
		{
		error = cifrarInputOutput(tac,temp);
/* Si se pudo ejecutar correctamente el cifrado se devuelve 0. En caso contrario se
 * devuelve 1.*/		
		if (!error) 
		{
			remove("C:/temp.txt");
			return 0;
		}
		else
		{
			remove("C:/temp.txt");
			return 1;
		}
		}
		else return 1;
	}
/* Si se produjo un error se devuelve 1.*/	
	else
	{
		remove("C:/temp.txt");
		return 1;
	}
	}
	else return 1;
}


int cifrarInputOutput(TAC *tac, FILE *descifrado)
{
	int  status = 0; // Variable de estado de lectura de archivo.
	char cadena[MAXBUFFER]; // Cadena donde se guarda el texto a cifrar
	int error; // Variable de control de errores.*/
/* Se recorre el archivo de texto descifrado hasta su ultima linea.*/	
	status = fscanf(descifrado,"%[^\n]\n",cadena);

	while(status != EOF)
	{
/* Se intenta escribir la linea en el archivo de cifrado.*/		
		error = TAC_Escribir(tac,cadena);

/* Si se pudo se continua con la proxima linea. En caso contrario se devuelve 1.*/		
		if (!error)
		status = fscanf(descifrado,"%[^\n]\n",cadena);
		else
		{
			fclose(descifrado);
			return 1;
		}
	}
/* Se devuelve 0 sino hay error.*/
	fclose(descifrado);
	return 0;
}

int descifrarInputPantalla(TAC *tac)
{
	int  status = 0; // Variable de estado de lectura de archivo.
	char cadena[MAXBUFFER]; // Cadena donde se guarda el texto a cifrar

/* Se recorre el archivo de texto cifrado hasta su ultima linea.*/	
	status = TAC_Leer(tac,cadena);
	while(status == 0)
	{
		printf("\n%s",cadena);
		status = TAC_Leer(tac,cadena);
	}
	if (status == (-2))
		return 1;
	else
/* Se devuelve 0 sino hay error.*/	
	return 0;
}

int descifrarInputOutput(TAC *tac,FILE *descifrado)
{
	int  status = 0; // Variable de estado de lectura de archivo.
	char cadena[MAXBUFFER]; // Cadena donde se guarda el texto a cifrar
	int error; // Variable de control de errores.*/
/* Se recorre el archivo de texto cifrado hasta su ultima linea.*/	
	status = TAC_Leer(tac,cadena);
	while(status != (-1))
	{
/* Se intenta escribir la linea en el archivo de descifrado.*/		
		error = fprintf(descifrado,"%s\n",cadena);
/* Si se pudo se continua con la proxima linea. En caso contrario se devuelve 1.*/		
		if (error >= 0)
		status = TAC_Leer(tac,cadena);
		else
		{
			fclose(descifrado);
			return 1;
		}
	}
	if (status == (-2))
	{
		fclose(descifrado);
		return 1;
	}
	else
	{
/* Se devuelve 0 sino hay error.*/	
		fclose(descifrado);
		return 0;
	}
}

int esCifrable(char *mensaje)
{
	int i=0;
	
	strcat(mensaje,"\0"); 
	while (mensaje[i] != '\0')
	{
		if (!esCaracterValido(mensaje[i]))
			return 0;
		i++;
	}
	return 1;
}

char* cifrarCadena(char* cadena, unsigned char matrizDeCaracteres[9][9]){
    int i;
    unsigned char parDeCaracteres[2];
    char* cadenaRetorno = malloc(3*strlen(cadena)*sizeof(char));
    strcpy(cadenaRetorno,"");
    char* parCifrado;
    //Si la cantidad de caracteres de la cadena es impar, le agrego al final el caracter '@'.
    if (!(esPar(cadena))){
        cadena = strcat(cadena, "@");
    }
    //Tomo de a pares los caracteres de la cadena y los voy cifrando.
    for (i = 0; i < strlen(cadena); i += 2){
        parDeCaracteres[0] = cadena[i];
        parDeCaracteres[1] = cadena[i + 1];
        parCifrado = cifrarPar(parDeCaracteres,matrizDeCaracteres);
        strcat(cadenaRetorno, parCifrado);
        free(parCifrado);
    }
    return cadenaRetorno;
}

char* cifrarPar(unsigned char parDeCaracteres[2], unsigned char matrizDeCaracteres[9][9]){
    char* retorno = malloc(4*sizeof(char));
    //Acoto la longitud logica de la cadena a devolver.
    retorno[2] = '\0';
    retorno[3] = '\0';
  
    //Verifico si los caracteres a cifrar son iguales.
    if (parDeCaracteres[0]==parDeCaracteres[1]){
        retorno[0] = '&';
        retorno[1] = parDeCaracteres[0];
    }
    else{
        //Verifico si los caracteres a cifrar estan en la misma columna.
        if (mismaColumna(matrizDeCaracteres, parDeCaracteres[0], parDeCaracteres[1])){
            retorno[0] = '$';
            retorno[1] = siguienteVertical(matrizDeCaracteres,parDeCaracteres[0]);
            retorno[2] = siguienteVertical(matrizDeCaracteres,parDeCaracteres[1]);
        }
        else{
            //Verifico si los caracteres a cifrar estan en la misma fila.
            if (mismaFila(matrizDeCaracteres, parDeCaracteres[0], parDeCaracteres[1])){
                retorno[0] = '%';
                retorno[1] = siguienteHorizontal(matrizDeCaracteres,parDeCaracteres[0]);
                retorno[2] = siguienteHorizontal(matrizDeCaracteres,parDeCaracteres[1]);
            }
            //Si no es ninguno de los casos anteriores,
            //realizo lo correspondiente según algoritmo de cifrado.
            else{
                int* posicionA = buscarClave(matrizDeCaracteres, parDeCaracteres[0]);
                int* posicionB = buscarClave(matrizDeCaracteres, parDeCaracteres[1]);
                retorno[0] = matrizDeCaracteres[posicionA[0]][posicionB[1]];
                retorno[1] = matrizDeCaracteres[posicionB[0]][posicionA[1]];
                free(posicionA);
                free(posicionB);
            }
        }
    }
    return retorno;
}

void Descifrar(unsigned char matrizDeCaracteres[9][9],unsigned char mensaje_cifrado[MAXBUFFER],unsigned char mensaje_descifrado[MAXBUFFER]){

    unsigned char c1,c2;
     int *posc1;
     int *posc2;
     int  pos1x,pos1y;
     int  pos2x,pos2y;
     int  i,j;
     i=0;
     j=0;
     while ( i < strlen(mensaje_cifrado)){
         /* Si encuentro & hago esto*/
     if ( mensaje_cifrado[i] == '&'){

        mensaje_descifrado[j]= mensaje_cifrado[i+1];
        mensaje_descifrado[j+1]= mensaje_cifrado[i+1];
        i=i+2;
        j=j+2;

        }else
        if ( mensaje_cifrado[i] == '$' ){
            c1 = mensaje_cifrado[i+1];
            c2 = mensaje_cifrado[i+2];
            mensaje_descifrado[j]  = anteriorVertical(matrizDeCaracteres,c1);
            mensaje_descifrado[j+1]= anteriorVertical(matrizDeCaracteres,c2);
            i=i+3;
            j=j+2;
            }else
            if ( mensaje_cifrado[i] == '%' ){
            c1 = mensaje_cifrado[i+1];
            c2 = mensaje_cifrado[i+2];
            mensaje_descifrado[j]  = anteriorHorizontal(matrizDeCaracteres,c1);
            mensaje_descifrado[j+1]= anteriorHorizontal(matrizDeCaracteres,c2);
            i=i+3;
            j=j+2;
            }else{
              c1 = mensaje_cifrado[i];
              c2 = mensaje_cifrado[i+1];
              posc1 = buscarClave(matrizDeCaracteres,c1);
              posc2 = buscarClave(matrizDeCaracteres,c2);
              pos1x = posc1[0];
              pos1y = posc1[1];
              pos2x = posc2[0];
              pos2y = posc2[1];
              free(posc1);
              free(posc2);	            
mensaje_descifrado[j]= matrizDeCaracteres[pos1x][pos2y];
            mensaje_descifrado[j+1]= matrizDeCaracteres[pos2x][pos1y];
            i=i+2;
            j=j+2;
              };
};

  /*  Borro el @ de las cadenas impares */
   if ( mensaje_descifrado[j-1]=='@'){
        mensaje_descifrado [j-1]='\0';
        }else mensaje_descifrado [j]='\0';

}

int descifrarLinea(TAC *tac,unsigned char *mensaje){

    unsigned char mensaje_descifrado[MAXBUFFER];

    Descifrar(tac->matriz,mensaje,mensaje_descifrado);
    strcpy(mensaje,mensaje_descifrado);
    return 0;
}
