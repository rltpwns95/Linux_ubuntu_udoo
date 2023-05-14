make<br>
file led.ko<br>
sudo insmod led.ko<br>
lsmod<br>
sudo dmesg   (이걸 쓰면 화면에 아무것도 안나오다가 명령어를 주면 출력됨)<br>
![Untitled](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/a8227ad0-64b4-4dee-b205-765bb3d29051)<br>
sudo rmmod led.ko   (ko생략가능)<br>
sudo cat /proc/kmsg<br>
만약 sudo insmod led.ko를 중복으로 쓰면 이미 사용중이라 안된다.<br>
다시 지웠다가 등록하면 가능하다.<br>
입력한 값에 따라 led켜기<br>
앞에서 led썼던 폴더가 있어서 그 폴더를 그대로 복사했다.<br>
이후 sudo vi led.c로 텍스트를 변경하였다.<br>
	#include <linux/init.h>
	#include <linux/module.h>
	#include <linux/kernel.h>
	#include <linux/gpio.h>
	#include <linux/moduleparam.h>
	
	#define DEBUG 1
	#define IMX_GPIO_NR(bank, nr)       (((bank) - 1) * 32 + (nr))
	
	static int onevalue = 1;
	static char *twostring = NULL;
	
	module_param(onevalue, int, 0);
	module_param(twostring, charp, 0);
	
	 int led[] = {
		 IMX_GPIO_NR(1, 16),   //16
		 IMX_GPIO_NR(1, 17),   //17
		 IMX_GPIO_NR(1, 18),   //18
		 IMX_GPIO_NR(1, 19),   //19
	 };
	static int led_request(void)
	{
		int ret = 0;
		int i;
		for (i = 0; i < ARRAY_SIZE(led); i++) {
			ret = gpio_request(led[i], "gpio led");
			if(ret<0){
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
	
	void led_write(unsigned long data)
	{
		    int i;
			for(i = 0; i < ARRAY_SIZE(led); i++){
				gpio_direction_output(led[i], (data >> i ) & 0x01);
	//gpio_set_value(led[i], (data >> i ) & 0x01);위에서 이미 초기화
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
		printk("Hello, world[onevalue=%d:twostring=%s]\n", onevalue, twostring);
		led_request();
		led_write(onevalue);
	//	led_free();
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
	
	/* 모듈에 대한 정보(라이센스, 저자, 설명)를 나타내는 매크로이다. */
	MODULE_AUTHOR("YOU Young-chang frog@falinux.com");
	MODULE_DESCRIPTION("Module Parameter Test Module");
	MODULE_LICENSE("Dual BSD/GPL");
static을 사용한 이유는? 여기 파일안에서만 사용하겠다는 의미로 static를 사용.<br>
다른 파일에서도 같은 이름이 있을 경우 문제가 발생하니까
