#include <stdio.h>
#include <malloc.h>
int semilla = 1;

typedef struct nodo {
 int color; //1. Rojo 2. Amarillo 3. Verde 4. Azul
 struct nodo *sig;
} nodo;

nodo *top, *nuevo, *aux, *top2;

void push() { 
    nuevo = (nodo*) malloc(sizeof(nodo)); 
    do {
        printf("Elige el color 1-Rojo 2-Amarillo 3-Verde 4-Azul:  ");
        scanf("%d", &nuevo->color); 
    } while(nuevo->color<1 || nuevo->color>4);
    nuevo->sig = top; 
    top = nuevo;
    nuevo = NULL;
    free(nuevo);
}

void pop() { 
    if (top != NULL){
        aux = top; 
        top = top->sig;              
        free(aux); 
    }
}

void peek(){
    if (top != NULL){
        printf("El elemento TOP es: %d\n", top->color);
    }   else {
        printf("Pila Vacia\n");
    }
}

void main (){
    int opcion;
    do {
        printf("1. Push\n2. Pop\n3. Peek\n4. Salir\n");
        scanf("%d", &opcion);
        switch(opcion){
            case 1: push(); break;
            case 2: pop(); break;
            case 3: peek(); break;
        }
    } while(opcion!=4);
}