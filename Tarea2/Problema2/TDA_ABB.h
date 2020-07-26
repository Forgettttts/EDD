#include <stdlib.h>
#include <stdio.h>

typedef int tipoElem;

typedef struct _treeNode
{ //*struct de Nodo del arbol
    tipoElem info;
    struct _treeNode *izq;
    struct _treeNode *der;
} treeNode;

typedef struct
{ //*Struct de arbol binario ("Un árbol binario se identifica con un puntero a su nodo raíz")

    treeNode *raiz;
    int nElems;

} tABB;


/********************
 * void initTree()
 *******************
 * Resumen Función: 
   Inicializa el arbol vacío.
 ********************
 * input:
   tABB *T: puntero a un arbol ya declarado.
 ********************
 * Returns:
   Nada; de tipo void.
 ********************/
void initTree(tABB *T)
{ //*inicializa un ABB vacio
    T->raiz = NULL;
    T->nElems = 0;
}


/********************
 * void initNode()
 *******************
 * Resumen Función: 
   Inicializa un nodo, con un valor dado
 ********************
 * input:
   treeNode* N: puntero a un nodo ya declarado.
   tipoElem item: Elemento tipo tipoElem, el cual se guardara en el nodo
 ********************
 * Returns:
   Nada; de tipo void.
 ********************/
void initNode(treeNode *N, tipoElem item) //? Inicializar un nodo
{
    N->info = item;
    N->izq = NULL;
    N->der = NULL;
}
/********************
 * void clearHelp()
 *******************
 * Resumen Función: 
   Funcion de ayuda para clear(), se llama recursivamente, recorre el arbol , borrando los nodos.
 ********************
 * input:
   treeNode* nodo: puntero a un nodo
 ********************
 * Returns:
   Nada; de tipo void.
 ********************/
void clearHelp(treeNode *nodo)
{
    if (nodo == NULL)
        return;           //* árbol vacío, se detiene
    clearHelp(nodo->izq); //* visita subárbol izquierdo recursivamente
    clearHelp(nodo->der); //* visita subárbol derecho recursivamente
    free(nodo);           //* después de borrar subárboles, se borra a sí mismo
}
/********************
 * void clear()
 *******************
 * Resumen Función: 
   Elimina todos los elementos del arbol, con la ayuda de clearHelp()
 ********************
 * input:
   tABB *T: Puntero a un arbol.
 ********************
 * Returns:
   Nada; de tipo void.
 ********************/
void clear(tABB *T)
{                       //*Elimina todos los elementos del ABB
    clearHelp(T->raiz); //*funcion auxiliar para eliminar nodos
    T->raiz = NULL;
    T->nElems = 0;
}
/********************
 * int getValue()
 *******************
 * Resumen Función: 
   Obtiene el valor almacenado en el nodo entregado.
 ********************
 * input:
   treeNode *N: Nodo de un arbol.
 ********************
 * Returns:
   tipoElem, el valor almacenado en el nodo.
 ********************/
tipoElem getValue(treeNode *N) //?Obtiene el item de un nodo
{
    return N->info;
}
/********************
 * int size()
 *******************
 * Resumen Función: 
   Entrega el tamaño de el arbol (cantidad de elementos).
 ********************
 * input:
   tABB* T: Puntero al arbol al cual le queremos calcular el tamaño.
 ********************
 * Returns:
   int, cantidad de elementos en el arbol.
 ********************/
int size(tABB *T)
{ //* Cantidad de elementos en un arbol T
    return T->nElems;
}
/********************
 * void preOrdenHelp()
 *******************
 * Resumen Función: 
   Funcion auxiliar para recorrer el arbol con un pre-orden, imprimiendo cada elemento por pantalla.
 ********************
 * input:
   treeNode *nodo: Puntero al nodo desde el cual comienza a hacerse el recorrido en pre-orden.
 ********************
 * Returns:
   void, no retorna nada, solo ejecuta instruccion
 ********************/
