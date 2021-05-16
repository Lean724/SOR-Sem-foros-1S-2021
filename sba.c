#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>
#include <pthread.h>    
#include <semaphore.h>  
#include <unistd.h>
#define LIMITE 100



//Pasos de la receta
	char pasoReceta1 [LIMITE];     
	char pasoReceta2 [LIMITE];
	char pasoReceta3 [LIMITE];
	char pasoReceta4 [LIMITE];
	char pasoReceta5 [LIMITE];
	char pasoReceta6 [LIMITE];
	char pasoReceta7 [LIMITE];
	char pasoReceta8 [LIMITE];
	char pasoReceta9 [LIMITE];
	char pasoReceta10 [LIMITE];
	char pasoReceta11 [LIMITE];


//Semaforos Compartidos
sem_t semaforoAUX1;
sem_t semaforoAUX2;
sem_t semaforoAUX3;


//creo estructura de semaforos 
struct semaforos {
	sem_t semaforoCortar;
	sem_t semaforoArmar;
	sem_t semaforoMezclarIngredientes;
	sem_t semaforoUsarElemento;
	sem_t semaforoParaCocinar;
	sem_t semaforoParaHornear;
	sem_t semaforoAgregar;
	sem_t semaforoEmpanar;
	
};

struct pasos {
   char accion [LIMITE];
   char ingredientes[4][LIMITE]; 
};
struct parametro {
 int equipo_param;
 struct semaforos semaforos_param;
 struct pasos pasos_param[8];
};

FILE* archivoAEscribir; //referencia del archivo que tengo que escribir

void* cortar(void *data) {
	struct parametro *mydata = data;
	printf("\tEquipo %d -",mydata->equipo_param);
	puts (pasoReceta1);
	fprintf(archivoAEscribir,"\tEquipo %d -",mydata->equipo_param);
	fputs(pasoReceta1,archivoAEscribir);
	usleep( 1000000 );  //Para detener la receta un toque y simular tiempo de preparación
	sem_post(&mydata->semaforos_param.semaforoMezclarIngredientes);
}

void* mezclar(void *data){
	char *accion="mezclar";
	struct parametro *mydata=data;
	sem_wait(&mydata->semaforos_param.semaforoMezclarIngredientes);
	usleep(80000);
	printf("\tEquipo %d -",mydata->equipo_param);
	puts(pasoReceta2);
	fprintf(archivoAEscribir,"\tEquipo %d -",mydata->equipo_param);
	fputs(pasoReceta2,archivoAEscribir);
	usleep(50000);
	sem_post(&mydata->semaforos_param.semaforoUsarElemento);
}

void* usarElemento(void *data){
	struct parametro *mydata=data;
	sem_wait(&mydata->semaforos_param.semaforoUsarElemento);
	sem_wait(&semaforoAUX1);
	usleep(2000000);
	printf("\tEquipo %d -",mydata->equipo_param);
	puts(pasoReceta3);
	fprintf(archivoAEscribir,"\tEquipo %d -",mydata->equipo_param);
	fputs(pasoReceta3,archivoAEscribir);
	sem_post(&semaforoAUX1);
	sem_post(&mydata->semaforos_param.semaforoAgregar);

}


void* agregar(void *data){
	char *accion="agregar";
	struct parametro *mydata=data;
	sem_wait(&mydata->semaforos_param.semaforoAgregar);
	usleep(80000);
	printf("\tEquipo %d -",mydata->equipo_param);
	puts(pasoReceta4);	
	fprintf(archivoAEscribir,"\tEquipo %d -",mydata->equipo_param);
	fputs(pasoReceta4,archivoAEscribir);
	usleep(50000);
	sem_post(&mydata->semaforos_param.semaforoEmpanar);
}


void* empanar(void *data){
	char *accion="empanar";
	struct parametro *mydata=data;
	sem_wait(&mydata->semaforos_param.semaforoEmpanar);
	usleep(80000);
	printf("\tEquipo %d -",mydata->equipo_param);
	puts(pasoReceta5);
	fprintf(archivoAEscribir,"\tEquipo %d -",mydata->equipo_param);
	fputs(pasoReceta5,archivoAEscribir);
	usleep(50000);
	sem_post(&mydata->semaforos_param.semaforoParaCocinar);
}


void* cocinar(void *data){
	struct parametro *mydata=data;
	sem_wait(&mydata->semaforos_param.semaforoParaCocinar);
	sem_wait(&semaforoAUX2);
	printf("\tEquipo %d -",mydata->equipo_param);
	puts(pasoReceta6);
	fprintf(archivoAEscribir,"\tEquipo %d -",mydata->equipo_param);
	fputs(pasoReceta6,archivoAEscribir);	
	usleep(5000000);
	printf("\tEquipo %d -",mydata->equipo_param);
	puts(pasoReceta7);
	fprintf(archivoAEscribir,"\tEquipo %d -",mydata->equipo_param);
	fputs(pasoReceta7,archivoAEscribir);
	sem_post(&semaforoAUX2);
	sem_post(&mydata->semaforos_param.semaforoParaHornear);
}

