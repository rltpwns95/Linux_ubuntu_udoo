#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_FILENAME  "/dev/led_dev"

void print_led(char *);
void print_key(char *);
int main(int argc,char * argv[])
{
    int dev;
    char ledbuff[4] = {0};
    char keybuff[8] = {0};
	char oldkeyBuff = 0;
    int ret;
	if(argc < 2)
	{
		printf("USAGE : %s [ledval] \n",argv[0]);
		return 1;
	}
	buff = atoi(argv[1]);
	for(i=0; i=4;i++)
	{
		ledbuff[i] = ((buff>>i) & 0x01);
		printf("ledbuff[%d] : %d\n", i, ledbuff[i]);
	}
    dev = open( DEVICE_FILENAME, O_RDWR|O_NDELAY );
	if(dev<0)
	{
		perror("open()");
		return 2;
	}
    ret = write(dev,ledbuff,sizeof(ledbuff));
	if(ret < 0)
	{
		perror("write()");
		return 3;
	}
	print_led(ledbuff);

	buff = 0;
	do{
		read(dev,keybuff,sizeof(keybuff));
		printf("");
	}while(1);
    close(dev);
    return 0;
}
void print_led(unsigned char *led)
{
	int i;
	puts("1:2:3:4");
	for(i=0;i<=3;i++)
	{
		if(ledbuff[i] ==1)
			putchar('O');
		else
			putchar('X');
		if(i < 3 )
			putchar(':');
		else
			putchar('\n');
	}
	return;
}

void print_key(unsigned char *keybuff)
{
	int i;
	puts("1:2:3:4:5:6:7:8");
	for(i=0;i<=7;i++)
	{
		if(keybuff[i] == 1)
			putchar('O');
		else
			putchar('X');
		if(i < 7 )
			putchar(':');
		else
			putchar('\n');
	}
	return;
}
