#include<stdio.h>
#include<stdlib.h>
#include"Stack.h"
#include"Queue.h"

bool balancedBrackets(char *exp);
bool hasHigherPrecedence(char* top, char *operator);
char * InfixToPosfix(char *exp);

int main()
{
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	char expression[100];
	char* posfija;
	printf("Ingrese una expresion matematica\n");
	scanf("%[^\n]",expression);
	//balancedBrackets(expression);
	posfija=InfixToPosfix(expression);
	printf("%s",posfija);
	return 0;
}
//Desarrollo de funcion
bool balancedBrackets(char *exp)
{
	//Definiciones
	Stack s; //Pila a utilizar en la funcion
	s=createStack(); //crear la pila
	char* aux;
	int i=0;
	//condicional
	while(exp[i]!='\0')
	{
		//agregar elementos a la pila
		if(exp[i]=='(' || exp[i]=='[')
			push(s,(char*)&exp[i]);
		//borrar elementos de la pila
		else if(exp[i]==')' || exp[i]==']')
		{
			if(exp[i]==')'){
				//Verificar si el tamaño de la pila en
				if(isEmpty(s)==true){
					printf("Error");
					return false;
				}
				//elimina caracteres si es que coinciden
				aux=(char*)pop(s);
				if(*aux!='('){
					printf("Error");
					return false;
				}
			}
			//Verificar si el tamaño de la pila en
			if(exp[i]==']'){
				if(isEmpty(s)==true){
					printf("Error");
					return false;
				}
				//elimina caracteres si es que coinciden
				aux=(char*)pop(s);
				if(*aux!='['){
					printf("Error");
					return false;
				}
			}
		}
		i++;
	}
	//valida si la pila esta vacia para mandar o no el mensaje de ERROR
	if(isEmpty(s)==true){
		printf("Correcto");
		return true;
	}
	else{
		printf("Error");
		return false;
	}
}
char * InfixToPosfix(char *exp)
{
	Stack p=createStack();
	Queue c=create_queue();
	Queue temp=create_queue();
	char *final=(char*)malloc(sizeof(char)*50);
	int i=0;
	char* tempo;
	char* aux;
	char* tope;
	while(exp[i]!='\0'){
		offer_queue(temp,(char*)&exp[i]);
		i++;
	}
	tempo=(char*)peek_queue(temp);
	while(*tempo!='\0')
	{
		if(*tempo=='0'||*tempo=='1'||*tempo=='2'||*tempo=='3'||*tempo=='4'||*tempo=='5'||*tempo=='6'||*tempo=='7'||*tempo=='8'||*tempo=='9')
		{
			offer_queue(c,(char*)&tempo);
			printf("%c",*tempo);
		}
		else if(*tempo=='(')
			push(p,(char*)&exp[i]);
		else if(*tempo=='+'||*tempo=='-'||*tempo=='*'||*tempo=='/')
		{
			while(isEmpty(p)==false)
			{
				tope=(char*)top(p);
				if(*tope!='(')
				{
					//if(hasHigherPrecedence(tope,tempo)==true)
					{
						aux=(char*)pop(p);
						offer_queue(c,(char*)&aux);
					}
				}
					else{
						break;
					}
				push(p,(char*)&tempo);
			}
		}
		else if(*tempo==')')
		{
			while(isEmpty(p)==false)
			{
				tope=(char*)top(p);
				if(*tope!='(')
				{
					aux=(char*)pop(p);
					offer_queue(c,(char*)&aux);
				}
				else
					break;
			}
			if(isEmpty(p)==false)
				aux=(char*)pop(p);
		}
		aux=(char*)poll_queue(temp);
		tempo=(char*)peek_queue(temp);
	}
	if(isEmpty(p)==false)
	{
		while(isEmpty(p)==false)
		{
			aux=(char*)pop(p);
			offer_queue(c,(char*)&aux);
		}
	}
	int j=0;
	while(isEmpty_queue(c)==falso)
	{
		aux=(char*)poll_queue(c);
		printf("%c",*aux);
		*(final+j)=*aux;
		j++;
	}
	return final;
}
bool hasHigherPrecedence(char* top, char *operator)
{
	if(*top=='(')
		return true;
	else if((*top=='/'||*top=='*')&&(*operator=='+'||*operator=='-'))
		return true;
	else
		return false;
}




