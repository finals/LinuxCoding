ifneq ($(KERNELRELEASE),)
	obj-m := simpleblk.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

clean:
	rm -f *.o *.ko *.symvers *.mod.o *.mod.c *.order *.cmd *.tmp_versions