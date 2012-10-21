PACKAGE	= libSystem
VERSION	= 0.1.6
SUBDIRS	= data doc include src tests
RM	?= rm -f
LN	?= ln -f
TAR	?= tar -czvf


all: subdirs

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE)) || exit; done

clean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) clean) || exit; done

distclean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) distclean) || exit; done

dist:
	$(RM) -r -- $(PACKAGE)-$(VERSION)
	$(LN) -s -- . $(PACKAGE)-$(VERSION)
	@$(TAR) $(PACKAGE)-$(VERSION).tar.gz -- \
		$(PACKAGE)-$(VERSION)/data/Makefile \
		$(PACKAGE)-$(VERSION)/data/libSystem.pc.in \
		$(PACKAGE)-$(VERSION)/data/pkgconfig.sh \
		$(PACKAGE)-$(VERSION)/data/project.conf \
		$(PACKAGE)-$(VERSION)/doc/Makefile \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc.sh \
		$(PACKAGE)-$(VERSION)/doc/project.conf \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/Makefile \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/libSystem-docs.xml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/project.conf \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/Makefile \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/System.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/array.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/buffer.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/config.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/error.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/event.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/file.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/hash.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/libSystem-unused.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/object.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/parser.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/plugin.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/string.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/token.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/project.conf \
		$(PACKAGE)-$(VERSION)/include/System.h \
		$(PACKAGE)-$(VERSION)/include/Makefile \
		$(PACKAGE)-$(VERSION)/include/project.conf \
		$(PACKAGE)-$(VERSION)/include/System/array.h \
		$(PACKAGE)-$(VERSION)/include/System/buffer.h \
		$(PACKAGE)-$(VERSION)/include/System/config.h \
		$(PACKAGE)-$(VERSION)/include/System/error.h \
		$(PACKAGE)-$(VERSION)/include/System/event.h \
		$(PACKAGE)-$(VERSION)/include/System/file.h \
		$(PACKAGE)-$(VERSION)/include/System/hash.h \
		$(PACKAGE)-$(VERSION)/include/System/object.h \
		$(PACKAGE)-$(VERSION)/include/System/parser.h \
		$(PACKAGE)-$(VERSION)/include/System/plugin.h \
		$(PACKAGE)-$(VERSION)/include/System/string.h \
		$(PACKAGE)-$(VERSION)/include/System/token.h \
		$(PACKAGE)-$(VERSION)/include/System/Makefile \
		$(PACKAGE)-$(VERSION)/include/System/project.conf \
		$(PACKAGE)-$(VERSION)/src/array.c \
		$(PACKAGE)-$(VERSION)/src/buffer.c \
		$(PACKAGE)-$(VERSION)/src/config.c \
		$(PACKAGE)-$(VERSION)/src/error.c \
		$(PACKAGE)-$(VERSION)/src/event.c \
		$(PACKAGE)-$(VERSION)/src/hash.c \
		$(PACKAGE)-$(VERSION)/src/object.c \
		$(PACKAGE)-$(VERSION)/src/parser.c \
		$(PACKAGE)-$(VERSION)/src/plugin.c \
		$(PACKAGE)-$(VERSION)/src/string.c \
		$(PACKAGE)-$(VERSION)/src/token.c \
		$(PACKAGE)-$(VERSION)/src/Makefile \
		$(PACKAGE)-$(VERSION)/src/token.h \
		$(PACKAGE)-$(VERSION)/src/project.conf \
		$(PACKAGE)-$(VERSION)/tests/string.c \
		$(PACKAGE)-$(VERSION)/tests/Makefile \
		$(PACKAGE)-$(VERSION)/tests/tests.sh \
		$(PACKAGE)-$(VERSION)/tests/project.conf \
		$(PACKAGE)-$(VERSION)/Makefile \
		$(PACKAGE)-$(VERSION)/COPYING \
		$(PACKAGE)-$(VERSION)/config.sh \
		$(PACKAGE)-$(VERSION)/README \
		$(PACKAGE)-$(VERSION)/project.conf
	$(RM) -- $(PACKAGE)-$(VERSION)

install:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) install) || exit; done

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done

.PHONY: all subdirs clean distclean dist install uninstall
