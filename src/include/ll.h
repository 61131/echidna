#ifndef _LL_H
#define _LL_H

#ifdef _MSC_VER
#include <stdlib.h>
#else
#include <pthread.h>
#endif
#include <macros.h>


#define ll_copy(...)            _ll_copy(_NARG(__VA_ARGS__), __VA_ARGS__)

#define ll_delete(...)          _ll_delete(_NARG(__VA_ARGS__), __VA_ARGS__)

#define ll_destroy(...)         _ll_destroy(_NARG(__VA_ARGS__), __VA_ARGS__)

#define ll_initialise(...)      _ll_initialise(_NARG( __VA_ARGS__ ), __VA_ARGS__)

#define ll_merge(...)           _ll_merge(_NARG(__VA_ARGS__), __VA_ARGS__)


typedef void (*LL_DESTROY)(void *pArg);

struct _LLE;

typedef struct _LLE {

    struct _LL * List;

    struct _LLE * Next;
    
    struct _LLE * Previous;
    
    void * Data;
}
LLE;

typedef struct _LL {
    
    LL_DESTROY Destroy;
    
    LLE * Head;
    
    LLE * Tail;
    
    LLE * Item;
    
    size_t Size;
    
    uint8_t Alloc;
#ifdef _MSC_VER
    void* Lock;
#else
    pthread_rwlock_t Lock;
#endif
}
LL;

typedef struct _LL_ITER {
    
    LLE * Item;
    
    LLE * Next;
}
LL_ITER;


int _ll_copy(size_t Arg, LL *List, ...);

void _ll_delete(size_t Arg, LLE *Element, ...);

void _ll_destroy(size_t Arg, LL *List, ...);

int _ll_initialise(size_t Arg, LL *List, ...);

int _ll_merge(size_t Arg, LL *List, ...);

int ll_insert(LL *List, void *Data);

int ll_insert_head(LL *List, void *Data);

int ll_insert_tail(LL *List, void *Data);

void * ll_iterate(LL *List);

void * ll_iterate_first(LL_ITER *Iter, LL *List);

void * ll_iterate_last(LL_ITER *Iter, LL *List);

void * ll_iterate_next(LL_ITER *Iter);

void * ll_iterate_previous(LL_ITER *Iter );

LL * ll_new(void);

void ll_reset(LL * List);


#endif  /* _LL_H */


