#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std ;

//AUTOR: NAIVER ANILLO
//VERSION v1.

struct pso
{
	int f;
	int c;
	pso *sig;
};
//SUBPROGRAMA PARA VER LA VISITA DE LA POSICION QUE DIGITO EL USUARIO
void ver_visita(pso *cab, bool *sw1, int fe1, int ce1);
//SUBPROGRAMA PARA ACTUALIZAR LAS CAB1(QUE SON LAS POSICIONES QUE VISITO) Y CAB2 QUE ES EL RECORRIDO CUANDO ENTRA A LA MATRIZ.
void actualizar(pso **cab, pso **cab2, int fe1, int ce1, pso **p, pso **q, int *puntos1, int *av1);
//IMPRIMIR LISTA
void imprimir(pso *cab);
int main()
{
	//[VARIABLES]
	//PUNTOS: Se acumula los puntos del usuario, cuando visita una posicion que tiene un 1.
	//SUM: Esta variable la uso para sumar los 1(unos), que se encuentra en la matriz, para compararlo con la variable de PUNTOS.
	//CONT: Esta variable la uso para que cuente los lados que revisa, es para garantizar que reviso los 4 lados.
	//INTS: Esta variable la uso para contar los intentos del usuario, si llega a ubicar la posicion en un 0, le suma 1 la variable hasta llegar a los 3 intentos.
	//FE Y CE: Estas variables es la que almacenan la fila y la columna que quiere empezar el usuario. Estas variables cambian cuando va recorriendo la matriz. 
	//C Y F: Estas variables es el tamaño de la matriz. 
	//OC Y OF: Estas variables se encargan de almacenar las posiciones del origen cuando se mete a la matriz a recorrerla. Solo cambia cuando el usuario digita la posicion inicial.
	//AV: Esta variable la uso para avisarle a la maquina que llego al origen por segunda vez y si va a contar un punto desde el origen, lo contara. Le puse esto porque antes de
	//entrar a la matriz cuento el punto de origen y si cuenta un punto desde el origen por segunda vez no lo contara por que ese conteo esta afuera del ciclo.
	//CAB: Esta lista estara guardando las posiciones de cada visita de cada posicion de la matriz, es para evitar contar puntos ya acumulados.
	//CAB2: Esta lista estara guardando el recorrido desde el punto de origen hasta que no encuentre 1(unos), para revisar los demas lados. Uso esta lista para retroceder hasta llegar al punto de origen.
	int puntos=0, sum=0, cont=0, ints=0, ce=0, fe=0,c=0,f=0,i,j,of=0,oc=0,av=0;
	struct pso *cab, *cab2, *q, *p, *r;
	bool sw, sl;
	
	cout<<"[TAMAÑO DE LA MATRIZ]"<<endl; 

	do{
		cout<<"Digita la cantidad de filas: ";
		cin>>f;
		cout<<"Digita la cantidad de columnas: ";
		cin>>c;
	}while(f<1 || c<1);
	
	int M[f+2][c+2];
	
	for(i=0;i<(f+2);i++)
	{
		for(j=0;j<(c+2);j++)
		{
			do{
				cout<<"Posicion ["<<i<<"]["<<j<<"]: ";
				cin>>M[i][j];
			}while(M[i][j]<0 || M[i][j]>1);
			sum=M[i][j]+sum;
		}
	}
	
	cab=NULL;
	while(puntos<sum && ints<3)
	{
		cab2=NULL;
		sw=true;
		
		do{
			cout<<"\n[Ingrese la posicion que quiera empezar sin "<<endl;
			cout<<"pasarse del tamaño de la matriz] "<<endl;
			cout<<"Fila: ";
			cin>>fe;
			
			cout<<"Columna: ";
			cin>>ce;
		}while(fe>f || ce>c || fe<1 || ce<1);
		
		of=fe;
		oc=ce;
		
		if(cab != NULL)
		{
			ver_visita(cab,&sw,fe,ce);
		}
		
		if(M[fe][ce]==0)
		{
			cout<<"BOMBA!!, llevas "<<(ints=ints+1)<<" intentos";
		}else{
			if(sw==false)
			{
				cout<<"Esa posicion ya esta visitado"<<endl;
			}else{
				if(M[fe][ce]==1)
				{
					puntos=puntos+1;
					sl=true;
					if(puntos==sum){
							r= new pso;
								r->f=fe;
								r->c=ce;
								r->sig=NULL;
								p->sig=r;
								p=p->sig;
					}
					while(sl==true && puntos<sum)
					{
						sw=true;
						while(sw==true && cont<4) //DIRECCION ARRIBA 
						{
							cont=cont+1;
							if(cab != NULL){
								fe=fe-1;
								ver_visita(cab,&sw,fe,ce);
								fe=fe+1;
							}
							if(sw==true && M[fe-1][ce] == 1)
							{
								actualizar(&cab,&cab2,fe,ce,&p,&q,&puntos,&av);
								fe=fe-1;
								cont=cont+1;
							}else{
								sw=false;
							}
						}
						
						sw=true;
						
						while(sw==true && cont<4) //DIRECCION DERECHA
						{
							cont=cont+1;
							if(cab != NULL)
							{
								ce=ce+1;
								ver_visita(cab,&sw,fe,ce);
								ce=ce-1;
							}
							
							if(sw==true && M[fe][ce+1] == 1)
							{
								actualizar(&cab,&cab2,fe,ce,&p,&q,&puntos,&av);
								ce=ce+1;
								cont=0;
							}else{
								sw=false;
							}
						}
						
						sw=true;
						
						while(sw==true && cont<4 ) //DIRECCION ABAJO
						{
							cont=cont+1;
							if(cab != NULL)
							{
								fe=fe+1;
								ver_visita(cab,&sw,fe,ce);
								fe=fe-1;
							}
							
							if(sw==true && M[fe+1][ce] == 1)
							{
								actualizar(&cab,&cab2,fe,ce,&p,&q,&puntos,&av);
								fe=fe+1;
								cont=0;
							}else{
								sw=false;
							}
						}
						
						sw=true;
						
						while(sw==true && cont<4) //DIRECCION IZQUIERDA
						{
							cont=cont+1;
							if(cab != NULL)
							{
								ce=ce-1;
								ver_visita(cab,&sw,fe,ce);
								ce=ce+1;
							}
							
							if(sw==true && M[fe][ce-1] == 1)
							{
								actualizar(&cab,&cab2,fe,ce,&p,&q,&puntos,&av);
								ce=ce-1;
								cont=0;
							}else{
								sw=false;
							}
						}
						
						sw=true;
						
						if(cont>=4 && (fe != of || ce != oc))
						{
							ver_visita(cab,&sw,fe,ce);
							
							if(sw==true)
							{
								r= new pso;
								r->f=fe;
								r->c=ce;
								r->sig=NULL;
								p->sig=r;
								p=p->sig;
							}
							fe=q->f;
							ce=q->c;
							r=cab2;
							
							while(r->sig != q && r != q)
							{
								r=r->sig;
							}
							
							if(cab2->sig == NULL)
							{
								cab2=NULL;
							}else{
								r->sig=NULL;
							}
							free(q);
							
							if(cab2 != NULL)
							{
								q=r;
							}
							cont=0;
						}else{
							
							if(cont>=4 && fe==of && ce==oc)
							{
								ver_visita(cab,&sw,fe,ce);
							
							if(sw==true)
							{
								if(cab == NULL )
								{
								   cab = new pso;
								   cab->f=fe;
								   cab->c=ce;
								   p=cab;
								   p->sig=NULL;
								}else{
								  r= new pso;
								  r->f=fe;
								  r->c=ce;
								  r->sig=NULL;
								  p->sig=r;
								  p=p->sig;
								}
								
							}
								sl=false;
								cont=0;
								av=0;
								
							}
						}
					}
				}
			}
		}
		
	}
	
	system("cls");
	
	if(ints>=3)
	{
		cout<<"Se acababaron los intentos "<<endl;
		cout<<"Reunistes "<<puntos<<" puntos de "<<sum<<" puntos";
	}else{
		cout<<"Ganastes"<<endl;
		cout<<"Reunistes "<<puntos<<" puntos de "<<sum<<" puntos";
	}
	
	imprimir(cab);
	cout<<endl;
	imprimir(cab2);
	
	cout<<" "<<endl;
	
	for(i=0;i<(f+2);i++)
	{
		for(j=0;j<(c+2);j++)
		{
			cout<<M[i][j]<<" ";
		}
		cout<<endl;
	}
	
	system("pause");
}

