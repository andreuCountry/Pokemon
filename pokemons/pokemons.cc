#include <stdio.h>
#include <stdlib.h>
#include <structs.h>

Pokemon* CrearLista() {
    Pokemon* lista = nullptr;

    return lista;
}

void InsertarPokemon(Pokemon** lista, int valor) {
    Pokemon* newLista = (Pokemon*) malloc(1*sizeof(Pokemon));
    newLista->info = valor;
    newLista->prox = *lista;
    newLista->ante = nullptr;

    if ((*lista) != nullptr) {
        (*lista)->ante = newLista;
    }

    *lista = newLista;
}

void MostrarLista(Pokemon* lista2) {

    Pokemon* p;

    for(p = lista2; p != nullptr; p = p->prox) {
        printf(" %d", p->info);
    }
}

Pokemon* BuscarEnLista(Pokemon* lista2, int valor) {
    Pokemon* p = lista2;
    Pokemon* aux = nullptr;

    for(int i = 0; p != nullptr; p = p->prox) {

        if (p->info == valor) {
            aux = p;
        }

        i++;
    }

    if (aux != nullptr) {
        return aux;
    } else {
        return p;
    }
}

void InvertidoMostrarLista(Pokemon* lista2) {
    Pokemon* aux = nullptr;

    for (aux = lista2; aux->prox != nullptr; aux = aux->prox);

    for (int j = 0; aux != nullptr; aux = aux->ante) {
        printf(" %d", aux->info);
    }

}

Pokemon* ExtraerLista(Pokemon** lista2) {
    Pokemon* p = *lista2;
    Pokemon* aux = nullptr;
    Pokemon* aux2 = nullptr;

    aux = p->prox;
    aux2 = p->ante;
    
    if (aux != nullptr) {
        aux->ante = aux2;
    }

    if (aux2 != nullptr) {
        aux2->prox = aux;
    }

    p->prox = nullptr;
    p->ante = nullptr;

    // si la lista sigue apuntando a uno que vas a liberar se rompe
    *lista2 = aux;

    return p;
}

int LongitudLista(Pokemon* lista2) {
    
    Pokemon* p = lista2;
    int contador = 0;

    for (int i = 0; p != nullptr; p = p->prox) {
        contador++;
    }

    return contador;
}

void EliminarElemento(Pokemon** lista2, int value) {
    
    Pokemon* p = *lista2;
    Pokemon* aux = nullptr;
    Pokemon* aux2 = nullptr;
    Pokemon* to_delete = nullptr;

    for (int i = 0; p != nullptr; p = p->prox) {
        if (value == p->info) {
            if (p->prox != nullptr) {
                aux = p->prox;
                aux->ante = p->ante;
                aux->prox = p->prox->prox;
            }

            if (p->ante != nullptr) {
                aux2 = p->ante;
                aux2->prox = p->prox;
            }

            p->prox = nullptr;
            p->ante = nullptr;
            to_delete = p;

        }
    }

    if (to_delete != nullptr) {
        free(to_delete);
    } else {
        printf(">>> No encontrado en lista. \n");
    }

}
