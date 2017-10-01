#include <stdlib.h>
#include <stdio.h>

#include "lista.h"
#include "lista_ordenada.h"
#include "trie.h"
#include "constantes.h"

//Comparador de enteros
int mi_comparador(void * val1, void * val2){
    int a = *((int *)val1);
    int b = *((int *)val2);
    if (a<b) return -1;
    else if (a==b) return 0;
    else return 1;
}

//Muestra contenido de una lista de chars en un reglon
void mostrar_lista(TLista lista){
    TPosicion pos = l_primera(lista);
    while(pos!=POS_NULA){
        printf("%c", *((char *) l_recuperar(lista, pos)));
        pos = l_siguiente(lista, pos);
    }
    printf("\n");
}

//Muestra contenido de una lista ordenada de enteros en un reglon
void mostrar_lista_ordenada(TListaOrdenada lista){
    TPosicion pos = lo_primera(lista);
    while(pos!=POS_NULA){
        printf("%d", *((int *) pos->elemento));
        pos = lo_siguiente(lista, pos);
    }
    printf("\n");
}

void tester_lista(){
    char ch [] = {'O','C','2','0','1','7'};
    TElemento mi_elemento;

    //1 - Lista vacía
    TLista mi_lista = crear_lista();
    printf("1 :: Crea lista vacia :: cant_elem (0): %d\n", l_size(mi_lista));
    printf("1 :: Primera :: POS_NULA (%p): %p\n", POS_NULA, l_primera(mi_lista));
    printf("1 :: Ultima :: POS_NULA (%p): %p\n", POS_NULA, l_ultima(mi_lista));
    printf("1 :: Siguiente :: POS_NULA (%p): %p\n", POS_NULA, l_siguiente(mi_lista, POS_NULA));
    printf("1 :: Anterior :: POS_NULA (%p): %p\n", POS_NULA, l_anterior(mi_lista, POS_NULA));
    printf("1 :: Eliminar :: LST_POS_INV (%d): %d\n", LST_POS_INV, l_eliminar(mi_lista, POS_NULA));
    printf("1 :: Recuperar :: ELE_NULO (%p): %p\n", ELE_NULO, l_recuperar(mi_lista, POS_NULA));

    //2 - Lista < 7 >
    mi_elemento = &ch[5]; l_insertar(mi_lista, POS_NULA, mi_elemento);
    printf("2 :: cant_elem (1): %d\n", l_size(mi_lista));
    printf("2 :: primer elemento (7): %c\n", *((char *) l_recuperar(mi_lista, l_primera(mi_lista))));

    //3 - Lista < 2 1 7 >
    mi_elemento = &ch[2]; l_insertar(mi_lista, l_primera(mi_lista), mi_elemento);
    mi_elemento = &ch[3]; l_insertar(mi_lista, l_ultima(mi_lista), mi_elemento);
    printf("3 :: cant_elem (3): %d\n", l_size(mi_lista));
    printf("3 :: primer elemento (2): %c\n", *((char *) l_recuperar(mi_lista, l_primera(mi_lista))));
    printf("3 :: ultimo elemento (7): %c\n", *((char *) l_recuperar(mi_lista, l_ultima(mi_lista))));

    //4 - Lista < 2 0 1 7 >
    mi_elemento = &ch[4]; l_insertar(mi_lista, l_ultima(mi_lista), mi_elemento);
    printf("4 :: cant_elem (4): %d\n", l_size(mi_lista));
    printf("4 :: primer elemento (2): %c\n", *((char *) l_recuperar(mi_lista, l_primera(mi_lista))));
    printf("4 :: segundo elemento (0): %c\n", *((char *) l_recuperar(mi_lista, l_siguiente(mi_lista, l_primera(mi_lista)))));
    printf("4 :: tercer elemento (1): %c\n", *((char *) l_recuperar(mi_lista, l_anterior(mi_lista, l_ultima(mi_lista)))));
    printf("4 :: ultimo elemento (7): %c\n", *((char *) l_recuperar(mi_lista, l_ultima(mi_lista))));

    //5 - Lista < O C 2 0 1 7 >
    mi_elemento = &ch[0]; l_insertar(mi_lista, POS_NULA, mi_elemento);
    mi_elemento = &ch[1]; l_insertar(mi_lista, l_siguiente(mi_lista, l_primera(mi_lista)), mi_elemento);
    printf("5 :: Lista (OC2017): "); mostrar_lista(mi_lista);

    //6- Lista < C 2 0 1 7 >
    l_eliminar(mi_lista, l_primera(mi_lista));
    printf("6 :: cant_elem (5): %d\n", l_size(mi_lista));
    printf("6 :: Lista (C2017): "); mostrar_lista(mi_lista);

    //7- Lista < C 0 1 7 >
    l_eliminar(mi_lista, l_siguiente(mi_lista, l_primera(mi_lista)));
    printf("7 :: cant_elem (4): %d\n", l_size(mi_lista));
    printf("7 :: Lista (C017): "); mostrar_lista(mi_lista);

    //8- Lista < C 0 7 >
    l_eliminar(mi_lista, l_anterior(mi_lista, l_ultima(mi_lista)));
    printf("8 :: cant_elem (3): %d\n", l_size(mi_lista));
    printf("7 :: Lista (C07): "); mostrar_lista(mi_lista);

    //9- Lista <C 0>
    l_eliminar(mi_lista, l_ultima(mi_lista));
    printf("9 :: cant_elem (2): %d\n", l_size(mi_lista));
    printf("9 :: Lista (C0): "); mostrar_lista(mi_lista);

    //10- Lista <>
    l_eliminar(mi_lista, l_ultima(mi_lista));
    l_eliminar(mi_lista, l_ultima(mi_lista));
    printf("10 :: cant_elem (0): %d\n", l_size(mi_lista));
    printf("10 :: Lista (): "); mostrar_lista(mi_lista);
}

