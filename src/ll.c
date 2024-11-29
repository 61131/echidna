#ifdef _MSC_VER
#include <Windows.h>
#endif
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <ll.h>


static LLE * _ll_new_element(LL *List);


static LLE *
_ll_new_element(LL *List) {
    LLE *pElement;

    errno = 0;
    if((pElement = (LLE *) calloc(1, sizeof(*pElement))) == NULL) 
        return NULL;
    pElement->List = List;
    pElement->Next = pElement->Previous = NULL;
    pElement->Data = NULL;
    return pElement;
}


int
_ll_copy(size_t Arg, LL *List, ...) {
    LL *pList;
    LL_ITER sIter;
    va_list sArg;
    void *pData;
    int nResult;

    if(Arg < 2) {
        errno = EINVAL;
        return -1;
    }

    va_start(sArg, List);
    while(Arg-- > 1) {
        pList = (LL *) va_arg(sArg, LL *);
        if((pList == NULL) ||
                (pList->Head == NULL))
            continue;

#ifdef _MSC_VER
        EnterCriticalSection(pList->Lock);
#else
        if((nResult = pthread_rwlock_rdlock(&pList->Lock)) != 0)
            goto error;
#endif
        for(pData = ll_iterate_first(&sIter, pList);
                pData;
                pData = ll_iterate_next(&sIter))
            ll_insert(List, pData);

#ifdef _MSC_VER
        LeaveCriticalSection(pList->Lock);
#else
        pthread_rwlock_unlock(&pList->Lock);
#endif
    }
    va_end(sArg);
    nResult = 0;
#ifndef _MSC_VER
error:
#endif
    return nResult;
}


void
_ll_delete(size_t Arg, LLE *Element, ...) {
    LL_DESTROY pDestroy;
    LL *pList;
    LLE *pNext, *pPrevious;
    va_list sArg;
    void **pValue;
#ifndef _MSC_VER
    int nResult;
#endif

    assert(Element != NULL);
    assert(Element->List != NULL);

    if(Arg > 1) {
        va_start(sArg, Element);
        pValue = (void **) va_arg(sArg, void **);
        va_end(sArg);
    }
    else
        pValue = NULL;

    pList = Element->List;
#ifdef _MSC_VER
    EnterCriticalSection(pList->Lock);
#else
    if(((nResult = pthread_rwlock_wrlock(&pList->Lock)) != 0) &&
            (nResult != EDEADLK))
        return;
#endif
    pDestroy = pList->Destroy;

    pNext = Element->Next;
    pPrevious = Element->Previous;
    if(pPrevious != NULL)
        pPrevious->Next = pNext;
    if(pNext != NULL)
        pNext->Previous = pPrevious;
    if(pList->Head == Element)
        pList->Head = pNext;
    if(pList->Tail == Element)
        pList->Tail = pPrevious;
    assert(pList->Size > 0);
    --pList->Size;

#ifdef _MSC_VER
    LeaveCriticalSection(pList->Lock);
#else
    pthread_rwlock_unlock(&pList->Lock);
#endif
    if(pValue != NULL)
        *pValue = Element->Data;
    else if(pDestroy != NULL) 
        pDestroy(Element->Data);

    free(Element);
}


void 
_ll_destroy(size_t Arg, LL *List, ...) {
    LL_DESTROY pDestroy;
    LLE *pElement, *pNext;
    va_list sArg;
#ifndef _MSC_VER
    int nResult;
#endif

    pDestroy = List->Destroy;
    if(Arg > 1) {
        va_start( sArg, List );
        pDestroy = (LL_DESTROY) va_arg(sArg, LL_DESTROY);
        va_end(sArg);
    }

#ifdef _MSC_VER
    if (List->Lock)
    {
      EnterCriticalSection(List->Lock);
#else
    if (((nResult = pthread_rwlock_wrlock(&List->Lock)) != 0) &&
      (nResult != EDEADLK))
      return;
#endif
    for (pElement = List->Head; pElement; pElement = pNext) {
      pNext = pElement->Next;
      if (pDestroy) {
        (pDestroy)(pElement->Data);
      }
      free(pElement);
    }
    List->Head = List->Tail = List->Item = NULL;
    List->Size = 0;
#ifdef _MSC_VER
    LeaveCriticalSection(List->Lock);
    DeleteCriticalSection(List->Lock);
    free(List->Lock);
    List->Lock = NULL;
    }
#else
    pthread_rwlock_unlock(&List->Lock);
    pthread_rwlock_destroy(&List->Lock);
#endif
    if(List->Alloc) 
        free(List);
}


int
_ll_initialise(size_t Arg, LL *List, ...) {
    va_list sArg;
#ifndef _MSC_VER
    int nResult;
#endif

    List->Head = List->Tail = NULL;
    List->Item = NULL;
    List->Size = 0;
    List->Alloc = 0;
#ifdef _MSC_VER
    List->Lock = malloc(sizeof(CRITICAL_SECTION));
    if(!List->Lock)
    {
        return 1;
    }
    InitializeCriticalSection(List->Lock);
#else
    if((nResult = pthread_rwlock_init(&List->Lock, NULL)) != 0)
        return nResult;
#endif
    if(Arg > 1) {
        va_start(sArg, List);
        List->Destroy = va_arg(sArg, LL_DESTROY);
        va_end(sArg);
    }
    return 0;
}


