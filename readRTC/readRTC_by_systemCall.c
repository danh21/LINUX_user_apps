#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>

#define RTC_addr_port 	0x0070
#define RTC_data_port	0x0071

// Convert BCD to decimal
#define BCD_TO_DEC(x)   (((x) >> 4) * 10 + ((x) & 0x0F))

// RTC registers
#define RTC_REG_SEC     0x00
#define RTC_REG_MIN     0x02
#define RTC_REG_HOUR    0x04

static unsigned char rtc_read(unsigned char addr_port, unsigned char data_port, unsigned char reg)
{
    outb(reg, addr_port);
    return inb(data_port);
}

void dump_port(unsigned char addr_port, unsigned char data_port)
{
    unsigned char hour, min, sec;

	sec = BCD_TO_DEC(rtc_read(RTC_addr_port, RTC_data_port, RTC_REG_SEC));
	min = BCD_TO_DEC(rtc_read(RTC_addr_port, RTC_data_port, RTC_REG_MIN));
	hour = BCD_TO_DEC(rtc_read(RTC_addr_port, RTC_data_port, RTC_REG_HOUR));

    printf("Real time: %02d:%02d:%02d\n", hour, min, sec);  // ← consistent %02d
}

int main(int argc, char *argv[])
{
	/*
		add permission for I/O ports (0x000 → 0xFFFF)
		level 3 = full access
	*/
    // if (iopl(3) < 0) {                          // ← missing error handling
    //     perror("iopl failed — run as root");
    //     return 1;
    // }

	/*
		arg1 = start port (0x70)
		arg2 = length (2 ports: 0x70, 0x71)
		arg3 = 1=enable / 0=disable
	*/
	ioperm(RTC_addr_port, 2, 1);

    dump_port(RTC_addr_port, RTC_data_port);

    return 0;
}