void* hornear(void *data){
	char *accion="hornear";
	struct parametro *mydata=data;
	sem_wait(&mydata->semaforos_param.semaforoParaHornear);
	sem_wait(&semaforoAUX3);
	printf("\tEquipo %d -", mydata->equipo_param);
	puts(pasoReceta8);
	fprintf(archivoAEscribir,"\tEquipo %d -",mydata->equipo_param);
	fputs(pasoReceta8,archivoAEscribir);
	usleep(1000000);
	printf("\tEquipo %d -",mydata->equipo_param);
	puts(pasoReceta9);
	fprintf(archivoAEscribir,"\tEquipo %d -",mydata->equipo_param);
	fputs(pasoReceta9,archivoAEscribir);
	sem_post(&semaforoAUX3);
	sem_post(&semaforoAUX3);
	sem_post(&mydata->semaforos_param.semaforoCortar);
}

void* cortar1(void *data){
	char *accion="empanar";
	struct parametro *mydata=data;
	sem_wait(&mydata->semaforos_param.semaforoCortar);
	usleep(80000);
	printf("\tEquipo %d -",mydata->equipo_param);
	puts(pasoReceta10);
	fprintf(archivoAEscribir,"\tEquipo %d -",mydata->equipo_param);
	fputs(pasoReceta10,archivoAEscribir);
	usleep(50000);
	sem_post(&mydata->semaforos_param.semaforoArmar);
}

void* armar(void *data){
	char *accion="empanar";
	struct parametro *mydata=data;
	sem_wait(&mydata->semaforos_param.semaforoArmar);
	usleep(80000);
	printf("\tEquipo %d -",mydata->equipo_param);
	puts(pasoReceta11);
	fprintf(archivoAEscribir,"\tEquipo %d -",mydata->equipo_param);
	fputs(pasoReceta11,archivoAEscribir);
	usleep(50000);
	pthread_exit(NULL);
}