void preOrdenHelp(treeNode *nodo)
{

    if (nodo == NULL)
        return;
    printf("%d ", nodo->info);
    preOrdenHelp(nodo->izq);
    preOrdenHelp(nodo->der);
}
/********************
 * void preOrden()
 *******************
 * Resumen Función: 
   Funcion que recorre el arbol e n pre-orden, imprimiendo cada elemento por pantalla.
 ********************
 * input:
   tABB* T: Puntero al arbol que queremos recorren en preorden
 ********************
 * Returns:
   void, no retorna nada, solo ejecuta instruccion
 ********************/
void preOrden(tABB *T) //? Recorrido en inOrden
{
    preOrdenHelp(T->raiz);
    printf("\n");
}
/********************
 * void* findHelp()
 *******************
 * Resumen Función: 
   Funcion auxiliar para encontrar el nodo donde se encuentra cierto elemento dentro del arbol, si es que el elemento pertenece al arbol,
   retorna la posicion donde esta, si no, retorna bajo que nodo se puede insertar. Ejemplo, si se busca el 3, pero no esta, y si esta el 5, y
   la posicion correcta de insercion sera bajo el 5, se retornara la direccion de memoria del nodo que contiene al 5. 
 ********************
 * input:
   treeNode *nodo: Puntero a nodo desde el cual comienza a hacerse la busqueda.
   tipoElemen item: Elemento que se quiere encontrar dentro del arbol 
 ********************
 * Returns:
   treeNode*, direccion del nodo que contiene el elemento, si es que esta, si no, direccion del nodo en el cual se deberia insertar debajo.
 ********************/
treeNode *findHelp(treeNode *nodo, tipoElem item) //?Retorna un puntero a la posición del nodo que contiene el ítem, y si no está retorna dónde se debe insertar
{
    if (getValue(nodo) == item)
    {
        return nodo;
    }

    if (item < getValue(nodo))
    {
        if ((nodo->izq == NULL))
        {
            return nodo;
        }
        else
        {
            return findHelp(nodo->izq, item); //* Si es que el item que buscamos, es menor que en el que estabamos, buscamos por la izquierda
        }
    }

    else
    {
        if ((nodo->der == NULL))
        {
            return nodo;
        }
        else
        {
            return findHelp(nodo->der, item); //* Si es que el item que buscamos, es mayor que en el que estabamos, buscamos por la iderecha
        }
    }
    return NULL;
}
/********************
 * treeNo* find()
 *******************
 * Resumen Función: 
   Busca el nodo en el cual esta contenido cierto item, si no esta, se entrega la poscion en la cual se deberia insertar. Se ayuda de la
   funcion findHelp
 ********************
 * input:
   tABB*T: Puntero a el arbol en el que se buscara un elemento
   tipoElemen item: Elemento que se quiere encontrar dentro del arbol 
 ********************
 * Returns:
   treeNode*, direccion del nodo que contiene el elemento, si es que esta, si no, direccion del nodo en el cual se deberia insertar debajo.
 ********************/
treeNode *find(tABB *T, tipoElem item) //? Revisa si hay un "item" en un ABB T, retorna 0 si encuentra, 1 en caso de no encontrarlo
{
    return findHelp(T->raiz, item);
}
/********************
 * int success_find()
 *******************
 * Resumen Función: 
   REvisa si es que la busqueda en find() fue exitosa (es decir, que la direccion de memoria que retorno, contiene al elemento buscado) o
   si es que no (retorno la direccion de memoria del nodo donde se podria insertar debajo el numero buscado)
 ********************
 * input:
   tABB* T: Puntero a el arbol en el que se corroborara la busqueda del arbol
   tipoElemen item: Elemento que se quiere revisar si es que fue encontrado en el arbol.
 ********************
 * Returns:
   int, 0 si es que el elemento no esta en el arbol y lo que se retorno en find() es la direccion de memoria del nodo donde se podria insertar debajo el numero buscado,
   1 si es que se encotro el elemento en el arbol y lo que se retorno fue la direccion de memoria del nodo que contiene al numero
 ********************/
