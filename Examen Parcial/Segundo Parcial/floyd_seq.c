/*C PROGRAM TO IMPLEMENT ALL PAIR SHORTEST PATH USING FLOYDS ALGORITHM
 
INPUT: N VALUE FOR NUMBER OF VERTICES
 
OUTPUT: ADJACENCY MATRIX
SHORTEST DISTANCE MATRIX
*/
 
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define N 1000
 
double diffclock(clock_t clock1,clock_t clock2);

void AdjacencyMatrix(int a[][N],int n){ //To generate adjacency matrix for given nodes
	int i,j;
	for(i = 0;i < n; i++){
		for(j = 0;j <= n; j++){
			a[i][j] = 0;
		}
	}
	 
	for(i = 1; i < n; i++){
		for(j=0;j<i;j++){
			a[i][j] = rand()%10;
			a[j][i] = 99;
		}
	}
}
 
 
int min(int a,int b){
	if(a < b)
		return a;
	else
		return b;
}
 
void floyds(int a[][N],int n){
 
	int i,j,k;
	for(k = 0;k < n ; k++){
		for(i = 0;i < n; i++){
			for(j = 0;j < n ; j++){
				a[i][j] = min (a[i][j], a[i][k] + a[k][j] );
			}
		}
	}
 
}
 
int main(){
	int a[N][N],n,i,j;
	n = N;
	AdjacencyMatrix(a,n);

	clock_t begin=clock();	

	floyds(a,n);

	clock_t end=clock();
	double dif = diffclock(end,begin); 

	printf ("Elasped time is %.5lf seconds\n", dif ); 

	return 0;
}

double diffclock(clock_t clock1,clock_t clock2)
{
    double diffticks=clock1-clock2;
    double diffms=(diffticks)/CLOCKS_PER_SEC;
    return diffms;
}
