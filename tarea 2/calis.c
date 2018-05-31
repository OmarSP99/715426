#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char nombre[15];
	float calificacion;
} Profesor;

Profesor* averageArray(Profesor arr[40] ,Profesor auxiliar[40], int n);
void readArray(Profesor arr[20], int n);
void mergeArrays(Profesor arr[40], int n, Profesor arr1[20], int n1, Profesor arr2[20], int n2);
void sortArray(Profesor arr[40], int n);
void printArray(Profesor arr[20], int n);


int main()
{
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	Profesor arr1[20];  //Primer arreglo
	Profesor arr2[20];  //Segundo arreglo
	Profesor arrF[40];  //Arreglo final, con elementos fusionados y ordenados
	Profesor final[40];
	int n1, n2; //Longitud de los arreglos

	printf("Ingrese el numero de profesores (Ingenieria) [1,20]\n");
	scanf("%d",&n1);
	while(n1<1 || n1>20)
	{
		printf("Ingrese el numero de profesores (Ingenieria) [1,20]\n");
		scanf("%d",&n1);
	}
	readArray(arr1,n1); //leer el primer arreglo

	printf("Ingrese el numero de profesores (Licenciatura) [1,20]\n");
	scanf("%d",&n2);
	while(n2<1 || n2>20)
	{
		printf("Ingrese el numero de profesores (Licenciatura) [1,20]\n");
		scanf("%d",&n2);
	}
	readArray(arr2,n2); //leer el segundo arreglo

	mergeArrays(arrF,n1+n2,arr1,n1,arr2,n2);  //Fusionar los dos arreglos en un tercer arreglo
	averageArray(arrF,final,n1+n2);
	sortArray(final,n1+n2);  //Ordenar los elementos del tercer arreglo, recuerde que pueden  //existir profesores repetidos
	printArray(final,n1+n2);   //Imprimir el resultado final
	return 0;
}
void readArray(Profesor arr[20], int n)
{
	Profesor * ap=arr;
	for(int i=0;i<n;i++)
	{
		scanf("%s[^\n]",(ap+i)->nombre);
		scanf("%f",&(ap+i)->calificacion);
	}

}
void printArray(Profesor arr[20], int n)
{
	Profesor * ap=arr;
	for(int i=0;i<n;i++)
	{
		if(strcmp((ap+i)->nombre," ")==1)
		{
			printf("%s\t\t",(ap+i)->nombre);
			printf("%.2f\n",(ap+i)->calificacion);
		}
	}
}
void mergeArrays(Profesor arr[40], int n, Profesor arr1[20], int n1, Profesor arr2[20], int n2)
{
	//Profesor * ap=arr;
	//Profesor * ap1=arr1;
	//Profesor * ap2=arr2;
	int i,j;
	for(i=0;i<n1;i++)
		arr[i]=arr1[i];
		//strcpy((arr+i)->nombre,(arr1+i)->nombre);
		//(arr+i)->calificacion=(arr1+i)->calificacion;
	for(j=0;j<n2;j++)
		arr[i++]=arr2[j];
		//i++;
		//strcpy((arr+i)->nombre,(arr2+j)->nombre);
		//(arr+i)->calificacion=(arr2+j)->calificacion;
}
Profesor* averageArray(Profesor arr[40] ,Profesor auxiliar[40], int n)
{
	int i,j;
	float acum,rep,cf;
	for(i=0;i<n;i++)
	{
		acum=0;
		rep=1;
		for(j=0;j<n;j++)
		{
			if(strcmp(arr[i].nombre,arr[j].nombre)==0 && i!=j && strcmp(arr[i].nombre," ")==1)
			{
				acum+=arr[i].calificacion;
				rep++;
				strcpy(arr[j].nombre," ");
				arr[j].calificacion=0;
			}
		}
		cf=(acum+arr[i].calificacion)/rep;
		strcpy(auxiliar[i].nombre,arr[i].nombre);
		auxiliar[i].calificacion=cf;
	}
	return auxiliar;
/*	Profesor * ap=arr;
	Profesor * aux=auxiliar;
	for(i=0;i<n;i++)
	{
		acum=0;
		rep=1;
		for(j=0;i<n;j++)
		{
			if(strcmp((*(ap+i)).nombre,(ap+j)->nombre)==0 && i!=j && strcmp((ap+i)->nombre," ")==1)
			{
				acum+=(ap+j)->calificacion;
				rep++;
				strcpy((ap+j)->nombre," ");
				(ap+j)->calificacion=0;
			}
		}
		strcpy((aux+i)->nombre,(ap+i)->nombre);
		(aux+i)->calificacion=(acum+(arr+i)->calificacion)/rep;
	}*/

}

void sortArray(Profesor arr[], int n)
{
	int h, i;
	int huboCambios; //bandera
	Profesor aux;
	for(h=0; h<n-1; h++)
	{
		huboCambios = 0;
		for(i=0; i<n-1-h; i++)
				if(arr[i].calificacion > arr[i+1].calificacion)
				{
					aux = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = aux;
					huboCambios = 1;
				}
		if(huboCambios==0)
			break;
	}
}

