#include <stdlib.h>
#include <stdio.h>

typedef int tipoElem;

typedef struct _treeNode { //*struct de Nodo del arbol
    tipoElem info;
    struct _treeNode *izq;
    struct _treeNode *der;
} treeNode;



typedef struct {//*Struct de arbol binario ("Un árbol binario se identifica con un puntero a su nodo raíz")

    treeNode *raiz;
    int nElems;

} tABB;



void initTree(tABB* T) { //*inicializa un ABB vacio
    T->raiz = NULL;
    T->nElems = 0;
}


void initNode(treeNode *N, tipoElem item) //? Inicializar un nodo
{ 
    N->info = item;
    N->izq = NULL;
    N->der = NULL;
}


void clearHelp(treeNode *nodo) {
 if (nodo == NULL) return; //* árbol vacío, se detiene
 clearHelp(nodo->izq); //* visita subárbol izquierdo recursivamente
 clearHelp(nodo->der); //* visita subárbol derecho recursivamente
 free(nodo); //* después de borrar subárboles, se borra a sí mismo
}


void clear(tABB* T) { //*Elimina todos los elementos del ABB
    clearHelp(T->raiz); //*funcion auxiliar para eliminar nodos
    T->raiz = NULL;
    T->nElems = 0;
}


int getValue(treeNode *N)//?Obtiene el item de un nodo
{ 
    return N->info;
}


int size(tABB* T) { //* Cantidad de elementos en un arbol T
    return T->nElems;
}


void preOrdenHelp (treeNode *nodo) {

if (nodo == NULL)
        return;
    printf("%d ", nodo->info);
    preOrdenHelp(nodo->izq);  
    preOrdenHelp(nodo->der); 

}


void preOrden(tABB *T)//? Recorrido en inOrden
{ 
    preOrdenHelp(T->raiz);
    printf("\n");
}


treeNode* findHelp(treeNode *nodo, tipoElem item) //?Retorna un puntero a la posición del nodo que contiene el ítem, y si no está retorna dónde se debe insertar
{
    if (getValue(nodo) == item){
        return nodo;
    }

    if (item < getValue(nodo))
        if ((nodo->izq == NULL)){
            return nodo;
        }
        else{
            return findHelp(nodo->izq, item);//* Si es que el item que buscamos, es menor que en el que estabamos, buscamos por la izquierda
        }
        
    else
        if ((nodo->der == NULL)){
            return nodo;
        }
        else{
            return findHelp(nodo->der, item); //* Si es que el item que buscamos, es mayor que en el que estabamos, buscamos por la iderecha
        }
        
        
}


treeNode* find(tABB *T, tipoElem item) //? Revisa si hay un "item" en un ABB T, retorna 0 si encuentra, 1 en caso de no encontrarlo
{
    return findHelp(T->raiz, item);
}


int success_find(tABB* T, tipoElem item){ //?Esta función me indica si la búsqueda fue exitosa o no
    if (getValue(find(T, item)) != item){
        return 0; //*El elemento no está en el arbol
    }
    else{
        return 1; //*El elemento ya existe en el arbol
    }
}


void insertHelp(treeNode **N, treeNode *initem) //? Auxiliar para insert, la cual esta abajo
{
    if (*N == NULL) //* Llegamos a la hoja correspondiente donde se debe insertar
        *N = initem; 
    else if (initem->info < getValue(*N))//
        return insertHelp(&(*N)->izq, initem);//* Si es que el item del nodo a insertar es menor que el item del nodo actual, avanzamos a la izquierda
    else if (initem->info > getValue(*N))
        return insertHelp(&(*N)->der, initem);//* Si es que el item del nodo a insertar es mayor que el item del nodo actual, avanzamos a la derecha
}


void insert(tABB *T, tipoElem item)//? Insertar un nodo, queda en posicion de hoja
{
    //* Creamos un nodo, y le damos la memoria que necesita 
    treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
    initNode(newNode, item); //* Aqui guardamos la info. en el nodo recien creado

    if (T->raiz == NULL)//* Si es que no hay ningun nodo en el arbol, el nodo recien creado, sera la raiz
    {
        T->raiz = newNode;
        T->nElems++;
    }
    else if (success_find(T, item) == 1)//* Si el nodo ya está en el arbol solo retorna
    {
        return;
    }
    else
    {
        insertHelp(&T->raiz, newNode);//* Si es que el arbol no esta vacio, ni contiene ya al item, se inserta el item
    }
}




//! +*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+* SEGUIR DESDE AQUÍ +*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*

void predecesorHelp(treeNode* nodo, tipoElem antecesor, treeNode* pred, treeNode* retornito){ //* 
    
    if ((getValue(nodo) > *pred->info ) && (getValue(nodo) <= antecesor))
    {
        *retornito= &nodo;
        *pred->info=getValue(nodo);
    }

    if (antecesor < getValue(nodo)){
        if ((nodo->izq == NULL))
        {
            return;
        }
        else
        {
            predecesorHelp(nodo->izq, antecesor, pred, retornito); //* Si es que el item que buscamos, es menor que en el que estabamos, buscamos por la izquierda
        }
    }
    else if (antecesor > getValue(nodo)){
        if ((nodo->der == NULL))
        {
            return;
        }
        else
        {
            predecesorHelp(nodo->der, antecesor, pred, retornito); //* Si es que el item que buscamos, es mayor que en el que estabamos, buscamos por la iderecha
        }
    }
}

