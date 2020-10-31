#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int quo;
int pro[10],n,work;
    int fd1[2];
    int fd2[2];

limpiar (){
    if( pipe( fd1 )==-1 ){
        printf("error al crear la pipa #1\n");
        return 1;
    }
    if( pipe( fd2 )==-1 ){
        printf("error al crear la pipa #2\n");
        return 1;
    }
}
int main (){


    printf("da el valor del quantum entre 1 y 10 \n");
    scanf("%d",&quo);
    srand(time(NULL)); // randomize seed

    for(int i=1;i<=4;i++){
        pro[i]=rand()%20;
        while( pro[i]<=1 )
            pro[i]=(  pro[i]+rand() )%20;
    }

    for(int i=1;i<=4;i++)
        printf("proceso#%d tiempo=%d\n",i,pro[i]);
    n=4;

    while( n ){
        for(int i=1;i<=4;i++)
            if( pro[i] ){
                limpiar();
                int id= fork();
                if( id>0 ){
                    close( fd1[0] );
                    write(fd1[1], &pro[i], sizeof( pro[i] ) );
                    close( fd1[1] );
        /// esperamos a que avance en el proceso correspondiente
                    wait(NULL);
                    int tem;
                    close( fd2[1] );
                    read( fd2[0],&tem,sizeof( tem ) );
                    close( fd2[0] );
                    work+=( pro[i]-tem );
                    pro[i]=tem;
                    if( tem==0 )
                        n--;
                    for(int i=1;i<=4;i++)
                        printf("proceso#%d tiempo=%d\n",i,pro[i]);
                    printf("trabajo acumulado %d\n",work);
                }
                else{
                    int tra=0;
                    close( fd1[1] );
                    read( fd1[0],&tra,sizeof( tra ) );
                    close( fd1[0] );
                    printf("inicia el proceso#%d duracion=%d\n",i,tra);
                    int lim=tra;
                    if(quo<tra)
                        lim=quo;
                    for(int i=1;i<=lim;i++)
                        tra--;
                    //printf("finaliza el proceso#%d duracion=%d\n",i,tra);
                    close( fd2[0] );
                    write( fd2[1],&tra,sizeof( tra ) );
                    close( fd2[1] );
                    exit(0);
                }

            }

    }


    return 0;
}


