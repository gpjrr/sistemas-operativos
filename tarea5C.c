#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#define AMX 1000

/// 0 1 2 3 
int suma(int bloque){
    int sum=0;
    for(int i=1;i<=25;i++)
        sum+= i+bloque*25 ;
///	printf("\n blo=%d su=%d \n",bloque,sum);
    return sum;
}
int main(){
	FILE *archivo;
    int sumas[10];
    int cien=0;
        
    archivo=fopen("respuesta2.txt","w");
    fclose(archivo);
    
    for(int i=0;i<4;i++){
        int id=fork();
        if( id>0 )
            wait(3);
        else {
                
            int res=suma(i);
            archivo=fopen("respuesta2.txt","a");
            fprintf(archivo,"%d\n",res);
            printf("\n pasos=%d res=%d\n",i,res);
            fclose(archivo);                
	exit(i);
        }
        
    }
    archivo=fopen("respuesta2.txt","r");
    
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

































