/***************************************************/
/*! \class Thread
    \brief STK thread class.

    This class provides a uniform interface for
    cross-platform thread use.  On Linux and IRIX
    systems, the pthread library is used.  Under Windows,
    the Windows thread library is used.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2002.
*/
/***************************************************/

#include "Thread.h"

Thread :: Thread()
{
  thread = 0;
}

Thread :: ~Thread()
{
#ifdef USING_PTHREADS

  pthread_cancel(thread);
  pthread_join(thread, NULL);

#elif defined(_WIN32)|| defined(_WIN64)

  if ( thread )
    TerminateThread((HANDLE)thread, 0);

#endif
}

bool Thread :: start( THREAD_FUNCTION routine, void * ptr )
{
  bool result = false;
#ifdef USING_PTHREADS

  if ( pthread_create(&thread, NULL, *routine, ptr) == 0 )
    result = true;

#elif defined(_WIN32)|| defined(_WIN64)
  unsigned thread_id;
  thread = _beginthreadex(NULL, 0, routine, ptr, 0, &thread_id);
  if ( thread ) result = true;

#endif
  return result;
}

bool Thread :: wait( long milliseconds )
{
  bool result = false;
#ifdef USING_PTHREADS

  pthread_cancel(thread);
  pthread_join(thread, NULL);

#elif defined(_WIN32)|| defined(_WIN64)

  DWORD timeout, retval;
  if ( milliseconds < 0 ) timeout = INFINITE;
  else timeout = milliseconds;
  retval = WaitForSingleObject( (HANDLE)thread, timeout );
  if ( retval == WAIT_OBJECT_0 ) {
    CloseHandle( (HANDLE)thread );
    thread = 0;
    result = true;
  }

#endif
  return result;
}

void Thread :: test(void)
{
#ifdef USING_PTHREADS

  pthread_testcancel();

#endif
}


Mutex :: Mutex()
{

#ifdef USING_PTHREADS

  pthread_mutex_init(&mutex, NULL);

#elif defined(_WIN32)|| defined(_WIN64)

  InitializeCriticalSection(&mutex);

#endif 
}

Mutex :: ~Mutex()
{
#ifdef USING_PTHREADS

  pthread_mutex_destroy(&mutex);

#elif defined(_WIN32)|| defined(_WIN64)

  DeleteCriticalSection(&mutex);

#endif 
}

void Mutex :: lock()
{
#ifdef USING_PTHREADS

  pthread_mutex_lock(&mutex);

#elif defined(_WIN32)|| defined(_WIN64)

  EnterCriticalSection(&mutex);

#endif 
}

void Mutex :: unlock()
{
#ifdef USING_PTHREADS

  pthread_mutex_unlock(&mutex);

#elif defined(_WIN32)|| defined(_WIN64)

  LeaveCriticalSection(&mutex);

#endif 
}
