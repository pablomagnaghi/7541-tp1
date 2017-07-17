#include "funciones_matriz.h"

int cargarMatriz(FILE* archivo, unsigned char matrizDeCaracteres[9][9]){

    int retorno = 0;

	int cantCaracteres, cantLineas, cortePorError;
	unsigned char caracter;
	cantCaracteres = 0;
	cantLineas = 1;
	cortePorError = 0;
	int i = 0;
	int aux;

	//Estas variables auxiliares son para verificar que no se repitan los caracteres.
	int nCaracteres = 0;
	unsigned char vCaracteres[82];
	int estaRepetido = 0;
       
	//Recorro todos los caracteres encontrados en el archivo,
	//cuento las lineas y los caracteres, verifico que cada caracter
	//sea valido y que no se repita, agrego los caracteres a la matriz de caracteres.
	while(((aux = fgetc(archivo)) != EOF) && (!(cortePorError))){
		caracter = (unsigned char)aux;
		if (caracter == '\n'){
			cantLineas++;
			i = 0;
		}
		else{
			estaRepetido = strchr(vCaracteres,caracter);
			if (esCaracterValido(caracter)&&(!estaRepetido)){
				vCaracteres[nCaracteres] = caracter;
				vCaracteres[nCaracteres+1] = '\0';
				nCaracteres++;
				
				cantCaracteres++;
				matrizDeCaracteres[cantLineas - 1][i] = caracter;
				i++;
			}
			else{
				cortePorError = 1;
			}
        }
	}
	if ((cantCaracteres == 81) && (cantLineas == 9) && (!(cortePorError))){
		retorno = 1;
	}
	else{
		printf("La cantidad de caracteres leida es: %d\n", cantCaracteres);
		printf("La cantidad de lineas leidas es: %d\n", cantLineas);
		printf("El corte por error en algun caracter es: %d\n",cortePorError);
		retorno = 0;  
	}
	fclose(archivo);

    return retorno;
}

int esCaracterValido(unsigned char caracter){
    int retorno = 0;
    char* caracteresValidos = "ABCDEFGHIJKLMNOPQRSTUVWXYZÁÉÍÓÚÜÑabcdefghijklmnopqrstuvwxyzáéíóúüñ0123456789.,@ 	";
    if (strchr(caracteresValidos,caracter)){
        retorno = 1;
    }
    if (caracter == '	'){
    	retorno = 1;
    }
    return retorno;
}

int* buscarClave(unsigned char matrizDeCaracteres[9][9], unsigned char a){
    int i;
    int j;
    //Reservo memoria para devolver la posición del caracter en la matriz.
    int* retorno = malloc(2*sizeof(int));
    retorno[0] = -2;
       retorno[1] = -2;
    //Recorro cada posición de la matriz de caracteres
    //y guardo la posición que contiene al caracter buscado.
    for (i = 0; (i < 9)&&(retorno[0] < 0); i++){
        for (j = 0; (j < 9)&&(retorno[0] < 0); j++){
            if (a == (unsigned char)matrizDeCaracteres[i][j]){
                retorno[0] = i;
                retorno[1] = j;
            }
        }
    }
    return retorno;
}

int mismaFila(unsigned char matrizDeCaracteres[9][9], unsigned char a, unsigned char b){
    //Busco la posición de ambos caracteres.
    int* posicionA = buscarClave(matrizDeCaracteres,a);
    int* posicionB = buscarClave(matrizDeCaracteres,b);
    int retorno = 0;
     
    //Si las filas coinciden retorno 1.
    if ((posicionA[0] == posicionB[0])&&(posicionA[0] > 0)){
        retorno = 1;
    }
     
    //Libero la memoria que utilizaban las variables de posición.
    free(posicionA);
    free(posicionB);
    return retorno;
}

int mismaColumna(unsigned char matrizDeCaracteres[9][9], unsigned char a, unsigned char b){
    //Busco la posición de ambos caracteres.
    int* posicionA = buscarClave(matrizDeCaracteres,a);
    int* posicionB = buscarClave(matrizDeCaracteres,b);
    int retorno = 0;
 
    //Si las columnas coinciden retorno 1.
    if ((posicionA[1] == posicionB[1])&&(posicionA[1] > 0)){
        retorno = 1;
    }
 
    //Libero la memoria que utilizaban las variables de posición.
       free(posicionA);
       free(posicionB);
    return retorno;
}