int success_find(tABB *T, tipoElem item)
{ //?Esta función me indica si la búsqueda fue exitosa o no
    if (getValue(find(T, item)) != item)
    {
        return 0; //*El elemento no está en el arbol
    }
    else
    {
        return 1; //*El elemento ya existe en el arbol
    }
}

/********************
 * void insertHelp()
 *******************
 * Resumen Función: 
   Funcion auxiliar de insert, inserta un nodo en la posicion correcta segun la jerarquia de un ABB
 ********************
 * input:
   treeNode **N: Puntero a un puntero de tipo treeNode, es el nodo que se esta revisando en esa ejecucion de la funcion
   treeNode *initem: Puntero a un nodo que se quiere insertar
 ********************
 * Returns:
   nada, es de tipo void.
 ********************/
void insertHelp(treeNode **N, treeNode *initem) //? Auxiliar para insert, la cual esta abajo
{
    if (*N == NULL){ //* Llegamos a la hoja correspondiente donde se debe insertar
        *N = initem;
    }
    else if (initem->info < getValue(*N))      //
        return insertHelp(&(*N)->izq, initem); //* Si es que el item del nodo a insertar es menor que el item del nodo actual, avanzamos a la izquierda
    else if (initem->info > getValue(*N))
        return insertHelp(&(*N)->der, initem); //* Si es que el item del nodo a insertar es mayor que el item del nodo actual, avanzamos a la derecha
}

/********************
 * void insert()
 *******************
 * Resumen Función: 
   Inserta un elemento en la posicion correcta segun la jerarquia de un ABB, ayudandose de insertHelp()
 ********************
 * input:
   tABB* T: Puntero al arbol en el cual se quiere insertar un nodo.
   tipoElem item: Item que se quiere insertar en el arbol.
 ********************
 * Returns:
   nada, es de tipo void.
 ********************/
void insert(tABB *T, tipoElem item) //? Insertar un nodo, queda en posicion de hoja
{
    //* Creamos un nodo, y le damos la memoria que necesita
    treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
    initNode(newNode, item); //* Aqui guardamos la info. en el nodo recien creado

    if (T->raiz == NULL) //* Si es que no hay ningun nodo en el arbol, el nodo recien creado, sera la raiz
    {
        T->raiz = newNode;
        T->nElems++;
    }
    else if (success_find(T, item) == 1) //* Si el nodo ya está en el arbol solo retorna
    {
        return;
    }
    else
    {
        insertHelp(&T->raiz, newNode); //* Si es que el arbol no esta vacio, ni contiene ya al item, se inserta el item
    }
}

/********************
 * treeNode* predecesor()
 *******************
 * Resumen Función: 
   Funcion que retorna la poscion del nodo que almacena el elemento antecesor del que le entreguemos como parametro
 ********************
 * input:
   treeNode *aBorrar: Puntero a el nodo del cual se quiere saber su antecesor (el nombre se debe a que se usa mayormente en la funcion que borra un nodo).
 ********************
 * Returns:
   treeNode *, un puntero al nodo que almacena el elemento antecesor del que le entreguemos como parametro
 ********************/
treeNode *predecesor(treeNode *aBorrar)
{
    aBorrar = aBorrar->izq;
    while ((aBorrar->der) != NULL)
    {
        aBorrar = aBorrar->der;
    }
    return aBorrar;
}
/********************
 * treeNode* sucesorHelp
 *******************
 * Resumen Función: 
   Funcion auxiliar (de sucesor())para encontrar el sucesor de un numero, en ciertos casos
 ********************
 * input:
   treeNode *nodo: Nodo en el cual se esta buscando si cumple la condicion para poder actualizarse el sucesor de un numero 
   tipoelem suce: Sucesor, el numero +1, lo ocupamos como referencia
   treeNode* inicial: Puntero a nodo en el cual iremos almacenando el valor del sucesor mas optimo encontrado hasta el momento
   treeNode* retornito: Puntero a nodo, el cual apuntara al nodo que contiene el mejor numero sucesor hasta el momento
 ********************
 * Returns:
   treeNode *, un puntero al nodo que contiene al mejor candidato a sucesor dentro del arbol
 ********************/
