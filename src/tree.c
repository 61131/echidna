#include <string.h>
#include <errno.h>
#include <assert.h>

#include <log.h>
#include <tree.h>


static int _tree_compare( void *pA, void *pB );

static void * _tree_iterate( TREE_ITER *pIter, int nDirection );

static void * _tree_iterate_start( TREE_ITER *pIter, TREE *pTree, int nDirection );

static void _tree_node_destroy( size_t uArg, TREE_NODE *pNode, ... );

static TREE_NODE * _tree_node_new( void );

static int _tree_direction( TREE_NODE *pNode );

static TREE_NODE * _tree_rotate1( TREE_NODE *pNode, int nDirection );

static TREE_NODE * _tree_rotate2( TREE_NODE *pNode, int nDirection );


static int
_tree_compare( void *pA, void *pB ) {
    return ( pA > pB ) - ( pA < pB );
}


static void *
_tree_iterate( TREE_ITER *pIter, int nDirection ) {
    TREE_NODE *pNode;

    if( pIter->Node->Node[ nDirection ] != NULL ) {
        pIter->Path[ pIter->Top++ ] = pIter->Node;
        pIter->Node = pIter->Node->Node[ nDirection ];
        while( pIter->Node->Node[ ! nDirection ] != NULL ) {
            pIter->Path[ pIter->Top++ ] = pIter->Node;
            pIter->Node = pIter->Node->Node[ ! nDirection ];
        }
    }
    else {
        pNode = NULL;
        do {
            if( pIter->Top == 0 ) {
                pIter->Node = NULL;
                break;
            }
            pNode = pIter->Node;
            pIter->Node = pIter->Path[ --pIter->Top ];
        }
        while( pNode == pIter->Node->Node[ nDirection ] );
    }
    return ( pIter->Node != NULL ) ? pIter->Node->Data : NULL;
}


