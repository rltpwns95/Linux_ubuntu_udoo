#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <string.h>

#define DEVICE_FILENAME "/dev/ledkey_dev"

int main(int argc, char *argv[])
{
	int dev;
	char buff;
	int ret;
	int num = 1;
	struct pollfd Events[2]; //2개의 장치 이벤트
	char keyStr[80];	//입력받은 문자열

    if(argc != 2)
    {
        printf("Usage : %s [led_data(0x0~0xf)]\n",argv[0]);
        return 1;
    }
    buff = (char)strtoul(argv[1],NULL,16);
	//16진수를 언사인롱으로 쓰기 위해서 좌측이 char라서 
//    if(!((0 <= buff) && (buff <= 15)))
    if((buff < 0) || (15 < buff))
    {
        printf("Usage : %s [led_data(0x0~0xf)]\n",argv[0]);
        return 2;
    }

//  dev = open(DEVICE_FILENAME, O_RDWR | O_NONBLOCK);
  	dev = open(DEVICE_FILENAME, O_RDWR ); //블로킹 io로 열음
	if(dev < 0)
	{
		perror("open");
		return 2;
	}
	write(dev,&buff,sizeof(buff));

	fflush(stdin); //표준입력장치의 번호 fflush(파일포인트변수)
//	입력버퍼를 클리어하겠다.
	memset( Events, 0, sizeof(Events));//크기만큼 초기화
  	Events[0].fd = fileno(stdin); //0을 넣어줘도 됩니다. 키보드
  	Events[0].events = POLLIN; 
	//POLLIN은 입력에 대한 이벤트, POLLOUT은 출력에 대한 이벤트
	Events[1].fd = dev; //장치파일에 대한 (정수3번)
	Events[1].events = POLLIN;
	while(1)
	{
		ret = poll(Events, 2, 2000); //poll(이벤트, 개수, 타임아웃2초);
		if(ret<0)
		{
			perror("poll");
			exit(1);
		}
		else if(ret==0)
		{
  			printf("poll time out : %d Sec\n",2*num++);//2,4,6,8,..
			continue;
		}
		if(Events[0].revents & POLLIN)  //stdin
		{
			fgets(keyStr,sizeof(keyStr),stdin);//80byte크기
			//키보드에서 부터 받는 값
			//gets는 안쓰는게 좋다. fgets를 사용하자.
			if(keyStr[0] == 'q')
				break;
			keyStr[strlen(keyStr)-1] = '\0'; //strlen(keyStr)=2 
			//2-1 =1 why? \n(쓰레기 값)을 (\0을 넣어)지우려고
			printf("STDIN : %s\n",keyStr);
			buff = (char)atoi(keyStr);
			write(dev,&buff,sizeof(buff));
		}
		else if(Events[1].revents & POLLIN) //ledkey
		{
			ret = read(dev,&buff,sizeof(buff));
			//스위치로 부터 받는 값
			printf("key_no : %d\n",buff);
			write(dev,&buff,sizeof(buff));
			if(buff == 8)
				break;
		}
	}
	close(dev);
	return 0;
}
