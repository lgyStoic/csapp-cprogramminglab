/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    if (!q) {
        return NULL;
    }
    /* What if malloc returned NULL? */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if(!q) return;
    while (q->head) {
        list_ele_t *t = q->head->next;
        free(q->head->value);
        free(q->head);
        q->head = t;
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (!q)
    {
        return false;       
    }
    newh = (list_ele_t *)malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    
    newh->value = (char *)malloc(strlen(s) + 1);
    if(!(newh->value)) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);
    
    newh->next = q->head;
    q->head = newh;
    if (q->size == 0)
    {
        q->tail = newh;
    }
    
    q->size += 1;
    return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
    {
        return false;
    }
    list_ele_t *newt = (list_ele_t*)malloc(sizeof(list_ele_t));
    if(!newt) {
        return false;
    }
    newt->value = (char*)malloc(strlen(s) + 1);
    if(!(newt->value)) {
        free(newt);
        return false;
    }
    strcpy(newt->value, s);
    if (q->size == 0) {
        q->tail = q->head = newt;
    } else {
        q->tail->next = newt;
        q->tail = newt;
        q->tail->next = NULL;
    }
    q->size += 1;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if(!q) {
        return false;
    }
    if (q->size == 0)
    {
        return false;
    }
    
    strncpy(sp, q->head->value, bufsize - 1);
    sp[bufsize - 1] = '\0';
    if (q->size == 1) {
        free(q->head->value);
        free(q->head);
        q->head = q->tail = NULL;
    } else {
        list_ele_t *t = q->head;
        q->head = t->next;
        free(t->value);
        free(t);
    }
    q->size -= 1;
    
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if(!q) return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if(!q) return;
    if (q->size <= 1)
    {
        return;
    }
    list_ele_t *i = q->head->next;
    list_ele_t *rt = q->head;
    while (i != q->tail)
    {
        list_ele_t *t = i->next;
        i->next = q->head;
        q->head = i;
        i = t;
    }
    q->tail->next = q->head;
    q->head = q->tail;
    q->tail = rt;
    rt->next = NULL;
}

