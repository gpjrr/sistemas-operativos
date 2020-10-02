#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int arr[1010];

int compare(const void* a, const void* b){
	const int* x = (int*) a;
	const int* y = (int*) b;
	if (*x > *y)
		return 1;
	else if (*x < *y)
		return -1;
	return 0;
}
int bin(int ini,int fin,int val){
	while( ini<=fin ){
		int mit=(ini+fin)/2;
//printf("%d %d %d=%d\n",ini,mit,fin,arr[mit]);
		if( arr[mit]==val )
		return mit;
		if( arr[mit]>val )
			fin=mit-1;
		else
			ini=mit+1;

	}
return -1;

}
int n=100;
int cub[101010];

int main(){
    int val;
    FILE *archivo;
    int mini;
      srand ( time(NULL) );
    for(int i=0;i<n;i++)
        arr[i]=( rand() )%200+1;
  for(int i=0;i<n;i++)
           printf(" %d",arr[i]);

                    printf("\n dar el valor que buscas\n");
                    scanf("%d",&val);

    for(int i=1;i<=5;i++){
        int id=fork();
        if( id>0 ){
            if( i==5 ){
		printf("proceso padre\n");
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
		wait(1);
        }
        else {
            switch( i ){
                case 1:
			printf("proceso %d \n",i);
                  
                    printf("\n arreglo ordenado \n");
                    qsort(arr,n,sizeof(int),compare   );
                    for(int i=0;i<n;i++)
                        printf(" %d",arr[i]);
                    int pos=0;
                    arr[0]=0;
                    for(int i=0;i<n;i++){
                        cub[ arr[i] ]++;
                        if(  cub[ pos ] < cub[ arr[i] ] )
                            pos=arr[i];
                    }
                  printf("\n la moda es %d y se repite %d veces \n",pos,cub[pos]);
              	    exit(1);
	 	    break;
                case 2:
			printf("proceso %d \n",i);
                   qsort(arr,n,sizeof(int),compare   );
	        printf("buscamos a %d\n ",val) ;       
		    int res= bin(0,n-1,val);
			if(res>=0)
                           printf("\n  %d esta en la posicion %d \n",val,res);
			else
				printf("\n%d no se encuentra \n",val) ;          
           
                	exit(1);
		break;
                case 3:
			printf("proceso %d \n",i);

                    archivo=fopen("min.txt","w");
                     mini=arr[0];
                    for(int i=0;i<n/2;i++)
                        if( arr[i]<mini )
                            mini=arr[i];

                    printf("\nel valor minimo en la primer mitad es %d\n",mini);
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

                    printf("\nel valor minimo en la segunda mitad es %d\n",mini);
                    fprintf(archivo,"%d ",mini);
                    fclose(archivo);
			return(0);
                    break;
            }
        }

    }
    return 0;
}

