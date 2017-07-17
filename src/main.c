#include "TDA_archivo_cifrado.h"
#include "funciones_aux.h"
#include "string.h"

int main(int argc, char *argv[])
{	
/*VARIABLES*/	
	
	TAC  tac;
	FILE *descifrado; //Puntero a archivo de descifrado.
	
	char p_config[100]; //Path de archivo de configuración
	char comando[3]; //Comando para cifrar o descifrar;
	char p_cifrado[100]; //Path de archivo cifrado (salida o entrada).
	char p_descifrado[100]; //Path de archivo descifrado (salida o entrada).
	
	int  error;

/* Se recuperan los parametros de ejecucion.*/		
/* Se inicializan los string que contienen los parametros.*/
	strcpy(p_config,"\0");
	strcpy(comando,"\0");
	strcpy(p_cifrado,"\0");
	strcpy(p_descifrado,"\0");
	
/* Previamente se chequea que los argumentos recibidos no esten 
 * vacios.*/
/* Se toman los parametros solo si se ingreso algo ademas 
 * del programa a ejecutar.*/	
	if (argc > 1)
	{
	if (argv[1])strcpy(p_config,argv[1]);
	if (argv[2])strcpy(comando,argv[2]);
	if (argv[3])strcpy(p_cifrado,argv[3]);	
	if (argv[4])strcpy(p_descifrado,argv[4]);

	}
	
/* En primer lugar se valida el parametro de cifrar o descifrar.*/		
		if((strcmp(comando,"-c")!= 0) && (strcmp(comando,"-d")!=0))	
/* Si no tiene uno de los valores posibles, se informa por pantalla al usuario.*/		   
			printf("Tercer parametro invalido. Utilice '-c' para cifrar y '-d' para descifrar\n");
		else
		{
/* Si se ingreso el parametro comando, se procede a normalizar las rutas.*/			
			normalizarRutas(p_config,p_cifrado,p_descifrado);			
/* Si el comando elegido fue '-c' se validan los parametros y se procede a ejecutar
* los procesos de cifrado.*/			
			if (strcmp(comando,"-c")==0)
			{
/* Para iniciar el proceso se intenta abrir(crear) el TDA archivo cifrado 
* en modo escritura. Sino existe se crea, en caso de existir se sobreescribe*/				
				error = TAC_Abrir(&tac,p_cifrado,'w',p_config);

				switch (error)
				{	
				case -1: printf("La ruta del archivo de configuracion es invalida, intente de nuevo.\n");
						 break;
				case -2: printf("La ruta del archivo cifrado es invalida. Reingrese parametros\n");
						 break;
				case -3: printf("El archivo de configuracion es invalido.\n");
						 break;
				case 0 :						
				{
/* Si la ruta del archivo descifrado esta vacia se ejecuta la instruccion de cifrar
* un texto ingresado por consola y se lo guarda en la ruta de archivo de cifrado.*/				
					if(strcmp(p_descifrado,"\0")== 0)
					{
						error = cifrarPantallaOutput(&tac);
						if (error) printf("Caracteres invalidos en mensaje a cifrar\n");
					}
/* Si la ruta del archivo descifrado existe se ejecuta la instruccion de cifrar un
* mensaje desde ese archivo y se lo guarda en la ruta de archivo de cifrado.*/					
					else
					{
						if((descifrado=fopen(p_descifrado,"r"))!= NULL)
						{
						error = cifrarInputOutput(&tac,descifrado);
						if (error) printf("Caracteres invalidos en mensaje a cifrar\n");
						}
						else 
						printf("La ruta del archivo descifrado es invalida. Reingrese parametros\n");
					}	
/* Se cierra el TDA.*/						
					TAC_Cerrar(&tac);
				} // fin CASE 0
				break;
				} // fin SWITCH
				
			}
/* En el caso de que el comando elegido fuese '-d' se procede de igual manera pero
 * ejecutando las instrucciones de descifrado.*/			
			else
			{
/* Para iniciar el proceso se intenta abrir(crear) el TDA archivo cifrado 
*  en modo lectura. Sino existe se devuelve error*/	
				error = TAC_Abrir(&tac,p_cifrado,'r',p_config);

				switch (error)
				{	
				case (-1): printf("La ruta del archivo de configuración es invalida, intente de nuevo.\n");
				break;
				case (-2): printf("La ruta del archivo cifrado es invalida. Reingrese parametros\n");
				break;
				case (-3): printf("El archivo de configuración es invalido.\n");
				break;
				case 0 :
				{
/* Si la ruta del archivo descifrado esta vacia se ejecuta la instruccion de descifrar
*  el contenido del archivo cifrado y mostrarlo por consola.*/										
					if(strcmp(p_descifrado,"\0")== 0)
						error = descifrarInputPantalla(&tac);
/* Si la ruta del archivo descifrado existe se ejecuta la instruccion de descifrar 
*  el contenido del archivo y guardarlo en la ruta de archivo de descifrado.*/					
					else
					{
						if((descifrado=fopen(p_descifrado,"w"))!= NULL)
						error = descifrarInputOutput(&tac,descifrado);
						else 
						printf("La ruta del archivo descifrado es invalida. Reingrese parametros\n");
					}	
/* Se cierra el TDA.*/					
					TAC_Cerrar(&tac);
				} // fin CASE 0
				break;
				} // fin SWITCH				
			}	
		}
		
	//imprimirMatriz(tac.matriz);
    return 0;
}
