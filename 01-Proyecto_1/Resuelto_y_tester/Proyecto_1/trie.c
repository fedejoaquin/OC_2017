#include <stdlib.h>
#include "trie.h"
#include "constantes.h"

TNodo nodo_aux;

int mi_comparador_nodos_trie(void * val1, void * val2){
    TNodo n1 = (TNodo) val1;
    TNodo n2 = (TNodo) val2;
    if ((n1->rotulo)<(n2->rotulo)) return -1;
    else if ((n1->rotulo)==(n2->rotulo)) return 0;
    else return 1;
}

//Busca y retorna la posicion de la lista parametrizada, cuyo nodo contenga un rotulo igual al del nodo buscado.
//Si no existe nodo con dicho rotulo, retorna NULL.
TNodo buscar_nodo_char(TListaOrdenada lista, TNodo buscado){
    if (lo_size(lista) == 0) return POS_NULA;
    TPosicion actual = lo_primera(lista);

    //Inspecciono nodos mientras tengan rótulos menores y no se termine la lista
    while( actual!= POS_NULA && (mi_comparador_nodos_trie(actual->elemento, buscado) < 0)){
        actual = lo_siguiente(lista, actual);
    }

    //Si corto bucle por nodo con rótulo igual al buscado, retorno posicion correspondiente.
    if (actual!=NULL && (mi_comparador_nodos_trie(actual->elemento, buscado) == 0))
        return actual->elemento;

    return POS_NULA;
}

//Agrega el nodo correspondiente a la posición pos-ésima del str.
//Finaliza cuando se consumió todo el str.
int agrandar_trie(TNodo padre, char * str, int pos){
    //Fin de agrandar recursivo
    if (str[pos] == '\0'){
        padre->contador = 1;
        return TRUE;
    }

    //Creacion de nuevo nodo y chequeo de alocación correcta
    TNodo nuevo = (TNodo) malloc(sizeof(struct nodo));
    if (nuevo == NULL) return FALSE;

    //Set de atributos, y agrega nodo a la lista de hijos de padre.
    nuevo->contador = 0;
    nuevo->hijos = crear_lista_ordenada(&mi_comparador_nodos_trie);
    nuevo->padre = padre;
    nuevo->rotulo = str[pos];
    lo_insertar(padre->hijos, nuevo);

    //Llamada recursiva para generar los próximos nodos
    return agrandar_trie(nuevo, str, pos+1);
}

//Eliminar recursivo. Se asume que nodo no tiene hijos (lista hijos vacia).
//Finaliza cuando nodo es raiz de trie, o cuando padre de nodo tiene mas de un hijo.
void eliminar(TTrie tr, TNodo nodo){
    TNodo padre = nodo->padre;

    if (nodo != tr->raiz){

        nodo->contador = 0;
        free(nodo->hijos->lista); //Este free lo deberiamos haber considerado con un lo_destruir.
        free(nodo->hijos);
        nodo->padre = NULL;
        nodo->rotulo = ' ';

        //Se elimina el nodo en cuestion, asi como tambien de la lista de su padre
        //Se elimina el nodo padre tambien, sólo si su unico hijo es el nodo anteriormente eliminado
        if(lo_size(padre->hijos) == 1){
            lo_eliminar(padre->hijos, lo_primera(padre->hijos));
            free(nodo);
            eliminar(tr, padre);
        }else{
            TPosicion pos = lo_primera(padre->hijos);
            while(pos->elemento != nodo){
                pos = lo_siguiente(padre->hijos, pos);
            }
            lo_eliminar(padre->hijos, pos);
            free(nodo);
        }
    }
}

TTrie crear_trie(){
    TTrie ret = (TTrie) malloc(sizeof(struct trie));
    TNodo raiz = (TNodo) malloc(sizeof(struct nodo));
    nodo_aux = (TNodo) malloc(sizeof(struct nodo)); //Auxiliar creado para busquedas futuras

    raiz->rotulo = ' ';
    raiz->padre = NULL;
    raiz->contador = 0;
    raiz->hijos = crear_lista_ordenada(&mi_comparador_nodos_trie);

    nodo_aux->rotulo = ' ';
    nodo_aux->padre = NULL;
    nodo_aux->contador = 0;
    nodo_aux->hijos = NULL;

    ret->cantidad_elementos = 0;
    ret->raiz = raiz;
    return ret;
}