int esPar(char* cadena){
    int retorno = 0;
    //Verifico que la cadena sea válida.
    if (strlen(cadena)>0){
        //Si la cadena es divisible por 2, entonces retorno 1.
        if ((strlen(cadena)%2)==0){
            retorno = 1;
        }
    }
    return retorno;
}

unsigned char siguienteHorizontal(unsigned char matrizDeCaracteres[9][9], unsigned char a){
    //Por defecto, devuelvo un caracter inválido.
    unsigned char retorno = '%';
    //Busco la posición del caracter en la matriz, copio las coordenadas y libero la memoria.
    int* posicion = buscarClave(matrizDeCaracteres, a);
    int fila = posicion[0];
    int columna = posicion[1];
    free(posicion);
  
    //Verifico que la posición sea válida.
    if (fila > -1){
        if (columna < 8){
            retorno = matrizDeCaracteres[fila][columna+1];
        }
        else{
            if ((columna == 8)&&(fila < 8)){
                retorno = matrizDeCaracteres[fila+1][0];
            }
            else{
                if ((columna == 8)&&(fila == 8)){
                    retorno = matrizDeCaracteres[0][0];
                }
            }
        }
    }
  
    return retorno;
}

unsigned char anteriorHorizontal(unsigned char matrizDeCaracteres[9][9], unsigned char a){
       //Por defecto, devuelvo un caracter inválido.
       unsigned char retorno = '%';
       //Busco la posición del caracter en la matriz, copio las coordenadas y libero la memoria.
    int* posicion = buscarClave(matrizDeCaracteres, a);
    int fila = posicion[0];
    int columna = posicion[1];
    free(posicion);
  
    //Verifico que la posición sea válida.
    if (fila > -1){
        if (columna > 0){
            retorno = matrizDeCaracteres[fila][columna-1];
        }
        else{
            if ((columna == 0)&&(fila > 0)){
                retorno = matrizDeCaracteres[fila-1][8];
            }
            else{
                if ((columna == 0)&&(fila == 0)){
                        retorno = matrizDeCaracteres[8][8];
                }
            }
        }
    }
  
    return retorno;
}

unsigned char siguienteVertical(unsigned char matrizDeCaracteres[9][9], unsigned char a){
    //Por defecto, devuelvo un caracter inválido.
    unsigned char retorno = '%';
    //Busco la posición del caracter en la matriz, copio las coordenadas y libero la memoria.
    int* posicion = buscarClave(matrizDeCaracteres, a);
    int fila = posicion[0];
    int columna = posicion[1];
    free(posicion);
  
    //Verifico que la posición sea válida.
    if (fila > -1){
        if (fila < 8){
            retorno = matrizDeCaracteres[fila+1][columna];
        }
        else{
            if ((fila == 8)&&(columna < 8)){
                retorno = matrizDeCaracteres[0][columna+1];
            }
            else{
                if ((fila == 8)&&(columna==8)){
                    retorno = matrizDeCaracteres[0][0];
                }
            }
        }
    }
  
    return retorno;
}

unsigned char anteriorVertical(unsigned char matrizDeCaracteres[9][9], unsigned char a){
    //Por defecto, devuelvo un caracter inválido.
    unsigned char retorno = '%';
    //Busco la posición del caracter en la matriz, copio las coordenadas y libero la memoria.
    int* posicion = buscarClave(matrizDeCaracteres, a);
    int fila = posicion[0];
    int columna = posicion[1];
    free(posicion);
  
    //Verifico que la posición sea válida.
    if (fila > -1){
        if (fila > 0){
            retorno = matrizDeCaracteres[fila-1][columna];
        }
        else{
            if ((fila == 0)&&(columna > 0)){
                retorno = matrizDeCaracteres[8][columna-1];
            }
            else{
                if ((fila == 0)&&(columna==0)){
                    retorno = matrizDeCaracteres[8][8];
                }
            }
        }
    }
  
    return retorno;
}

void imprimirMatriz(unsigned char matrizDeCaracteres[9][9]){
    int i;
    int j;
    //Recorro cada posición de la matriz y escribo por pantalla el caracter.
    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            printf("%c", matrizDeCaracteres[i][j]);
            if (j == 8){
                printf("%c",'\n');
            }
        }
    }
}
