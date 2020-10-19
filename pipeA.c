#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){
    FILE *archivo;
    archivo=fopen("banco.txt","w+");
    fprintf(archivo,"1000");
    fclose( archivo );
    int id=fork();
    if( id==0 ){
        //padre
        archivo=fopen("banco.txt","r");
        int saldoA=0;
        fscanf(archivo,"%d",&saldoA);
        printf("el saldo de A es %d\n",saldoA);

        fclose(archivo);
        archivo=fopen("banco.txt","w");

        saldoA+=100;
	printf("el nuevo saldo de A es %d\n",saldoA);
        fprintf(archivo,"%d",saldoA);
        fclose(archivo);
    
    
        archivo=fopen("banco.txt","r");
        int saldoF=0;
        fscanf(archivo,"%d",&saldoF);
        printf("el saldo final es %d \n",saldoF);
    }
    else{
        archivo=fopen("banco.txt","r");
        int saldoB=0;
        fscanf(archivo,"%d",&saldoB);
        printf("el saldo de B es %d\n",saldoB);

        fclose(archivo);
        archivo=fopen("banco.txt","w");

        saldoB-=200;
	printf("el nuevo saldo de B es %d\n",saldoB);
        fprintf(archivo,"%d",saldoB);
        fclose(archivo);
	return 0;
    }
    
    return 0;
}

