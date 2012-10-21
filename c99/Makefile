PACKAGE	= C99
VERSION	= 0.0.0
SUBDIRS	= data doc include src
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
		$(PACKAGE)-$(VERSION)/data/C99.pc.in \
		$(PACKAGE)-$(VERSION)/data/pkgconfig.sh \
		$(PACKAGE)-$(VERSION)/data/project.conf \
		$(PACKAGE)-$(VERSION)/doc/Makefile \
		$(PACKAGE)-$(VERSION)/doc/GRAMMAR \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc.sh \
		$(PACKAGE)-$(VERSION)/doc/project.conf \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/Makefile \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/C99-docs.xml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/project.conf \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/Makefile \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/c99-unused.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/c99.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/target.sgml \
		$(PACKAGE)-$(VERSION)/doc/gtkdoc/tmpl/project.conf \
		$(PACKAGE)-$(VERSION)/include/C99.h \
		$(PACKAGE)-$(VERSION)/include/Makefile \
		$(PACKAGE)-$(VERSION)/include/project.conf \
		$(PACKAGE)-$(VERSION)/include/C99/c99.h \
		$(PACKAGE)-$(VERSION)/include/C99/target.h \
		$(PACKAGE)-$(VERSION)/include/C99/Makefile \
		$(PACKAGE)-$(VERSION)/include/C99/project.conf \
		$(PACKAGE)-$(VERSION)/src/c99.c \
		$(PACKAGE)-$(VERSION)/src/code.c \
		$(PACKAGE)-$(VERSION)/src/main.c \
		$(PACKAGE)-$(VERSION)/src/parser.c \
		$(PACKAGE)-$(VERSION)/src/scanner.c \
		$(PACKAGE)-$(VERSION)/src/tokenset.c \
		$(PACKAGE)-$(VERSION)/src/Makefile \
		$(PACKAGE)-$(VERSION)/src/code.h \
		$(PACKAGE)-$(VERSION)/src/common.h \
		$(PACKAGE)-$(VERSION)/src/parser.h \
		$(PACKAGE)-$(VERSION)/src/scanner.h \
		$(PACKAGE)-$(VERSION)/src/tokenset.h \
		$(PACKAGE)-$(VERSION)/src/project.conf \
		$(PACKAGE)-$(VERSION)/src/sets/Makefile \
		$(PACKAGE)-$(VERSION)/src/sets/abstract_declarator.set \
		$(PACKAGE)-$(VERSION)/src/sets/abstract_or_declarator.set \
		$(PACKAGE)-$(VERSION)/src/sets/argument_expr_list.set \
		$(PACKAGE)-$(VERSION)/src/sets/assignment_expr.set \
		$(PACKAGE)-$(VERSION)/src/sets/assignment_operator.set \
		$(PACKAGE)-$(VERSION)/src/sets/block_item.set \
		$(PACKAGE)-$(VERSION)/src/sets/block_item_list.set \
		$(PACKAGE)-$(VERSION)/src/sets/cast_expr.set \
		$(PACKAGE)-$(VERSION)/src/sets/compound_statement.set \
		$(PACKAGE)-$(VERSION)/src/sets/conditional_expr.set \
		$(PACKAGE)-$(VERSION)/src/sets/declaration.set \
		$(PACKAGE)-$(VERSION)/src/sets/declaration_list.set \
		$(PACKAGE)-$(VERSION)/src/sets/declaration_specifiers.set \
		$(PACKAGE)-$(VERSION)/src/sets/declarator.set \
		$(PACKAGE)-$(VERSION)/src/sets/designation.set \
		$(PACKAGE)-$(VERSION)/src/sets/designator.set \
		$(PACKAGE)-$(VERSION)/src/sets/direct_abstract_declarator.set \
		$(PACKAGE)-$(VERSION)/src/sets/direct_declarator.set \
		$(PACKAGE)-$(VERSION)/src/sets/enum_specifier.set \
		$(PACKAGE)-$(VERSION)/src/sets/enumeration_constant.set \
		$(PACKAGE)-$(VERSION)/src/sets/enumerator.set \
		$(PACKAGE)-$(VERSION)/src/sets/expression.set \
		$(PACKAGE)-$(VERSION)/src/sets/expression_statement.set \
		$(PACKAGE)-$(VERSION)/src/sets/external_declaration.set \
		$(PACKAGE)-$(VERSION)/src/sets/function_definition.set \
		$(PACKAGE)-$(VERSION)/src/sets/function_specifier.set \
		$(PACKAGE)-$(VERSION)/src/sets/identifier.set \
		$(PACKAGE)-$(VERSION)/src/sets/identifier_list.set \
		$(PACKAGE)-$(VERSION)/src/sets/init_declarator.set \
		$(PACKAGE)-$(VERSION)/src/sets/init_declarator_list.set \
		$(PACKAGE)-$(VERSION)/src/sets/iteration_statement.set \
		$(PACKAGE)-$(VERSION)/src/sets/jump_statement.set \
		$(PACKAGE)-$(VERSION)/src/sets/keyword.set \
		$(PACKAGE)-$(VERSION)/src/sets/labeled_statement.set \
		$(PACKAGE)-$(VERSION)/src/sets/parameter_declaration.set \
		$(PACKAGE)-$(VERSION)/src/sets/parameter_list.set \
		$(PACKAGE)-$(VERSION)/src/sets/parameter_type_list.set \
		$(PACKAGE)-$(VERSION)/src/sets/pointer.set \
		$(PACKAGE)-$(VERSION)/src/sets/postfix_expr.set \
		$(PACKAGE)-$(VERSION)/src/sets/primary_expr.set \
		$(PACKAGE)-$(VERSION)/src/sets/punctuator.set \
		$(PACKAGE)-$(VERSION)/src/sets/selection_statement.set \
		$(PACKAGE)-$(VERSION)/src/sets/specifier_qualifier_list.set \
		$(PACKAGE)-$(VERSION)/src/sets/statement.set \
		$(PACKAGE)-$(VERSION)/src/sets/storage_class_specifier.set \
		$(PACKAGE)-$(VERSION)/src/sets/struct_declaration.set \
		$(PACKAGE)-$(VERSION)/src/sets/struct_declaration_list.set \
		$(PACKAGE)-$(VERSION)/src/sets/struct_or_union_specifier.set \
		$(PACKAGE)-$(VERSION)/src/sets/type_name.set \
		$(PACKAGE)-$(VERSION)/src/sets/type_qualifier.set \
		$(PACKAGE)-$(VERSION)/src/sets/type_specifier.set \
		$(PACKAGE)-$(VERSION)/src/sets/typedef_name.set \
		$(PACKAGE)-$(VERSION)/src/sets/unary_expr.set \
		$(PACKAGE)-$(VERSION)/src/sets/unary_operator.set \
		$(PACKAGE)-$(VERSION)/src/sets/project.conf \
		$(PACKAGE)-$(VERSION)/src/target/asm.c \
		$(PACKAGE)-$(VERSION)/src/target/graph.c \
		$(PACKAGE)-$(VERSION)/src/target/indent.c \
		$(PACKAGE)-$(VERSION)/src/target/Makefile \
		$(PACKAGE)-$(VERSION)/src/target/asm/amd64.c \
		$(PACKAGE)-$(VERSION)/src/target/asm/i386.c \
		$(PACKAGE)-$(VERSION)/src/target/asm/i486.c \
		$(PACKAGE)-$(VERSION)/src/target/asm/i586.c \
		$(PACKAGE)-$(VERSION)/src/target/asm/i686.c \
		$(PACKAGE)-$(VERSION)/src/target/project.conf \
		$(PACKAGE)-$(VERSION)/Makefile \
		$(PACKAGE)-$(VERSION)/config.h \
		$(PACKAGE)-$(VERSION)/config.sh \
		$(PACKAGE)-$(VERSION)/project.conf
	$(RM) -- $(PACKAGE)-$(VERSION)

install:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) install) || exit; done

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done

.PHONY: all subdirs clean distclean dist install uninstall