treeNode *sucesorHelp(treeNode *nodo, tipoElem suce, treeNode *inicial, treeNode *retornito)
{ //*nodo=ctual, suce=n°+1, P.inicial=u, P. retornito=Null
    if ((getValue(nodo) < inicial->info) && (getValue(nodo) >= suce)) //creemos que la primera condicion no sirve porque u es mayor a todo
    {
        retornito = nodo;
        inicial->info = getValue(nodo);
        if (inicial->info == suce)
        {
            return retornito; //* Retornamos si es que lo de antentro del if se cumple, ya uqe se encontro el antecesor justo.
        }
    }
    if (suce < getValue(nodo))
    {
        if ((nodo->izq == NULL))
        {
            return retornito;
        }
        else
        {
            return sucesorHelp(nodo->izq, suce, inicial, retornito); //* Si es que el item que buscamos, es menor que en el que estabamos, buscamos por la izquierda
        }
    }
    else if (suce > getValue(nodo))
    {
        if ((nodo->der == NULL))
        {
            return retornito;
        }
        else
        {
            return sucesorHelp(nodo->der, suce, inicial, retornito); //* Si es que el item que buscamos, es mayor que en el que estabamos, buscamos por la iderecha
        }
    }
    retornito=inicial;
    return retornito;
}
/********************
 * treeNode* sucesorRapido()
 *******************
 * Resumen Función: 
   Funcion que retorna la poscion del nodo que almacena el elemento que es el sucesor al que le entregamos como parametro en ciertos casos,
   el nombre se debe a que los casos en los que se usa esta funcion (llamada desde sucesor()) son mas simples y rapidos de retornar.
 ********************
 * input:
   treeNode *aBuscar: Puntero a el nodo del cual se quiere saber su sucesor.
 ********************
 * Returns:
   treeNode *, un puntero al nodo que almacena el elemento sucesor al cual le entregamos como parametro a la funcion sucesor(), la cual
   a su vez llama a sucesorRapido().
 ********************/
treeNode *sucesorRapido(treeNode *aBuscar)
{
    aBuscar = aBuscar->der;
    while ((aBuscar->izq) != NULL)
    {
        aBuscar = aBuscar->izq;
    }
    return aBuscar;
}

tipoElem findMax(tABB* T){
    treeNode* nodo= T->raiz;
    while(nodo->der !=NULL){
        nodo = nodo->der;
    }
    return getValue(nodo);
}

treeNode *sucesor(tABB *T, tipoElem item, int max)
{
    treeNode INICIAL;
    treeNode *INIT = &INICIAL;
    initNode(INIT, max); //*Inicializamos un nuevo nodo, con info=0
    if (T->raiz == NULL) //* CASO 0= El árbol esta vacio
    {
        return INIT;
    }
    treeNode *posicion = find(T, item);
    if (posicion->info == item)
    { //* El item es un nodo que existe en el árbol
        if (posicion->der != NULL)
        {
                return sucesorRapido(posicion);
        }
        else if ((posicion->der == NULL))
        {
            
            if (((findMax(T) <= item)  && (item <= max ))){
                treeNode NodoMax;
                initNode(&NodoMax, (tipoElem)max);
                treeNode* p = &NodoMax;
                return p;
            }
            else
            {
                treeNode *RETORNO = NULL;
                return sucesorHelp(T->raiz, (++item), &INICIAL, RETORNO);
            }
        }
    }

    else
    { //* El item no está en el árbol
        if (((findMax(T) < item)  && (item < max ))){
            treeNode NodoMax;
            initNode(&NodoMax, (tipoElem)max);
            treeNode* p = &NodoMax;
            return p;
        }
        else
        {
            treeNode *RETORNO = NULL;
            return sucesorHelp(T->raiz, (++item), &INICIAL, RETORNO);
        }
        
    }
    return NULL;
}


