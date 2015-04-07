

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> 

#define TRUE 1
#define FALSE 0
#define NUM_PUNTOS 3
#define NUM_COMANDOS 4

enum {IZQUIERDO, DERECHO};


typedef struct _nodo {
   int dato;
   int FE;
   struct _nodo *derecho;
   struct _nodo *izquierdo;
   struct _nodo *padre;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Arbol;

typedef struct _nodolista {
   int valor;
   struct _nodolista *siguiente;
   struct _nodolista *anterior;
} tipoNodolista;
typedef tipoNodolista *pNodol;
typedef tipoNodolista *Lista;
/*metodos del arbol vl*/
void Insertar(Arbol *a, int dat);
int Vacio(Arbol r);
int EsHoja(pNodo r);
int NumeroNodos(Arbol a, int* c);
int AlturaArbol(Arbol a, int* altura);
int Altura(Arbol a, int dat);
void InOrden(Arbol, void (*func)(int*));
void Equilibrar(Arbol *raiz, pNodo nodo, int, int);
void RSI(Arbol *raiz, pNodo nodo);
void RSD(Arbol *raiz, pNodo nodo);
void RDI(Arbol *raiz, pNodo nodo);
void RDD(Arbol *raiz, pNodo nodo);
void auxContador(Arbol a, int*);
void auxAltura(Arbol a, int, int*);
void Mostrar(int *d);
void leer1(Arbol *A);
void enOrden(Arbol);
/*metodos de la lista*/
void Insertarlista(Lista *l, int v);
void MostrarLista(Lista l);
void OrdenarBurbuja(Lista *l);
void ingresoVector(Lista l, int t);
void OrdenarSort(int v [], int d);
void MostrarVector(int v2 [], int largo);
void grafica();
int tamano;
double valoresX[NUM_PUNTOS];
double valoresY[NUM_PUNTOS];
int main(int argc, char *argv[])
{
   Arbol ArbolInt=NULL;
   Lista lista = NULL;
   clock_t start = clock();  
   leer1(&ArbolInt); 
   double i= (double)clock() -start/CLOCKS_PER_SEC;
   printf(" insercion arbol %f", i);
   valoresY[0]=i;
   printf("\n");
   clock_t start2 = clock();  
   printf("Mostrar el recorido en Orden: \n");
   //InOrden(ArbolInt, Mostrar);
   enOrden(ArbolInt);
   double i2= (double)clock() -start2/CLOCKS_PER_SEC;
   valoresX[0]=i2;
   printf("\n");
   printf(" Tiempo del recorido del arbol %f", i2); 
   
   printf("\n");
   printf("---------------\n");
   clock_t start3 = clock();  
   leer2(&lista);
   double i3= (double)clock() -start3/CLOCKS_PER_SEC;
   printf(" Tiempo de insercion en lista %f",  i3);
   valoresY[1]=i3;
   valoresY[2]=i3;
   printf("\n");
   clock_t start4 = clock();  
   ingresoVector(lista,tamano); 
   double i4= (double)clock() -start4/CLOCKS_PER_SEC;
   printf(" Tiempo de  Ordenamiento quicksort %f", i4); 
   valoresX[1]=i4;
   printf("\n");
   clock_t start5 = clock();  
   OrdenarBurbuja(&lista);
   double i5= (double)clock() -start5/CLOCKS_PER_SEC;
   printf(" Tiempo de  Ordenamiento Burbuja %f", i5); 
   valoresX[2]=i5;
   printf("\n");
   MostrarLista(lista);
   printf("\n");
   grafica();
   return 0;
}
void leer1(Arbol *A){
     
         FILE *archivo;
	  char caracteres[100];
          int val;
          archivo = fopen("prueba.txt","r");
       	if (archivo == NULL){

		printf("\nError de apertura del archivo. \n\n");
                
        }else{


	    
            
	    while (feof(archivo) == 0)
	    {
		
                fgets(caracteres,100,archivo);
 		
                val = atoi(caracteres);
                
                if (val != 0){
                Insertar(A,val); 
                }
                
	    }
        }
        fclose(archivo);
         
}
void leer2 (Lista *l){
    FILE *archivo;
	  char caracteres[100];
          int val;
          archivo = fopen("prueba.txt","r");
       	if (archivo == NULL){

		printf("\nError de apertura del archivo. \n\n");
                
        }else{


	   
            
	    while (feof(archivo) == 0)
	    {
		
                fgets(caracteres,100,archivo);
 		
                val = atoi(caracteres);
                
                if (val != 0){
                Insertarlista(l,val); 
                }
                
	    }
        }
        fclose(archivo);

}
void Insertar(Arbol *a, int dat)
{
   pNodo padre = NULL;
   pNodo actual = *a;

   
   while(!Vacio(actual) && dat != actual->dato) {
      padre = actual;
      if(dat < actual->dato) actual = actual->izquierdo;
      else if(dat > actual->dato) actual = actual->derecho;
   }

   
   if(!Vacio(actual)) return;
   
   if(Vacio(padre)) {
      *a = (Arbol)malloc(sizeof(tipoNodo));
      (*a)->dato = dat;
      (*a)->izquierdo = (*a)->derecho = NULL;
      (*a)->padre = NULL;
      (*a)->FE = 0;
   }
   
   else if(dat < padre->dato) {
      actual = (Arbol)malloc(sizeof(tipoNodo));
      padre->izquierdo = actual;
      actual->dato = dat;
      actual->izquierdo = actual->derecho = NULL;
      actual->padre = padre;
      actual->FE = 0;
      Equilibrar(a, padre, IZQUIERDO, TRUE);
   }
  
   else if(dat > padre->dato) {
      actual = (Arbol)malloc(sizeof(tipoNodo));
      padre->derecho = actual;
      actual->dato = dat;
      actual->izquierdo = actual->derecho = NULL;
      actual->padre = padre;
      actual->FE = 0;
      Equilibrar(a, padre, DERECHO, TRUE);
  }
}
void Equilibrar(Arbol *a, pNodo nodo, int rama, int nuevo)
{
   int salir = FALSE;

   
   while(nodo && !salir) {
      if(nuevo)
         if(rama == IZQUIERDO) nodo->FE--; 
         else                  nodo->FE++;
      else
         if(rama == IZQUIERDO) nodo->FE++; 
         else                  nodo->FE--;
      if(nodo->FE == 0) salir = TRUE; 
      else if(nodo->FE == -2) { 
         if(nodo->izquierdo->FE == 1) RDD(a, nodo); 
         else RSD(a, nodo);                         
         salir = TRUE;
      }
      else if(nodo->FE == 2) {  
         if(nodo->derecho->FE == -1) RDI(a, nodo); 
         else RSI(a, nodo);                        
         salir = TRUE;
      }
      if(nodo->padre)
         if(nodo->padre->derecho == nodo) rama = DERECHO; else rama = IZQUIERDO;
      nodo = nodo->padre; 
   }
}
void RDD(Arbol *raiz, Arbol nodo)
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->izquierdo;
   pNodo R = Q->derecho;
   pNodo B = R->izquierdo;
   pNodo C = R->derecho;

   if(Padre)
     if(Padre->derecho == nodo) Padre->derecho = R;
     else Padre->izquierdo = R;
   else *raiz = R;

   
   Q->derecho = B;
   P->izquierdo = C;
   R->izquierdo = Q;
   R->derecho = P;

  
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = Q;
   if(C) C->padre = P;

   
   switch(R->FE) {
      case -1: Q->FE = 0; P->FE = 1; break;
      case 0:  Q->FE = 0; P->FE = 0; break;
      case 1:  Q->FE = -1; P->FE = 0; break;
   }
   R->FE = 0;
}
void RDI(Arbol *a, pNodo nodo)
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->derecho;
   pNodo R = Q->izquierdo;
   pNodo B = R->izquierdo;
   pNodo C = R->derecho;

   if(Padre)
     if(Padre->derecho == nodo) Padre->derecho = R;
     else Padre->izquierdo = R;
   else *a = R;

   
   P->derecho = B;
   Q->izquierdo = C;
   R->izquierdo = P;
   R->derecho = Q;

   
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = P;
   if(C) C->padre = Q;

   
   switch(R->FE) {
      case -1: P->FE = 0; Q->FE = 1; break;
      case 0:  P->FE = 0; Q->FE = 0; break;
      case 1:  P->FE = -1; Q->FE = 0; break;
   }
   R->FE = 0;
}
void RSD(Arbol *a, pNodo nodo)
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->izquierdo;
   pNodo B = Q->derecho;

   if(Padre)
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else *a = Q;

   
   P->izquierdo = B;
   Q->derecho = P;

   
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;

   
   P->FE = 0;
   Q->FE = 0;
}
void RSI(Arbol *a, pNodo nodo)
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->derecho;
   pNodo B = Q->izquierdo;

   if(Padre)
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else *a = Q;

   
   P->derecho = B;
   Q->izquierdo = P;

   
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;

   
   P->FE = 0;
   Q->FE = 0;
}
void InOrden(Arbol a, void (*func)(int*))
{
   if(a->izquierdo) InOrden(a->izquierdo, func);
   func(&(a->dato));
   if(a->derecho) InOrden(a->derecho, func);
}
int Altura(Arbol a, int dat)
{
   int altura = 0;
   pNodo actual = a;

   
   while(!Vacio(actual)) {
      if(dat == actual->dato) return altura; 
      else {
         altura++; 
         if(dat < actual->dato) actual = actual->izquierdo;
         else if(dat > actual->dato) actual = actual->derecho;
      }
   }
   return -1; 
}
int NumeroNodos(Arbol a, int *contador)
{
   *contador = 0;

   auxContador(a, contador); 
   return *contador;
}
void auxContador(Arbol nodo, int *c)
{
   (*c)++; 
 
   if(nodo->izquierdo) auxContador(nodo->izquierdo, c);
   if(nodo->derecho)   auxContador(nodo->derecho, c);
}
int AlturaArbol(Arbol a, int *altura)
{
   *altura = 0;

   auxAltura(a, 0, altura); 
   return *altura;
}
void auxAltura(pNodo nodo, int a, int *altura)
{
   
   if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1, altura);
   if(nodo->derecho)   auxAltura(nodo->derecho, a+1, altura);
   
   if(EsHoja(nodo) && a > *altura) *altura = a;
}
int Vacio(Arbol r)
{
   return r==NULL;
}
int EsHoja(pNodo r)
{
   return !r->derecho && !r->izquierdo;
}
void Mostrar(int *d)
{
   printf("%d, ", *d);
}
void enOrden(Arbol a)
{
   if(a->izquierdo) enOrden(a->izquierdo);
   printf("%d ",a->dato);
   if(a->derecho) enOrden(a->derecho);
}
void Insertarlista(Lista *lista, int v)
{
   pNodol nuevo, actual;

  
   nuevo = (pNodol)malloc(sizeof(tipoNodolista));
   nuevo->valor = v;
   
   
   actual = *lista;
   if(actual) while(actual->anterior) actual = actual->anterior;
   
   if(!actual || actual->valor ) {
      
      nuevo->siguiente = actual; 
      nuevo->anterior = NULL;
      if(actual) actual->anterior = nuevo;
      if(!*lista) *lista = nuevo;
   }
   
   
   tamano=tamano+1;
}
void MostrarLista(Lista lista)
{
   pNodol nodo = lista;

   if(!lista) {printf("Lista vacía");}

   nodo = lista;
   
      while(nodo->anterior) nodo = nodo->anterior;
      printf("El orden Por Burbuja es: \n ");
      while(nodo) {
         printf("%d ,", nodo->valor);
         nodo = nodo->siguiente;
      }
   
}
void OrdenarBurbuja(Lista *lista){
    pNodol nodo=*lista;
    pNodol nodo2;
    int aux;
    
    while (nodo->anterior) {nodo=nodo->anterior;}
    while (nodo != NULL){
        aux=nodo->valor;
        nodo2=nodo->siguiente;
        while (nodo2 != NULL){
            if(nodo->valor > nodo2->valor){
                int temp;
                temp=nodo->valor;
                nodo->valor=nodo2->valor;
                nodo2->valor=temp;
            
            }
            nodo2=nodo2->siguiente;
            
        }
        nodo=nodo->siguiente;
      
    }
    
   
}
void ingresoVector(Lista lista , int t){
    int vector [t];
    int k=0;
    int c =t;
    pNodol nodo =lista;
    while (nodo->anterior) {nodo=nodo->anterior;}
    while (nodo){
        vector[k]=nodo->valor;
        k++;
        nodo=nodo->siguiente;
    }
    
    OrdenarSort(vector,c);
    //MostrarVector(vector,c);
    
}
void MostrarVector(int v[], int d){

    printf("El orden por quicksort \n");
    int i;
    for (i=0; i < d; i++) {
	printf("%d,", v[i]);  
    }
    printf("\n");	

}
void  OrdenarSort(int v2[], int d){
    int insercion;
    int siguiente;
    
    
    for (siguiente=1; siguiente < d; siguiente++) {
        insercion=v2[siguiente];
        
        int moverElemento =siguiente;
        while (moverElemento >0 && v2[moverElemento-1]> insercion){
            v2[moverElemento]= v2[moverElemento-1];
            moverElemento--;
        }
        v2[moverElemento] =insercion;
    }
    MostrarVector(v2,d);

}
void grafica (){
// X, Y valores de los puntos a graficar
    //double valoresX[NUM_PUNTOS] = {0.0, 1.0, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0};
    //double valoresY[NUM_PUNTOS] = {1,2,3,4,5,6,7,8,9,10,11};
    register int i=0;
    /* se crea y se abre el archivo puntosGraficar.txt en modo escritura 
     * para almacenar los valores de x y y que están declarados en los arreglos
     * valoresX y valoresY*/
    FILE * archivoPuntos = fopen("puntosGraficar.txt", "w");

    /*Guardar los puntos x,y en el archivo de texto creado y abierto previamente*/
    for (i=0;i<NUM_PUNTOS;i++){
       fprintf(archivoPuntos, "%lf %lf \n", valoresX[i], valoresY[i]);
 }
 
    /*lista de comandos para ejecutar y configurar la visualización que tendrán
     * los puntos en la gráfica con gnuplot*/
    char * configGnuplot[] = {"set title \" Grafica   \"", 
                                "set ylabel \"----Y--->\"",
                                "set xlabel \"---- X--->\"",
                                "plot \"puntosGraficar.txt\" using 1:2 with lines"
                               };

    /*Se crea una archivo de tipo poen, es una tebería IPC que se usa, para
     * ejecutar gnuplot y enviarle el archivo a graficar*/
    FILE * ventanaGnuplot = popen ("gnuplot -persist", "w");
    // Executing gnuplot commands one by one
    for (i=0;i<NUM_COMANDOS;i++){
     fprintf(ventanaGnuplot, "%s \n", configGnuplot[i]);
 }
 fclose(archivoPuntos);


}
