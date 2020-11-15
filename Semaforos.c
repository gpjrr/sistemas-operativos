#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEM_HIJO 0
#define SEM_PADRE 1
int a[100];
main(int argc, char *argv[]) {


	int aux=1, semid, pid;
	struct sembuf operacion;
	key_t llave;

	llave=ftok(argv[0],'K');
	if ((semid=semget(llave,2,IPC_CREAT|0600))==-1){
		perror("semget");
		exit(-1);
	}
	semctl(semid,SEM_HIJO,SETVAL,0);
	semctl(semid,SEM_PADRE,SETVAL,1);

	for(int i=0; i<100;i++)
		a[i]=rand()%100;


	int min1, min2;
	min1 = a[0];
	min2 = a[50];

	if((pid=fork())==-1){
		perror("fork");
		exit(-1);
		}

    if(pid==0){ 
        while(aux<1){
	    for(int i=0; i<50;i++)
                if (min1>a[i])
                    min1 = a[i];
            printf("El minimo de la parte 1 es: %d", min1);
			operacion.sem_num=SEM_HIJO;
			operacion.sem_op=-1;
			operacion.sem_flg=0;
			semop(semid,&operacion,1);

			
			operacion.sem_num=SEM_PADRE;
			operacion.sem_op=1;
			semop(semid,&operacion,1);
			aux++;
		}
        semctl(semid,0,IPC_RMID,0);
	}
	if(pid==1){
	while(aux<1){
        for (int i=50; i<100;i++)
            if (min1>a[i])
                min2 = a[i];
        
        printf("\nEl minimo de la parte 2 es: %d", min2);
			operacion.sem_num=SEM_HIJO;
			operacion.sem_op=-1;
			operacion.sem_flg=0;
			semop(semid,&operacion,1);

			
			operacion.sem_num=SEM_PADRE;
			operacion.sem_op=1;
			semop(semid,&operacion,1);
		}

	semctl(semid,0,IPC_RMID,0);
	}
	else { 
	operacion.sem_flg=0;
	while(aux<1){
		operacion.sem_num=SEM_PADRE;
		operacion.sem_op=-1;
		semop(semid,&operacion,1);
		operacion.sem_num=SEM_HIJO;
		operacion.sem_op=1;
		semop(semid,&operacion,1);
		aux++;
		}

	semctl(semid,0,IPC_RMID,0);
	}
	
	

}

