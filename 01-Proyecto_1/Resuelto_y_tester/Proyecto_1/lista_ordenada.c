#include <stdlib.h>
#include "lista_ordenada.h"
#include "constantes.h"

int (*comparador)(void *,void *);

TListaOrdenada crear_lista_ordenada(int (*f)(void *,void *)){
    comparador = f;
    TListaOrdenada ret = (TListaOrdenada) malloc(sizeof(struct lista_ordenada));
    ret->cantidad_elementos = 0;
    ret->lista = crear_lista();
    return ret;
}

int lo_insertar(TListaOrdenada lista, TElemento elem){
    //Check lista ordenada inicializada
    if (lista == NULL) exit(LST_NO_INI);

    int ret;

    //Si lista vacia, inserta primero
    if (lista->cantidad_elementos == 0){
        ret = l_insertar(lista->lista, POS_NULA, elem);
    }else{
        TPosicion actual = l_primera(lista->lista);
        while( actual != POS_NULA && comparador(elem, actual->elemento)>0 ){
            actual = l_siguiente(lista->lista, actual);
        }
        //Si no llegue al final de la lista, elem es menor o igual que
        //el elemento en pos actual, por lo que inserto antes de actual
        if (actual != POS_NULA){
            ret = l_insertar(lista->lista, actual, elem);
        }else{ //Debo insertar al final
            //Estrategia:
            // 1 --> Lista = < ..., Elem, Elem_aux>
            // 2 --> Elem_aux = Actual->elemento;
            // 3 --> Lista = < ..., Elem >
            // 4 --> Lista = < ..., Elem_aux, Elem >
            ret = l_insertar(lista->lista, l_ultima(lista->lista), elem); //1
            if (ret == TRUE){
                TElemento elem_aux = l_recuperar(lista->lista, l_ultima(lista->lista)); //2
                l_eliminar(lista->lista, l_ultima(lista->lista)); //3
                ret = l_insertar(lista->lista, l_ultima(lista->lista), elem_aux); //4
            }
        }
    }
    if (ret ==  TRUE) lista->cantidad_elementos = lista->cantidad_elementos + 1;
    return ret;
}

int lo_eliminar(TListaOrdenada lista, TPosicion pos){
    //Check lista ordenada inicializada
    if (lista == NULL) exit(LST_NO_INI);

    if (l_eliminar(lista->lista, pos) == TRUE){
        lista->cantidad_elementos = lista->cantidad_elementos - 1;
        return TRUE;
    }
    return FALSE;
}

int lo_size(TListaOrdenada lista){
    //Check lista ordenada inicializada
    if (lista == NULL) exit(LST_NO_INI);

    return lista->cantidad_elementos;
}

TPosicion lo_primera(TListaOrdenada lista){
    //Check lista ordenada inicializada
    if (lista == NULL) exit(LST_NO_INI);

    return l_primera(lista->lista);
}

TPosicion lo_ultima(TListaOrdenada lista){
    //Check lista ordenada inicializada
    if (lista == NULL) exit(LST_NO_INI);

    return l_ultima(lista->lista);
}

TPosicion lo_siguiente(TListaOrdenada lista, TPosicion pos){
    //Check lista ordenada inicializada
    if (lista == NULL) exit(LST_NO_INI);

    return l_siguiente(lista->lista, pos);
}
