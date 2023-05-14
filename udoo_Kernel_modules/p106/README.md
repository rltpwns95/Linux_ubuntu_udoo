##udoo에서 ubuntu로 돌려보자.<br>
udoo에서 기존에 쓰던 파일을 nfs를 이용해서 ubuntu에 보내줬다.<br>
파일 Makefile를 확인<br>

  MOD := hello
  obj-m := $(MOD).o
 
  #CROSS = ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
  KDIR := /lib/modules/$(shell uname -r)/build
  #KDIR := /home/udooer/kernel/linux_kernel-3.14-1.0.x-udoo
  PWD := $(shell pwd)
 
  default:
      $(MAKE) -C $(KDIR) M=$(PWD) modules $(CROSS)
  #   cp $(MOD).ko /srv/nfs
  clean:
  #   rm -rf *.ko
      rm -rf *.mod.*
      rm -rf .*.cmd
      rm -rf *.o
      rm -rf modules.order
      rm -rf Module.symvers
      rm -rf $(MOD).mod
      rm -rf .tmp_versions

ubuntu에선 KDIR위에껄 주석을 풀고 아래는 주석처리 왜 위에껄 그대로 쓸까?<br>
![Untitled](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/a7af808f-48ba-48ee-983b-cc2e29f7172e)<br>

udoo에서 하듯 동일하게 실행<br>
make<br>
file hello.ko<br>
sudo insmod hello.ko<br>
lsmod<br>
![Untitled](https://github.com/rltpwns95/Linux_ubuntu_udoo/assets/124419697/0f7b4cde-a6f3-40e0-a111-3a09d5a57049)<br>