void tester_lista_ordenada(){
    int ints_1 [] = {0,1,2,3,4,-1};
    int ints_2 [] = {0,1,2,3,4,-2};
    TElemento mi_elemento;

    //1 - Lista vacía
    TListaOrdenada mi_lista = crear_lista_ordenada(&mi_comparador);
    printf("1 :: Crea lista vacia :: cant_elem (0): %d\n", lo_size(mi_lista));
    printf("1 :: Primera :: POS_NULA (%p): %p\n", POS_NULA, lo_primera(mi_lista));
    printf("1 :: Ultima :: POS_NULA (%p): %p\n", POS_NULA, lo_ultima(mi_lista));
    printf("1 :: Siguiente :: POS_NULA (%p): %p\n", POS_NULA, lo_siguiente(mi_lista, POS_NULA));
    printf("1 :: Eliminar :: FALSE (%d): %d\n", FALSE, lo_eliminar(mi_lista, POS_NULA));

    //2 - Lista < 0 >
    mi_elemento = &ints_1[0]; lo_insertar(mi_lista, mi_elemento);
    printf("2 :: cant_elem (1): %d\n", lo_size(mi_lista));
    printf("2 :: Lista (0): "); mostrar_lista_ordenada(mi_lista);

    //3 - Lista < 0 1 2 >
    mi_elemento = &ints_1[2]; lo_insertar(mi_lista, mi_elemento);
    mi_elemento = &ints_1[1]; lo_insertar(mi_lista, mi_elemento);
    printf("3 :: cant_elem (3): %d\n", lo_size(mi_lista));
    printf("3 :: Lista (0 1 2): "); mostrar_lista_ordenada(mi_lista);

    //4 - Lista < 0 0 1 2 >
    mi_elemento = &ints_2[0]; lo_insertar(mi_lista, mi_elemento);
    printf("4 :: cant_elem (4): %d\n", lo_size(mi_lista));
    printf("4 :: Lista (0 0 1 2): "); mostrar_lista_ordenada(mi_lista);

    //5 - Lista < 0 0 1 1 2 >
    mi_elemento = &ints_2[1]; lo_insertar(mi_lista, mi_elemento);
    printf("5 :: cant_elem (5): %d\n", lo_size(mi_lista));
    printf("5 :: Lista (0 0 1 1 2): "); mostrar_lista_ordenada(mi_lista);

    //6 - Lista < 0 0 1 1 2 3>
    mi_elemento = &ints_1[3]; lo_insertar(mi_lista, mi_elemento);
    printf("6 :: cant_elem (6): %d\n", lo_size(mi_lista));
    printf("6 :: Lista (0 0 1 1 2 3): "); mostrar_lista_ordenada(mi_lista);

    //7 - Lista < 0 0 1 1 2 3 4>
    mi_elemento = &ints_1[4]; lo_insertar(mi_lista, mi_elemento);
    printf("7 :: cant_elem (7): %d\n", lo_size(mi_lista));
    printf("7 :: Lista (0 0 1 1 2 3 4): "); mostrar_lista_ordenada(mi_lista);

    //8 - Lista < 0 0 1 1 2 3 3 4>
    mi_elemento = &ints_2[3]; lo_insertar(mi_lista, mi_elemento);
    mi_elemento = &ints_2[4]; lo_insertar(mi_lista, mi_elemento);
    mi_elemento = &ints_2[2]; lo_insertar(mi_lista, mi_elemento);
    mi_elemento = &ints_1[5]; lo_insertar(mi_lista, mi_elemento);
    mi_elemento = &ints_2[5]; lo_insertar(mi_lista, mi_elemento);
    printf("8 :: cant_elem (12): %d\n", lo_size(mi_lista));
    printf("8 :: Lista (-2 -1 0 0 1 1 2 2 3 3 4 4): "); mostrar_lista_ordenada(mi_lista);

    //8 - Lista < 0 0 1 1 2 3 3 4>
    lo_eliminar(mi_lista, lo_primera(mi_lista));
    printf("9 :: cant_elem (11): %d\n", lo_size(mi_lista));
    printf("9 :: Lista (-1 0 0 1 1 2 2 3 3 4 4): "); mostrar_lista_ordenada(mi_lista);
    printf("9 :: Primera (-1): %d\n", *((int *) lo_primera(mi_lista)->elemento));
    printf("9 :: Ultima (4): %d\n", *((int *) lo_ultima(mi_lista)->elemento));
    printf("9 :: Siguiente (0): %d\n", *((int *) lo_siguiente(mi_lista, lo_primera(mi_lista))->elemento));

    while(lo_size(mi_lista) != 0) lo_eliminar(mi_lista, lo_primera(mi_lista));
    printf("10 :: Lista (): "); mostrar_lista_ordenada(mi_lista);

}

