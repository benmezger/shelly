#include <stdio.h>
#include <stdlib.h>

#include "array.h"

struct node *new_node(void *data, struct node *next){
    struct node *rv = malloc(sizeof *rv);
    if (rv){
        rv->data = data;
        rv->next = next;
    }
    return rv;
}

struct node *append(struct node_list *list, void *data){
    return insert_before(list, list->tail, data);
}

struct node_list *new_list(int has_dummy_head, int has_dummy_tail){
    struct node_list *list = malloc(sizeof *list);

    if (list){
        struct node *tail = has_dummy_tail ? new_node(NULL, NULL) : NULL;
        if (has_dummy_head && tail == NULL){
            /* Release the list if a dummy couldn't be allocated */
            free(list);
            list = NULL;
        }
        else {
            list->head = has_dummy_head ? new_node(NULL, tail) : NULL;
            list->tail = tail;

            list->has_dummy_head = has_dummy_head;
            list->has_dummy_tail = has_dummy_tail;

            list->size = 0;

            if (has_dummy_head && list->head == NULL){
                /* Release the list if a dummy couldn't be allocated */
                free(list);
                list = NULL;
            }
        }
    }
    return list;
}

struct node *insert_after(struct node_list *list, struct node *pos, void *data){
    struct node *rv = NULL;

    if (list != NULL && pos != NULL){
        if (pos != list->tail){
            /* Create a new node and set the next link */
            rv = new_node(data, pos->next);
            if (rv != NULL){
                pos->next = rv;
                ++list->size;
            }
        }
        else {
            rv = insert_before(list, pos, data);
        }
    }
    return rv;
}

struct node *insert_before(struct node_list *list, struct node *pos, void *data){
    struct node *rv = NULL;

    if (list != NULL && pos != NULL){
        if (pos != list->head){
            /* Find the previous node */
            struct node *it = list->head;
            while (it->next != pos)
                it = it->next;

            /* Create a new node and set the next link */
            rv = new_node(data, it->next);

            if (rv != NULL){
                it->next = rv;
                ++list->size;
            }
        }
        else {
            rv = insert_after(list, pos, data);
        }
    }
    return rv;
}

struct node *delete_node(struct node_list *list, struct node *pos){
    struct node *rv = NULL;
    if (list != NULL && pos != NULL){
        struct node *it = list->head;
        struct node *prev = NULL;

        /* Shift the head by one if removing the dummy */
        if (pos == list->head)
            pos = pos->next;

        /* find the previous node and its previous node */
        while (it->next != pos){
            prev = it;
            it = it->next;
        }

        if (pos != list->tail){
            /* remove the selected node */
            rv = pos;
            it->next = rv->next;
            rv->next = NULL;
            --list->size;
        }
        else if (it != list->head){
            /* remove the node before the tail */
            rv = it;
            prev->next = rv->next;
            rv->next = NULL;
            --list->size;
        }
        else {
            /* list is empty */
            ;;
        }
    }
    return rv;
}

int has_data(struct node_list *list, void *data, int (*cmp_func)(struct node *, void *)){
    if (list->size == 0)
        return 0;

    struct node *it = list->head;
    while (it->next != NULL){
        if (cmp_func(it, data)){
            return 1;
        }
        it = it->next;
    }
    return 0;
}
