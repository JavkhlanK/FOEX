#include <stdio.h>
#include <time.h>
#include <string.h>

#if _WIN32
#define timegm _mkgmtime
#endif

int offsetToUTCInMinutes(time_t);


void main()
{
    char buff[512];
    time_t now = time(NULL);
    if (strftime(buff, sizeof buff, "%Y-%m-%dT%H:%M:%S", localtime(&now)))
    {
        char timezone[16];
        int currentOffset = offsetToUTCInMinutes(now);
        sprintf(timezone, currentOffset < 0 ? "-%02d%02d" : "+%02d%02d", currentOffset / 60, currentOffset % 60);

        printf("It's %s%s right now.\nAs timestamp in ms since 1970-01-01: %d\n", buff, timezone, now);
        int asd = localtime(&now)->tm_isdst;
    }
    else
    {
        printf("strftime() failed!");
    }
}

int offsetToUTCInMinutes(time_t time)
{
    struct tm *locg = localtime(&time);
    struct tm locl;
    memcpy(&locl, locg, sizeof(struct tm));
    return (int)(timegm(locg) - mktime(&locl)) / 60;
}