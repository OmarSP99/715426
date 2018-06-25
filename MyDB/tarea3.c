#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* clientes;
FILE* cuentas;
FILE* transacciones;
FILE* MyDB;

typedef struct
{
	int d,m,a;
}fecha;
typedef struct
{
	int id;
	char nom[20];
	char app[20];
	char apm[20];
	fecha f;
}usuario;
typedef struct
{
	int id_c;
	int id_u;
	float saldo;
	fecha apertura;
}cuenta;
typedef struct
{
	int id_tr;
	int operacion;

}tranferencia;

char cl[50]="\\clientes.dat";
char cu[50]="\\cuentas.dat";
char tr[50]="\\transacciones.dat";

void CreateUser(char ruta[],FILE* archivo);
void PrintUsers(char ruta[],FILE*archivo);
void SearchUser(int ID,char ruta[],FILE*archivo);
void DeleteUser(int ID,char ruta[],FILE*archivo);

void CreateAccount(int ID,char ruta[],FILE*archivo);
void PrintAccount(char ruta[],FILE*archivo,FILE* archivo2,char ruta2[]);
void SearchAccount(int ID,char ruta[],FILE*archivo,FILE* archivo2,char ruta2[]);
void DeleteAccount(int ID,char ruta[],FILE*archivo);

typedef enum{true,false}bool;