//SUBPROGRAMAS
void ver_visita(pso *cab, bool *sw1, int fe1, int ce1)
{
	pso *p;
	p=cab;
	
	while(p != NULL && *sw1 != false)
	{
		if(fe1 == p->f && ce1 == p->c)
		{
			*sw1=false;
		}
		
		p=p->sig;
	}

}

void actualizar(pso **cab, pso **cab2, int fe1, int ce1, pso **p, pso **q, int *puntos1, int *av1)
{
	bool sw=true;
	pso *r;
	
	if(*cab == NULL)
	{
		*cab = new pso;
		(*cab)->f=fe1;
		(*cab)->c=ce1;
		*p=*cab;
		(*p)->sig=NULL;
	}else{
		ver_visita(*cab,&sw,fe1,ce1);
		if(sw == true){
	   		r= new pso;
			r->f=fe1;
			r->c=ce1;
			r->sig=NULL;
			(*p)->sig=r;
			*p=(*p)->sig;	
		}
		
	}
	
	if(*cab2 == NULL)
	{
		av1=av1+1;
		*cab2= new pso;
		(*cab2)->f=fe1;
		(*cab2)->c=ce1;
		*q=*cab2;
		(*q)->sig=NULL;
		if(*av1>1)
		{
			*puntos1=*puntos1+1;
		}
	}else{
	   		r= new pso;
			r->f=fe1;
			r->c=ce1;
			r->sig=NULL;
			(*q)->sig=r;
			*q=(*q)->sig;	
			*puntos1=*puntos1+1;
	}
	
	
}

void imprimir(pso *cab)
{
	pso *p;
	
	p=cab;
	cout<<" "<<endl;
	while(p != NULL)
	{
		cout<<p->f<<" "<<p->c<<" --> ";
		
		p=p->sig;
	}
	
	cout<<" NULL"<<endl;
}


