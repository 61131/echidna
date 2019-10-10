#include <string.h>
#include <errno.h>
#include <assert.h>

#include <log.h>
#include <tree.h>


static int _tree_compare(void *A, void *B);

static void * _tree_iterate(TREE_ITER *It, int Direction);

static void * _tree_iterate_start(TREE_ITER *It, TREE *Tree, int Direction);

static void _tree_node_destroy(size_t Arg, TREE_NODE *Node, ...);

static TREE_NODE * _tree_node_new(void);

static int _tree_direction(TREE_NODE *Node);

static TREE_NODE * _tree_rotate1(TREE_NODE *Node, int Direction);

static TREE_NODE * _tree_rotate2(TREE_NODE *Node, int Direction);


static int
_tree_compare(void *A, void *B) {
    return (A > B) - (A < B);
}


static void *
_tree_iterate(TREE_ITER *Iter, int Direction) {
    TREE_NODE *pNode;

    if(Iter->Node->Node[Direction] != NULL) {
        Iter->Path[Iter->Top++] = Iter->Node;
        Iter->Node = Iter->Node->Node[Direction];
        while(Iter->Node->Node[!Direction] != NULL) {
            Iter->Path[Iter->Top++] = Iter->Node;
            Iter->Node = Iter->Node->Node[!Direction];
        }
    }
    else {
        pNode = NULL;
        do {
            if(Iter->Top == 0) {
                Iter->Node = NULL;
                break;
            }
            pNode = Iter->Node;
            Iter->Node = Iter->Path[--Iter->Top];
        }
        while(pNode == Iter->Node->Node[Direction]);
    }
    return (Iter->Node != NULL) ? Iter->Node->Data : NULL;
}


static void *
_tree_iterate_start(TREE_ITER *Iter, TREE *Tree, int Direction) {
    Iter->Tree = Tree;
    Iter->Node = Tree->Root;
    Iter->Top = 0;

    if(Iter->Node != NULL) {
        while(Iter->Node->Node[Direction] != NULL) {
            Iter->Path[Iter->Top++] = Iter->Node;
            Iter->Node = Iter->Node->Node[Direction];
        }
    }
    return (Iter->Node != NULL) ? Iter->Node->Data : NULL;
}


static void 
_tree_node_destroy( size_t uArg, TREE_NODE *pNode, ... ) {
    _TREE_DESTROY pDestroy;
    va_list sArg;

    assert(pNode != NULL);
    if(uArg > 1) {
        va_start(sArg, pNode);
        pDestroy = va_arg(sArg, _TREE_DESTROY);
        if(pDestroy)
            pDestroy(pNode->Data);
        va_end(sArg);
    }
    free(pNode);
}


