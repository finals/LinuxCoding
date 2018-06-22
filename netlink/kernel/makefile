ifneq ($(KERNELRELEASE),)
	obj-m := kern_example.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
