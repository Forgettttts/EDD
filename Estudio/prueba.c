#define MAX_SIZE 1000000

//!                                                     ....:::: CERTAMEN 2 ::::....

//! ********************************* Problema 1 *********************************

typedef tipoElem;

typedef struct {
	tipoElem array[MAX_SIZE];
	int len;
} tColap;

//? borrar el nodo i (y su contenido) preservando las propiedades del heapH
void borrarNodoHeap(tColap* H, int i) {
	H->array[i]=H->array[H->len];
	H->len--;

	while ((2*i+1<= H->len)  &&  ((H->array[i] < H->array[2*i])  ||  H->array[i]<H->array[2*i+1])) { //! PARA HUNDIR
		tipoElem maximal;
		if (H->array[2*i]>H->array[2*i+1]){
			maximal=2*i;
		}
		else{
			maximal=2*i+1;
		}
		tipoElem temp = H->array[i];
		H->array[i]= H->array[maximal];
		H->array[maximal]=temp;
		i=maximal;
	}

	while((2*i<=H->len)&&(H->array[i]<H->array[2*i])){ //! PARA HUNDIR CASO BORDE, SOLO ALCANZA A TENER 1 HIJO ANTES DE QUE EL HEAP ACABE
		tipoElem temp= H->array[i];
		H->array[i]= H->array[2*i];
		H->array[2*i]=temp;
		i=2*i;
	}

	while (i>1 && H->array[i/2]<H->array[i]){ //! PARA FLOTAR
		tipoElem temp = H->array[i/2];
		H->array[i/2]= H->array[i];
		H->array[i]=temp;
		i=i/2;
	}
}





//!                                                     ....:::: PRE-CERTAMEN 2 ::::....

void modificarValorHeap(tColap* H, int i, tipoElem j){
	H->array[i]=j;

	while (i>1 && H->array[i]>H->array[i/2]){ //! FLOTAR
		tipoElem temp= H->array[i/2];
		H->array[i/2]=H->array[i];
		H->array[i]=temp;
		i=i/2;
	}

	while ((2*i+1)<H->len && ((H->array[i] < H->array[2*i])  ||  H->array[i]<H->array[2*i+1])){ //! HUNDIR GRAL.
		tipoElem maximal, temp;

		if (H->array[2*i]>H->array[2*i+1]) {
			maximal=2*i;
		}
		else {
			maximal=2*i+1;
		}
		temp=H->array[i];
		H->array[i]=H->array[maximal];
		H->array[maximal]=temp;
		i=maximal;
	}
	while ((2*i<=H->len)&&(H->array[i]<H->array[2*i])) { //! PARA HUNDIR CASO BORDE, SOLO ALCANZA A TENER 1 HIJO ANTES DE QUE EL HEAP ACABE
		tipoElem temp= H->array[i];
		H->array[i]= H->array[2*i];
		H->array[2*i]=temp;
		i=2*i;
	}
}