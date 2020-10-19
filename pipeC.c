#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 


int main(){
    int fd,fd1;
    char *file="/tmp/myfifo";
    mkfifo(file,0666);


    int id=fork();
    if( id>0 ){
        int saldoA=1000;
        int saldoF=0;
        printf("el saldo inicial es %d \n",saldoA);

        fd=open( file,O_WRONLY );
        write(fd , &saldoA, sizeof( saldoA ) );
        close( fd );

        ///wait(0);
sleep(4);
        printf("el usuario B ya interactuo\n");
        printf("el usuario A vuelve a interactuar\n");

        fd1 = open( file , O_RDONLY);
        read( fd1,&saldoF,sizeof( saldoF ) );
        close( fd1 );

        printf("el saldo que ve  A es %d\n",saldoF);
        printf("el usuario A deposita 100\n");

        saldoF+=100;
        printf(" el saldo final es %d \n",saldoF);
        return 0;
    }
    else{
        int saldoB=0;

        fd1 = open( file , O_RDONLY);
        read( fd1,&saldoB,sizeof( saldoB ) );
        close( fd1 );

        printf("el usuario B lee el saldo %d\n",saldoB);
        printf("el usuario B retira 200 pesos\n");
        saldoB-=200;

        fd1=open( file, O_WRONLY );
	///printf(" ya termino\n ");
        write( fd1,&saldoB,sizeof( saldoB ) );
        close( fd1 );
        
	exit(0);
    }



    return 0;
}

