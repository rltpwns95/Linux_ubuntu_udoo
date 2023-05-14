#커널 모듈로 led_app을 이용하여 led제어하기.<br>

1. 인자로 전달된 led 값에 따라 LED를 켜거나 끕니다.<br>
2. LED의 상태를 읽어와서 켜진 LED는 'O', 꺼진 LED는 'X'로 출력합니다.<br><br>

DEVICE_FILENAME 상수는 LED 장치 파일의 경로를 나타냅니다.<br>print_led() 함수는 전달된 led 값에 따라 LED의 상태를 출력하는 함수입니다.<br>main() 함수에서는 인자로 전달된 led 값을 buff 변수에 저장한 후, open() 함수를 사용하여 LED 장치 파일을 열고, write() 함수를 사용하여 buff 값을 LED 장치 파일에 씁니다.<br>그리고 read() 함수를 사용하여 LED 장치 파일에서 읽은 값을 buff 변수에 저장하고, print_led() 함수를 호출하여 LED 상태를 출력합니다.<br>마지막으로 close() 함수를 사용하여 LED 장치 파일을 닫습니다.

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
