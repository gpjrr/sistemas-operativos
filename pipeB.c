#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main(){
    int fd1[2];
    int fd2[2];
    int fd3[2];
    if( pipe( fd1 )==-1 ){
        printf("error al crear la pipa #1\n");
        return 1;
    }
    if( pipe( fd2 )==-1 ){
        printf("error al crear la pipa #2\n");
        return 1;
    }
    int id=fork();
    if( id>0 ){
        int saldoA=1000;
        int saldoF=0;
        printf("el usuario A lee el saldo %d \n",saldoA);
        close( fd1[0] );
        write(fd1[1], &saldoA, sizeof( saldoA ) );
        close( fd1[1] );

        wait(NULL);
        printf("el usuario B ya interactuo\n");
        printf("el usuario A vuelve a interactuar\n");
        close( fd2[1] );
        read( fd2[0],&saldoF,sizeof( saldoF ) );
        close( fd2[0] );
        printf("el usuario A deposita 100\n");
        saldoF+=100;
        printf(" el saldo final es %d \n",saldoF);
        return 0;
    }
    else{
        int saldoB=0;
        close( fd1[1] );
        read( fd1[0],&saldoB,sizeof( saldoB ) );
        close( fd1[0] );

        printf("el usuario B lee el saldo %d\n",saldoB);
        printf("el usuario B retira 200 pesos\n");
        saldoB-=200;

        close( fd2[0] );
        write( fd2[1],&saldoB,sizeof( saldoB ) );
        close( fd2[1] );
        exit(0);
    }
        


    return 0;
}