treeNode *predecesor(tABB *T, tipoElem item) // predecesor (T,50) antecesor= 49
{
    treeNode INICIAL;
    initNode(&INICIAL, 0); //*Inicializamos un nuevo nodo, con info=0
    treeNode* RETORNO; //* Declaramos un puntero que apuntara al predecesor, el cual retornaremos
    predecesorHelp(T->raiz, (--item), &INICIAL, RETORNO); 
    return RETORNO; //* Retornamos el predecesor
}

void sucesor(tABB* T, tipoElem item, int max){
    
    treeNode* suce = find(T, (++item));
    if (getValue(suce) == item){ // Si el valor del nodo que retornó la búsqueda es el mismo item, es porque no exíste un predecesor en el árbol, por lo tanto, retorno el u
        printf("%d\n", max);
    }
    else{
        printf("%d", getValue(suce));
    } 
    return;
}


void borrar(tABB *T, tipoElem item){

    if ((success_find(T, item)) == 0) //*El elemento no está en el árbol, por lo tanto, sólo retorna
    {
        return;
    }
    else
    {
        treeNode* pos = find(T, item);
        //CASO 1
        if ((pos->izq == NULL) && (pos->der == NULL)) //*Si ambos hijos del nodo son NULL, es una hoja
        {
            free(pos);
            return;
        }

        //CASO 2
        else if ((pos->izq != NULL) && (pos->der == NULL)) //*Si tiene hijo izquiero, y su puntero derecho es NULL
        {
            pos->info=pos->izq->info;
            treeNode* AUX;
            AUX=pos->izq;
            if(((pos->izq->izq)==NULL)&&((pos->izq->der)==NULL)){ //* Si es que el hijo izquierdo, no tiene hijos
                pos->izq=NULL;
                pos->der=NULL;
            }
            else if(((pos->izq->izq)!=NULL)&&((pos->izq->der)==NULL)){ //* Si es que el hijo izquierdo, tiene solo hijo izqueirdo
                pos->izq=pos->izq->izq;
                pos->der=NULL;
            }
            else if(((pos->izq->izq)==NULL)&&((pos->izq->der)!=NULL)){ //* Si es que el hijo izquierdo, tiene solo hijo derecho
                pos->izq=NULL;
                pos->der=pos->izq->der;
            }
            else if(((pos->izq->izq)!=NULL)&&((pos->izq->der)!=NULL)){ //* Si es que el hijo izquierdo, tiene ambos hijos
                pos->izq=pos->izq->izq;
                pos->der=pos->izq->der;
            }
            free(AUX);
            return;
        }

        
        else if ((pos->izq == NULL) && (pos->der != NULL)) //*Si tiene hijo derecho, y su puntero izquierdo es NULL
        {
            pos->info=pos->der->info;
            treeNode* AUX;
            AUX=pos->der;
            if(((pos->der->izq)==NULL)&&((pos->der->der)==NULL)){ //* Si es que el hijo derecho, no tiene hijos
                pos->izq=NULL;
                pos->der=NULL;
            }
            else if(((pos->der->izq)!=NULL)&&((pos->der->der)==NULL)){ //* Si es que el hijo derecho, tiene solo hijo izqueirdo
                pos->izq=pos->der->izq;
                pos->der=NULL;
            }
            else if(((pos->der->izq)==NULL)&&((pos->der->der)!=NULL)){ //* Si es que el hijo derecho, tiene solo hijo derecho
                pos->izq=NULL;
                pos->der=pos->der->der;
            }
            else if(((pos->der->izq)!=NULL)&&((pos->der->der)!=NULL)){ //* Si es que el hijo derecho, tiene ambos hijos
                pos->izq=pos->der->izq;
                pos->der=pos->der->der;
            }
            free(AUX);
            return;
        }

        //CASO 3
        else //* Si es que tiene ambos hijos
        {
            treeNode* pred = predecesor(T, item);
            pos->info = getValue(pred);
            borrar(T, getValue(pred));
            return;
        }
    }
}




//todo: BORRAR N: elimina el entero N del conjunto, sólo si éste pertenece al conjunto.En caso de que el elemento a borrar tenga dos hijos no nulos en el árbol, aplique la política que LO REEMPLAZA POR SU PREDECESOR.
//todo: Falta implementar funcion sucesor(S,x)
//todo: Modificar preorden para que printee los elementos del arbol en preorden, con el formato que se pide en la tarea
/*
(a) Borrado de una hoja
(b) Borrado de un nodo que es subarbol, donde a un lado tiene un nodo y al otro no tiene nada
(c) Borrado de un nodo que es subarbol, donde a ambos lados tiene hojas o subarboles
	(c.1) A un lado tiene un sub-arbol de altura 1, y al otro un subarbol mas grande
	(c.2) A ambos lados tiene sub-arboles de altura >1
*/
