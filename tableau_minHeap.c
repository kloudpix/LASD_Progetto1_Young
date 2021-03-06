#include "tableau_minHeap.h"

//Heapify
void tableau_minHeap_heapify(TABLEAU T_young, int idx_row, int idx_col)	{
	TABLEAUptr T_ptr_min;	//riferimento al puntatore col valore più piccolo
	TABLEAUptr T_ptr_left = tableau_minHeap_sinistro(T_young, idx_row, idx_col);	//indice di riga sul valore a sinistra
	TABLEAUptr T_ptr_right = tableau_minHeap_destro(T_young, idx_row, idx_col);	//indice di colonna sul valore a destra

	//in base all'ordinamento Heap, determino quale valore ho bisogno di sostituire nei vertici figli
	if (T_ptr_left && *T_ptr_left < *(T_young[idx_row][idx_col]))	//confronto dei valori fra posizione attuale e figlio sinistro
		T_ptr_min = T_ptr_left;
	else
		T_ptr_min = T_young[idx_row][idx_col];	//posizione attuale

	if(T_ptr_right && *T_ptr_right < *(T_ptr_min))	//confronto dei valori fra posizione attuale e figlio destro
		T_ptr_min = T_ptr_right;

	if(T_ptr_min != T_young[idx_row][idx_col])	{	//se effettivamente ho un valore da scambiare
		int tmp = *T_young[idx_row][idx_col];	//mi conservo momentaneamente il valore nella posizione attuale
		tableau_minHeap_swap(T_young[idx_row][idx_col], T_ptr_min);	//effetto lo scambio fra i valori all'interno dei due puntatori'
		if(T_ptr_left && tmp == *T_ptr_left)	//se il valore conservato è stato posizionato a sinistra/riga successiva
			tableau_minHeap_heapify(T_young, idx_row+1, idx_col);	//continuo heapify nella riga successiva
		else if (T_ptr_right && tmp == *T_ptr_right)	//se il valore conservato è stato posizionato a destra/colonna successiva
			tableau_minHeap_heapify(T_young, idx_row, idx_col+1);	//continuo heapify nella colonna successiva
	}
}


//Ricavo il puntatore del figlio sinistro (riga successiva)
TABLEAUptr tableau_minHeap_sinistro(TABLEAU T_young, int idx_row, int idx_col)	{
	if(idx_row+1 <= *(T_young[1][0]) && T_young[idx_row+1][idx_col])	//se non eccedo col numero di righe
		return T_young[idx_row+1][idx_col];	//ritorno il puntatore al figlio sinistro
	return NULL;	//altrimenti ritorno un puntatore vuoto
}


//Ricavo puntatore del il figlio destro (colonna successiva)
TABLEAUptr tableau_minHeap_destro(TABLEAU T_young, int idx_row, int idx_col)	{
	if(idx_col+1 <= *(T_young[0][1]) && T_young[idx_row][idx_col+1])	//se non eccedo col numero di righe
		return T_young[idx_row][idx_col+1];	//ritrono il puntatore al figlio destro
	return NULL;	//altrimenti ritorno un puntatore vuoto
}

//Riordino i valori a salire dalla posizione attuale
void tableau_minHeap_orderPadre(TABLEAU T_young, int idx_row, int idx_col)	{
	TABLEAUptr curr = T_young[idx_row][idx_col];
	TABLEAUptr padre = NULL;
	
	while((idx_row > 1 || idx_col > 1) && (padre = tableau_minHeap_padre(T_young, idx_row, idx_col)) && *(padre) > *(curr))	{
		int tmp = *T_young[idx_row][idx_col];	//mi conservo momentaneamente il valore nella posizione attuale
		tableau_minHeap_swap(curr, padre);
		if(idx_row-1 >= 1 && T_young[idx_row-1][idx_col] && tmp == *(T_young[idx_row-1][idx_col]))	//se il valore conservato è stato posizionato sopra
			curr = T_young[--idx_row][idx_col];	//continuo il controllo dei padri nella riga precedente
		else if(idx_col-1 >= 1 && T_young[idx_row][idx_col-1] && tmp == *(T_young[idx_row][idx_col-1]))	//se il valore conservato è stato posizionato sinistra
			curr = T_young[idx_row][--idx_col];	//continuo il controllo dei padri nella colonna precedente	
	}
}

//Indico fra i due padri chi ha il valore più grande (mi assicuro di mantenere una proprietà transitiva fra i valori da confrontare)
TABLEAUptr tableau_minHeap_padre(TABLEAU T_young, int idx_row, int idx_col)	{
	if((idx_row > 1 && idx_col == 1) || (idx_row > 1 && idx_col > 1 && *(T_young[idx_row-1][idx_col]) > *(T_young[idx_row][idx_col-1])))
		return T_young[idx_row-1][idx_col];	//faccio subito questo return se esiste solo il padre nella riga superiore
	else if((idx_row == 1 && idx_col > 1) || (idx_row > 1 && idx_col > 1 && *(T_young[idx_row-1][idx_col]) <= *(T_young[idx_row][idx_col-1])))
		return T_young[idx_row][idx_col-1]; ///faccio subito questo return se esiste solo il padre nella colonna precedente
	return NULL;
}

//Swap dei valori nei riferimenti
void tableau_minHeap_swap(TABLEAUptr T_ptr_el, TABLEAUptr T_ptr_min) {
    int tmp = *T_ptr_el;
    *T_ptr_el = *T_ptr_min;
    *T_ptr_min = tmp;
}
