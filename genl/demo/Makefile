ifneq ($(KERNELRELEASE),)

obj-m := demo_kern.o

else
	
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules 
	gcc -o demo_user demo_user.c

modules_install:
	make -C $(KDIR) M=$(PWD) modules_install ARCH=arm CROSS_COMPILE=arm-bcm2708-linux-gnueabi-
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers  modul*
	rm -f ./release/*

endif