#include <stdio.h>
#include <stdlib.h>

// Nodo del contenedor
struct Contenedor {
    int id;
    float tara;
    float carga;
    float peso_total;
    float costo;
    struct Contenedor *next;
    struct Contenedor *prev;
};

typedef struct Contenedor Contenedor;

// ID autogenerado
static int contador_id = 1;

// Limpia la entrada del teclado
void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

// Lee un float sin valores negativos
float leerFloatNoNegativo(const char *mensaje) {
    float valor;

    while (1) {
        printf("%s", mensaje);
        if (scanf("%f", &valor) != 1) {
            printf("Entrada invalida. Intente nuevamente.\n");
            limpiarBuffer();
            continue;
        }

        if (valor < 0) {
            printf("El valor no puede ser negativo.\n");
            limpiarBuffer();
            continue;
        }

        limpiarBuffer();
        return valor;
    }
}

// Lee un ID valido
int leerEnteroPositivo(const char *mensaje) {
    int valor;

    while (1) {
        printf("%s", mensaje);
        if (scanf("%d", &valor) != 1) {
            printf("Entrada invalida. Intente nuevamente.\n");
            limpiarBuffer();
            continue;
        }

        if (valor <= 0) {
            printf("El ID debe ser mayor que cero.\n");
            limpiarBuffer();
            continue;
        }

        limpiarBuffer();
        return valor;
    }
}

// Crea un contenedor nuevo
Contenedor *crearContenedor(float tara, float carga, float costo) {
    Contenedor *nuevo = (Contenedor *)malloc(sizeof(Contenedor));
    if (nuevo == NULL) {
        printf("Error: no se pudo reservar memoria.\n");
        exit(EXIT_FAILURE);
    }

    nuevo->id = contador_id++;
    nuevo->tara = tara;
    nuevo->carga = carga;
    nuevo->peso_total = tara + carga;
    nuevo->costo = costo;
    nuevo->next = NULL;
    nuevo->prev = NULL;

    return nuevo;
}

// Agrega al final de la lista
void insertarFinal(Contenedor **head, Contenedor **tail, Contenedor *nuevo) {
    if (*head == NULL) {
        *head = nuevo;
        *tail = nuevo;
        return;
    }

    nuevo->prev = *tail;
    (*tail)->next = nuevo;
    *tail = nuevo;
}

// Busca por ID
Contenedor *buscarPorId(Contenedor *head, int id) {
    while (head != NULL) {
        if (head->id == id) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// Muestra un contenedor
void mostrarContenedor(const Contenedor *cont) {
    printf("\n=== Contenedor ID %d ===\n", cont->id);
    printf("Tara: %.2f\n", cont->tara);
    printf("Carga: %.2f\n", cont->carga);
    printf("Peso total: %.2f\n", cont->peso_total);
    printf("Costo: %.2f\n", cont->costo);
}

// Muestra toda la lista
void mostrarLista(Contenedor *head) {
    if (head == NULL) {
        printf("No hay contenedores registrados.\n");
        return;
    }

    printf("\n=== LISTA DE CONTENEDORES ===\n");
    while (head != NULL) {
        mostrarContenedor(head);
        head = head->next;
    }
}

// Actualiza los datos de un contenedor
void actualizarContenedor(Contenedor *head) {
    int id;
    Contenedor *cont;
    float nueva_tara, nueva_carga, nuevo_costo;

    id = leerEnteroPositivo("Ingrese el ID del contenedor a actualizar: ");
    cont = buscarPorId(head, id);

    if (cont == NULL) {
        printf("No se encontro un contenedor con el ID %d.\n", id);
        return;
    }

    printf("Actualizando contenedor ID %d\n", cont->id);
    nueva_tara = leerFloatNoNegativo("Ingrese la nueva tara: ");
    nueva_carga = leerFloatNoNegativo("Ingrese la nueva carga: ");
    nuevo_costo = leerFloatNoNegativo("Ingrese el nuevo costo: ");

    cont->tara = nueva_tara;
    cont->carga = nueva_carga;
    cont->peso_total = nueva_tara + nueva_carga;
    cont->costo = nuevo_costo;

    printf("Contenedor actualizado correctamente.\n");
    mostrarContenedor(cont);
}

// Elimina un contenedor
int eliminarContenedor(Contenedor **head, Contenedor **tail, int id) {
    Contenedor *actual = *head;

    while (actual != NULL) {
        if (actual->id == id) {
            if (actual->prev != NULL) {
                actual->prev->next = actual->next;
            } else {
                *head = actual->next;
            }

            if (actual->next != NULL) {
                actual->next->prev = actual->prev;
            } else {
                *tail = actual->prev;
            }

            free(actual);
            printf("Contenedor con ID %d eliminado correctamente.\n", id);
            return 1;
        }
        actual = actual->next;
    }

    printf("No se encontro un contenedor con el ID %d.\n", id);
    return 0;
}

// Busca y muestra un contenedor
void buscarYMostrar(Contenedor *head) {
    int id;
    Contenedor *cont;

    id = leerEnteroPositivo("Ingrese el ID a buscar: ");
    cont = buscarPorId(head, id);

    if (cont == NULL) {
        printf("No existe un contenedor con el ID %d.\n", id);
        return;
    }

    mostrarContenedor(cont);
}

// Libera memoria
void liberarLista(Contenedor *head) {
    Contenedor *siguiente;

    while (head != NULL) {
        siguiente = head->next;
        free(head);
        head = siguiente;
    }
}

// Muestra el menu principal
int menu(void) {
    int opcion;

    printf("\n========================================\n");
    printf("SISTEMA DE GESTION DE CONTENEDORES\n");
    printf("========================================\n");
    printf("1. Insertar contenedor\n");
    printf("2. Buscar contenedor\n");
    printf("3. Actualizar contenedor\n");
    printf("4. Eliminar contenedor\n");
    printf("5. Mostrar todos\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");

    if (scanf("%d", &opcion) != 1) {
        limpiarBuffer();
        printf("Entrada invalida.\n");
        return -1;
    }

    limpiarBuffer();
    return opcion;
}

int main(void) {
    Contenedor *head = NULL;
    Contenedor *tail = NULL;
    int opcion;

    do {
        opcion = menu();

        switch (opcion) {
            case 1: {
                float tara, carga, costo;
                Contenedor *nuevo;

                tara = leerFloatNoNegativo("Ingrese el peso vacio (tara): ");
                carga = leerFloatNoNegativo("Ingrese el peso de carga: ");
                costo = leerFloatNoNegativo("Ingrese el costo asociado: ");

                nuevo = crearContenedor(tara, carga, costo);
                insertarFinal(&head, &tail, nuevo);

                printf("Contenedor registrado correctamente.\n");
                mostrarContenedor(nuevo);
                break;
            }
            case 2:
                buscarYMostrar(head);
                break;
            case 3:
                actualizarContenedor(head);
                break;
            case 4: {
                int id;
                id = leerEnteroPositivo("Ingrese el ID del contenedor a eliminar: ");
                eliminarContenedor(&head, &tail, id);
                break;
            }
            case 5:
                mostrarLista(head);
                break;
            case 0:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion no valida.\n");
                break;
        }
    } while (opcion != 0);

    liberarLista(head);
    return 0;
}
