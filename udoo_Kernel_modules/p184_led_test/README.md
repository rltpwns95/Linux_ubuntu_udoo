#커널 모듈로 led_app을 이용하여 led제어하기.

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
