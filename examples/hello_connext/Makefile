.PHONY: clean all COMMONDDS_HOME
all: generate pub sub

COMMONDDS_HOME:
ifndef COMMONDDS_HOME
    COMMONDDS_HOME = ../..
endif

NDDSHOME:
ifndef NDDSHOME
    NDDSHOME = $(HOME)/rti_connext_dds-5.2.3
endif

CXX = g++
RTI_INCLUDES = -I$(NDDSHOME)/include -I$(NDDSHOME)/include/ndds
CXXFLAGS := -DRTI_UNIX -DRTI_LINUX -DRTI_64BIT -m64 -O2 -Wall
CXXFLAGS += -Iinclude -Isrc/idl -I$(COMMONDDS_HOME)/include $(RTI_INCLUDES)

SRCS = src/HelloPublisher.cxx		\
	   src/HelloSubscriber.cxx		\
	   src/idl/HelloWorld.cxx		\
	   src/idl/HelloWorldPlugin.cxx	\
	   src/idl/HelloWorldSupport.cxx
OBJS = $(SRCS:%.cxx=%.o)

NDDSLIBS = -lnddscppz -lnddscz -lnddscorez
SYSLIBS = -ldl -lnsl -lm -lpthread -lrt
LIBS = -L$(NDDSHOME)/lib/x64Linux3gcc4.8.2 $(NDDSLIBS) $(SYSLIBS)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c -o obj/$(notdir $@) $<

generate:
	mkdir -p src/idl
	$(NDDSHOME)/bin/rtiddsgen -d src/idl src/HelloWorld.idl -replace -language C++

pub: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(filter-out obj/HelloSubscriber.o, $(addprefix obj/,$(notdir $(OBJS)))) $(LIBS)

sub: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(filter-out obj/HelloPublisher.o, $(addprefix obj/,$(notdir $(OBJS)))) $(LIBS)

clean:
	rm -rf obj
	rm -f pub sub

