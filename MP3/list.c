/* list.c                  <<-- A template to be updated and 
 * Xiang Ma           <<-- changed
 * harlanr
 * ECE 223 Fall 2014
 * MP2
 *
 * Propose: A template for list.c. You will make many changes.
 *
 * Assumptions: Many details are incomplete.  
 *
 * Bugs: Many details have not been implemented.
 */

/* The interface definition for the two-way linked list ADT is based on one 
 * defined by OPNET, Inc. http://www.opnet.com/
 */
#include <stdlib.h>
#include <assert.h>

#include "datatypes.h"   // defines data_t 
#include "list.h"        // defines public functions for list ADT

/* definitions for private constants used in list.c only */

#define LIST_SORTED    9999
#define LIST_UNSORTED -8888

/* prototypes for private functions used in list.c only */
void list_debug_validate(list_t *L);
void list_sort(list_t **list_ptr, int sort_type);
void Insertion_sort(list_t *list_ptr);
void SelectionSort_I(list_t *A, list_node_t *m, list_node_t *n);
void SelectionSort_R(list_t *A, list_node_t *m, list_node_t *n);
list_node_t *FindMin(list_t *A, list_node_t *m, list_node_t *n);
list_t *MergSort(list_t *list_ptr);
list_t *Merg(list_t *L, list_t *R);

void list_debug_validate(list_t *L);

/* ----- below are the functions  ----- */

/* Obtains a pointer to an element stored in the specified list, at the
 * specified list position
 * 
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from list_construct.
 *
 * pos_index: position of the element to be accessed.  Index starts at 0 at
 *            head of the list, and incremented by one until the tail is
 *            reached.  Can also specify LISTPOS_HEAD and LISTPOS_TAIL
 *
 * return value: pointer to element accessed within the specified list.  A
 * value NULL is returned if the pos_index does not correspond to an element in
 * the list.
 */
data_t * list_access(list_t *list_ptr, int pos_index)
{   

	int count=0;	
    list_node_t *L;

	
    // debugging function to verify that the structure of the list is valid
    //list_debug_validate(list_ptr);

    /* handle special cases.
     *   1.  The list is empty
     *   2.  Asking for the head 
     *   3.  Asking for the tail
     *   4.  specifying a position that is out of range.  This is not defined
     *       to be an error in this function, but instead it is assumed the 
     *       calling function correctly specifies the position index
     */
    if (list_entries(list_ptr) == 0) {
        return NULL;  // list is empty
    }
    else if (pos_index == LISTPOS_HEAD || pos_index == 0) {
        return list_ptr->ll_head->data_ptr;
    }
    else if (pos_index == LISTPOS_TAIL || pos_index == list_entries(list_ptr) - 1) {
        return list_ptr->ll_tail->data_ptr;
    }
    else if (pos_index < 0 || pos_index >= list_entries(list_ptr))
        return NULL;   // does not correspond to position in list

    // loop through the list until find correct position index
    L=list_ptr->ll_head;
    while (L != NULL && count != pos_index) {
        L=L->ll_next;
        count++;
    }
    // already verified that pos_index should be valid so L better not be null
    assert(L != NULL);
    assert(L->data_ptr != NULL);
    return L->data_ptr;
}

/* Allocates a new, empty list 
 *
 * By convention, the list is initially assumed to be sorted.  The field sorted
 * can only take values LIST_SORTED or LIST_UNSORTED
 *
 * Use list_destruct to remove and deallocate all elements on a list 
 * and the header block.
 */
list_t * list_construct(void)
{
    list_t *L;
    L = (list_t *) malloc(sizeof(list_t));
    assert(L != NULL);
    L->ll_head = NULL;
    L->ll_tail = NULL;
    L->ll_entries = 0;
    L->ll_sorted_state = LIST_SORTED;
    //list_debug_validate(L);
    return L;
}

