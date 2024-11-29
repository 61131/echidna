#ifdef _MSC_VER
#include <Windows.h>
#else
#include <pthread.h>
#endif
#include <errno.h>

void* lock_init(void)
{
  void* pLock;
#ifdef _MSC_VER
  pLock = malloc(sizeof(CRITICAL_SECTION));
  if(pLock) InitializeCriticalSection(pLock);
#else
  pLock = malloc(sizeof(pthread_rwlock_t));
  if (pLock)
  {
    if (pthread_rwlock_init((pthread_rwlock_t*)pLock, NULL) != 0)
    {
      free(pLock);
      pLock = NULL;
    }
  }
#endif

  return pLock;
}

void lock_exit(void* pLock)
{
  if (!pLock) return;
#ifdef _MSC_VER
  DeleteCriticalSection(pLock);
#else
  pthread_rwlock_destroy((pthread_rwlock_t*)pLock);
#endif
  free(pLock);
}

int lock_rd(void* pLock)
{
  int nResult = 0;
  if (!pLock)
  {
    nResult = EACCES;
  }
  else
  {
#ifdef _MSC_VER
    EnterCriticalSection(pLock);
#else
    nResult = pthread_rwlock_rdlock((pthread_rwlock_t*)pLock);
#endif
  }

  return nResult;
}

int lock_wr(void* pLock)
{
  int nResult = 0;
  if (!pLock)
  {
    nResult = EACCES;
  }
  else
  {
#ifdef _MSC_VER
    EnterCriticalSection(pLock);
#else
    nResult = pthread_rwlock_wrlock((pthread_rwlock_t*)pLock);
    if (nResult == EDEADLK)
    {
      nResult = 0;
    }
#endif
  }
  return nResult;
}

int lock_unlock(void* pLock)
{
  int nResult = 0;
  if (!pLock)
  {
    nResult = EACCES;
  }
  else
  {
#ifdef _MSC_VER
    LeaveCriticalSection(pLock);
#else
    nResult = pthread_rwlock_unlock((pthread_rwlock_t*)pLock);
#endif
  }
  return nResult;
}