/********************
 * void* borrar()
 *******************
 * Resumen Función: 
   Busca el nodo en el cual esta contenido cierto item, si no esta, se entrega la poscion en la cual se deberia insertar. Se ayuda de la
   funcion findHelp
 ********************
 * input:
   tABB*T: Puntero a el arbol en el que se buscara un elemento
   tipoElemen item: Elemento que se quiere encontrar dentro del arbol 
 ********************
 * Returns:
   treeNode*, direccion del nodo que contiene el elemento, si es que esta, si no, direccion del nodo en el cual se deberia insertar debajo.
 ********************/
void borrar(tABB *T, treeNode* ParaBorrar)
{

    if ((success_find(T, getValue(ParaBorrar))) == 0) //*El elemento no está en el árbol, por lo tanto, sólo retorna
    {
        return;
    }
    else
    {
        treeNode *pos = ParaBorrar;
        //CASO 1
        if ((pos->izq == NULL) && (pos->der == NULL)) //*Si ambos hijos del nodo son NULL, es una hoja
        {
            free(pos);
            return;
        }

        //CASO 2
        else if ((pos->izq != NULL) && (pos->der == NULL)) //*Si tiene hijo izquiero, y su puntero derecho es NULL
        {
            pos->info = pos->izq->info;
            treeNode *AUX;
            AUX = pos->izq;
            if (((pos->izq->izq) == NULL) && ((pos->izq->der) == NULL))
            { //* Si es que el hijo izquierdo, no tiene hijos
                pos->izq = NULL;
                pos->der = NULL;
            }
            else if (((pos->izq->izq) != NULL) && ((pos->izq->der) == NULL))
            { //* Si es que el hijo izquierdo, tiene solo hijo izqueirdo
                pos->izq = pos->izq->izq;
                pos->der = NULL;
            }
            else if (((pos->izq->izq) == NULL) && ((pos->izq->der) != NULL))
            { //* Si es que el hijo izquierdo, tiene solo hijo derecho
                pos->izq = NULL;
                pos->der = pos->izq->der;
            }
            else if (((pos->izq->izq) != NULL) && ((pos->izq->der) != NULL))
            { //* Si es que el hijo izquierdo, tiene ambos hijos
                pos->izq = pos->izq->izq;
                pos->der = pos->izq->der;
            }
            free(AUX);
            return;
        }

        else if ((pos->izq == NULL) && (pos->der != NULL)) //*Si tiene hijo derecho, y su puntero izquierdo es NULL
        {
            pos->info = pos->der->info;
            treeNode *AUX;
            AUX = pos->der;
            if (((pos->der->izq) == NULL) && ((pos->der->der) == NULL))
            { //* Si es que el hijo derecho, no tiene hijos
                pos->izq = NULL;
                pos->der = NULL;
            }
            else if (((pos->der->izq) != NULL) && ((pos->der->der) == NULL))
            { //* Si es que el hijo derecho, tiene solo hijo izqueirdo
                pos->izq = pos->der->izq;
                pos->der = NULL;
            }
            else if (((pos->der->izq) == NULL) && ((pos->der->der) != NULL))
            { //* Si es que el hijo derecho, tiene solo hijo derecho
                pos->izq = NULL;
                pos->der = pos->der->der;
            }
            else if (((pos->der->izq) != NULL) && ((pos->der->der) != NULL))
            { //* Si es que el hijo derecho, tiene ambos hijos
                pos->izq = pos->der->izq;
                pos->der = pos->der->der;
            }
            free(AUX);
            return;
        }

        //CASO 3
        else //* Si es que tiene ambos hijos
        {   
            treeNode *pred = predecesor(pos); // Puntero al predecesor del nodo ParaBorrar
            pos->info = getValue(pred);
            borrar(T, pred);
            return;
        }
    }
}
