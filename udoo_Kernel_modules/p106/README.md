##udoo에서 ubuntu로 돌려보자.<br>
udoo에서 기존에 쓰던 파일을 nfs를 이용해서 ubuntu에 보내줬다.<br>
파일 Makefile를 확인<br>
![image](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/c53ebe1e-ab9c-4380-94e1-3b918b1d0518)<br>
ubuntu에선 KDIR위에껄 주석을 풀고 아래는 주석처리 왜 위에껄 그대로 쓸까?<br>
![Untitled](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/a7af808f-48ba-48ee-983b-cc2e29f7172e)<br>

udoo에서 하듯 동일하게 실행<br>
make<br>
file hello.ko<br>
sudo insmod hello.ko<br>
lsmod<br>
![Untitled](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/0f7b4cde-a6f3-40e0-a111-3a09d5a57049)<br>