int main()
{
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	int mp,ms;
	char ruta_alternativa[100];
	char ruta_pri[100];
	char ruta_cli[100];
	char ruta_cue[100];
	char ruta_tra[100];
	MyDB=fopen("mydb.sys","r");
	int busqueda;

	if(MyDB==NULL){
		printf("<<<Esta es la primera vez de ejecucion>>>\n");
		printf("Indica donde queries guardar los archivos\n");
		scanf("%s",ruta_pri);
		strcpy(ruta_cli, ruta_pri);
		strcat(ruta_cli, cl);
		strcpy(ruta_cue, ruta_pri);
		strcat(ruta_cue, cu);
		strcpy(ruta_tra, ruta_pri);
		strcat(ruta_tra, tr);

		MyDB=fopen("mydb.sys","w+");
		fprintf(MyDB,"%s",ruta_pri);
		fclose(MyDB);

		clientes=fopen(ruta_cli,"a+b");
		if(ruta_cli==NULL)
			printf("Error al abrir el archivo: clientes.dat");
		cuentas=fopen(ruta_cue,"a+b");
		if(ruta_cue==NULL)
			printf("Error al abrir el archivo: cuentas.dat");
		transacciones=fopen(ruta_tra,"a+b");
		if(ruta_tra==NULL)
			printf("Error al abrir el archivo: transaccioness.dat");

		int a=0;
		fwrite(&a,sizeof(int),1,clientes);
		fwrite(&a,sizeof(int),1,cuentas);
		fwrite(&a,sizeof(int),1,transacciones);

		fclose(clientes);
		fclose(cuentas);
		fclose(transacciones);
	}
	else
	{
		fscanf(MyDB,"%s",ruta_alternativa);
		strcpy(ruta_cli, ruta_alternativa);
		strcat(ruta_cli, cl);
		strcpy(ruta_cue, ruta_alternativa);
		strcat(ruta_cue, cu);
		strcpy(ruta_tra, ruta_alternativa);
		strcat(ruta_tra, tr);
		fclose(MyDB);
	}
	printf("<<[1]Clientes>> <<[2]Cuentas>> <<[3]Transacciones>> <<[4]Salir>>\n");
	scanf("%d",&mp);
	do
	{
		switch(mp)
		{
			case 1:
				printf("<<[1]Nuevo>> <<[2]Buscar>> <<[3]Eliminar>> <<[4]Imprimir>>\n");
				scanf("%d",&ms);
				switch(ms)
			 	{
					case 1:
						clientes=fopen(ruta_cli,"a+b");
						CreateUser(ruta_cli,clientes);
						fclose(clientes);
						break;
					case 2:
						printf("Ingrese el ID del usuario que desea buscar: ");
						scanf("%d",&busqueda);
						clientes=fopen(ruta_cli,"a+b");
						SearchUser(busqueda,ruta_cli,clientes);
						fclose(clientes);
						break;
					case 3:
						printf("Ingrese el ID del usuario que desea eliminar: ");
						scanf("%d",&busqueda);
						clientes=fopen(ruta_cli,"a+b");
						DeleteUser(busqueda,ruta_cli,clientes);
						fclose(clientes);
						break;
					case 4:
						clientes=fopen(ruta_cli,"a+b");
						PrintUsers(ruta_cli,clientes);
						fclose(clientes);
						break;
				}
			break;
			case 2:
				printf("<<[1]Nuevo>> <<[2]Buscar>> <<[3]Eliminar>> <<[4]Imprimir>>\n");
				scanf("%d",&ms);
				switch(ms)
				{
					case 1:
						printf("Indique el ID de usuario: ");
						scanf("%d",&busqueda);
						cuentas=fopen(ruta_cue,"a+b");
						CreateAccount(busqueda,ruta_cue,cuentas);
						fclose(cuentas);
						break;
					case 2:
						printf("Indique el ID de usuario: ");
						scanf("%d",&busqueda);
						cuentas=fopen(ruta_cue,"a+b");
						SearchAccount(busqueda,ruta_cue,cuentas,clientes,ruta_cli);
						fclose(cuentas);
						break;
					case 3:
						printf("Ingrese el ID de la cuenta que desea eliminar: ");
						scanf("%d",&busqueda);
						clientes=fopen(ruta_cli,"a+b");
						DeleteAccount(busqueda,ruta_cli,clientes);
						fclose(clientes);
						break;
					case 4:
						cuentas=fopen(ruta_cue,"a+b");
						PrintAccount(ruta_cue,cuentas,clientes,ruta_cli);
						fclose(cuentas);
						break;
				}
			break;
			case 3:
				printf("<<[1]Deposito>> <<[2]Retiro>> <<[3]Transacción>>\n");
			break;
			case 4: return 0;
			break;
		}
		printf("<<[1]Clientes>> <<[2]Cuentas>> <<[3]Transacciones>> <<[4]Salir>>\n");
		scanf("%d",&mp);

	}while(mp>=1 && mp<=4);

	system("pause");
	return 0;
}
void CreateUser(char ruta[],FILE* archivo)
{
	usuario user_temp;
	int id;
	archivo=fopen(ruta,"rb");
	if(archivo==NULL)
		printf("Error al abrir el archivo");
	fread(&id,sizeof(int),1,archivo);
	fclose(archivo);
	id++;
	archivo=fopen(ruta,"a+b");
	user_temp.id=id;
	printf("Nombre: ");
	scanf("%s",user_temp.nom);

	printf("Apellido Paterno: ");
	scanf("%s",user_temp.app);

	printf("Apellido Materno: ");
	scanf("%s",user_temp.apm);

	printf("Fecha:\n");
	printf(">>Dia: ");
	scanf("%i",&user_temp.f.d);
	printf(">>Mes: ");
	scanf("%i",&user_temp.f.m);
	printf(">>Año: ");
	scanf("%i",&user_temp.f.a);

	fwrite(&user_temp,sizeof(usuario),1,archivo);
	fclose(archivo);
	archivo=fopen(ruta,"r+b");
	fwrite(&id,sizeof(int),1,archivo);
	fclose(archivo);
}
void PrintUsers(char ruta[],FILE*archivo)
{
	int id;
	archivo=fopen(ruta,"rb");
	printf("ID\t\tNOMBRE\t\tAPELLIDO P.\tAPELLIDO M.\tFECHA\n");
	fread(&id,sizeof(int),1,archivo);
	usuario user_temp;
	while(fread(&user_temp,sizeof(usuario),1,archivo)==1)
		printf("%d\t\t%s\t\t%s\t\t%s\t\t%d/%d/%d\n",user_temp.id,user_temp.nom,user_temp.app,user_temp.apm,user_temp.f.d,user_temp.f.m,user_temp.f.a);
}
void SearchUser(int ID,char ruta[],FILE*archivo)
{
	int id;
	archivo=fopen(ruta,"rb");
	fread(&id,sizeof(int),1,archivo);
	usuario user_temp;
	while(fread(&user_temp,sizeof(usuario),1,archivo)==1)
	{
		if(user_temp.id==ID)
		{
			printf("ID\t\tNOMBRE\t\tAPELLIDO P.\tAPELLIDO M.\tFECHA\n");
			printf("%d\t\t%s\t\t%s\t\t%s\t\t%d/%d/%d\n",user_temp.id,user_temp.nom,user_temp.app,user_temp.apm,user_temp.f.d,user_temp.f.m,user_temp.f.a);
		}
	}
}
void DeleteUser(int ID,char ruta[],FILE*archivo)
{
	int a, cont=0, true=0;
	archivo=fopen(ruta, "r+b");
	fread(&a, sizeof(int),1,archivo);
	usuario user_temp;
	usuario *temp=(usuario *)malloc(sizeof(usuario));
	while(fread(&user_temp,sizeof(usuario),1,archivo)==1)
	{
		if(ID!=user_temp.id)
		{
			(temp+cont)->id=user_temp.id;
			strcpy((temp+cont)->nom,user_temp.nom);
			strcpy((temp+cont)->app,user_temp.app);
			strcpy((temp+cont)->apm,user_temp.apm);
			(temp+cont)->f=user_temp.f;
			cont++;
			temp=(usuario*)realloc(temp, sizeof(usuario)*(cont+1));
			true=1;
		}
	}
	if(true==1)
		printf("Este ID no está en el archivo.\n");
	fclose(archivo);
	archivo=fopen(ruta, "wb");
	fwrite(&a, sizeof(int),1,archivo);
	fclose(archivo);
	archivo=fopen(ruta,"a+b");
	fwrite(temp,sizeof(usuario),cont--,archivo);
	fclose(archivo);
	free(temp);
}
//void idClientes(int id,char ruta[],FILE* archivo,FILE* archivo2,char ruta2[])
//{
//	usuario temp;
//	cuenta aux;
//	while(fread(&aux,sizeof(cuenta),1,archivo)==1)
//		while(fread(&temp,sizeof(usuario),1,archivo2)==1){
//			if(temp.id==aux.id_u)
//				printf("%s",temp.nom);
//		}
//}
void CreateAccount(int ID,char ruta[],FILE*archivo)
{
	cuenta account_temp;
	int id;
	archivo=fopen(ruta,"rb");
	if(archivo==NULL)
		printf("Error al abrir el archivo");
	fread(&id,sizeof(int),1,archivo);
	fclose(archivo);
	id++;
	archivo=fopen(ruta,"a+b");
	account_temp.id_c=id;
	account_temp.id_u=ID;
	printf("Saldo de apertura: ");
	scanf("%f",&account_temp.saldo);
	printf("Fecha:\n");
	printf(">>Dia: ");
	scanf("%i",&account_temp.apertura.d);
	printf(">>Mes: ");
	scanf("%i",&account_temp.apertura.m);
	printf(">>Año: ");
	scanf("%i",&account_temp.apertura.a);

	fwrite(&account_temp,sizeof(cuenta),1,archivo);
	fclose(archivo);
	archivo=fopen(ruta,"r+b");
	fwrite(&id,sizeof(int),1,archivo);
	fclose(archivo);
}
void PrintAccount(char ruta[],FILE*archivo,FILE* archivo2,char ruta2[])
{
	int id;
	archivo=fopen(ruta,"rb");
	archivo2=fopen(ruta2,"rb");
	fread(&id,sizeof(int),1,archivo);
	cuenta account_temp;
	usuario usu;
	printf("USUARIO\t\tID CUENTA\tSALDO\t\t\tFECHA\n");
	while(fread(&account_temp,sizeof(cuenta),1,archivo)==1)
	{
		//idClientes(account_temp.id_u,ruta,archivo,archivo2,ruta2);
		fseek(archivo2,sizeof(int),SEEK_SET);
		while(fread(&usu,sizeof(usuario), 1,archivo2)==1)
			if(usu.id==account_temp.id_u)
				printf("%s",usu.nom);
		printf("\t\t%d\t\t%.2f\t\t\t%d/%d/%d\n",account_temp.id_c,account_temp.saldo,account_temp.apertura.d,account_temp.apertura.m,account_temp.apertura.a);
	}
	fclose(archivo2);
	fclose(archivo);

}
void SearchAccount(int ID,char ruta[],FILE*archivo,FILE* archivo2,char ruta2[])
{
	int id;
	archivo=fopen(ruta,"rb");
	archivo2=fopen(ruta2,"rb");
	fread(&id,sizeof(int),1,archivo);
	cuenta account_temp;
	usuario user_temp;
	printf("USUARIO\t\tID CUENTA\tSALDO\t\tFECHA\n");
	while(fread(&account_temp,sizeof(cuenta),1,archivo)==1)
	{
		if(account_temp.id_u==ID){
			fseek(archivo2,sizeof(int),SEEK_SET);
			while(fread(&user_temp,sizeof(usuario),1,archivo2))
				if(user_temp.id==account_temp.id_u)
					printf("%s",user_temp.nom);
			printf("\t\t%d\t\t%.2f\t\t%d/%d/%d\n",account_temp.id_c,account_temp.saldo,account_temp.apertura.d,account_temp.apertura.m,account_temp.apertura.a);
		}

	}
	fclose(archivo);
	fclose(archivo2);
}
void DeleteAccount(int ID,char ruta[],FILE*archivo)
{
	int a, cont=0, true=0;
	archivo=fopen(ruta, "r+b");
	fread(&a, sizeof(int),1,archivo);
	cuenta account_temp;
	cuenta *temp=(cuenta*)malloc(sizeof(cuenta));
	while(fread(&account_temp,sizeof(cuenta),1,archivo)==1)
	{
		if(ID!=account_temp.id_u)
		{
			(temp+cont)->id_u=account_temp.id_u;
			(temp+cont)->id_c=account_temp.id_c;
			(temp+cont)->saldo=account_temp.saldo;
			(temp+cont)->apertura=account_temp.apertura;
			cont++;
			temp=(cuenta*)realloc(temp, sizeof(cuenta)*(cont+1));
			true=1;
		}
	}
	if(true==1)
		printf("Este ID no está en el archivo.\n");
	fclose(archivo);
	archivo=fopen(ruta, "wb");
	fwrite(&a, sizeof(int),1,archivo);
	fclose(archivo);
	archivo=fopen(ruta,"a+b");
	fwrite(temp,sizeof(cuenta),cont--,archivo);
	fclose(archivo);
	free(temp);
}

