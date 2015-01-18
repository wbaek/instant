#ifndef __WBAEK_OTHERS_H__
#define __WBAEK_OTHERS_H__

#include <sys/time.h>
#include <unistd.h>

namespace instant {
    namespace Utils {
        class Others {
          public:
            static std::string GetCurrentTime(const std::string & format =
                                              "%Y-%m-%d %H:%M:%S") {
                time_t now = time(NULL);
                char buffer[128];
                struct tm *ts = localtime(&now);
                 strftime(buffer, sizeof(buffer), format.c_str(), ts);

                 return std::string(buffer);
            }
            
            static double GetTickCount() {
                return GetMilliSeconds();
            }
            
            static double GetMilliSeconds() {
                struct timeval gettick;
                 gettimeofday(&gettick, NULL);
                 return (gettick.tv_sec * 1000.0 +
                         gettick.tv_usec / 1000.0);
            }
        };

    };
};

#endif                          // __WBAEK_OTEHR_H__
