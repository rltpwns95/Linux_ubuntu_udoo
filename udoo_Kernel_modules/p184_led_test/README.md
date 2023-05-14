#커널 모듈로 led_app을 이용하여 led제어하기.<br>

1. 인자로 전달된 led 값에 따라 LED를 켜거나 끕니다.<br>
2. LED의 상태를 읽어와서 켜진 LED는 'O', 꺼진 LED는 'X'로 출력합니다.<br><br>
      #include <stdio.h>
      #include <sys/types.h>
      #include <sys/stat.h>
      #include <sys/ioctl.h>
      #include <fcntl.h>
      #include <unistd.h>
      
      #define DEVICE_FILENAME  "/dev/led_dev"       //DEVICE_FILENAME 상수는 LED 장치 파일의 경로를 나타냅니다.
      
      void print_led(unsigned char led);            //print_led() 함수는 전달된 led 값에 따라 LED의 상태를 출력하는 함수입니다.
      int main(int argc,char * argv[])
      {
          int dev;
          char buff = 0;                            //인자로 전달된 led 값을 buff 변수에 저장
          int ret;
      	if(argc < 2)
      	{
      		printf("USAGE : %s [ledval] \n",argv[0]);
      		return 1;
      	}
      	buff = atoi(argv[1]);
          dev = open( DEVICE_FILENAME, O_RDWR|O_NDELAY );         //open() 함수를 사용하여 LED 장치 파일을 열고
      	if(dev<0)
      	{
      		perror("open()");
      		return 2;
      	}
          ret = write(dev,&buff,sizeof(buff));                    //write() 함수를 사용하여 buff 값을 LED 장치 파일에 씁니다.
      	if(ret < 0)
      		perror("write()");
      	
      	buff = 0;
      	ret = read(dev,&buff,sizeof(buff));                       //read() 함수를 사용하여 LED 장치 파일에서 읽은 값을 buff 변수에 저장
      
      	print_led(buff);                                         //print_led() 함수를 호출하여 LED 상태를 출력
          close(dev);                                            //close() 함수를 사용하여 LED 장치 파일을 닫습니다.(OFF의 뜻이 아니다.)
          return 0;
      }
      void print_led(unsigned char led)
      {
      	int i;
      	puts("1:2:3:4");
      	for(i=0;i<=3;i++)
      	{
      		if(led & (0x01 << i))
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
<br><br>
##실행방법<br>
1. make<br>
2. sudo mknod /dev/led_dev c 240 32   (장치 파일을 생성)
3. sudo insmod led_dev.ko    (커널 모듈을 로드)
4. sudo ./led_app _(켜고 싶은 값을 주면 led가 켜진다.)<br>
![image](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/a254730c-3549-482b-b3cc-1e950c57516c)<br>
6. sudo lsmod<br>
![image](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/555a38b9-750f-4a4d-adcf-930a0caa661b)<br>
7. sudo dmesg<br>
![image](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/011bfa5d-7a7a-4752-bf70-591eaaf38b50)<br>
8. sudo rmmod led_dev
