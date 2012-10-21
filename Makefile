CC?=gcc

#compile c99
C99MAIN=c99/src/main.c
#compile cpp
CPPMAIN=cpp/src/main.c

CFLAGS=-Ic99/include -Icpp/include
CFLAGS+=-DTC_NULL=0 -g -ggdb
CFLAGS+=-I../../../System/src/libSystem/include/
SRC+=libSystem/src/object.c
SRC+=libSystem/src/error.c
SRC+=libSystem/src/token.c
SRC+=libSystem/src/string.c
SRC+=libSystem/src/parser.c
SRC+=libSystem/src/plugin.c
SRC+=c99/src/c99.c
SRC+=c99/src/parser.c
SRC+=c99/src/scanner.c
SRC+=c99/src/tokenset.c
SRC+=c99/src/code.c
SRC+=cpp/src/cpp.c
SRC+=cpp/src/parser.c
SRC+=cpp/src/scanner.c


#CFLAGS+=-DCPP_CODE_NULL=NULL

all: asm c99 cpp libSystem
	${CC} ${CFLAGS} ${SRC} -ldl ${C99MAIN} -o _c99 
	${CC} ${CFLAGS} ${SRC} -ldl ${CPPMAIN} -o _cpp

clean:
	rm -f _c99 _cpp 

asm:
	sh gitclonedir.sh DeforaOS/DeforaOS/Apps/Devel/src/asm

c99:
	sh gitclonedir.sh DeforaOS/DeforaOS/Apps/Devel/src/c99

cpp:
	sh gitclonedir.sh DeforaOS/DeforaOS/Apps/Devel/src/cpp

libSystem:
	sh gitclonedir.sh DeforaOS/DeforaOS/System/src/libSystem


wcl:
	wc -l ${SRC} ${MAIN}
	ls -l ${SRC} ${MAIN}