static TREE_NODE *
_tree_node_new(void) {
    TREE_NODE *pNode;

    errno = 0;
    if((pNode = calloc(1, sizeof(*pNode))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    pNode->Direction = 1;
    pNode->Node[0] = pNode->Node[1] = NULL;
    pNode->Data = NULL;

    return pNode;
}


static int 
_tree_direction(TREE_NODE *Node) {
    return (Node != NULL) ? Node->Direction : 0;
}


static TREE_NODE * 
_tree_rotate1(TREE_NODE *Node, int Direction) {
    TREE_NODE *pResult;
    int nInverse;

    pResult = NULL;
    nInverse = (Direction == 0);
    if(Node != NULL) {
        pResult = Node->Node[nInverse];
        Node->Node[nInverse] = pResult->Node[Direction];
        pResult->Node[Direction] = Node;
        Node->Direction = 1;
        pResult->Direction = 0;
    }
    return pResult;
}


static TREE_NODE *
_tree_rotate2(TREE_NODE *Node, int Direction) {
    TREE_NODE *pResult;
    int nInverse;

    pResult = NULL;
    nInverse = (Direction == 0);
    if(Node != NULL) {
        Node->Node[nInverse] = _tree_rotate1(Node->Node[nInverse], nInverse);
        pResult = _tree_rotate1(Node, Direction);
    }
    return pResult;
}


void 
_tree_destroy(size_t Arg, TREE *Tree, ...) {
    _TREE_DESTROY pDestroy;
    TREE_NODE *pN, *pNode;
    va_list sArg;

    if(Tree == NULL)
        return;
    pDestroy = Tree->Destroy;
    if(Arg > 1) {
        va_start(sArg, Tree);
        pDestroy = va_arg(sArg, _TREE_DESTROY);
        va_end(sArg);
    }

    pNode = Tree->Root;
    pN = NULL;
    while(pNode) {
        if( pNode->Node[0] == NULL ) {
            pN = pNode->Node[1];
            tree_node_destroy(pNode, pDestroy);
            pNode = NULL;
        }
        else {
            pN = pNode->Node[0];
            pNode->Node[0] = pN->Node[1];
            pN->Node[1] = pNode;
        }
        pNode = pN;
    }

    Tree->Root = NULL;
}


void
_tree_initialise(size_t Arg, TREE *Tree, ...) {
    va_list sArg;

    if(Tree == NULL)
        return;
    Tree->Compare = _tree_compare;
    Tree->Destroy = NULL;
    Tree->Root = NULL;
    Tree->Alloc = Tree->Size = 0;

    va_start(sArg, Tree);
    if(Arg > 1)
        Tree->Compare = va_arg(sArg, _TREE_COMPARE);
    if(Arg > 2)
        Tree->Destroy = va_arg(sArg, _TREE_DESTROY);
    va_end(sArg);
}


int 
_tree_insert(size_t Arg, TREE *Tree, ... ) {
    TREE_NODE *pN1, *pN2, *pN3, *pN4, *pNode;
    TREE_NODE sRoot;
    va_list sArg;
    int nIndex1, nIndex2, nLast, nResult;

    nResult = -1;
    va_start(sArg, Tree);
    for(; Arg > 1; --Arg) {
        if((pNode = _tree_node_new()) == NULL) {
            nResult = -1;
            break;
        }
        pNode->Data = va_arg(sArg, void *);

        if(tree_search(Tree, pNode->Data) != NULL) {
            errno = EEXIST;
            nResult = -1;
            break;
        }

        if(Tree->Root == NULL) {
            Tree->Root = pNode;
            nResult = 0;
        }
        else {
            memset(&sRoot, 0, sizeof(sRoot));
            nIndex1 = nLast = 0;

            pN2 = &sRoot;
            pN1 = pN3 = NULL;
            pN4 = pN2->Node[1] = Tree->Root;

            while(1) {
                if(pN4 == NULL) {
                    if(pN3 != NULL)
                        pN3->Node[nIndex1] = pN4 = pNode;
                }
                else if(_tree_direction(pN4->Node[0]) && 
                        _tree_direction(pN4->Node[1])) {
                    pN4->Direction = 1;
                    pN4->Node[0]->Direction = 0;
                    pN4->Node[1]->Direction = 0;
                }

                if(_tree_direction(pN4) &&
                        _tree_direction(pN3)) {
                    nIndex2 = (pN2->Node[1] == pN1);
                    if(pN4 == pN3->Node[nLast]) 
                        pN2->Node[nIndex2] = _tree_rotate1(pN1, (nLast == 0));
                    else
                        pN2->Node[nIndex2] = _tree_rotate2(pN1, (nLast == 0));
                }
                if(Tree->Compare(pN4->Data, pNode->Data) == 0)
                    break;

                nLast = nIndex1;
                nIndex1 = (Tree->Compare(pN4->Data, pNode->Data) < 0);
                if(pN1 != NULL)
                    pN2 = pN1;
                pN1 = pN3, pN3 = pN4;
                pN4 = pN4->Node[nIndex1];
            }
            Tree->Root = sRoot.Node[1];
        }
        Tree->Root->Direction = 0;
        ++Tree->Size;

        nResult = 0;
    }
    va_end(sArg);
    return nResult;
}


void *
tree_iterate(TREE_ITER *Iter) {
    TREE_NODE *pNode;

    if(Iter->Node == NULL)
        return NULL;
    pNode = Iter->Node;
    _tree_iterate(Iter, 1);
    return pNode->Data;
}


void *
tree_iterate_first(TREE_ITER *Iter, TREE *Tree) {
    return _tree_iterate_start(Iter, Tree, 0);
}


void *
tree_iterate_last(TREE_ITER *Iter, TREE *Tree) {
    return _tree_iterate_start(Iter, Tree, 1);
}


void *
tree_iterate_next(TREE_ITER *Iter) {
    return _tree_iterate(Iter, 1);
}


TREE_ITER *
tree_iterate_new(TREE *Tree) {
    TREE_ITER *pIter;

    errno = 0;
    if((pIter = calloc(1, sizeof(*pIter))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    pIter->Tree = Tree;
    pIter->Node = Tree->Root;
    pIter->Top = 0;
    return pIter;
}


void *
tree_iterate_previous(TREE_ITER *Iter) {
    return _tree_iterate(Iter, 0);
}


void
tree_iterate_reset(TREE_ITER *Iter, TREE *Tree) {
    Iter->Tree = Tree;
    Iter->Node = Tree->Root;
    Iter->Top = 0;

    if(Iter->Node != NULL) {
        while(Iter->Node->Node[0] != NULL) {
            Iter->Path[Iter->Top++] = Iter->Node;
            Iter->Node = Iter->Node->Node[0];
        }
    }
}


TREE *
tree_new(void) {
    TREE *pTree;

    errno = 0;
    if((pTree = calloc(1, sizeof(*pTree))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    tree_initialise(pTree);
    pTree->Alloc = 1;
    return pTree;
}


int 
tree_remove(TREE *Tree, void *Data) {
    TREE_NODE sHead, sNode;
    TREE_NODE *pN1, *pN2, *pN3, *pN4, *pN5;
    int nDirection, nLast, nResult;
    void *pValue;

    memset(&sHead, 0, sizeof(sHead));
    nDirection = 1;
    sNode.Data = Data;
    pN1 = &sHead;
    pN2 = pN3 = pN4 = NULL;
    pN1->Node[1] = Tree->Root;

    while(pN1->Node[nDirection] != NULL) {
        nLast = nDirection;
        pN3 = pN2, pN2 = pN1;
        pN1 = pN1->Node[nDirection];
        if((nResult = Tree->Compare(pN1->Data, sNode.Data)) == 0)
            pN4 = pN1;
        nDirection = (nResult < 0);

        if(!_tree_direction(pN1) &&
                ! _tree_direction(pN1->Node[nDirection])) {
            if(_tree_direction(pN1->Node[!nDirection])) {
                pN2 = pN2->Node[nLast] = _tree_rotate1(pN1, nDirection);
            }
            else if(!_tree_direction(pN1->Node[!nDirection])) {
                if((pN5 = pN2->Node[!nLast]) != NULL) {
                    if(!_tree_direction(pN5->Node[!nLast]) &&
                            !_tree_direction(pN5->Node[nLast])) {
                        pN2->Direction = 0;
                        pN1->Direction = pN5->Direction = 1;
                    }
                    else {
                        nResult = (pN3->Node[1] == pN2);
                        if(_tree_direction(pN5->Node[nLast])) {
                            pN3->Node[nResult] = _tree_rotate2(pN2, nLast);
                        }
                        else if(_tree_direction(pN5->Node[!nLast])) {
                            pN3->Node[nResult] = _tree_rotate1(pN2, nLast);
                        }

                        pN1->Direction = pN3->Node[nResult]->Direction = 1;
                        pN3->Node[nResult]->Node[0]->Direction = 0;
                        pN3->Node[nResult]->Node[1]->Direction = 0;
                    }
                }
            }
        }
    }

    if(!pN4) {
        errno = ENOENT;
        return -1;
    }

    pValue = pN4->Data;
    pN4->Data = pN1->Data;
    pN1->Data = pValue;
    pN2->Node[pN2->Node[1] == pN1] = pN1->Node[pN1->Node[0] == NULL];
    tree_node_destroy(pN1);
    pN1 = NULL;

    Tree->Root = sHead.Node[1];
    if(Tree->Root != NULL) 
        Tree->Root->Direction = 0;
    --Tree->Size;
    return 0;
}


void * 
tree_search(TREE *Tree, void *Data) {
    TREE_NODE *pIter, sNode;
    int nIndex;

    sNode.Data = Data;
    for(pIter = Tree->Root; pIter != NULL;) {
        if((nIndex = Tree->Compare(pIter->Data, sNode.Data)) == 0)
            break;
        pIter = pIter->Node[nIndex < 0];
    }
    return (pIter != NULL) ? pIter->Data : NULL;
}