void tester_trie(){
    char * strings [] = {"esto\0","es\0","organización\0","de\0","computadoras\0",
                         "estamos\0","felices\0","de\0","esta\0","prueba\0"};
    //1 - Trie {}
    TTrie mi_trie = crear_trie();
    printf("1 :: Crea trie vacio :: cant_elem (0): %d\n", tr_size(mi_trie));
    printf("1 :: Pertenece :: FALSE (%d): %d\n", FALSE, tr_pertenece(mi_trie, strings[0]));
    printf("1 :: Recuperar :: STR_NO_PER (%d): %d\n", STR_NO_PER, tr_recuperar(mi_trie, strings[0]));
    printf("1 :: Eliminar :: FALSE (%d): %d\n", FALSE, tr_eliminar(mi_trie, strings[0]));

    //2 - Trie { esto }
    printf("2 :: insertar esto :: TRUE (%d) : %d\n", TRUE, tr_insertar(mi_trie, strings[0]));
    printf("2 :: cant_elem (1): %d\n", tr_size(mi_trie));
    printf("2 :: Pertenece esto :: TRUE (%d): %d\n", TRUE, tr_pertenece(mi_trie, strings[0]));
    printf("2 :: Pertenece es :: FALSE (%d): %d\n", FALSE, tr_pertenece(mi_trie, strings[1]));
    printf("2 :: Recuperar esto:: (1): %d\n", tr_recuperar(mi_trie, strings[0]));
    printf("2 :: Recuperar es:: STR_NO_PER (%d): %d\n", STR_NO_PER, tr_recuperar(mi_trie, strings[1]));
    printf("2 :: Recuperar est:: STR_NO_PER (%d): %d\n", STR_NO_PER, tr_recuperar(mi_trie, "est\0"));
    printf("2 :: Recuperar e:: STR_NO_PER (%d): %d\n", STR_NO_PER, tr_recuperar(mi_trie, "e\0"));

    //3 - Trie { esto, es }
    printf("3 :: insertar es :: TRUE (%d) : %d\n", TRUE, tr_insertar(mi_trie, strings[1]));
    printf("3 :: cant_elem (2): %d\n", tr_size(mi_trie));
    printf("3 :: Pertenece esto :: TRUE (%d): %d\n", TRUE, tr_pertenece(mi_trie, strings[0]));
    printf("3 :: Pertenece es :: TRUE (%d): %d\n", TRUE, tr_pertenece(mi_trie, strings[1]));
    printf("3 :: Pertenece est :: FALSE (%d): %d\n", FALSE, tr_pertenece(mi_trie, "est\0"));
    printf("3 :: Pertenece e :: FALSE (%d): %d\n", FALSE, tr_pertenece(mi_trie, "e\0"));
    printf("3 :: Recuperar esto:: (1): %d\n", tr_recuperar(mi_trie, strings[0]));
    printf("3 :: Recuperar es:: (1): %d\n", tr_recuperar(mi_trie, strings[1]));
    printf("3 :: Recuperar est:: STR_NO_PER (%d): %d\n", STR_NO_PER, tr_recuperar(mi_trie, "est\0"));
    printf("3 :: Recuperar e:: STR_NO_PER (%d): %d\n", STR_NO_PER, tr_recuperar(mi_trie, "e\0"));

    //4 - Trie { esto, es, organizacion, de, computadoras }
    printf("4 :: insertar organizaci%cn :: TRUE (%d) : %d\n", 162, TRUE, tr_insertar(mi_trie, strings[2]));
    printf("4 :: insertar de :: TRUE (%d) : %d\n", TRUE, tr_insertar(mi_trie, strings[3]));
    printf("4 :: insertar computadoras :: TRUE (%d) : %d\n", TRUE, tr_insertar(mi_trie, strings[4]));
    printf("4 :: cant_elem (5): %d\n", tr_size(mi_trie));
    printf("4 :: Pertenece organizaci%cn :: TRUE (%d): %d\n", 162, TRUE, tr_pertenece(mi_trie, strings[2]));
    printf("4 :: Pertenece de :: TRUE (%d): %d\n", TRUE, tr_pertenece(mi_trie, strings[3]));
    printf("4 :: Pertenece computadoras :: TRUE (%d): %d\n", TRUE, tr_pertenece(mi_trie, strings[4]));

    //5 - Trie { esto, es, organizacion, de(2), computadoras, estamos, felices, esta, prueba }
    printf("5 :: insertar estamos :: TRUE (%d) : %d\n", TRUE, tr_insertar(mi_trie, strings[5]));
    printf("5 :: insertar felices :: TRUE (%d) : %d\n", TRUE, tr_insertar(mi_trie, strings[6]));
    printf("5 :: insertar de :: FALSE (%d) : %d\n", FALSE, tr_insertar(mi_trie, strings[7]));
    printf("5 :: insertar esta :: TRUE (%d) : %d\n", TRUE, tr_insertar(mi_trie, strings[8]));
    printf("5 :: insertar prueba :: TRUE (%d) : %d\n", TRUE, tr_insertar(mi_trie, strings[9]));
    printf("5 :: cant_elem (9): %d\n", tr_size(mi_trie));
    printf("5 :: Pertenece estamos :: TRUE (%d): %d\n", TRUE, tr_pertenece(mi_trie, strings[5]));
    printf("5 :: Pertenece felices :: TRUE (%d): %d\n", TRUE, tr_pertenece(mi_trie, strings[6]));
    printf("5 :: Pertenece de :: TRUE (%d): %d\n", TRUE, tr_pertenece(mi_trie, strings[7]));
    printf("5 :: Pertenece esta :: TRUE (%d): %d\n", TRUE, tr_pertenece(mi_trie, strings[8]));
    printf("5 :: Pertenece prueba :: TRUE (%d): %d\n", TRUE, tr_pertenece(mi_trie, strings[9]));
    printf("5 :: Recuperar estamos:: (1): %d\n", tr_recuperar(mi_trie, strings[5]));
    printf("5 :: Recuperar de:: (2): %d\n", tr_recuperar(mi_trie, strings[7]));
    printf("5 :: Recuperar esta:: (1): %d\n", tr_recuperar(mi_trie, "esta\0"));

    //6 - Trie { esto, es, de(2), computadoras, estamos, felices, esta, prueba }
    printf("6 :: eliminar organizaci%cn :: TRUE (%d) : %d\n", 162, TRUE, tr_eliminar(mi_trie, strings[2]));
    printf("6 :: cant_elem (8): %d\n", tr_size(mi_trie));
    printf("6 :: Pertenece organizaci%cn :: FALSE (%d): %d\n", 162, FALSE, tr_pertenece(mi_trie, strings[2]));
    printf("6 :: Recuperar organizaci%cn :: STR_NO_PER (%d): %d\n", 162, STR_NO_PER, tr_recuperar(mi_trie, strings[2]));
    printf("6 :: eliminar organizaci%cn :: FALSE (%d) : %d\n", 162, FALSE, tr_eliminar(mi_trie, strings[2]));
    printf("6 :: cant_elem (8): %d\n", tr_size(mi_trie));

    //7 - Trie { esto, es, de(2), computadoras, estamos, felices, prueba}
    printf("7 :: eliminar esta :: TRUE (%d) : %d\n", TRUE, tr_eliminar(mi_trie, strings[8]));
    printf("7 :: cant_elem (7): %d\n", tr_size(mi_trie));
    printf("7 :: Pertenece esta :: FALSE (%d): %d\n", FALSE, tr_pertenece(mi_trie, strings[8]));
    printf("7 :: Recuperar esta :: STR_NO_PER (%d): %d\n", STR_NO_PER, tr_recuperar(mi_trie, strings[8]));
    printf("7 :: Pertenece estamos :: TRUE (%d): %d\n", TRUE, tr_pertenece(mi_trie, strings[5]));
    printf("7 :: Recuperar estamos :: (1): %d\n",tr_recuperar(mi_trie, strings[5]));

    //8 - Trie { }
    printf("8 :: eliminar esto :: TRUE (%d) : %d\n", TRUE, tr_eliminar(mi_trie, strings[0]));
    printf("8 :: eliminar es :: TRUE (%d) : %d\n", TRUE, tr_eliminar(mi_trie, strings[1]));
    printf("8 :: eliminar de :: TRUE (%d) : %d\n", TRUE, tr_eliminar(mi_trie, strings[3]));
    printf("8 :: eliminar computadoras :: TRUE (%d) : %d\n", TRUE, tr_eliminar(mi_trie, strings[4]));
    printf("8 :: eliminar estamos :: TRUE (%d) : %d\n", TRUE, tr_eliminar(mi_trie, strings[5]));
    printf("8 :: eliminar felices :: TRUE (%d) : %d\n", TRUE, tr_eliminar(mi_trie, strings[6]));
    printf("8 :: eliminar prueba :: TRUE (%d) : %d\n", TRUE, tr_eliminar(mi_trie, strings[9]));
    printf("8 :: cant_elem (0): %d\n", tr_size(mi_trie));
    printf("8 :: Pertenece esto :: FALSE (%d): %d\n", FALSE, tr_pertenece(mi_trie, strings[0]));
    printf("8 :: Pertenece es :: FALSE (%d): %d\n", FALSE, tr_pertenece(mi_trie, strings[1]));
    printf("8 :: Pertenece organizaci%cn :: FALSE (%d): %d\n", 162, FALSE, tr_pertenece(mi_trie, strings[2]));
    printf("8 :: Pertenece de :: FALSE (%d): %d\n", FALSE, tr_pertenece(mi_trie, strings[3]));
    printf("8 :: Pertenece computadoras :: FALSE (%d): %d\n", FALSE, tr_pertenece(mi_trie, strings[4]));
    printf("8 :: Pertenece estamos :: FALSE (%d): %d\n", FALSE, tr_pertenece(mi_trie, strings[5]));
    printf("8 :: Pertenece felices :: FALSE (%d): %d\n", FALSE, tr_pertenece(mi_trie, strings[6]));
    printf("8 :: Pertenece prueba :: FALSE (%d): %d\n", FALSE, tr_pertenece(mi_trie, strings[9]));
}

int main(){
    //tester_lista();
    //tester_lista_ordenada();
    tester_trie();
    return 0;
}
