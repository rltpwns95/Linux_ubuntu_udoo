*위 코드는 /dev 디렉토리에 "testdev1"이라는 캐릭터 장치 파일을 생성하고, 이 파일을 읽기/쓰기 가능하도록 open() 함수를 이용하여 열어보는 코드입니다.<br><br>

int main(int argc, char *argv[])      (명령행 인자(argument)의 개수, 명령행 인자들을 포인터 배열)<br><br>

    ret = mknod("/dev/testdev1", S_IFCHR| S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH, (240<<8)|1);<br>
mknod() 함수를 이용하여 "/dev/testdev1" 파일을 생성합니다. 이때 S_IFCHR 플래그를 사용하여 캐릭터 장치 파일을 생성하고, S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH 플래그를 사용하여 파일의 권한을 설정했습니다.
(S_IRUSR: 소유자 읽기 권한, S_IWUSR: 소유자 쓰기 권한, S_IRGRP: 그룹 읽기 권한, S_IROTH: 다른 사용자 읽기 권한)<br>
그리고 (240<<8)|1 값을 세번째 인자로 넘기는데, 이는 major number가 240이고 minor number가 1인 장치 파일을 생성하도록 지정한 것입니다.<br><br><br>


	if(ret<0){
		perror("mknod()");
		return 1;
	}
	ret = open("/dev/testdev1",O_RDWR);    이어서 open() 함수를 이용하여 "/dev/testdev1" 파일을 엽니다. O_RDWR 플래그를 사용하여 읽기/쓰기가 모두 가능하도록 파일을 엽니다.
	if(ret<0){
		perror("open()");   만약 mknod() 함수나 open() 함수 호출 중 에러가 발생하면, perror() 함수를 이용하여 에러 메시지를 출력하고, 각각 1과 ENOENT를 리턴합니다.
		return EPERM          EPERM은 "Operation not permitted" (수행할 수 없는 연산)을 의미 위에선 수석처리
		return ENOENT;	      ENOENT는 "No such file or directory" (파일이나 디렉토리가 없음)을 의미
	}
	return 0;
} <br>
mknod() 함수 호출에서 에러가 발생하면, 생성하려는 파일이 이미 존재하는 경우가 대부분이므로 EPERM이 아니라 ENOENT를 리턴하는 것이 더 적절합니다.<br><br>
![image](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/2303f6df-1844-41d1-b749-352d420002a9)<br>
오류코드: No such device or address<br>
![image](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/48879161-28f6-4213-8594-1b4de7dcc9fc)<br>
![image](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/de77a2f3-d5a9-44bd-8ead-370b2658d49c)<br>
위 사진처럼 오류가 발생하여 226~246사이에 240이 안 만들어진게 보일 것이다.<br>
![Untitled](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/b0d35eb7-356d-405a-a89c-23b87a358ad3)<br>
에러코드 내용을 확인하기 위해서 'ctrl + ]' 로 해당 오류코드 설명을 확인해보았다.<br> (다시 코드로 돌아갈 때는 (ctrl + t)
![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/e5ba14d7-1553-4c80-80b9-6a031a19f66f/Untitled.png)<br>
![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/8465279d-2627-4cfd-a281-ff7e582750e1/Untitled.png)<br>
ENOENT오류가 나타나서 'echo $?' 를 입력했을 때 2의 값이 나오는게 보일 것이다.<br>
여기서 echo $? 는 마지막으로 출력된 값을 출력해서 보여주는 명령어라고 보면 됩니다.<br><br>

커널영역에서 Hello wrold<br>


  #include <linux/init.h>
  #include <linux/module.h>
  #include <linux/kernel.h>
 
  static int hello_init(void)
  {
      printk("Hello, world\n");
      return 0;
  }
  static void hello_exit(void)
  {
      printk("Goodbye, world\n");
  }
 
  module_init(hello_init);        /module_init 시작
  module_exit(hello_exit);        /module_exit 종료
 
  MODULE_LICENSE("Dual BSD/GPL"); /안 넣으면 오류발생하니까 꼭 넣자.<br>

**커널에서는 printk를 사용한다!!!<br>

이제 Makefile을 넣어준다.<br>

  MOD := hello
  obj-m := $(MOD).o             //모듈의 오브젝트명
 
  CROSS = ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-  //gcc있다보니 주석해도 오류는 없다.
  #KDIR := /lib/modules/$(shell uname -r)/build
  KDIR := /home/udooer/kernel/linux_kernel-3.14-1.0.x-udoo
  PWD := $(shell pwd)
 
  default:
      $(MAKE) -C $(KDIR) M=$(PWD) modules $(CROSS) //위에 있는 KDIR, PWD, CROSS
  #   cp $(MOD).ko /srv/nfs
  clean:
  #   rm -rf *.ko              //ko은 안지워지게 하려고 주석
      rm -rf *.mod.*
      rm -rf .*.cmd
      rm -rf *.o
      rm -rf modules.order
      rm -rf Module.symvers
      rm -rf $(MOD).mod
<br>
![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/f3a7b842-c115-40cc-b7c3-fcdd403d213d/Untitled.png)<br>
이제 make명령어를 주면<br>
![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/ba83aa6f-119e-4786-892d-0528f960f5fb/Untitled.png)<br>
hello.ko만들어진걸 볼 수 있다.<br>
sudo insmod hello.ko<br>
lsmod 현재 시스템에서 로드된 커널 모듈들의 정보를 출력하는 명령어로 아래 사진처럼<br>
![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/abce2038-afd8-47c0-9c08-2c10b12e958a/Untitled.png)<br>
Hello가 보일 것이다.<br>
dmesg 리눅스에서 시스템 로그 메시지를 출력하는 명령어<br>
![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/2b61c61f-817d-43a6-9465-070972bbdeaf/Untitled.png)<br>
sudo rmmod hello : 제거 명령어<br>
lsmod<br>
dmesg<br>
![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/18fc3dfd-9d42-4001-80ce-059ca2a9bfb8/Untitled.png)<br>
위 그림처럼 insmod로 등록하면 hello.c에 만들었던 hello_init에 넣었던, 'Hello, world'를, 이후 rmmod로 해제하면 hello_exit에 넣었던, 'goodbye, world'를 출력
