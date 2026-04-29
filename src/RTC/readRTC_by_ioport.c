#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>

#define RTC_addr_port 	0x0070
#define RTC_data_port	0x0071

// Convert BCD to decimal
#define BCD_TO_DEC(x)   (((x) >> 4) * 10 + ((x) & 0x0F))

// RTC registers
// https://github.com/torvalds/linux/blob/master/include/linux/mc146818rtc.h
#define RTC_REG_SEC     0x00
#define RTC_REG_MIN     0x02
#define RTC_REG_HOUR    0x04

#define TIMEZONE_OFFSET 7   // UTC+7 Vietnam

static unsigned char dump_port(unsigned char addr_port, unsigned char data_port, unsigned char reg)
{
    outb(reg, addr_port);
    return inb(data_port);
}

void rtc_read(unsigned char addr_port, unsigned char data_port)
{
    unsigned char hour, min, sec;

	sec = BCD_TO_DEC(dump_port(RTC_addr_port, RTC_data_port, RTC_REG_SEC));
	min = BCD_TO_DEC(dump_port(RTC_addr_port, RTC_data_port, RTC_REG_MIN));
	hour = BCD_TO_DEC(dump_port(RTC_addr_port, RTC_data_port, RTC_REG_HOUR));
	hour = (hour + TIMEZONE_OFFSET) % 24; // Convert UTC to local time

    printf("Real time: %02d:%02d:%02d\n", hour, min, sec);
}

int main(int argc, char *argv[])
{
	// allow the user space application to access the I/O ports
	// from RTC_addr_port, count 2, ENABLE
	ioperm(RTC_addr_port, 2, 1);

	// read RTC data
    rtc_read(RTC_addr_port, RTC_data_port);

    return 0;
}