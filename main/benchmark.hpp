#ifndef __WBAEK_BENCHMARK_HPP__
#define __WBAEK_BENCHMARK_HPP__

#include <unistd.h>
#include <stdarg.h>
#include <sys/time.h>
#include <cstdlib>
#include <cstdio>

// BSD-License
// refer : https://github.com/iwiwi/parallel-radix-sort/blob/master/measure.cc

struct __bench__ {
      double start;
      char msg[2048];
      __bench__(const char* format, ...)
          __attribute__((format(printf, 2, 3)))
          {
              va_list args;
              va_start(args, format);
              vsnprintf(msg, sizeof(msg), format, args);
              va_end(args);

              start = sec();
          }
      ~__bench__() {
          fprintf(stdout, "%20.20s: %.6f sec\n", msg, sec() - start);
      }
      double sec() {
          struct timeval tv;
          gettimeofday(&tv, NULL);
          return tv.tv_sec + tv.tv_usec * 1e-6;
      }
      operator bool() { return false; }
};

#define benchmark(...) if (__bench__ __b__ = __bench__(__VA_ARGS__)); else

#endif //__WBAEK_BENCHMARK_HPP__
