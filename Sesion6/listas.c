#include <stdio.h>
#include <malloc.h>

typedef struct alumno 
{ 
    int edad;
    char nombre[20]; 
    struct alumno *sig; 
} alumno;

alumno *aux, *cab = NULL; //Inicia vacio

int insertarNodo(){
    alumno *nuevo = (alumno*) malloc(sizeof(alumno));
    printf ("Cual es su edad: ");
    scanf ("%d", &nuevo->edad);
    if (nuevo->edad >= 20){
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Cual es su nombre: ");
        scanf("%s", &nuevo->nombre);
        nuevo->sig = NULL;    
        if(cab==NULL){        
            cab = nuevo;        
        } else{
            aux = cab;
            while(aux->sig!=NULL){
                aux = aux->sig;
            }
            aux->sig = nuevo;        
        }
        aux = nuevo = NULL;
    }else{
        printf("Pailas no puedes ingresar\n");
    }

    
    
    
}
int mostrarNodo(){
    aux = cab;
        while(aux!=NULL){
            printf("%s \n", aux->nombre);
            aux = aux->sig;
        }        
}

int main(){
    int opcion;

    do{
        printf("Menu\n1. Registrar\n2. Mostrar\n5. Salir\nDigite su opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
            case 1: insertarNodo();break;
            case 2: mostrarNodo(); break;        
        }
    }while(opcion!=5);

}
