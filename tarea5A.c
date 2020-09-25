#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#define AMX 1000
int inicio=0;
int pasos=0;
/// 0 1 2 3 
int suma(int bloque){
    int sum=0;
    for(int i=0;i<25;i++)
        sum+= i+1+bloque*i ;
	printf("\n blo=%d su=%d \n",bloque,sum);
    return sum;
}
int main(){
	FILE *archivo;
    if( inicio==0 ){
        pasos=0;
        /// lleno el arreglo 1 2 3 .... 98 99 10
        
        archivo=fopen("respuesta.txt","w+");
        fclose(archivo);
        inicio++;
    }
    
    int res=suma(pasos);
    archivo=fopen("respuesta.txt","w+");
    fprintf(archivo,"\n%d\n",res);
	printf("\n pasos=%d res=%d\n",pasos,res);
    pasos++;
    fclose(archivo);
    
    if( pasos<=3 )
        fork();
    
    archivo=fopen("respuesta.txt","r");
    int sumas[10];
    int cien=0;
    for(int i=0;i<4;i++){
        fscanf(archivo,"%d",&sumas[i]);
        cien+=sumas[i];
    }
    for(int i=0;i<4;i++)
        printf("%d ",sumas[i]);
    printf("\n suma=%d \n",cien);

	fclose(archivo);

    return 0;
}



