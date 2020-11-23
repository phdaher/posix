SUBDIRS=echo cat head tail ls shell

CMDS=all clean

$(CMDS):
	@for dir in $(SUBDIRS); \
	do \
		$(MAKE) -C $${dir} $@ || exit $$?; \
	done
