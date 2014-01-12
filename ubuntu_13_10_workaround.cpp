#include <pthread.h>

void f()
{
  int i = pthread_getconcurrency();
}

