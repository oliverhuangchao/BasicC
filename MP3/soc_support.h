/* soc_support.h
 * Xiang Ma        <<-- MANY changes needed including your name
 * harlanr
 * ECE 223 Fall 2014 
 * MP2
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
 *              All functions in this file must start with the prefix
 *              soc_
 *
 * Bugs:
 *
 * You must change this file for your design.
 *
 * (You CANNOT modify any of the details of the list.h interface, or use any 
 *  of the private variables outside of list.c.)
 */

/* prototype function definitions */

int soc_compare(socket_t *soc_a, socket_t *soc_b);

list_t *soc_create();
void soc_cleanup(list_t *);
int soc_number_entries(list_t *);
socket_t *soc_access(list_t *, int);

void soc_sorted_insert(list_t *, socket_t *);
socket_t *soc_sorted_lookup(list_t *, int);
socket_t *soc_sorted_remove(list_t *, int);
socket_t *soc_sorted_update(list_t *, socket_t *);

int soc_unsorted_insert(list_t *, socket_t *, int);
socket_t *soc_unsorted_remove(list_t *, int);
socket_t * soc_unsorted_replace(list_t *, socket_t *, int);

void soc_get_socket_id(socket_t *);
void soc_fill_record(socket_t *);
void soc_print_socket_rec(socket_t *);
void soc_sort(list_t **, int);

/* commands specified to vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
