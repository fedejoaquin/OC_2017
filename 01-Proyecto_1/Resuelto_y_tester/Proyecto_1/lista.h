#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef void * TElemento;

typedef struct celda {
    TElemento elemento;
    struct celda * proxima_celda;
} * TCelda;

typedef struct lista {
    unsigned int cantidad_elementos;
    TCelda primer_celda;
} * TLista;

typedef struct celda * TPosicion;

TLista crear_lista();
int l_insertar(TLista lista, TPosicion pos, TElemento elem);
int l_eliminar(TLista lista, TPosicion pos);
TPosicion l_primera(TLista lista);
TPosicion l_ultima(TLista lista);
TPosicion l_anterior(TLista lista, TPosicion pos);
TPosicion l_siguiente(TLista lista, TPosicion pos);
TElemento l_recuperar(TLista lista, TPosicion pos);
int l_size(TLista lista);

#endif // LISTA_H_INCLUDED