int
_ll_merge(size_t Arg, LL *List, ...) {
    LL *pList;
    va_list sArg;
    int nResult;

    if(Arg < 2) {
        errno = EINVAL;
        return -1;
    }

#ifdef _MSC_VER
    EnterCriticalSection(List->Lock);
#else
    if(((nResult = pthread_rwlock_wrlock(&List->Lock)) != 0) &&
            (nResult != EDEADLK))
        return nResult;
#endif
    va_start(sArg, List);
    while(Arg-- > 1) {
        if((pList = (LL *) va_arg(sArg, LL *)) == NULL)
            continue;

#ifdef _MSC_VER
        EnterCriticalSection(List->Lock);
#else
        if(((nResult = pthread_rwlock_wrlock(&pList->Lock)) != 0) &&
                (nResult != EDEADLK))
            goto error;
#endif
        if(List->Head == NULL) {
            List->Head = pList->Head;
            List->Tail = pList->Tail;
        }
        else {
            List->Tail->Next = pList->Head;
            pList->Head->Previous = List->Tail;
            List->Tail = pList->Tail;
        }
        List->Size += pList->Size;

        /*
            The following is an important step which renders the original list structure 
            as effectively useless - This is so that there is only a single "owner" of 
            list elements that have been merged into the first list.
        */

        pList->Head = pList->Tail = pList->Item = NULL;
        pList->Size = 0;
#ifdef _MSC_VER
        LeaveCriticalSection(List->Lock);
#else
        pthread_rwlock_unlock(&pList->Lock);
#endif
        ll_destroy(pList);
    }
    va_end(sArg);
    nResult = 0;

#ifdef _MSC_VER
    LeaveCriticalSection(List->Lock);
#else
error:
    pthread_rwlock_unlock(&List->Lock);
#endif
    return nResult;
}


int
ll_insert(LL *List, void *Data) {
    return ll_insert_tail(List, Data);
}


int 
ll_insert_head(LL *List, void *Data) {
    LLE *pElement;
    int nResult;

#ifdef _MSC_VER
    EnterCriticalSection(List->Lock);
#else
    if(((nResult = pthread_rwlock_wrlock(&List->Lock)) != 0) &&
            (nResult != EDEADLK)) 
        return nResult;
#endif   
    if((pElement = _ll_new_element(List)) == NULL) {
        nResult = -1;
        goto error;
    }
    pElement->Data = Data;

    if(List->Head == NULL) {
        List->Head = pElement;
        List->Tail = pElement;
    }
    else {
        pElement->Next = List->Head;
        List->Head->Previous = pElement;
        List->Head = pElement;
    }
    ++List->Size;
    nResult = 0;

error:
#ifdef _MSC_VER
    LeaveCriticalSection(List->Lock);
#else
    pthread_rwlock_unlock(&List->Lock);
#endif
    return nResult;
}


int
ll_insert_tail(LL *List, void *Data) {
    LLE *pElement;
    int nResult;

#ifdef _MSC_VER
    EnterCriticalSection(List->Lock);
#else
    if(((nResult = pthread_rwlock_wrlock(&List->Lock)) != 0) &&
            (nResult != EDEADLK)) 
        return nResult;
#endif   
    if((pElement = _ll_new_element(List)) == NULL) {
        nResult = -1;
        goto error;
    }
    pElement->Data = Data;

    if(List->Head == NULL) {
        List->Head = pElement;
        List->Tail = pElement;
    }
    else {
        pElement->Previous = List->Tail;
        List->Tail->Next = pElement;
        List->Tail = pElement;
    }
    ++List->Size;
    nResult = 0;

error:
#ifdef _MSC_VER
    LeaveCriticalSection(List->Lock);
#else
    pthread_rwlock_unlock(&List->Lock);
#endif
    return nResult;
}


void *
ll_iterate(LL *List) {
    LLE *pLLE;

    if(List->Item == NULL)
        return NULL;
    pLLE = List->Item;
    List->Item = pLLE->Next;
    return pLLE->Data;
}


void *
ll_iterate_first(LL_ITER *Iter, LL *List) {
    Iter->Item = List->Head;
    Iter->Next = NULL;
    if(Iter->Item == NULL)
        return NULL;
    Iter->Next = Iter->Item->Next;
    return Iter->Item->Data;
}


void *
ll_iterate_last(LL_ITER *Iter, LL *List) {
    Iter->Item = List->Tail;
    Iter->Next = NULL;
    if(Iter->Item == NULL)
        return NULL;
    Iter->Next = Iter->Item->Previous;
    return Iter->Item->Data;
}


void *
ll_iterate_next(LL_ITER *Iter) {
    Iter->Item = Iter->Next;
    Iter->Next = NULL;
    if(Iter->Item == NULL)
        return NULL;
    Iter->Next = Iter->Item->Next;
    return Iter->Item->Data;
}


void *
ll_iterate_previous(LL_ITER *Iter) {
    Iter->Item = Iter->Next;
    Iter->Next = NULL;
    if(Iter->Item == NULL)
        return NULL;
    Iter->Next = Iter->Item->Previous;
    return Iter->Item->Data;
}


LL *
ll_new(void) {
    LL *pList;

    errno = 0;
    if((pList = (LL *) calloc(1, sizeof(*pList))) == NULL) 
        return NULL;
    if(ll_initialise(pList) != 0) {
        free(pList);
        return NULL;
    }
    pList->Alloc = 1;
    return pList;
}


void
ll_reset(LL *List) {
    List->Item = List->Head;
}

