#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
int n;
char arr[1010];
void dfs(int alt,int yo,int bato){
    if( bato>n )
        return;
    printf("letra=%c alt=%d  dad=%d yoPid=%d \n",arr[bato-1],alt,getppid(),getpid() );


    int id=fork();
//printf("id1==%d\n",id);
    if(  id!=0 ){
        int id2=fork();
///	printf("id2==%d\n",id2);
        if( id2==0 )
            dfs(alt+1,id2,bato*2);

    }
    else
        dfs(alt+1,id,bato*2+1);

}
int main ( ){
    
    gets(arr);
    n=strlen(arr);
	printf("n=%d\n",n);    
int id=fork();
    
	printf("yooo=%d\n",id);
	if(  id!=0 )
        dfs( 1,id, 1 );

    return 0;
}


