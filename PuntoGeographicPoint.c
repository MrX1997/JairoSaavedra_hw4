#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


double _randomnumero(void);
void cargar_datos(double **Matriz);
void coord(double **Matriz, double *x,double *y);
double **Matriz(void);
double radio( double x,double y);
void freePointer(double **matrix);

int nx=744;
int ny=500;
int deltarandom=2;
int Niteraciones=1000;
double *x_datos;
double *y_datos;
int N=120877;
double x_maximo,y_maximo,r_maximo;

int main(void)
{   
 // cantidad de puntos continentales 
	 int i;
    int j;

    double x_mod,y_mod,r_mod,x_nuevo,y_nuevo,r_nuevo,alpha;
    double x_maximo,y_maximo,r_maximo;
    double **matriz=Matriz();
    

    x_datos = malloc(N*sizeof(double));
    y_datos = malloc(N*sizeof(double));
    

    
    cargar_datos(matriz);
    coord(matriz,x_datos,y_datos);
    
    

    x_mod=(2*_randomnumero()*N/744);
    y_mod=(2*_randomnumero()*N/500);
    r_mod=radio(x_mod,y_mod);
    
    FILE *punto = fopen("datos.txt", "w");
    
    for(i=0; i<Niteraciones; i++)
	{
    
        x_nuevo = x_mod + (2*_randomnumero() - 1)*deltarandom;
        y_nuevo = y_mod + (2*_randomnumero() - 1)*deltarandom;

		if(x_nuevo<0 )
    	{	
    			x_nuevo=744-x_nuevo;
    	}
		if(y_nuevo<0 )
    	{	
    			y_nuevo=500-y_nuevo;
    	}
		if(x_nuevo>744 )
    	{	
    			x_nuevo=744-x_nuevo;
    	}
		if(y_nuevo>500 )
    	{	
    			y_nuevo=500-y_nuevo;
    	}
        
        r_nuevo = radio(x_nuevo, y_nuevo);
        alpha = exp((r_nuevo - r_mod));

        if(r_nuevo>r_maximo)
        {
            x_maximo=x_nuevo;
            y_maximo=y_nuevo;
            r_maximo=r_nuevo;
        }
        	
            if(alpha > 1)
    			{
    				alpha = 1;
    			}
        	 if(alpha > _randomnumero())
    			{
    				x_mod = x_nuevo;
    				y_mod = y_nuevo;
    				r_mod = r_nuevo;
    			}
        
    }
    fprintf(punto,"%f %f %f\n",x_mod,y_mod,r_mod);
    fclose(punto);
    
    x_maximo=-x_maximo*2*180/nx;
    y_maximo=y_maximo*2*90/ny-90;
    r_maximo=r_maximo*20000/744;


	printf("Las coordenadas del punto %f %f\n",y_maximo,x_maximo);
	freePointer(matriz);
    return 0;
}

double radio(double x,double y)
{
    int i;
    double min, eval;
    min=pow(pow(x_datos[0]-x,2.0)+pow(y_datos[0]-y,2.0),0.5);
    for(i=0;i<N;i++)
    {
        eval=pow(pow(x_datos[i]-x,2.0)+pow(y_datos[i]-y,2.0),0.5);
        if(eval<min)
        {
                min=eval;
        }
    }
    return min;
}
        
void coord(double **Matriz, double *x,double *y)
{
    int k=0;
    int i;
    int j;
    
    for(i=0;i<ny;i++)
    {
        for(j=0;j<nx;j++)
        {
                
                if(Matriz[i][j]==1)
                {
                        
                x[k]=(double) j;
                y[k]=(double) i;
                k=k+1;
                }
                
        }
    }
}


double _randomnumero(void)
{
    return (double) rand()/RAND_MAX;
}



// Carga los datos 
void cargar_datos(double **Matriz)
{
 
	char *delimiter=" ";

    FILE *arch=fopen("map_data.txt","r");

	char data[2000];
	char * pch;

	int j=0;
	while(fscanf(arch, "%s",data)==1)
	{
		

			pch = strtok(data," ");
        Matriz[j/744][j%744]=atof(pch);

		j++;

	}


	fclose(arch);

}
    

double **Matriz(void)
{
    int i;
    double **matriz;
    matriz = malloc(ny*sizeof(double *));

    for(i = 0; i < ny; i++)
    {
        matriz[i] = malloc(nx*sizeof(double));
    }

    return matriz;
}	  

void freePointer(double **matriz)
{
    int i;
    for(i = 0; i<ny; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}















/*    
// otro metodo de cargar datos 
double retornamatriz(int filas, int columnas)
{
    FILE *file;
    file=fopen("map_data.txt", "r");
    int len=1000;
    char lineas[len];
    char *separar=NULL;
    const char *delim;
    delim=" ";
    
    double val;
    int i=0;
    int j=0;
    double matriz[500][744];

 

// LEE EL ARCHIVO Y LO GUARDA EN LA MATRIZ
  while(fgets(lineas,len,file) )
{
  //printf("%s\n",lineas );
  j=0;
  separar=strtok(lineas,delim);
    while(separar !=NULL)
    {
      if(j !=0)
      {
      
      //printf("el trozo es :%s\n", separar );
        val= atof(separar);
      //printf("en doble es: %e\n", val);
        matriz[i][j-1]=val;
      //printf("%e\t", val );
      }
      
      separar=strtok(NULL, delim);
      
      if (j>=0 && j<=744)
      {
        j=j+1;
      }
      
    }
    //printf("\n");
    if(i>=0 && i<=500)
    {
      i=i+1;
    }
}
}
*/
	
  

