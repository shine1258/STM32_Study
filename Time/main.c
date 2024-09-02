#include <stdio.h>
#include <time.h>

time_t time_cnt = 0;
struct tm time_date;
char *time_str = NULL;

int main(void)
{
    // time_cnt = time(NULL);
    // time(&time_cnt);
    time_cnt = 1672588795;
    time_date = *gmtime(&time_cnt);

    printf("%d\n", time_date.tm_year + 1900);
    printf("%d\n", time_date.tm_mon + 1);
    printf("%d\n", time_date.tm_mday);
    printf("%d\n", time_date.tm_hour);
    printf("%d\n", time_date.tm_min);
    printf("%d\n", time_date.tm_sec);
    printf("%d\n", time_date.tm_wday);

    time_cnt = mktime(&time_date);
    printf("%ld\n", time_cnt);

    time_str = ctime(&time_cnt);
    printf("%s\n", time_str);

    time_str = asctime(&time_date);
    printf("%s\n", time_str);

    char t[50];
    strftime(t, 50, "%Y-%m-%d %H:%M:%S", &time_date);
    printf("%s\n", t);

    return 0;
}
