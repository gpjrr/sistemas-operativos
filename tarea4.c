#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
int ban=0;
int n,a[10101];
int ini,fin;

int process_fork(int nproc) {
    int i;
    for(i=1; i<=nproc-1;i++)
        if(fork()==0)
            return(i);
    return(0);
}
void Proceso1(){
    int sum=0;
    for(int i=0;i<n;i++)
        sum+=a[i];
    printf("la suma de los n numeros es %d \n",sum);
}
void Proceso2(){
    printf("los numeros impares en el rango son: \n");
    for(int i=ini;i<=fin;i++)
        if( i%2==1 )
        printf("%d ",i);
    printf("\n");
}
void Proceso3(){
    int suma=0;
    for(int i=0;i<n;i++)
        if( i%2==0 )
            suma+=a[i];
printf("la suma de los valores en las posiciones impares es %d \n",suma);
}

void Proceso4(){
    int suma=0;
    for(int i=0;i<n;i++)
        if( i%2==1 )
            suma+=a[i];
printf("la suma de los valores en las posiciones pares es %d \n",suma);
}
void Proceso5(){
    int min=(1e9);
    int max=-(1e9);
    for(int i=0;i<n;i++){
        if( a[i]<min )
            min=a[i];
        if( a[i]>max )
            max=a[i];
    }
    printf("el valor maximo es %d \n",max);
    printf("el valor minimo es %d \n",min);    
}
int main() {
    if( ban==0 ){
        printf("dar el valor de n \n");
        scanf("%d",&n);
        printf("dar los n elementos \n");
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        printf("dar el primer valor de un rango \n");
        scanf("%d",&ini);
        printf("dar el segundo valor de un rango \n");
        scanf("%d",&fin);
        ban=1;
    }

    int valor=process_fork(5);
    switch( valor ){
        case 0:
            exit(1);
        case 1:
            printf( "soy el proceso %d, id=%d\n",valor,getpid() );
            Proceso1();
            exit(1);
        case 2:
            printf( "soy el proceso %d, id=%d\n",valor,getpid() );
            Proceso2();
            exit(1);
        case 3:
            printf( "soy el proceso %d, id=%d\n",valor,getpid() );
            Proceso3();
            exit(1);
        case 4:
            printf( "soy el proceso %d, id=%d\n",valor,getpid() );
            Proceso4();
            exit(1);
        case 5:
            printf( "soy el proceso %d, id=%d\n",valor,getpid() );
            Proceso5();
            exit(1);
    }
    return 0;
}

