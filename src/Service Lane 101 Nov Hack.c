#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n, i,t,j,a[100001],s;
    scanf("%d",&n);
    scanf("%d",&t);
    for(i=0;i<n;i++){scanf("%d",&a[i]) ;}
    while(t--){
    scanf("%d",&i);
    scanf("%d",&j);    
        
       int min = 4;
            for(s=i;s<=j;s++){
                if(a[s]<min){min = a[s];}
            
                        }
            
        printf("%d \n",min);
        
    
    }
    return 0;
}