/* Finds an element in a list and returns a pointer to it.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: element against which other elements in the list are compared.
 *           Note: uses the compare function defined in datatypes.h
 *
 * NOTICE: pos_index is returned and is not an input value!
 *
 * pos_index : integer value that is returned with the list index position.
 *
 *   Match is found
 *       return value: pointer to matching data_t element 
 *       pos_index: integer position of matching element
 *
 *   Match is not found
 *       return value: NULL
 *       pos_index:  -1
 */
data_t * list_elem_find(list_t *list_ptr, data_t *elem_ptr, int *pos_index)
{
    //list_debug_validate(list_ptr);

	list_node_t *L = list_ptr -> ll_head;
    *pos_index = 0;
    while(L != NULL){
		if(comp_proc(elem_ptr, L->data_ptr) == 0) return L->data_ptr;
        (*pos_index)++;
		L = L-> ll_next;
    }
    *pos_index = -1;
     return NULL;
}

/* Deallocates the contents of the specified list, releasing associated memory
 * resources for other purposes.
 */
void list_destruct(list_t *list_ptr)
{
    //list_debug_validate(list_ptr);
    list_node_t *N;

    /*
    free(list_ptr -> ll_next);
    free(list_ptr -> ll_head);
    */

    if(list_entries(list_ptr) != 0){
        N = list_ptr -> ll_head -> ll_next ;
        while(N != NULL){
            //N = N -> ll_prev;
            free(N -> ll_prev -> data_ptr);
            N->ll_prev->data_ptr = NULL;
            N->ll_prev->ll_prev = NULL;
            N->ll_prev->ll_next = NULL;
            free(N -> ll_prev);
            N = N -> ll_next;
        }
        N = list_ptr -> ll_tail ; 
        free(N -> data_ptr);
        N -> data_ptr = NULL ;
        N -> ll_prev = NULL;
        free(N);
    }
    list_ptr -> ll_tail = NULL;
    list_ptr -> ll_head =NULL;
    free(list_ptr);
}
	


/* Inserts the specified data element into the specified list at the specified
 * position.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: pointer to the element to be inserted into list.
 *
 * pos_index: numeric position index of the element to be inserted into the 
 *            list.  Index starts at 0 at head of the list, and incremented by 
 *            one until the tail is reached.  Can also specify LISTPOS_HEAD and
 *            LISTPOS_TAIL
 *
 * If pos_index is greater than the number of elements currently in the list, 
 * the element is simply appended to the end of the list (no additional elements
 * are inserted).
 *
 * Note that use of this function results in the list to be marked as unsorted,
 * even if the element has been inserted in the correct position.  That is, on
 * completion of this subroutine the list_ptr->ll_sorted_state must be equal 
 * to LIST_UNSORTED.
 */
void list_insert(list_t *list_ptr, data_t *elem_ptr, int pos_index)
{
    assert(list_ptr != NULL); 
	list_node_t *P;
	
	P = (list_node_t*)malloc(sizeof(list_node_t));
	P -> data_ptr = elem_ptr;
	P -> ll_next = NULL;
	P -> ll_prev = NULL;
    
    if (list_ptr -> ll_entries == 0)
    {
        list_ptr -> ll_head = P; 
        list_ptr -> ll_tail = P;
        
    }
    else if (pos_index >= list_ptr -> ll_entries || pos_index == LISTPOS_TAIL)
    { 
        P -> ll_prev = list_ptr -> ll_tail;
        list_ptr -> ll_tail -> ll_next = P;
        list_ptr -> ll_tail = P;
    }
    else if (pos_index == 0 || pos_index == LISTPOS_HEAD)
    {
        P -> ll_next = list_ptr -> ll_head;
        list_ptr -> ll_head -> ll_prev = P;
        list_ptr -> ll_head = P;         
    }

    else if (pos_index < 0)
        return;
	else 
    {
        list_node_t *N ; 
        N = list_ptr -> ll_head; 
        int count = 0;
        while(N != NULL && count != pos_index)
        {
            N = N -> ll_next ;
            count++;
        }
        P -> ll_next = N ;
        P -> ll_prev =  N -> ll_prev ;
        N -> ll_prev -> ll_next = P;
        N -> ll_prev = P;        
    }
	
    (list_ptr -> ll_entries)++ ;
	
	
    /* the last three lines of this function must be the following */
    if (list_ptr->ll_sorted_state == LIST_SORTED) 
        list_ptr->ll_sorted_state = LIST_UNSORTED;
    //list_debug_validate(list_ptr);
}

