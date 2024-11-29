#ifndef _LOCK_H__
#define _LOCK_H__

void* lock_init(void);
void lock_exit(void* pLock);
int lock_rd(void* pLock);
int lock_wr(void* pLock);
int lock_unlock(void* pLock);

#endif /* _LOCK_H__ */

