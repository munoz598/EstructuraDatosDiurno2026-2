#include <stdio.h>
#include <malloc.h>

typedef struct puntoControl
{ 
    int id; 
    float peso;
    struct puntoControl *sig; 
} puntoControl;

puntoControl *cab=NULL, *aux, *aux2;


int ingresarPeso(float p);
int recorrerRegistros();
int actualizar();
int eliminar();
int autollenado();
int main(){
    int opcion;
    float vPeso;
    autollenado();

    do{
        printf("Control Peso\n1. Registrar\n2. Mostrar\n3. Actualizar\n4. Eliminar\n5. Salir\nDigite su opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
            case 1: 
                printf ("Cual el peso (Kg): ");
                scanf("%f", &vPeso);
                ingresarPeso(vPeso);
            break;
            case 2: recorrerRegistros(); break;        
            case 3: actualizar(); break;
            case 4: eliminar(); break;
        }
    }while(opcion!=5);
}


int ingresarPeso(float p){
    puntoControl *nuevo = (puntoControl*) malloc(sizeof(puntoControl));
    nuevo->peso = p;
    nuevo->sig = NULL;    
    if(cab==NULL){        
        cab = nuevo;  
        cab->id = 1;      
    } else{
        aux = cab;
        while(aux->sig!=NULL){
            aux = aux->sig;
        }
        nuevo->id = aux->id+1;
        aux->sig = nuevo;        
    }
    aux = nuevo = NULL;
}
int recorrerRegistros(){
    aux = cab;
        while(aux!=NULL){
            printf("#%d - ", aux->id );
            printf("%.1f \n", aux->peso);
            aux = aux->sig;
        }        
}
int autollenado(){
    float valores[] = {10, 9, 6, 3, 6, 23, 16, 18, 2};
    for(int i = 0; i<9; i++){
        ingresarPeso(valores[i]);
    }
}
int actualizar(){
    int posicion;
    recorrerRegistros();
    printf("Que registro va a cambiar: ");
    scanf("%d", &posicion);
    aux = cab;
    while(aux!=NULL && aux->id!=posicion){       
        aux = aux->sig;
    }     
    if(aux==NULL){
        printf("El registro no existe");
    } else {
        printf ("Cual el peso (Kg): ");
        scanf("%f", &aux->peso);
    }
       

}
int eliminar(){
    int posicion;
    recorrerRegistros();
    printf("Que registro va a ELIMINAR: ");
    scanf("%d", &posicion);
    aux = cab;
    while(aux!=NULL && aux->id!=posicion){       
        aux = aux->sig;
    }     
    if(aux==NULL){
        printf("El registro no existe");
    } else {
        
        if(aux==cab){
            cab = cab->sig;
            free(aux);
        } else {
            
            aux2 = cab;
            while(aux2->sig!=aux){       
                    aux2 = aux2->sig;            
                }     
            aux2->sig = aux->sig;
            free(aux);
        }
    }
       

}