/* Inserts the element into the specified sorted list at the proper position,
 * as defined by the compare_proc.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: pointer to the element to be inserted into list.
 *
 * If you use list_insert_sorted, the list preserves its sorted nature.
 *
 * If you use list_insert, the list will be considered to be unsorted, even
 * if the element has been inserted in the correct position.
 *
 * If the list is not sorted and you call list_insert_sorted, this subroutine
 * should generate a system error and the program should immediately stop.
 *
 * The comparison procedure must accept two arguments (A and B) which are both
 * pointers to elements of type data_t.  The comparison procedure returns an
 * integer code which indicates the precedence relationship between the two
 * elements.  The integer code takes on the following values:
 *    1: A should be closer to the list head than B
 *   -1: B should be closer to the list head than A
 *    0: A and B are equal in rank
 *
 * Note: if the element to be inserted is equal in rank to an element already
 *       in the list, the newly inserted element will be placed after all the 
 *       elements of equal rank that are already in the list.
 */
void list_insert_sorted(list_t *list_ptr, data_t *elem_ptr)
{
    assert(list_ptr != NULL);
    assert(list_ptr->ll_sorted_state == LIST_SORTED);

    list_node_t *N;
    N = (list_node_t*)malloc(sizeof(list_node_t));
    N -> data_ptr = elem_ptr;
    N -> ll_next = NULL;
    N -> ll_prev = NULL;

    if(list_entries(list_ptr) == 0){
        list_ptr -> ll_head = N;
        list_ptr -> ll_tail = N;
    }
    
    else if (comp_proc(list_ptr -> ll_tail -> data_ptr , elem_ptr) >= 0){
        N -> ll_prev = list_ptr -> ll_tail;
        list_ptr -> ll_tail -> ll_next = N;
        list_ptr -> ll_tail = N;
    }
    else if(comp_proc(list_ptr -> ll_head -> data_ptr, elem_ptr) == -1){
        N -> ll_next = list_ptr -> ll_head;
        list_ptr -> ll_head -> ll_prev = N;
        list_ptr -> ll_head = N;
    }
    else{
        list_node_t *M;
        M = list_ptr -> ll_head;

        while(M -> ll_next != NULL){
            if(comp_proc(M -> data_ptr, elem_ptr) >=0 && comp_proc(elem_ptr, M -> ll_next -> data_ptr) == 1){
                N -> ll_next = M -> ll_next;
                N -> ll_prev = M;
                M -> ll_next -> ll_prev = N;
                M -> ll_next = N;
                break;
            }
            M = M -> ll_next;
        }
    }
    (list_ptr->ll_entries)++;
    /* the last line checks if the new list is correct */
    //list_debug_validate(list_ptr);
}

/* Removes an element from the specified list, at the specified list position,
 * and returns a pointer to the element.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * pos_index: position of the element to be removed.  Index starts at 0 at
 *            head of the list, and incremented by one until the tail is
 *            reached.  Can also specify LISTPOS_HEAD and LISTPOS_TAIL
 *
 * Attempting to remove an element at a position index that is not contained in
 * the list will result in no element being removed, and a NULL pointer will be
 * returned.
 */
