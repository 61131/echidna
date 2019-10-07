#ifndef _TREE_H
#define _TREE_H


#include <stdlib.h>

#include <macros.h>


#define TREE_PATH_MAX           (128)

#define tree_destroy(...)       _tree_destroy(_NARG(__VA_ARGS__), __VA_ARGS__)

#define tree_initialise(...)    _tree_initialise(_NARG(__VA_ARGS__), __VA_ARGS__)

#define tree_insert(...)        _tree_insert(_NARG(__VA_ARGS__), __VA_ARGS__)

#define tree_node_destroy(...)  _tree_node_destroy(_NARG(__VA_ARGS__), __VA_ARGS__)


typedef int (*_TREE_COMPARE)(void *A, void *B);

typedef void (*_TREE_DESTROY)(void *Arg);

typedef struct _TREE_NODE {

    int Direction;

    struct _TREE_NODE * Node[2];

    void * Data;
}
TREE_NODE;

typedef struct _TREE {

    struct _TREE_NODE * Root;

    _TREE_COMPARE Compare;

    _TREE_DESTROY Destroy;

    size_t Size;

    uint8_t Alloc;
}
TREE;

typedef struct _TREE_ITER {

    TREE * Tree;

    TREE_NODE * Node;

    TREE_NODE * Path[TREE_PATH_MAX];

    size_t Top;
}
TREE_ITER;


void _tree_destroy(size_t Arg, TREE *Tree, ...);

void _tree_initialise(size_t Arg, TREE *Tree, ...);

int _tree_insert(size_t Arg, TREE *Tree, ...);

void * tree_iterate(TREE_ITER *Iter);

void * tree_iterate_first(TREE_ITER *Iter, TREE *Tree);

void * tree_iterate_last(TREE_ITER *Iter, TREE *Tree);

void * tree_iterate_next(TREE_ITER *Iter);

void tree_iterate_reset(TREE_ITER *Iter, TREE *Tree);

TREE_ITER * tree_iterate_new(TREE *Tree);

void * tree_iterate_previous(TREE_ITER *Iter);

TREE * tree_new(void);

int tree_remove(TREE *Tree, void *Data);

void * tree_search(TREE *Tree, void *Data);


#endif  /* _TREE_H */


