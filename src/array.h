#ifndef ARRAY_H
#define ARRAY_H

struct node {
    void *data;
    struct node *next;
};

struct node_list {
    struct node *head;
    struct node *tail;
    int  size;
    int has_dummy_head;
    int has_dummy_tail;
};

/*
 * new_node(void *data, struct node *next);
 *
 * Creates a new node with the given data and links
 * Returns a pointer to the new node or NULL on error
 */
struct node *new_node(void *, struct node *);


/*
 * new_list(int has_dummy_head, int has_dummy_tail)
 *
 * Creates a new list with an optional dummy head and tail
 * Returns a pointer to the new created list, or NULL on error
 */
struct node_list *new_list(int, int);

/*
 * insert_after(struct node_list *list, struct node *pos, void *data)
 *
 * Insert a new node after the given node
 * Returns a pointer to the new node or NULL on error
 */
struct node *insert_after(struct node_list *, struct node *, void *);

/*
 * insert_before(struct node_list *list, struct node *pos, void *data)
 *
 * Insert a new node before the given node
 * Returns a pointer to the new node or NULL on error
 */
struct node *insert_before(struct node_list *, struct node *, void *);

/*
 * remove_node(sturct node_list *list, struct node *pos)
 *
 * Removes the selected node
 * Returns the removed node or NULL on error
 */
struct node *remove_node(struct node_list *, struct node *);

/*
 * has_data(struct node *list, void *data, int (*func)(struct node *, void *))
 *
 * Checks if given data exists in list, the *func is a comparative function passed by argument
 * which needs to receive a node as an argument and a data.
 * Func should return 1 if cmp(node->data, data) is equal or 0 if not.
 * Returns and integer specifying if list has the data or not.
 */
int has_data(struct node_list *, void *, int (*)(struct node *, void *));

/*
 * append(struct node_list *list, void *data){
 *
 * Appends the data to the end of the list
 * Returns the new node appended.
 */
struct node *append(struct node_list *, void *);


#endif
