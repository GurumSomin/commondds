.PHONY: clean all

OPENDDS_HOME = $(HOME)/OpenDDS-3.11
TAO_ROOT = $(OPENDDS_HOME)/ACE_wrappers/TAO
ACE_ROOT = $(OPENDDS_HOME)/ACE_wrappers
MPC_ROOT = $(OPENDDS_HOME)/ACE_wrappers/MPC
DDS_ROOT = $(OPENDDS_HOME)

NAME = opendds
CC = g++
CFLAGS = -Iinclude -I../include -I$(ACE_ROOT) -I$(TAO_ROOT) -I$(DDS_ROOT) -I../examples/hello/include \
	-fPIC \
	-Wl,-E \
	-Wno-deprecated-declarations -W -Wpointer-arith \
	-fno-strict-aliasing \
	-pthread -ggdb -pipe \
	-D_GNU_SOURCE -D__ACE_INLINE__

LIBS = -L$(ACE_ROOT)/lib \
		-L$(DDS_ROOT)/lib \
		-lOpenDDS_Tcp \
		-lOpenDDS_InfoRepoDiscovery \
		-lOpenDDS_Dcps \
		-lTAO_BiDirGIOP \
		-lTAO_PI \
		-lTAO_CodecFactory \
		-lTAO_PortableServer \
		-lTAO_AnyTypeCode \
		-lTAO \
		-lACE \
		-ldl \
		-lrt

SRCS = src/opendds.cpp
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

all: libdds_$(NAME).so

libdds_$(NAME).so: $(OBJS)
	$(CC) -shared $(CFLAGS) -o $@ $^ $(LIBS)

obj/%.o: src/%.cpp
	-mkdir -p obj
	$(CC) -c -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -rf obj
	rm -f libdds_$(NAME).so