int tr_insertar(TTrie tr, char* str){
    //Check trie inicializado
    if (tr == NULL) exit(LST_NO_INI);

    int i=-1, encontre=1, ret;
    TNodo actual = tr->raiz;
    TNodo anterior = NULL;

    //Recorro el Trie, mientras el char en la posición i-ésima se corresponda
    //con un nodo del nivel i+1-ésimo del trie, comenzando desde la coleccion
    //de nodos que corresponden a los hijos de la raiz.
    while(encontre && str[++i]!='\0'){
        anterior = actual;
        nodo_aux->rotulo = str[i];
        actual = buscar_nodo_char(actual->hijos, nodo_aux);
        encontre = actual != POS_NULA ? 1 : 0;
    }

    //Si en la búsqueda sólo se halló un prefijo de str, se agregan los nodos al trie para
    //considerar la palabra str completa.
    if (!encontre){
        //Se agregan al trie todos los nuevos nodos con los i-ésimos chars de str como
        //rótulo, comenzando por el nodo raíz o anterior, en función de si el bucle while halló
        //o no (a partir de la raiz del trie) un nodo cuyo rótulo concordara con un char de str.
        if (i == 0){
            agrandar_trie(tr->raiz, str, i);
        }else{
            agrandar_trie(anterior, str, i);
        }
        tr->cantidad_elementos = tr->cantidad_elementos + 1;
        ret = TRUE;
    }else{
        //Actual referencia al nodo cuyo rótulo concuerda con el ultimo char válido de str,
        //por lo que se incrementa la cantidad de apariciones de la palabra.
        actual->contador = actual->contador + 1;

        //Si el str no formaba parte del trie (era prefijo)
        if (actual->contador == 1 ){
            tr->cantidad_elementos = tr->cantidad_elementos + 1;
            ret = TRUE;
        }else
            ret = FALSE;
    }
    return ret;
}

int tr_pertenece(TTrie tr, char* str){
    //Check trie inicializado
    if (tr == NULL) exit(LST_NO_INI);

    int i=-1, encontre=1, ret;
    TNodo actual = tr->raiz;

    //Recorro el Trie, mientras el char en la posición i-ésima se corresponda
    //con un nodo del nivel i+1-ésimo del trie, comenzando desde la coleccion
    //de nodos que corresponden a los hijos de la raiz.
    while(encontre && str[++i]!='\0'){
        nodo_aux->rotulo = str[i];
        actual = buscar_nodo_char(actual->hijos, nodo_aux);
        encontre = actual != POS_NULA ? 1 : 0;
    }

    //Si se hallaron nodos cuyos rotulos corresponden a todos los chars de str, y no es prefijo, pertenece.
    if (encontre && str[i]=='\0')
        if (actual->contador != 0) //Si no es prefijo
            ret = TRUE;
        else
            ret = FALSE;
    else
        ret = FALSE;
    return ret;
}

int tr_recuperar(TTrie tr, char* str){
    //Check trie inicializado
    if (tr == NULL) exit(LST_NO_INI);

    int i=-1, encontre=1, ret = STR_NO_PER;
    TNodo actual = tr->raiz;

    //Recorro el Trie, mientras el char en la posición i-ésima se corresponda
    //con un nodo del nivel i+1-ésimo del trie, comenzando desde la coleccion
    //de nodos que corresponden a los hijos de la raiz.
    while(encontre && str[++i]!='\0'){
        nodo_aux->rotulo = str[i];
        actual = buscar_nodo_char(actual->hijos, nodo_aux);
        encontre = actual != POS_NULA ? 1 : 0;
    }

    //Si se hallaron nodos cuyos rotulos corresponden a todos los chars de str, y no es prefijo, pertenece.
    if (encontre && str[i]=='\0')
        if (actual->contador != 0) //Si no es prefijo
            ret = actual->contador;
        else
            ret = STR_NO_PER;
    else
        ret = STR_NO_PER;
    return ret;
}

int tr_size(TTrie tr){
    //Check trie inicializado
    if (tr == NULL) exit(LST_NO_INI);

    return tr->cantidad_elementos;
}

int tr_eliminar(TTrie tr, char* str){
    //Check trie inicializado
    if (tr == NULL) exit(LST_NO_INI);

    int i=-1, encontre=1;
    TNodo actual = tr->raiz;

    //Recorro el Trie, mientras el char en la posición i-ésima se corresponda
    //con un nodo del nivel i+1-ésimo del trie, comenzando desde la coleccion
    //de nodos que corresponden a los hijos de la raiz.
    while(encontre && str[++i]!='\0'){
        nodo_aux->rotulo = str[i];
        actual = buscar_nodo_char(actual->hijos, nodo_aux);
        encontre = actual != POS_NULA ? 1 : 0;
    }

    //Si se hallaron nodos cuyos rotulos corresponden a todos los chars de str
    if (encontre && str[i]=='\0'){
        //Si str corresponde a un prefijo de otras palabras, solo se indica que se eliminó
        //fijando el contador a cero
        if (lo_size(actual->hijos) != 0)
            actual->contador = 0;
        else
            eliminar(tr, actual);
        tr->cantidad_elementos = tr->cantidad_elementos - 1;
        return TRUE;
    }
    return FALSE;
}
