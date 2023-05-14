위 코드는 /dev 디렉토리에 "testdev1"이라는 캐릭터 장치 파일을 생성하고, 이 파일을 읽기/쓰기 가능하도록 open() 함수를 이용하여 열어보는 코드입니다.<br><br>

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
} 
mknod() 함수 호출에서 에러가 발생하면, 생성하려는 파일이 이미 존재하는 경우가 대부분이므로 EPERM이 아니라 ENOENT를 리턴하는 것이 더 적절합니다.
