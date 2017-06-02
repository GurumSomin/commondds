.PHONY: clean all COMMONDDS_HOME

CXX = g++
RTI_INCLUDES = -I$(NDDSHOME)/include -I$(NDDSHOME)/include/ndds
CXXFLAGS := -DRTI_UNIX -DRTI_LINUX -DRTI_64BIT -m64 -O2 -Wall
CXXFLAGS += -Iinclude -Isrc/idl $(RTI_INCLUDES)

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

all: generate pub sub

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c -o obj/$(notdir $@) $<

generate: $(GENERATED)

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
	@rm -rf obj src/idl
	@rm -f pub sub

