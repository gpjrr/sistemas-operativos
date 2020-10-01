#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
struct pp{
    int a,b;
}arr[3];
int main(){

    double aux;
  struct pp * point=arr;
            printf("dar los 2 valores del primer vector \n");
        scanf("%d",&arr[0].a);
        scanf("%d",&arr[0].b);
        printf("dar los 2 valores del segundo vector \n");
        scanf("%d",&arr[1].a);
        scanf("%d",&arr[1].b);


    switch (fork()){
        case -1:
            perror("Error de Procesos");
            exit(-1);
                break;
        case 0:
            aux+= ( (point+0)->a )*( (point+0)->a );
            aux+= ( (point+0)->b )*( (point+0)->b );
            aux = sqrt(aux);
            printf ("La norma es de v1 es: %f \n",aux);
            break;

        default:

            printf ("La suma de v1 con v2 es igual a: ");
            int sa,sb;
            sa=( (point+0)->a )+( (point+1)->a );
            sb=( (point+0)->b )+( (point+1)->b );
            printf("suma a=%d suma b=%d",sa,sb);
            printf("\n");
        break;

    }
}

