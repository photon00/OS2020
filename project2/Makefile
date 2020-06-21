SUBDIRS := master_device slave_device user_program

.PHONY: all ksocket subdirs install uninstall clean list
all: subdirs

ksocket:
	cd ksocket; \
	$(MAKE)

subdirs: ksocket
	for dir in $(SUBDIRS); do \
		cd $$dir; \
		$(MAKE); \
		cd .. ; \
	done

install:
	insmod ksocket/ksocket.ko ;\
	insmod master_device/master_device.ko ;\
	insmod slave_device/slave_device.ko

uninstall:
	rmmod slave_device ;\
	rmmod master_device ;\
	rmmod ksocket ;

clean:
	cd ksocket && make clean
	for dir in $(SUBDIRS); do \
		cd $$dir; \
		$(MAKE) clean; \
		cd .. ; \
	done

list:
	@ lsmod | grep -E '(master|slave|ksocket)' ; true
