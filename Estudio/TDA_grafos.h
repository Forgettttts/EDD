typedef int tVertice;

typedef struct tGrafo tGrafo;

// inicializa un grafo para n vértices
void initGraph(tGrafo *G, int n);

// libera la memoria utilizada por un grafo
void destroyGraph (tGrafo *G);

// retorna el número de vértices en el grafo
int nVertex(tGrafo *G);

// retorna el número de arcos en el grafo
int nEdges(tGrafo *G);

// Devuelve el primer vecino de un vértice v dado (asume que los
// vecinos de un vértice están ordenados por número de vértice)
tVertice first (tGrafo *G, tVertice v);

// Devuelve el menor vecino de v, cuya numeración es mayor a w.
// Si no existe dicho vecino, retorna el número de vértices del grafo
tVertice next (tGrafo *G, tVertice v, tVertice w);

// agrega un nuevo arco al grafo entre vértices v1 y v2 (no se
// pueden agregar nuevos vértices)
void setEdge (tGrafo *G, tVertice v1, tVertice v2, int peso);

// borra un arco existente entre vértices v1 y v2
void deleteEdge (tGrafo *G, tVertice v1, tVertice v2);

// dados dos vértices, indica si existe un arco entre ellos
int isEdge (tGrafo *G, tVertice v1, tVertice v2);

// devuelve el peso de un arco del grafo (0 si no existe)
int weight (tGrafo *G, tVertice v1, tVertice v2);

// obtiene la marca asignada a un vértice dado (ciertos algoritmos
// necesitan marcar los vértices
int getMark (tGrafo *G, tVertice v);

// marca un vértice con un valor dado
void setMark (tGrafo *G, tVertice v, int marca);

int nVecinos(tGrafo* G, tVertice v);