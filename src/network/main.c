#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <net/if.h>

int main(int argc, char *argv[])
{
    int s;
    int ret;
    struct ifreq ifr;
    int i;

    if (argc != 2)
    {
        printf("Usage %s [network interface]\n", argv[0]);
        return 1;
    }

    s = socket(PF_INET, SOCK_DGRAM, 0); // Supports datagrams
    if (s < 0)
    {
        perror("socket");
        return 1;
    }

    strcpy(ifr.ifr_name, argv[1]);  // interface name

    ret = ioctl(s, SIOCGIFHWADDR, &ifr);    //Get the hardware address of a device
    if (ret < 0)
    {
        perror("ioctl");
        return 1;
    }

    // get socket address
    for (i = 0; i < 6; i++)
        if (i == 5)
            printf("%02x", (unsigned char)ifr.ifr_hwaddr.sa_data[i]);   
        else
            printf("%02x:", (unsigned char)ifr.ifr_hwaddr.sa_data[i]);

    printf("\n");
    close(s);
    return 0;
}