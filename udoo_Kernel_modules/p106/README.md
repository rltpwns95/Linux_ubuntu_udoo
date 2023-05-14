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
sudo rmmod hello로 hello를 제거<br>
sudo dmesg를 입력하면<br>
![Untitled](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/7b82aa2e-c647-4f4d-8a45-229ef2576286)<br>
이처럼 goodbye, world를 출력한다.<br>
이전코드를 복사할거면 sudo cp로 한번에 복사가 가능하긴한데 파일 중간만 저장할거면 '1, 72 w ___.txt' 1에서 72번째 줄을 ___.txt파일에 저장하겠다는 명령어.<br><br>

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>            //led쓰려고

#define DEBUG 1
#define IMX_GPIO_NR(bank, nr)       (((bank) - 1) * 32 + (nr))
					  메크로함수
 int led[] = {                                             4개의 배열을 잡음 led[4]
	 IMX_GPIO_NR(1, 16),   //16
	 IMX_GPIO_NR(1, 17),   //17
	 IMX_GPIO_NR(1, 18),   //18
	 IMX_GPIO_NR(1, 19),   //19    1개에 32개씩 있다.
 };
static int led_request(void)         //시스템콜에 있는걸 그대로 이용했다
{
	int ret = 0;
	int i;           //4
	for (i = 0; i < ARRAY_SIZE(led); i++) {
		ret = gpio_request(led[i], "gpio led");                  16,17,18,19를 등록하기 위해서
		if(ret<0){                                               다른곳에서 request를 등록했다면 FAILED이 나온다.
			printk("#### FAILED Request gpio %d. error : %d \n", led[i], ret);
		}
	}
	return ret;
}
static void led_free(void)
{
	    int i;
		for (i = 0; i < ARRAY_SIZE(led); i++){
			gpio_free(led[i]);
		}
}
                                          8421
void led_write(unsigned long data) //15-> 1111(2진수)
                                         x0001
                                          0001
{
	    int i;
		for(i = 0; i < ARRAY_SIZE(led); i++){
			gpio_direction_output(led[i], (data >> i ) & 0x01);  1111->0111->0011->0001
																													 전부 1이라 4개다 on
gpio_set_value(led[i], (data >> i ) & 0x01);위에서 이미 초기화
			
			gpio_direction_output(led[i], 0);
			gpio_direction_output(led[i], (data >> i ) & 0x01); 두 함수를 하나로 쓸 수 있다.
			
		}
#if DEBUG
		printk("#### %s, data = %ld\n", __FUNCTION__, data);
#endif
}
void led_read(unsigned long * led_data)
{
	    int i;
		unsigned long data=0;
		unsigned long temp;
		for(i=0;i<4;i++)
		{
			gpio_direction_input(led[i]); //error led all turn off
			temp = gpio_get_value(led[i]) << i;
			data |= temp;
		}
#if DEBUG
		printk("#### %s, data = %ld\n", __FUNCTION__, data);
#endif
		*led_data = data;
		led_write(data);
		return;
}

static int led_init(void)
{
	printk("Hello, world\n");
	led_request();
	led_write(15);
	//led_free();
	return 0;

}
static void led_exit(void)
{
	printk("goodbye, world\n");
	led_write(0);
	led_free();
	return 0;
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("Dual BSD/GPL");
--------------------------------------------------------------
#define ARRAY_SIZE(_A) (sizeof(_A) / sizeof((_A)[0])) 즉 4이다.
led_exit()은 필요없다.
