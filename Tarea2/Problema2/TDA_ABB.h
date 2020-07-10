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
    N->izq = N->der = NULL;
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
    treeNode *newNode = (treeNode *)malloc(sizeof(treeNode)); //! ¿Seria mejor darle la memoria dentro de la funcion initNode?
    initNode(newNode, item); //* Aqui guardamos la info. en el nodo recien creado

    if (T->raiz == NULL)//* Si es que no hay ningun nodo en el arbol, el nodo recien creado, sera la raiz
    {
        T->raiz = newNode;
        T->nElems++;
    }
    else if (find(T, item)==0)//* Revisa si es que el item ya esta en el ABB
    {
        return;
    }
    else
    {
        insertHelp(&T->raiz, newNode);//* Si es que el arbol no esta vacio, ni contiene ya al item, se inserta el item
    }
}

int getValue(treeNode *N)//?Obtiene el item de un nodo
{ 
    return N->info;
}

treeNode findHelp(treeNode *nodo, tipoElem item) {
    if (nodo == NULL){
        return 0; //* item no está en el ABB
    } 
    if (getValue(nodo) == item){
        return nodo;
        }
    //* item encontrado
    if (item < getValue(nodo)){
        return findHelp(nodo->izq, item);
    }
    else{
        return findHelp(nodo->der, item);
    }
}

treeNode find(tABB *T, tipoElem item)
{ //* busca un item(numero) en un ABB, en el caso de no encontrarlo retorna 0
    return findHelp(T->raiz, item);
}

int size(tABB* T) { //* Cantidad de elementos en un arbol T
    return T->nElems;
}

void preOrdenHelp (treeNode *nodo) {

if (nodo == NULL)
        return;
    printf("%d, ", nodo->info);
    preOrderHelp(nodo->izq);  
    preOrderHelp(nodo->der); 

}

void preOrden(tABB *T)//? Recorrido en inOrden
{ 
    printf("[");
    inOrderHelp(T->raiz);
    printf("]\n");
}


void inOrderHelp(treeNode *nodo)//? Auxiliar de inOrder, la que esta abajo
{
    if (nodo == NULL)
        return;
    inOrderHelp(nodo->izq);   
    printf("%d, ", nodo->info); 
    inOrderHelp(nodo->der);
}

void inOrden(tABB* T){ //* recorrido in-orden de un ABB T
    inOrdenHelp (T->raiz);
}


void postOrderHelp(treeNode *nodo)//? Auxiliar de posOrder, la que esta abajo
{
    if (nodo == NULL)
        return;
    postOrderHelp(nodo->izq);  
    postOrderHelp(nodo->der);
    printf("%d, ", nodo->info); 
}

void postOrden(tABB *T)//? Recorrido en posOrden
{ 
    printf("[");
    postOrderHelp(T->raiz);
    printf("]\n");
}


//! +*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+* SEGUIR DESDE AQUÍ +*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*

int removeHelp(tABB *T, tipoElem item){
    if (nodo == NULL) return 0;
    if (getValue(nodo) == item){;
        free
        return 1;
    }
    //* item encontrado
    if (item < getValue(nodo)){
        return findHelp(nodo->izq, item);
    }
    else{
        return findHelp(nodo->der, item);
    }


}


void remove(tABB *T, tipoElem item)//? Elimina un item del ABB
{

    //* Buscar el elemtento, si no se encuentra, retornar, en caso contrario, ver si su puntero izquierdo
    //* esta vacio, si el derecho esta vacio tambien, entonces CASO 1.

    //* Buscar el elemtento, si no se encuentra, retornar, en caso contrario, ver si uno de sus punteros esta
    //* vacio, y el otro no esta vacio, CASO 2.

    //* Buscar el elemtento, si no se encuentra, retornar, en caso contrario, ver si ambos putneros no estan
    //* vacios, en ese caso, CASO 3. Si es que uno de sus arboles tiene altura 0, CASO 3.1, si es que ambos
    //* árboles tienen altura >0, CASO 3.2

    //* CASO 1: HOJA

    //* CASO 2: lado 1: VACIO, lado 2: SUB-ARBOL

    //*CASO 3:
    //*CASO 3.1:

    //*CASO 3.2

}


//todo: BORRAR N: elimina el entero N del conjunto, sólo si éste pertenece al conjunto.En caso de que el elemento a borrar tenga dos hijos no nulos en el árbol, aplique la política que LO REEMPLAZA POR SU PREDECESOR.
//todo: Falta implementar funcion sucesor(S,x)
/*
(a) Borrado de una hoja
(b) Borrado de un nodo que es subarbol, donde a un lado tiene un nodo y al otro no tiene nada
(c) Borrado de un nodo que es subarbol, donde a ambos lados tiene hojas o subarboles
	(c.1) A un lado tiene un sub-arbol de altura 1, y al otro un subarbol mas grande
	(c.2) A ambos lados tiene sub-arboles de altura >1
*/