data_t *list_remove(list_t *list_ptr, int pos_index)
{
    data_t *D;
    list_node_t *N;

    if(list_ptr -> ll_entries == 0)
        return NULL;

    else if((pos_index < 0 && pos_index != LISTPOS_TAIL && pos_index != LISTPOS_HEAD) || pos_index >= list_ptr -> ll_entries)
        return NULL;

    else if(list_ptr -> ll_entries == 1 && pos_index == 0){ 
        D = list_ptr->ll_head->data_ptr;
        N = list_ptr->ll_head;
        list_ptr -> ll_head -> data_ptr = NULL;
        list_ptr -> ll_head = NULL;
        list_ptr -> ll_tail =NULL;
    }else if(list_ptr -> ll_entries - 1 == pos_index || pos_index == LISTPOS_TAIL){
        D = list_ptr->ll_tail->data_ptr;
        N = list_ptr->ll_tail;
        list_ptr -> ll_tail -> data_ptr = NULL;
        list_ptr -> ll_tail -> ll_prev -> ll_next = NULL;
        list_ptr -> ll_tail = list_ptr -> ll_tail -> ll_prev;
        N -> ll_prev = NULL;
    }else if(pos_index == 0 || pos_index == LISTPOS_HEAD){
        D = list_ptr->ll_head->data_ptr;
        N = list_ptr -> ll_head;
        list_ptr -> ll_head -> data_ptr = NULL;
        list_ptr -> ll_head -> ll_next -> ll_prev = NULL;
        list_ptr -> ll_head = list_ptr -> ll_head -> ll_next;
        N -> ll_next = NULL;
    }else{
        int i = 0;
        N = list_ptr -> ll_head; 
        D = N -> data_ptr;
        while(N != NULL && i != pos_index)
        {
            N = N -> ll_next;
            D = N -> data_ptr;
            i++;
        }
        N -> ll_prev -> ll_next = N -> ll_next ;
        N -> ll_next -> ll_prev = N -> ll_prev ;
        N -> ll_prev = NULL;
        N -> ll_next = NULL;
    }
    free(N);
    (list_ptr->ll_entries)--;
    //list_debug_validate(list_ptr);
    return D;

}

/* Obtains the length of the specified list, that is, the number of elements
 * that the list contains.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * Returns an integer equal to the number of elements stored in the list.  An
 * empty list has a size of zero.
 */
int list_entries(list_t *list_ptr)
{
    assert(list_ptr != NULL);
    assert(list_ptr->ll_entries >= 0);
    return list_ptr->ll_entries;
}


/*sort by five different ways*/

void Insertion_sort(list_t *list_ptr)
{
    list_t *new_list = NULL;
    new_list = list_construct();
    data_t *D;
    int i = list_ptr -> ll_entries;
    while(i != 0){
        D = list_remove(list_ptr, 0) ;
        list_insert_sorted(new_list,D);
        i--;
    }
    list_ptr -> ll_head = new_list -> ll_head;
    list_ptr -> ll_tail = new_list -> ll_tail;
    list_ptr -> ll_entries = new_list -> ll_entries;
    new_list -> ll_head = NULL;
    new_list -> ll_tail = NULL;
    new_list -> ll_entries = 0;
    free(new_list);
}

list_node_t *FindMin(list_t *A,list_node_t *m, list_node_t*n)
{
    list_node_t *i = m;
    list_node_t *j = m;
    while(i != n)
    {
        i = i -> ll_next;
        if (comp_proc(i -> data_ptr, j -> data_ptr) >= 0) 
            j = i ;
    }
    return j;
}

void SelectionSort_R(list_t *A, list_node_t *m, list_node_t *n)
{
    list_node_t *Minposition = NULL;
    data_t *temp;
    if(m != n){

        Minposition = FindMin(A,m,n);
        temp = m -> data_ptr;
        m -> data_ptr = Minposition -> data_ptr;
        Minposition -> data_ptr = temp;

        SelectionSort_R(A, m -> ll_next,n);
    }
    return;
}    

