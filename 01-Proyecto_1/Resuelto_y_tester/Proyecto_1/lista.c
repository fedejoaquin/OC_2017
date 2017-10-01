#include <stdlib.h>
#include "lista.h"
#include "constantes.h"

TLista crear_lista(){
    TLista ret = (TLista) malloc(sizeof(struct lista));
    ret->cantidad_elementos = 0;
    ret->primer_celda = NULL;
    return ret;
}

int l_insertar(TLista lista, TPosicion pos, TElemento elem){
    //Check lista inicializada
    if (lista == NULL) exit(LST_NO_INI);

    //Reserva nueva celda y check de alocación OK
    TCelda nueva = (TCelda) malloc(sizeof(struct celda));
    if (nueva == NULL) return FALSE;

    nueva->elemento = elem;

    //Insertar primero.
    //Insertar antes de primero.
    if (pos == POS_NULA || lista->primer_celda == pos){
        TCelda proxima = lista->primer_celda;
        nueva->proxima_celda = proxima;
        lista->primer_celda = nueva;
    }else{ //Insertar antes de Pos
        TCelda actual = lista->primer_celda;
        TCelda anterior = NULL;
        while(actual != pos ){ //Se asume pos dentro de lista
            anterior = actual;
            actual = actual->proxima_celda;
        }
        nueva->proxima_celda = actual;
        anterior->proxima_celda = nueva;
    }

    //Incrementa cantidad de elementos
    lista->cantidad_elementos = lista->cantidad_elementos + 1;

    return TRUE;
}

int l_eliminar(TLista lista, TPosicion pos){
    //Check lista inicializada
    if (lista == NULL) exit(LST_NO_INI);

    //Check posicion valida
    if(pos == POS_NULA) return LST_POS_INV;

    //Primer posicion
    if(pos == lista->primer_celda){
        lista->primer_celda = pos->proxima_celda;
    }else{
        TCelda actual = lista->primer_celda;
        TCelda anterior = NULL;
        while(actual != pos ){ //Se asume pos dentro de lista
            anterior = actual;
            actual = actual->proxima_celda;
        }
        anterior->proxima_celda = actual->proxima_celda;
    }
    lista->cantidad_elementos = lista->cantidad_elementos - 1;
    free(pos);
    return TRUE;
}

TPosicion l_primera(TLista lista){
    //Check lista inicializada
    if (lista == NULL) exit(LST_NO_INI);
    if (lista->cantidad_elementos == 0) return POS_NULA;
    return lista->primer_celda;
}

TPosicion l_ultima(TLista lista){
    //Check lista inicializada
    if (lista == NULL) exit(LST_NO_INI);

    if (lista->cantidad_elementos == 0) return POS_NULA;

    //Avanza hasta última celda
    TCelda actual = lista->primer_celda;
    while(actual->proxima_celda != NULL )
        actual = actual->proxima_celda;

    return actual;
}

TPosicion l_anterior(TLista lista, TPosicion pos){
    //Check lista inicializada
    if (lista == NULL) exit(LST_NO_INI);

    //Check posicion valida
    if(pos == POS_NULA) return POS_NULA;

    //En caso de pos == primera, retorno = POS_NULL
    TCelda anterior = POS_NULA;
    TCelda actual = lista->primer_celda;

    //Busca la posicion pos en la lista, manteniendo la anterior
    while(actual != pos){ //Se asume pos valida
        anterior = actual;
        actual = actual->proxima_celda;
    }

    return anterior;
}

TPosicion l_siguiente(TLista lista, TPosicion pos){
    //Check lista inicializada
    if (lista == NULL) exit(LST_NO_INI);

    //Check posicion valida
    if(pos == POS_NULA) return POS_NULA;

    TPosicion ret = pos->proxima_celda == NULL ? POS_NULA : pos->proxima_celda;
    return ret;
}

TElemento l_recuperar(TLista lista, TPosicion pos){
    //Check lista inicializada
    if (lista == NULL) exit(LST_NO_INI);

    //Check posicion valida
    if(pos == POS_NULA) return ELE_NULO;

    return pos->elemento;
}

int l_size(TLista lista){
    //Check lista inicializada
    if (lista == NULL) exit(LST_NO_INI);

    return lista->cantidad_elementos;
}
