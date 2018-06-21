#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct{
	float calificacion;
	char nombre[15];
} Profesor;

Profesor *averageArray(Profesor arr[40], int n);
void readArray(Profesor arr[20], int n);
void mergeArrays(Profesor arrF[20], int n, Profesor arr1[20], int a, Profesor arr2[20], int b);
void sortArray(Profesor arr[20], int n);
void printArray(Profesor arr[20], int n);

int main()
{
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	Profesor arr1[20];  //Primer arreglo
	Profesor arr2[20];  //Segundo arreglo
	Profesor arrF[40];  //Arreglo final, con elementos fusionados y ordenados
	int n1, n2,nf; //Longitud de los arreglos
	do{
	printf("Ingenieria\n");
	scanf("%i",&n1);
	readArray(arr1,n1); //leer el primer arreglo
	printf("Licenciatura\n");
	scanf("%i",&n2);
	nf=n1+n2;
	readArray(arr2,n2); //leer el segundo arreglo
	mergeArrays(arrF,nf,arr1,n1,arr2,n2);  //Fusionar los dos arreglos en un tercer arreglo
	//sortArray(arrF,nf); //Ordenar los elementos del tercer arreglo, recuerde que pueden //existir profesores repetidos
	//printArray(arrF,nf); //Imprimir el resultado final
	}while(n1<20||n2<20||nf<=40);
	system("pause");
	return 0;
}
Profesor *averageArray(Profesor arr[40], int n)
{
	int i,j;
	float acum,rep;
	//float cf;
	Profesor* ap=arr;
	//Profesor temp;
	//Profesor* tempo=temp;
	Profesor *tempo;
	for(i=0;i<n;i++)
	{
		acum=0;
		rep=1;
		for(j=0;j<n;j++)
		{
			if(strcmp((*(ap+j)).nombre,(*(ap+i)).nombre)==0 && i!=j)
			{
				acum+=(*(ap+j)).calificacion;
				rep++;
				strcpy((*(ap+j)).nombre," ");
				(*(ap+j)).calificacion=0;
			}
		}
		strcpy((*(tempo+i)).nombre,(*(ap*i)).nombre);
		if(rep>1)
			(*(tempo+i)).calificacion=(acum+(*(ap+i)).calificacion)/rep;
		else
			(*(tempo+i)).calificacion=(*(ap*i)).calificacion;
	}
	return tempo;
}
void readArray(Profesor arr[20], int n)
{
	int i;
	Profesor*ap=arr;
	for(i=0;i<n;i++)
	{
		scanf("%s[^\n]",(*(ap+i)).nombre);
		scanf("%f",&(*(ap+i)).calificacion);
	}
}
void mergeArrays(Profesor arrF[40], int n, Profesor arr1[20], int a, Profesor arr2[20], int b)
{
	int i,j;
	Profesor* ap1=arr1;
	Profesor* ap2=arr2;
	Profesor* apF=arrF;
	for(i=0;i<a;i++)
	{
		arrF[i]=arr1[i];
	}
	for(j=0;j<b;j++)
	{
		arrF[i++]=arr2[j];
	}
	arrF=averageArray(arrF,n);


}
void sortArray(Profesor arr[20], int n)
{
	int i,j;
	int cambio;
	Profesor aux;
	Profesor *ap=arr;
	for(i=0;i<n-1;i++)
	{
		cambio=0;
		for(j=0;j<n-1-i;j++)
		{
			if(((*(ap+j)).calificacion!=0) && ((*(ap+j+1)).calificacion!=0))
			{
				if(arr[i].calificacion<arr[i+1].calificacion)
				{
					aux.calificacion=(*(ap+i)).calificacion;
					(*(ap+i)).calificacion=(*(ap+i+1)).calificacion;
					(*(ap+i+1)).calificacion=aux.calificacion;
					cambio=1;
				}
				if(cambio==0)
					break;
			}

		}

	}
}
void printArray(Profesor arr[], int n)
{
	Profesor* ap=arr;
	for(int i=0;i<n;i++)
	{
		printf("%s\t\t",(*(ap+i)).nombre);
		printf("%.2f\n",(*(ap+i)).calificacion);
	}
}

