ccflags-y := -I$(PWD)/inc
# normal makefile
obj-m   := hello1.o hello2.o
ccflags-y += -g 
KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp hello1.ko hello1.ko.unstripped
	cp hello2.ko hello2.ko.unstripped
	$(CROSS_COMPILE)strip -g hello1.ko
	$(CROSS_COMPILE)strip -g hello2.ko
	
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
