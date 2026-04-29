#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define RTC_addr_port 	0x0070
#define RTC_data_port	0x0071

// RTC registers
// https://github.com/torvalds/linux/blob/master/include/linux/mc146818rtc.h
#define RTC_REG_SEC     0x00
#define RTC_REG_MIN     0x02
#define RTC_REG_HOUR    0x04

#define TIMEZONE_OFFSET 7   // UTC+7 Vietnam

// Convert BCD to decimal
#define BCD_TO_DEC(x) (((x) >> 4) * 10 + ((x) & 0x0F))

static unsigned char rtc_read(int fd, unsigned char reg)
{
    unsigned char val;
    lseek(fd, RTC_addr_port, SEEK_SET);
    write(fd, &reg, 1);
    lseek(fd, RTC_data_port, SEEK_SET);
    read(fd, &val, 1);
    return val;
}

int main()
{
    int fd = open("/dev/port", O_RDWR);
    if (fd < 0) {
        perror("open /dev/port failed");
        return 1;
    }

    unsigned char sec  = BCD_TO_DEC(rtc_read(fd, RTC_REG_SEC));
    unsigned char min  = BCD_TO_DEC(rtc_read(fd, RTC_REG_MIN));
    unsigned char hour = BCD_TO_DEC(rtc_read(fd, RTC_REG_HOUR));
    hour = (hour + TIMEZONE_OFFSET) % 24; // Convert UTC to local time

    printf("Real time: %02d:%02d:%02d\n", hour, min, sec);

    close(fd);
    return 0;
}