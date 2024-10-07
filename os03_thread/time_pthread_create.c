/* 必要な #include を補うこと (man ページを参照) */
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

long cur_time() {
  struct timespec ts[1];
  clock_gettime(CLOCK_REALTIME, ts);
  return ts->tv_sec * 1000000000L + ts->tv_nsec;
}

void * do_nothing(void * arg) {
  return arg;
}

int main(int argc, char ** argv) {
  int n = (argc > 1 ? atoi(argv[1]) : 5);
  long t0 = cur_time();

  
  /* ここにプログラムを書く */

pthread_t thread_id;
int* res[n];
    for (int i = 0; i < n; i++) {
        pthread_create(&thread_id, 0, do_nothing, (void *) (long) i);
        pthread_join(thread_id, (void *) &res[i]);
    }

  long t1 = cur_time();
  long dt = t1 - t0;
    for (int i = 0; i < n; i++) {
        printf("%ld ", (long) res[i]);
    }
printf("\n");
  printf("%ld nsec to pthrea_create-and-join %d threads (%ld nsec/thread)\n",
         dt, n, dt / n);
  return 0;
}
