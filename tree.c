#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
int n;
void dfs(int alt,int yo){
    if( alt>n )
        return;
    printf("alt=%d yo=%d  dad=%d yoPid=%d \n",alt,yo,getppid(),getpid() );
    

    int id=fork();
//printf("id1==%d\n",id);
    if(  id!=0 ){
        int id2=fork();
///	printf("id2==%d\n",id2);
        if( id2==0 )
            dfs(alt+1,id2);

    }
    else
        dfs(alt+1,id);

}
int main ( ){
    n=3;
    //scanf("%d",&n);
    int id=fork();
	printf("yooo=%d\n",id);
	if(  id!=0 )
        dfs( 1,id );

    return 0;
}

