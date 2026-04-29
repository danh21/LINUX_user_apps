#include <errno.h>
#include <fcntl.h>
#include <linux/rtc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#define TIMEZONE_OFFSET 7   // UTC+7 Vietnam

const char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

int main(int argc, char** argv)
{
    int rtc_fd = open("/dev/rtc0", O_RDONLY);
    if (rtc_fd < 0) {
        perror("open /dev/rtc0");
        return EXIT_FAILURE;
    }

    struct rtc_time read_time;
    if (ioctl(rtc_fd, RTC_RD_TIME, &read_time) < 0) {
        close(rtc_fd);
        perror("ioctl RTC_RD_TIME");
        return EXIT_FAILURE;
    }
    close(rtc_fd);

    // Convert rtc_time → struct tm
    struct tm t = {0};
    t.tm_sec   = read_time.tm_sec;
    t.tm_min   = read_time.tm_min;
    t.tm_hour  = read_time.tm_hour + TIMEZONE_OFFSET;  // UTC → local
    t.tm_mday  = read_time.tm_mday;
    t.tm_mon   = read_time.tm_mon;
    t.tm_year  = read_time.tm_year;

    // mktime() recalculates tm_wday, tm_yday and normalizes overflow
    // e.g. if hour = 25 → carries over to next day, wday updated
    mktime(&t);
    
    printf("RTC Time : %s\n", asctime(&t));

    return EXIT_SUCCESS;
}