#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

typedef struct
{
	long long int limS;
	long long int limI;
}limites;

double pifinal=0;

DWORD WINAPI function(void* lim);

int main()
{
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	HANDLE H[16];
	int h;
	limites lim[16];
	long long int n=50000000000;
	printf("Ingrese el numero de hilos [1],[2],[4],[8],[16]:\n");
	scanf("%d",&h);
	n/=h;
	clock_t start=clock();
	for(long long int i=0;i<h;i++)
	{
		lim[i].limI=(n*i)+1;
		lim[i].limS=n*(i+1);
		H[i]=CreateThread(NULL,0,function,(void*)&lim[i],0,NULL);
	}
	for(long long int i=0;i<h;i++)
		WaitForSingleObject(H[i],INFINITE);

	clock_t stop=clock();
	long int mil=1000*(stop-start)/CLOCKS_PER_SEC;
	printf("%li milisegundos\n",mil);
	printf("PI=%.10f\n",pifinal);

//	for(long long int i=1;i<n;i++)
//	{
//		aux=((i+1)&1?-1.0:1)/(2*i-1);
//		acum+=aux;
//	}
//	pi=acum*4;

	return 0;
}
DWORD WINAPI function(void* lim)
{
	limites *auxiliar=(limites*)lim;
	double aux=0;
	for(long long int i=(*auxiliar).limI;i<=(*auxiliar).limS;i++)
		aux+=((i+1)&1?-1.0:1)/(2*i-1);
	aux*=4;
	pifinal+=aux;
	return 0;
}

