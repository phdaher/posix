SUBDIRS=echo cat head tail ls shell

CMDS=all clean

$(CMDS):
	@for dir in $(SUBDIRS); \
	do \
		$(MAKE) -C $${dir} $@ || exit $$?; \
	done

install:
	@for dir in $(SUBDIRS); \
	do \
		rm -f ../raiz_linux/root/bin/$${dir}; \
		cp -f $${dir}/$${dir} ../raiz_linux/root/bin/; \
	done

