#모률 매개변수 예제<br><br>

보통 부트로더의 용션 지정 기능을 이용하거나 모률 유틸리티인 insmod 명령에서 지정하여 커널 명령 형식으로조정할수 있다. <br>
이렇게 디바이스드라이버와같은초기값중에서 외부에서 변경할수있는것을모률매개변수라한다. <br>
디바이스드라이버를모율로만들었다면 다음 예처럼 insmod 명령으로 매개변수를 지정할수 있다.<br>
  insmo d   . / test .ko  onev alue=Ox27  t wo string=" Oh  my   g o d!! "<br>
insmod 명령을 통해 전달하는 모률 매개변수는 커널에 모률을 삽일할 때 처리된다.<br>
insmod() 힘수를 사용해 모율 형태로 추가되는 객체 내 변수에 값을 대입하기 위해 10진수는 17 ，  8진수는021 ，   16진수는Oxll 과같은형식으로 지정한다. 전달해야할값이 배열 형태라면 지정된 순서와 쉽표u로 구분된다. 각 요소는 값을 생략함으로써 넘어갈 수 있다. 만약
값이 큰따옴표 (")로 시작한다면 문자열은 C에서 사용하는 이스케이프 시권스 처리도 할 수있다. 셀 프롬프트에서 인용부호 자체는셀 해석에서 먼저 처리되기 때문에 조사해야힌다.<br><br>
예제는 디바이스 드라이버 내부에 정의된 정수<br>
값 하나와 문자열 값 하니를 모률 유틸리티 insmod 명령으로 제어할 수 있도록 선언히는 방법에대해설명한다.<br>
![image](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/466b6d9f-3304-4540-b7b2-29a9a66ef5a9)<br>
##실행방법<br>
make 명령어로 컴파일하고, 모듈을 커널에 적재하고 모듈 매개변수를 전달한다.<br>
sudo insmod hello.ko onevalue=0x27 twostring=\"oh my godrmmod test\"<br>
sudo rmmod hello.ko<br>

##실행결과<br>
Hello, world [ onevalue=39:twostring=oh my godrmmod test]<br>
Goodbye world
