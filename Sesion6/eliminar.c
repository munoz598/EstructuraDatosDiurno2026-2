#include <stdio.h>
#include <malloc.h>

typedef struct puntoControl
{ 
    float peso;
    struct puntoControl *sig; 
} puntoControl;

puntoControl *cab, *aux;
*cab = NULL;

int ingresarPeso();
int recorrerRegistros();
int main(){
    int opcion;

    do{
        printf("Control Peso\n1. Registrar\n2. Mostrar\n5. Salir\nDigite su opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
            case 1: ingresarPeso();break;
            case 2: recorrerRegistros(); break;        
        }
    }while(opcion!=5);
}