.PHONY: clean all COMMONDDS_HOME

COMMONDDS_HOME := ../..

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

GENERATED := src/idl/HelloWorld.h

all: $(GENERATED) pub sub

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c -o obj/$(notdir $@) $<

$(GENERATED): src/HelloWorld.idl
	@mkdir -p obj/
	@mkdir -p src/idl
	$(NDDSHOME)/bin/rtiddsgen -d src/idl src/HelloWorld.idl -replace -language C++

pub: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(filter-out obj/HelloSubscriber.o, $(addprefix obj/,$(notdir $(OBJS)))) $(LIBS)

sub: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(filter-out obj/HelloPublisher.o, $(addprefix obj/,$(notdir $(OBJS)))) $(LIBS)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c -o obj/$(notdir $@) $<

clean:
	@rm -rf obj
	@rm -rf src/idl/*
	@rm -f pub sub

