/* soc_support.c
 * Xiang Ma          <<-- many updates required including your name
 * xiangm
 * ECE 223 Fall 2014 
 * MP2
 *
 * Version 2: fixed bugs in soc_sorted_insert
 *
 * Propose: A template for MP2 
 *
 * Assumptions: suggested structure definitions and public functions 
 *              as defined for assignmnet.  
 *
 *              You must change this file for your design.
 *
 *              I have provided prototypes of some of the functions
 *              and you CANNOT change these prototypes
 *
 *              However, you must add additional functions to handle
 *              operations on the list with unsorted sockets.
 *
 * Bugs:
 *
 * You must change this file for your design.
 *
 * (You CANNOT modify any of the details of the list.h interface, or use any 
 *  of the private variables outside of list.c.)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "datatypes.h"
#include "list.h"
#include "soc_support.h"

#define MAXLINE 256

/* soc_compare is required by the list ADT for sorted lists. 
 *
 * This function returns 
 *     1 if rec_a should be closer to the head than rec_b,
 *    -1 if rec_b is to be considered closer to the head, and 
 *     0 if the records are equal.
 *
 * For the socket data we want to sort from lowest ID up, so
 * closer to the front means a smaller ID.
 *
 * The function expects pointers to two record structures, and it is an error
 * if either is NULL
 *
 * THIS FUNCTION SHOULD NOT BE CHANGED
 */
int soc_compare(socket_t *soc_a, socket_t *soc_b)
{
    assert(soc_a != NULL && soc_b != NULL);
    if (soc_a->socket_id < soc_b->socket_id)
	return 1;
    else if (soc_a->socket_id > soc_b->socket_id)
	return -1;
    else
	return 0;
}

/* This creates a list and it can be either a sorted or unsorted list
 */
list_t *soc_create()
{
    return list_construct();
}

/* this function frees the memory for either a sorted or unsorted list.
 */
void soc_cleanup(list_t *list_ptr)
{
    list_destruct(list_ptr);
}

/* Return the number of items in the list.  A list and it can be either 
 * a sorted or unsorted list
 */
int soc_number_entries(list_t *list_ptr)
{
    return list_entries(list_ptr);
}

socket_t *soc_access(list_t *list_ptr, int pos_index)
{
    return list_access(list_ptr, pos_index);
}


/* This function adds the structure to the list in sorted order.
 * If the new structure has the same socket_id as an
 * element in the list, then the new structure is placed after 
 * all sockets with the same id.
 */
void soc_sorted_insert(list_t *list_ptr, socket_t *socket)
{
    list_insert_sorted(list_ptr,socket);
}

/* This function looks for the first structure with the matching socket_id 
 * in the sorted list.  Or, null is returned if the element is not found 
 * in the list.
 */
socket_t *soc_sorted_lookup(list_t *list_ptr, int id)
{
    socket_t *rec_ptr = NULL;
    socket_t *D = NULL;
    int pos = -2;
    D = (socket_t *)malloc(sizeof(socket_t));
    D -> socket_id = id;
    rec_ptr = list_elem_find(list_ptr,D,&pos);
    free(D);
    return rec_ptr;
}

/* This function removes the first structure from the sorted list with the 
 * matching socket_id
 */
socket_t *soc_sorted_remove(list_t *list_ptr, int id)
{
    socket_t *D = NULL;
    int pos = -2;
    D = (socket_t *)malloc(sizeof(socket_t));
    D -> socket_id = id;
    list_elem_find(list_ptr,D,&pos);
    free(D);
    if (pos == -1){
        return NULL;
        printf ("do not find \n");
    }
    return list_remove(list_ptr, pos);
}

/* This function replaces the structure from the sorted list with the matching
 * socket_id.  If there are multiple records with the same socket_id, 
 * the first record is the one updated with the new information.
 */
socket_t *soc_sorted_update(list_t *list_ptr, socket_t *socket)
{
    socket_t *rec_ptr = NULL;
    int pos = -2;
    rec_ptr = list_elem_find(list_ptr,socket,&pos);
    if(rec_ptr == NULL) return NULL;

    rec_ptr = list_remove(list_ptr, pos);
    list_insert_sorted(list_ptr, socket);

    return rec_ptr;

}

/* Prompts user for socket ID and then calls another function
 * to fill in the remaining details of the record.
 *
 * The input to the function assumes that the structure has already been
 * created.  
 *
 * There is no output.
 */
void soc_get_socket_id(socket_t *new)
{
    char line[MAXLINE];
    assert(new != NULL);

    printf("Socket ID:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->socket_id);

    soc_fill_record(new);
}

int soc_unsorted_insert(list_t *list_ptr, socket_t *socket, int pos_index)
{
    int n = list_entries(list_ptr);

    list_insert(list_ptr, socket, pos_index);

    if (n < list_entries(list_ptr)) return 0;
    if (n == list_entries(list_ptr)) return -1;

    return -2;
}

socket_t *soc_unsorted_remove(list_t *list_ptr, int id)
{
    return list_remove(list_ptr, id);
}

socket_t *soc_unsorted_replace(list_t *list_ptr, socket_t *socket, int pos_index)
{
    socket_t *rec_ptr = NULL;

    rec_ptr = list_remove(list_ptr, pos_index);
    if (rec_ptr == NULL) return NULL;

    list_insert(list_ptr, socket, pos_index);
    return rec_ptr;
}

void soc_sort(list_t *list_ptr, int sort_type)
{
    list_sort(list_ptr, sort_type);
}

/* Prompts user for record input starting with the Socket ID.
 * The input is not checked for errors but will default to an acceptable value
 * if the input is incorrect or missing.
 *
 * The input to the function assumes that the structure has already been
 * created.  The contents of the structure are filled in.
 *
 * There is no output.
 */
void soc_fill_record(socket_t *new)
{
    char line[MAXLINE];
    assert(new != NULL);

    printf("Dest IP address:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->dest_ip_addr);
    printf("Source IP address:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->src_ip_addr);
    printf("Dest port number:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->dest_port_num);
    printf("Source port number:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->src_port_num);
    printf("Protocol (TCP|UDP|SSL|RTP):");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->protocol);
    printf("Address family (IPv4|IPv6):");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->address_family);
    printf("State (EST|CLOSE_WAIT|CLOSED):");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->state);
    printf("Data rate:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%f", &new->data_rate);
    printf("Time received (int):");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->time_received);
    printf("\n");
}

/* print the information for a particular Socket record 
 *
 * Input is a pointer to a record, and no entries are changed.
 *
 */
void soc_print_socket_rec(socket_t *socket)
{
    assert(socket != NULL);
    printf("Socket id: %d", socket->socket_id);
    printf(" Dest: %d, Src: %d, Dport: %d,", socket->dest_ip_addr, 
            socket->src_ip_addr, socket->dest_port_num);
    printf(" Src: %d,", socket->src_port_num); 
    printf(" Prot: %d, Fam: %d, St: %d", socket->protocol, 
            socket->address_family, socket->state);
    printf(" Rt: %g", socket->data_rate);
    printf(" Tm: %d\n", socket->time_received);
}
/*
int soc_find_id(list_t *list_ptr,int pos)
{
    int i;
    socket_t *rec_ptr = NULL;
    for (i = 0;i <= pos; i++)
    {

    }
    return 
}
*/
/* commands specified to vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