void* ejecutarReceta(void *i) {
   	FILE* fichero;
   	fichero = fopen("receta.txt", "rt");
   	fgets (pasoReceta1, LIMITE, fichero);
   	fgets (pasoReceta2, LIMITE, fichero);
	fgets (pasoReceta3, LIMITE, fichero);
	fgets (pasoReceta4, LIMITE, fichero);
	fgets (pasoReceta5, LIMITE, fichero);
	fgets (pasoReceta6, LIMITE, fichero);
	fgets (pasoReceta7, LIMITE, fichero);
	fgets (pasoReceta8, LIMITE, fichero);
	fgets (pasoReceta9, LIMITE, fichero);
	fgets (pasoReceta10, LIMITE, fichero);
	fgets (pasoReceta11, LIMITE, fichero);
   	fclose(fichero);
	archivoAEscribir= fopen("resultado.txt","wt");

	////////////SEMAFOROS///////////////
	sem_t semaforoMezclarIngredientes;
	sem_t semaforoUsarElemento;
	sem_t semaforoAgregar;
	sem_t semaforoEmpanar;
	sem_t semaforoParaCocinar;
	sem_t semaforoParaHornear;
	sem_t semaforoCortar;
	sem_t semaforoArmar;
	/////////////HILOSSSSSS/////
	pthread_t p1; 
	pthread_t p2;
	pthread_t p3; 
	pthread_t p4;
	pthread_t p5; 
	pthread_t p6;
	pthread_t p7; 
	pthread_t p8; 
	pthread_t p9; 

	
	//Equipos

	int p = *((int *) i);
	
	printf("En estos momentos, el equipo %d \n", p);
	struct parametro *pthread_data = malloc(sizeof(struct parametro));

	//arranco a preparar los semaforos
	pthread_data->equipo_param = p;
	pthread_data->semaforos_param.semaforoMezclarIngredientes = semaforoMezclarIngredientes;
	pthread_data->semaforos_param.semaforoUsarElemento= semaforoUsarElemento;
	pthread_data->semaforos_param.semaforoAgregar= semaforoAgregar;
	pthread_data->semaforos_param.semaforoEmpanar= semaforoEmpanar;
	pthread_data->semaforos_param.semaforoParaCocinar= semaforoParaCocinar;
	pthread_data->semaforos_param.semaforoParaHornear= semaforoParaHornear;
	pthread_data->semaforos_param.semaforoCortar= semaforoCortar;
	pthread_data->semaforos_param.semaforoArmar= semaforoArmar;
	//inicializo los semaforos
	sem_init(&(pthread_data->semaforos_param.semaforoMezclarIngredientes),0,0);
	sem_init(&(pthread_data->semaforos_param.semaforoUsarElemento),0,0);
	sem_init(&(pthread_data->semaforos_param.semaforoAgregar),0,0);
	sem_init(&(pthread_data->semaforos_param.semaforoEmpanar),0,0);
	sem_init(&(pthread_data->semaforos_param.semaforoParaCocinar),0,0);
	sem_init(&(pthread_data->semaforos_param.semaforoParaHornear),0,0);
	sem_init(&(pthread_data->semaforos_param.semaforoCortar),0,0);
	sem_init(&(pthread_data->semaforos_param.semaforoArmar),0,0);



	//creo los hilos a todos les paso el struct creado (el mismo a todos los hilos) ya que todos comparten los semaforos 
    int rc;
    rc = pthread_create(&p1,                           //identificador unico
                           NULL,                          //atributos del thread
                                cortar,             //funcion a ejecutar
                                pthread_data);                     //parametros de la funcion a ejecutar, pasado por referencia
	
	//crear demas hilos aqui

	rc= pthread_create(&p2,NULL,mezclar,pthread_data);
	rc= pthread_create(&p3,NULL,usarElemento,pthread_data);

	rc= pthread_create(&p4,NULL,agregar,pthread_data);
	rc= pthread_create(&p5,NULL,empanar,pthread_data);

	rc= pthread_create(&p6,NULL,cocinar,pthread_data);
	rc= pthread_create(&p7,NULL,hornear,pthread_data);

	rc= pthread_create(&p8,NULL,cortar1,pthread_data);
	rc= pthread_create(&p9,NULL,armar,pthread_data);


	//join de todos los hilos
	pthread_join (p1,NULL);
	pthread_join (p2,NULL);
	pthread_join (p3,NULL);
	pthread_join (p4,NULL);
	pthread_join (p5,NULL);
	pthread_join (p6,NULL);
	pthread_join (p7,NULL);
	pthread_join (p8,NULL);
	pthread_join (p9,NULL);

    if (rc){
       printf("Error:unable to create thread, %d \n", rc);
       exit(-1);
     }

	 
	//destruccion de los semaforos 
	sem_destroy(&semaforoMezclarIngredientes);
	sem_destroy(&semaforoUsarElemento);
	sem_destroy(&semaforoParaCocinar);
	sem_destroy(&semaforoParaHornear);
	sem_destroy(&semaforoAgregar);
	sem_destroy(&semaforoEmpanar);
	sem_destroy(&semaforoCortar);
	sem_destroy(&semaforoAgregar);
		
	//salida del hilo
	 pthread_exit(NULL);
}


int main ()
{

	//inicializo los auxiliares
	sem_init(&semaforoAUX1,0,1);
	sem_init(&semaforoAUX2,0,1);
	sem_init(&semaforoAUX3,0,2);


	//creo los nombres de los equipos 
	int rc;
	int *equipoNombre1 =malloc(sizeof(*equipoNombre1));
	int *equipoNombre2 =malloc(sizeof(*equipoNombre2));
	int *equipoNombre3 =malloc(sizeof(*equipoNombre3));
	int *equipoNombre4 =malloc(sizeof(*equipoNombre4));

  	//Equipos
	*equipoNombre1 = 1;
	*equipoNombre2 = 2;
	*equipoNombre3 = 3;
	*equipoNombre4 = 4;

	//creo las variables los hilos de los equipos
	pthread_t equipo1; 
	pthread_t equipo2;
	pthread_t equipo3; 
	pthread_t equipo4;

  
	//inicializo los hilos de los equipos
    rc = pthread_create(&equipo1,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre1); 

    rc = pthread_create(&equipo2,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre2);
	 rc = pthread_create(&equipo3,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre3);
	 rc = pthread_create(&equipo4,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre4);


   if (rc){
       printf("Error:unable to create thread, %d \n", rc);
       exit(-1);
     } 

	//join de todos los hilos
	pthread_join (equipo1,NULL);
	pthread_join (equipo2,NULL);
	pthread_join (equipo3,NULL);
	pthread_join (equipo4,NULL);

	fclose(archivoAEscribir);

	//Destruyo los auxiliares
	sem_destroy(&semaforoAUX1);
	sem_destroy(&semaforoAUX2);
	sem_destroy(&semaforoAUX3);

    pthread_exit(NULL);
}



//Para compilar:   gcc sba.c -o sba -lpthread
//Para ejecutar:   ./sba