void SelectionSort_I(list_t *A, list_node_t *m, list_node_t *n)
{
    list_node_t *Minposition = NULL;
    list_node_t *i = NULL;
    data_t *temp;

    while(m != n){
        i = m;
        Minposition = m;

        while(i != n){
            i = i -> ll_next;
            if (comp_proc(i -> data_ptr, Minposition -> data_ptr) >= 0)
                Minposition = i;
        }

        temp = m -> data_ptr;
        m -> data_ptr = Minposition -> data_ptr;
        Minposition -> data_ptr = temp;
        m = m -> ll_next;
    }
return;
}
/*---------------------------*/
/*--------- merge sort ------*/
/*--------------------------*/
list_t *MergSort(list_t *list_ptr)
{
    if(list_ptr -> ll_entries <= 1)
        return list_ptr;
    int i;
    list_t *new_list;
    list_node_t *N = list_ptr -> ll_head;
    for (i = 0; i <  (list_ptr -> ll_entries)/2; i++)
    {
        N = N -> ll_next;
    }
    new_list = list_construct();
    new_list -> ll_entries = list_ptr -> ll_entries - i;
    new_list -> ll_head = N;
    new_list -> ll_tail = list_ptr -> ll_tail;
    list_ptr -> ll_entries = i;
    list_ptr -> ll_tail = N -> ll_prev;
    N -> ll_prev -> ll_next = NULL ;
    N -> ll_prev = NULL;
    return Merg(MergSort(list_ptr), MergSort(new_list));
}

list_t *Merg(list_t *L, list_t *R)
{
    list_t *new_list;
    new_list = list_construct();
    //int pos_index = 0;
/*    int leftPos = 0;
    int rightPos = 0;*/
    while(list_entries(L)!=0 && list_entries(R)!=0){
        if(comp_proc(list_access(L,0), list_access(R,0)) >= 0){
            list_insert(new_list,list_remove(L,0) , LISTPOS_TAIL);

            //list_insert(new_list,list_access(L,leftPos) , LISTPOS_TAIL);
            //leftPos ++;
        }
        else{
            list_insert(new_list,list_remove(R,0),LISTPOS_TAIL);
          //list_insert(new_list,list_access(R,rightPos),LISTPOS_TAIL);
            //rightPos ++;
        }
    }

    if (list_entries(L) == 0)
    {
        while(list_entries(R) != 0){
            list_insert(new_list, list_remove(R, 0), LISTPOS_TAIL);
        }
    }
    else// if(list_entries(R) == 0)
    {
        while(list_entries(L) != 0){
            list_insert(new_list, list_remove(L,0) , LISTPOS_TAIL);
        }
    }

    assert (L -> ll_entries == 0 && R -> ll_entries == 0);
    free(L);
    free(R);
    return new_list;

}


/*void myqsort(data_t ** list_ptr)
{
    int i;
    int Asize = list_entries(list_ptr);

    int j_a = 0;
    int j_b = 0;
    data_t* pivot = list_remove(list_ptr,0.5*Asize);

    data_t ** QsortA = (data_t **) malloc(Asize*sizeof(data_t *));
    data_t ** QsortB = (data_t **) malloc(Asize*sizeof(data_t *));

    for (i = 0; i < Asize; i++) 
    {
        if (comp_proc(pivot,list_access(list_ptr,i))>0)
        {
            QsortA[i] = list_remove(list_ptr, LISTPOS_HEAD);
            j_a++;
        }
        else
        {
            QsortB[i] = list_remove(list_ptr, LISTPOS_HEAD);
            j_b++;
        }
    }

    qsort(QsortA);
    qsort(QsortB);

    for (i = 0; i < Asize; i++) 
    {
        list_insert(list_ptr, QsortA[i], LISTPOS_TAIL);
    }

    list_insert(list_ptr, pivot, LISTPOS_TAIL);
    
    for (i = 0; i < Asize; i++) 
    {
        list_insert(list_ptr, QsortB[i], LISTPOS_TAIL);
    }

    free(QsortA);
    free(QsortB);

}*/


int my_compare(const void *p_a, const void *p_b)
{
    return comp_proc(*(data_t **) p_b, *(data_t **) p_a);
}

