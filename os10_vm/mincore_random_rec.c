//% file: page_fault_rec_3.c
//% cmd: gcc -O3 -Wall -Wextra -o page_fault_rec_3 page_fault_rec_3.c

#include <assert.h>
#include <err.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

const long page_sz = 4096;

/* 実行時間とページフォルト回数の記録 */
typedef struct {
  struct timeval tv;
  struct rusage ru;
} timeval_rusage;

/* 実行時間とページフォルト回数をtrに記録する */
void record_timeval_rusage(timeval_rusage * tr) {
  if (gettimeofday(&tr->tv, 0) == -1) { err(1, "gettimeofday"); }
  if (getrusage(RUSAGE_SELF, &tr->ru) == -1) { err(1, "getrusage"); }
}

/* 実行時間とページフォルト回数の記録tr[0]〜tr[n_records-1]
   をファイルtime_usage_datに保存する */
void save_timeval_rusage(const char * time_usage_dat,
                         timeval_rusage * tr,
                         long n_records,
                         long record_interval) {
  FILE * wp = fopen(time_usage_dat, "w");
  if (!wp) { err(1, "fopen"); }
  for (long i = 0; i < n_records; i++) {
    fprintf(wp, "%ld\t%f\t%ld\t%ld\n", 
            i * record_interval * 4096,
            tr[i].tv.tv_sec + tr[i].tv.tv_usec * 1.0e-6,
            tr[i].ru.ru_minflt,
            tr[i].ru.ru_majflt);
  }
  fclose(wp);
}

/* addr[0:length]中のどのページがメモリ上にあるか
   + 最後にアクセスしたアドレス(last_accessed)を記録する */
void record_incore(FILE * wp, 
		   void * addr, size_t length, unsigned char * R,
		   long * mru, long n_mru) {
  size_t n_pages = (length + page_sz - 1) / page_sz;
  struct timeval tp[1];
  if (gettimeofday(tp, NULL) == -1) { perror("gettimeofday"); exit(1); }
  double t = tp->tv_sec + tp->tv_usec * 1.0e-6;
  /* get current time */
  fprintf(wp, "%f\n", t);
  if (mincore(addr, length, R) == -1) {
    err(1, "mincore");
  }
  fprintf(wp, "%lu\n", n_pages);
  size_t c = fwrite(R, n_pages, 1, wp);
  if (c != 1) {
    err(1, "fwrite");
  }

  fprintf(wp, "%ld\n", n_mru);
  c = fwrite(mru, sizeof(long), n_mru, wp);
  if (c != (size_t)n_mru) {
    err(1, "fwrite");
  }
}



/* 
   usage:
     ./page_fault_rec N S A RI
   (1) N MBの領域を割り当てる (デフォルト64 MB)
   (2) S > 0ならば二つのアクセス間の距離 (デフォルト 4096) -1ならばランダム
   (3) A 回 (2)に従ってページをアクセス (デフォルト -1). -1の場合, A = N * 256 * 3
       (N MB のページ数 x 3)
   (4) RIアクセスごとに時刻と, ページフォルト数を記録する 
       (デフォルト 500アクセス)
   (5) RIアクセスごとに, メモリ上にあるページを記録する
 */

int main(int argc, char ** argv) {
  int i = 1;
  /* 配列のサイズ(MB) */
  long n_mb            = (argc > i ? atol(argv[i]) : 64); i++;
  /* アクセス回数(デフォルトは配列のページ数 x 3回) */
  long n_accesses      = (argc > i ? atol(argv[i]) : -1); i++;
  /* 記録間隔 */
  long record_interval = (argc > i ? atol(argv[i]) : 500); i++;
  /* 乱数の種 */
  long seed            = (argc > i ? atol(argv[i]) : 1234567890123L); i++;
  long sz = n_mb * 1024L * 1024L; /* size in bytes */
  long n_pages = (sz + page_sz - 1) / page_sz;
  if (n_accesses == -1) n_accesses = n_pages * 3;
  long n_records = (n_accesses + record_interval - 1) / record_interval;
  char * a = (char *)sbrk(sz);
  if (!a) { err(1, "sbrk"); }
  timeval_rusage * tr = malloc(sizeof(timeval_rusage) * n_records);
  if (!tr) { err(1, "malloc"); }
  unsigned char * R = calloc(sizeof(unsigned char), n_pages);
  if (!R) { err(1, "calloc"); }
  FILE * wp = fopen("mincore.dat", "wb");
  if (!wp) { err(1, "fopen"); }
  long * mru = calloc(sizeof(long), record_interval);
  if (!mru) { err(1, "calloc"); }
  unsigned short rg[3] = { seed >> 32, seed >> 16, seed };
  long idx = 0;                 /* 次にアクセスする要素 */
  /* report_interval 回アクセスごとに . を打つ */
  const long n_dots = 100;
  long report_interval = (n_accesses + n_dots - 1) / n_dots;

  fprintf(stderr, "touching %ld MB %ld times\n", n_mb, n_accesses);
  long s = 0;
  for (long i = 0; i < n_accesses; i++) {
    if (i % report_interval == 0) {
      /* 進捗表示 */
      putchar('.'); fflush(stdout);
    }
    if (i % record_interval == 0) {
      /* 時間を記録 */
      long k = i / record_interval; /* 記録回数 */
      assert(k < n_records);
      record_timeval_rusage(&tr[k]);
      /* メモリ上のページを記録 */
      record_incore(wp, a, sz, R, mru, (i ? record_interval : 0));
    }
    idx = idx % sz;
    s += (a[idx]++);
    mru[i % record_interval] = idx;
    idx = nrand48(rg);
  }
  assert((n_accesses - 1) / record_interval + 1 == n_records);
  fclose(wp);
  /* save time and page faults */
  save_timeval_rusage("time_rusage.dat", tr, n_records, record_interval);
  printf("\ndone s = %ld\n", s);
  return 0;
}