static void *
_tree_iterate_start( TREE_ITER *pIter, TREE *pTree, int nDirection ) {
    pIter->Tree = pTree;
    pIter->Node = pTree->Root;
    pIter->Top = 0;

    if( pIter->Node != NULL ) {
        while( pIter->Node->Node[ nDirection ] != NULL ) {
            pIter->Path[ pIter->Top++ ] = pIter->Node;
            pIter->Node = pIter->Node->Node[ nDirection ];
        }
    }
    return ( pIter->Node != NULL ) ? pIter->Node->Data : NULL;
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
_tree_node_new( void ) {
    TREE_NODE *pNode;

    errno = 0;
    if( ( pNode = ( TREE_NODE * ) calloc( 1, sizeof( *pNode ) ) ) == NULL ) {
        log_critical( "Failed to allocate memory: %s", strerror( errno ) );
        return NULL;
    }
    pNode->Direction = 1;
    pNode->Node[0] = pNode->Node[1] = NULL;
    pNode->Data = NULL;

    return pNode;
}


static int 
_tree_direction( TREE_NODE *pNode ) {
    return ( pNode ) ? pNode->Direction : 0;
}


static TREE_NODE * 
_tree_rotate1( TREE_NODE *pNode, int nDirection ) {
    TREE_NODE *pResult;
    int nInverse;

    pResult = NULL;
    nInverse = ( nDirection == 0 );
    if( pNode != NULL  ) {
        pResult = pNode->Node[ nInverse ];
        pNode->Node[ nInverse ] = pResult->Node[ nDirection ];
        pResult->Node[ nDirection ] = pNode;
        pNode->Direction = 1;
        pResult->Direction = 0;
    }
    return pResult;
}


static TREE_NODE *
_tree_rotate2( TREE_NODE *pNode, int nDirection ) {
    TREE_NODE *pResult;
    int nInverse;

    pResult = NULL;
    nInverse = ( nDirection == 0 );
    if( pNode != NULL ) {
        pNode->Node[ nInverse ] = _tree_rotate1( pNode->Node[ nInverse ], nInverse );
        pResult = _tree_rotate1( pNode, nDirection );
    }
    return pResult;
}


void 
_tree_destroy( size_t uArg, TREE *pTree, ... ) {
    _TREE_DESTROY pDestroy;
    TREE_NODE *pN, *pNode;
    va_list sArg;

    pDestroy = pTree->Destroy;
    if(uArg > 1) {
        va_start(sArg, pTree);
        pDestroy = va_arg(sArg, _TREE_DESTROY);
        va_end(sArg);
    }

    pNode = pTree->Root;
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

    pTree->Root = NULL;
}


void
_tree_initialise( size_t uArg, TREE *pTree, ... ) {
    va_list sArg;

    pTree->Compare = _tree_compare;
    pTree->Destroy = NULL;
    pTree->Root = NULL;
    pTree->Alloc = pTree->Size = 0;

    va_start(sArg, pTree);
    if(uArg > 1)
        pTree->Compare = va_arg(sArg, _TREE_COMPARE);
    if(uArg > 2)
        pTree->Destroy = va_arg(sArg, _TREE_DESTROY);
    va_end(sArg);
}


int 
_tree_insert( size_t uArg, TREE *pTree, ... ) {
    TREE_NODE *pN1, *pN2, *pN3, *pN4, *pNode;
    TREE_NODE sRoot;
    va_list sArg;
    int nIndex1, nIndex2, nLast, nResult;

    nResult = -1;
    va_start( sArg, pTree );
    for( ; uArg > 1; --uArg ) {
        if( ( pNode = _tree_node_new() ) == NULL ) {
            nResult = errno;
            break;
        }
        pNode->Data = ( void * ) va_arg( sArg, void * );

        if( tree_search( pTree, pNode->Data ) != NULL ) {
            nResult = EEXIST;
            break;
        }

        if( pTree->Root == NULL ) {
            pTree->Root = pNode;
            nResult = 0;
        }
        else {
            ( void ) memset( &sRoot, 0, sizeof( sRoot ) );
            nIndex1 = nLast = 0;

            pN2 = &sRoot;
            pN1 = pN3 = NULL;
            pN4 = pN2->Node[1] = pTree->Root;

            while( 1 ) {
                if( pN4 == NULL ) {
                    if( pN3 != NULL )
                        pN3->Node[ nIndex1 ] = pN4 = pNode;
                }
                else if( _tree_direction( pN4->Node[0] ) && 
                        _tree_direction( pN4->Node[1] ) ) {
                    pN4->Direction = 1;
                    pN4->Node[0]->Direction = 0;
                    pN4->Node[1]->Direction = 0;
                }

                if( _tree_direction( pN4 ) &&
                        _tree_direction( pN3 ) ) {
                    nIndex2 = ( pN2->Node[1] == pN1 );
                    if( pN4 == pN3->Node[ nLast ] ) 
                        pN2->Node[ nIndex2 ] = _tree_rotate1( pN1, ( nLast == 0 ) );
                    else
                        pN2->Node[ nIndex2 ] = _tree_rotate2( pN1, ( nLast == 0 ) );
                }
                if( pTree->Compare( pN4->Data, pNode->Data ) == 0 )
                    break;

                nLast = nIndex1;
                nIndex1 = ( pTree->Compare( pN4->Data, pNode->Data ) < 0 );
                if( pN1 != NULL )
                    pN2 = pN1;
                pN1 = pN3, pN3 = pN4;
                pN4 = pN4->Node[ nIndex1 ];
            }
            pTree->Root = sRoot.Node[1];
        }
        pTree->Root->Direction = 0;
        ++pTree->Size;

        nResult = 0;
    }
    va_end( sArg );
    return nResult;
}


void *
tree_iterate( TREE_ITER *pIter ) {
    TREE_NODE *pNode;

    if( pIter->Node == NULL )
        return NULL;
    pNode = pIter->Node;
    _tree_iterate( pIter, 1 );
    return pNode->Data;
}


void *
tree_iterate_first( TREE_ITER *pIter, TREE *pTree ) {
    return _tree_iterate_start( pIter, pTree, 0 );
}


void *
tree_iterate_last( TREE_ITER *pIter, TREE *pTree ) {
    return _tree_iterate_start( pIter, pTree, 1 );
}


void *
tree_iterate_next( TREE_ITER *pIter ) {
    return _tree_iterate( pIter, 1 );
}


TREE_ITER *
tree_iterate_new( TREE *pTree ) {
    TREE_ITER *pIter;

    errno = 0;
    if( ( pIter = ( TREE_ITER * ) calloc( 1, sizeof( *pIter ) ) ) == NULL ) {
        log_critical( "Failed to allocate memory: %s", strerror( errno ) );
        return NULL;
    }
    pIter->Tree = pTree;
    pIter->Node = pTree->Root;
    pIter->Top = 0;
    return pIter;
}


void *
tree_iterate_previous( TREE_ITER *pIter ) {
    return _tree_iterate( pIter, 0 );
}


void
tree_iterate_reset( TREE_ITER *pIter, TREE *pTree ) {
    pIter->Tree = pTree;
    pIter->Node = pTree->Root;
    pIter->Top = 0;

    if( pIter->Node != NULL ) {
        while( pIter->Node->Node[0] != NULL ) {
            pIter->Path[ pIter->Top++ ] = pIter->Node;
            pIter->Node = pIter->Node->Node[0];
        }
    }
}


TREE *
tree_new( void ) {
    TREE *pTree;

    errno = 0;
    if( ( pTree = ( TREE * ) calloc( 1, sizeof( *pTree ) ) ) == NULL ) {
        log_critical( "Failed to allocate memory: %s", strerror( errno ) );
        return NULL;
    }
    tree_initialise( pTree );
    pTree->Alloc = 1;
    return pTree;
}


int 
tree_remove( TREE *pTree, void *pData ) {
    TREE_NODE sHead, sNode;
    TREE_NODE *pN1, *pN2, *pN3, *pN4, *pN5;
    int nDirection, nLast, nResult;
    void *pValue;

    ( void ) memset( &sHead, 0, sizeof( sHead ) );
    nDirection = 1;
    sNode.Data = pData;
    pN1 = &sHead;
    pN2 = pN3 = pN4 = NULL;
    pN1->Node[1] = pTree->Root;

    while( pN1->Node[ nDirection ] != NULL ) {
        nLast = nDirection;
        pN3 = pN2, pN2 = pN1;
        pN1 = pN1->Node[ nDirection ];
        if( ( nResult = pTree->Compare( pN1->Data, sNode.Data ) ) == 0 )
            pN4 = pN1;
        nDirection = ( nResult < 0 );

        if( ! _tree_direction( pN1 ) &&
                ! _tree_direction( pN1->Node[ nDirection ] ) ) {
            if( _tree_direction( pN1->Node[ ! nDirection ] ) ) {
                pN2 = pN2->Node[ nLast ] = _tree_rotate1( pN1, nDirection );
            }
            else if( ! _tree_direction( pN1->Node[ ! nDirection ] ) ) {
                if( ( pN5 = pN2->Node[ ! nLast ] ) != NULL ) {
                    if( ! _tree_direction( pN5->Node[ ! nLast ] ) &&
                            ! _tree_direction( pN5->Node[ nLast ] ) ) {
                        pN2->Direction = 0;
                        pN1->Direction = pN5->Direction = 1;
                    }
                    else {
                        nResult = ( pN3->Node[1] == pN2 );
                        if( _tree_direction( pN5->Node[ nLast ] ) ) {
                            pN3->Node[ nResult ] = _tree_rotate2( pN2, nLast );
                        }
                        else if( _tree_direction( pN5->Node[ ! nLast ] ) ) {
                            pN3->Node[ nResult ] = _tree_rotate1( pN2, nLast );
                        }

                        pN1->Direction = pN3->Node[ nResult ]->Direction = 1;
                        pN3->Node[ nResult ]->Node[0]->Direction = 0;
                        pN3->Node[ nResult ]->Node[1]->Direction = 0;
                    }
                }
            }
        }
    }

    if( ! pN4 )
        return -ENOENT;

    pValue = pN4->Data;
    pN4->Data = pN1->Data;
    pN1->Data = pValue;
    pN2->Node[ pN2->Node[1] == pN1 ] = pN1->Node[ pN1->Node[0] == NULL ];
    tree_node_destroy( pN1 );
    pN1 = NULL;

    pTree->Root = sHead.Node[1];
    if( pTree->Root != NULL ) 
        pTree->Root->Direction = 0;
    --pTree->Size;
    return 0;
}


void * 
tree_search( TREE *pTree, void *pData ) {
    TREE_NODE *pIter, sNode;
    int nIndex;

    sNode.Data = pData;
    for( pIter = pTree->Root; pIter != NULL; ) {
        if( ( nIndex = pTree->Compare( pIter->Data, sNode.Data ) ) == 0 )
            break;
        pIter = pIter->Node[ nIndex < 0 ];
    }
    return ( pIter != NULL ) ? pIter->Data : NULL;
}