/* Comparison function for qsort */

list_t * myqsort(list_t * list_ptr)
{
    int i, Asize = list_entries(list_ptr);
    data_t ** QsortA = (data_t **) malloc(Asize*sizeof(data_t *));

    for (i = 0; i < Asize; i++)
    {
        QsortA[i] = list_remove(list_ptr, 0);//LISTPOS_HEAD
    }
    
    qsort(QsortA, Asize, sizeof(data_t *), my_compare);
    
    for (i = 0; i < Asize; i++)
    {
        list_insert(list_ptr, QsortA[i], LISTPOS_TAIL);
    }
    free(QsortA);
    return list_ptr;
}



void list_sort(list_t **list_ptr, int sort_type){

    if(sort_type ==1)
        Insertion_sort(*list_ptr);
    else if(sort_type == 2)
        SelectionSort_I(*list_ptr,(*list_ptr) -> ll_head, (*list_ptr) -> ll_tail);
    else if(sort_type == 3)
        SelectionSort_R(*list_ptr,(*list_ptr) -> ll_head, (*list_ptr) -> ll_tail);
    else if(sort_type == 4)
        *list_ptr = MergSort(*list_ptr);
    else if(sort_type == 5)
        *list_ptr = myqsort(*list_ptr);

    (*list_ptr) -> ll_sorted_state = LIST_SORTED;
    //list_debug_validate(* list_ptr);
    return;


}





/* This function verifies that the pointers for the two-way linked list are
 * valid, and that the list size matches the number of items in the list.
 *
 * If the linked list is sorted it also checks that the elements in the list
 * appear in the proper order.
 *
 * The function produces no output if the two-way linked list is correct.  It
 * causes the program to terminate and print a line beginning with "Assertion
 * failed:" if an error is detected.
 *
 * The checks are not exhaustive, so an error may still exist in the
 * list even if these checks pass.
 *
 * YOU MUST NOT CHANGE THIS FUNCTION.  WE USE IT DURING GRADING TO VERIFY THAT
 * YOUR LIST IS CONSISTENT.
 */
void list_debug_validate(list_t *L)
{
    list_node_t *N;
    int count = 0;
    assert(L != NULL);
    if (L->ll_head == NULL)
        assert(L->ll_tail == NULL && L->ll_entries == 0);
    if (L->ll_tail == NULL)
        assert(L->ll_head == NULL && L->ll_entries == 0);
    if (L->ll_entries == 0)
        assert(L->ll_head == NULL && L->ll_tail == NULL);
    assert(L->ll_sorted_state == LIST_SORTED || L->ll_sorted_state == LIST_UNSORTED);

    if (L->ll_entries == 1) {
        assert(L->ll_head == L->ll_tail && L->ll_head != NULL);
        assert(L->ll_head->ll_next == NULL && L->ll_head->ll_prev == NULL);
        assert(L->ll_head->data_ptr != NULL);
    }
    if (L->ll_head == L->ll_tail && L->ll_head != NULL)
        assert(L->ll_entries == 1);
    if (L->ll_entries > 1) {
        assert(L->ll_head != L->ll_tail && L->ll_head != NULL && L->ll_tail != NULL);
        N = L->ll_head;
        assert(N->ll_prev == NULL);
        while (N != NULL) {
            assert(N->data_ptr != NULL);
            if (N->ll_next != NULL) assert(N->ll_next->ll_prev == N);
            else assert(N == L->ll_tail);
            count++;
            N = N->ll_next;
        }
        assert(count == L->ll_entries);
    }
    if (L->ll_sorted_state == LIST_SORTED && L->ll_head != NULL) {
        N = L->ll_head;
        while (N->ll_next != NULL) {
            assert(comp_proc(N->data_ptr, N->ll_next->data_ptr) != -1);
            N = N->ll_next;
        }
    }
}

/* commands for vim. ts: tabstop, sts: softtabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
