#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int arr[110];

int compare(const void* a, const void* b){
	const int* x = (int*) a;
	const int* y = (int*) b;
	if (*x > *y)
		return 1;
	else if (*x < *y)
		return -1;
	return 0;
}

int n=200;
int cub[101010];

int main(){
    int fin;
    FILE *archivo;
    int mini;
      srand ( time(NULL) );
    for(int i=0;i<n;i++)
        arr[i]=( rand() )%200+1;


    for(int i=1;i<=5;i++){
        int id=fork();
        if( id>0 ){
            if( i==5 ){
                archivo=fopen("min.txt","r");
                int res,t1;
                fscanf(archivo,"%d",&res);
                fscanf(archivo,"%d",&t1);
                if( t1<res )
                    res=t1;
                printf("\nel valor menor es %d\n",res);
                fclose(archivo);
                exit(0);
            }
		else
		sleep(10);
        }
        else {
            switch( i ){
                case 1:
			printf("proceso %d \n",i);

                    for(int i=0;i<n;i++)
                        printf(" %d",arr[i]);
                    printf("\n antees \n");
                    qsort(arr,n,sizeof(int),compare   );
                    int pos=0;
                    arr[0]=0;
                    for(int i=0;i<n;i++){
                        cub[ arr[i] ]++;
                        if(  cub[ pos ] < cub[ arr[i] ] )
                            pos=arr[i];
                    }
                    printf("repetidos=%d valor=%d \n",cub[pos],pos);
              	    exit(1);
	 	    break;
                case 2:
			printf("proceso %d \n",i);
                    fin=0;
                    printf("\n dar el valor que buscas\n");
                    scanf("%d",&fin);
///	        printf("fin=%d",fin) ;       
		    int *res= bsearch(&fin,arr,n,sizeof(int),compare);
                           printf("\n el %d esta en el arreglo",*res);
           
           
                	exit(1);
		break;
                case 3:
			printf("proceso %d \n",i);

                    archivo=fopen("min.txt","w");
                     mini=arr[0];
                    for(int i=0;i<n/2;i++)
                        if( arr[i]<mini )
                            mini=arr[i];

                    printf("\nm1=%d\n",mini);
                    fprintf(archivo,"%d ",mini);
                    fclose(archivo);
			return(0);
                    break;
                case 4:
			printf("proceso %d \n",i);

                    archivo=fopen("min.txt","a");
                    mini=arr[n/2];
                    for(int i=n/2;i<n;i++)
                        if( arr[i]<mini )
                            mini=arr[i];

                    printf("\nm2=%d\n",mini);
                    fprintf(archivo,"%d ",mini);
                    fclose(archivo);
			return(0);
                    break;
            }
        }

    }
    return 0;
}

