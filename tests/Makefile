ifdef MLANG_PATH
	SRC = $(MLANG_PATH)
else ifdef M_PATH
	SRC = $(M_PATH)
else
	SRC = /usr/local/src/mBackend
endif

ifeq ($m, 32)
OBJ	=	$(SRC)/objs32
MF	=	-m32
DEP = dep32
else
OBJ	=	$(SRC)/objs
MF	=	-m64
DEP = dep
endif

ifeq ($p, 1)
OBJ	:=	${OBJ}p
DEP := ${DEP}p
PROF	=	-pg
PROFC	=	-pg -DDEBUG=1
OPT	=
else
PROF	=
OPT	=	-fno-exceptions -Os
endif

MLANG_DIR:=$(CURDIR)
CFLAGS = -Wall -Wno-parentheses -Wno-trigraphs ${OPT} ${MF} -ggdb -march=core2 -mfpmath=sse -mssse3 -fno-strict-aliasing -fno-strict-overflow -fwrapv -fno-omit-frame-pointer ${PROFC}
LDFLAGS = ${MF} -lm -lz -lpthread -lrt -lcrypto -lpcre -lre2 -ggdb -rdynamic ${PROF}

CINCLUDE	= -iquote $(SRC)/MLANG -iquote $(SRC)/drinkless -iquote $(SRC)/common -iquote $(MLANG_DIR)/mlang
MLANG_OBJ := objs
EXE	:=	bin

ifeq ($p, 1)
MLANG_OBJ	:=	${MLANG_OBJ}p
EXE	:=	${EXE}p
endif

OBJDIRS	=	${EXE} ${DEP} ${MLANG_OBJ}

SRVOBJS	=	${OBJ}/common/kdb-data-common.o ${OBJ}/common/fast-backtrace.o ${OBJ}/common/server-functions.o ${OBJ}/common/utf8_utils.o \
			${OBJ}/common/crc32.o ${OBJ}/common/md5.o ${OBJ}/common/sha1.o ${OBJ}/common/base64.o ${OBJ}/common/unicode-utils.o \
			${OBJ}/net/net-events.o ${OBJ}/net/net-buffers.o ${OBJ}/net/net-crypto-aes.o ${OBJ}/crypto/aesni256.o

.PHONY:	all script engine main create_dirs

all:	main
engine: ${EXE}/engine
script: ${MLANG_OBJ}/script.o
main: ${EXE}/main

MLANG_ENGINE_OBJ=${OBJ}/MLANG/php-engine_.o

SUBDIRS:=$(patsubst %/,%,$(sort $(dir $(wildcard mlang/*/))))
SUBDIR_OBJS := $(SUBDIRS:%=$(MLANG_OBJ)/%.o)

ALL_CPP_FILES:=$(foreach dir,${SUBDIRS},$(wildcard ${dir}/*.cpp))
ALL_CPP_OBJS := $(patsubst %.cpp, $(MLANG_OBJ)/%.o, ${ALL_CPP_FILES})

OBJDIRS += $(foreach dir,${SUBDIRS},${MLANG_OBJ}/${dir})
DEPDIRS += $(foreach dir,${SUBDIRS},${DEP}/${dir})

DIRS = ${OBJDIRS} ${DEPDIRS}

create_dirs: ${DIRS}
${DIRS}:
	@test -d $@ || mkdir -p $@

DEPENDENCE_CPP := $(subst ${MLANG_OBJ}/,${DEP}/,$(patsubst %.o,%.d,${ALL_CPP_OBJS}))
-include ${DEPENDENCE_CPP}

${ALL_CPP_OBJS}:${MLANG_OBJ}/%.o: %.cpp | create_dirs
	${CXX} -c ${CFLAGS} ${CINCLUDE} -MP -MD -MF ${DEP}/$*.d -MQ ${MLANG_OBJ}/$*.o -o $@ $<

${MLANG_OBJ}/script.o: ${SUBDIR_OBJS} | create_dirs
	ld -r -o $@ $^

${EXE}/engine: ${SUBDIR_OBJS} ${MLANG_ENGINE_OBJ} | create_dirs
	${CXX} -o $@ $^ ${LDFLAGS}

${EXE}/main: $(MLANG_OBJ)/mlang/xmain.o ${MLANG_OBJ}/script.o ${OBJ}/MLANG/runtime/allocator.o ${OBJ}/MLANG/runtime/array_functions.o ${OBJ}/MLANG/runtime/bcmath.o ${OBJ}/MLANG/runtime/datetime.o ${OBJ}/MLANG/runtime/drivers.o ${OBJ}/MLANG/runtime/exception.o ${OBJ}/MLANG/runtime/files.o ${OBJ}/MLANG/runtime/interface.o ${OBJ}/MLANG/runtime/math_functions.o ${OBJ}/MLANG/runtime/mbstring.o ${OBJ}/MLANG/runtime/misc.o ${OBJ}/MLANG/runtime/openssl.o ${OBJ}/MLANG/runtime/regexp.o ${OBJ}/MLANG/runtime/rpc.o ${OBJ}/MLANG/runtime/string_functions.o ${OBJ}/MLANG/runtime/url.o ${OBJ}/MLANG/runtime/zlib.o ${OBJ}/MLANG/php_script.o ${OBJ}/drinkless/dl-utils-lite.o ${SRVOBJS} | create_dirs
	${CXX} -o $@ $^ ${LDFLAGS}


.SECONDEXPANSION:
${SUBDIR_OBJS} : $$(filter-out $(MLANG_OBJ)/mlang/xmain.o,$$(patsubst %.cpp,$(MLANG_OBJ)/%.o,$$(wildcard $$(patsubst $(MLANG_OBJ)/%.o,%,$$@)/*.cpp))) | create_dirs
	ld -r -o $@ $^
