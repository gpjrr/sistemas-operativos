#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEM_HIJO 0
#define SEM_PADRE 1
    int i=1, semid, pid;
    struct sembuf operacion;key_t llave;
    int a[120];

main(int argc, char *argv[]) {

    srand(time(NULL));
    for(int i=0;i<2;i++)
 llave=ftok(argv[0],'K');
    if ((semid=semget(llave,2,IPC_CREAT|0600))==-1){
        perror("semget");exit(-1);
    }

    
	for(int i=0; i<100;i++)
		a[i]=rand()%100;
    
    for(int i=0;i<100;i++)
        printf("%d ",a[i]);
    
	int min1, min2;
	min1=min2= 300;
    
    semctl(semid,SEM_HIJO,SETVAL,0);
    semctl(semid,SEM_PADRE,SETVAL,1);
    if((pid=fork())==-1){
            perror("fork");
    exit(-1);
    }
    else
    if(pid==0){

      while(i){
            operacion.sem_num=SEM_HIJO;
          operacion.sem_op=-1;
          operacion.sem_flg=0;
          semop(semid,&operacion,1);
          printf("PROCESO HIJO\n");
          for(int i=0; i<50;i++){
                if (min1>a[i])
                    min1 = a[i];
            }
            printf("El minimo de la parte 1 es: %d", min1);
          i--;
          operacion.sem_num=SEM_PADRE;
          operacion.sem_op=1;
          semop(semid,&operacion,1);
      }
      semctl(semid,0,IPC_RMID,0);
    }else {
        operacion.sem_flg=0;
        while(i){
            operacion.sem_num=SEM_PADRE;
            operacion.sem_op=-1;
            semop(semid,&operacion,1);
            printf("PROCESO PADRE \n");
            for (int i=50; i<100;i++){
                if (min2>a[i])
                    min2 = a[i];
            }
            printf("\nEl minimo de la parte 2 es: %d\n", min2);
	i--;            
operacion.sem_num=SEM_HIJO;
            operacion.sem_op=1;
            semop(semid,&operacion,1);
        }
        semctl(semid,0,IPC_RMID,0);
    }
    return 0 ;
}


