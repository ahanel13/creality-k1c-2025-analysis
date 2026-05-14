obj-m := sc_patch.o

KDIR  ?= /tmp/linux-5.10.186
ARCH  ?= mips
CROSS ?= mipsel-linux-gnu-

all:
	$(MAKE) -C $(KDIR) M=$(CURDIR) modules \
		ARCH=$(ARCH) CROSS_COMPILE=$(CROSS)

clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) clean \
		ARCH=$(ARCH) CROSS_COMPILE=$(CROSS)
