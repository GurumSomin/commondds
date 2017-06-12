.PHONY: clean all COMMONDDS_HOME

CXX = g++
RTI_INCLUDES = -I$(NDDSHOME)/include -I$(NDDSHOME)/include/ndds
CXXFLAGS := -DRTI_UNIX -DRTI_LINUX -DRTI_64BIT -m64 -O2 -Wall
CXXFLAGS += -Iinclude -Isrc/idl $(RTI_INCLUDES)

SRCS = src/pub.cpp \
	   src/sub.cpp

GSRCS = src/idl/Hello.cxx		\
	    src/idl/HelloPlugin.cxx	\
	    src/idl/HelloSupport.cxx
OBJS = $(GSRCS:%.cxx=%.o) $(SRCS:%.cpp=%.o)

NDDSLIBS = -lnddscppz -lnddscz -lnddscorez
SYSLIBS = -ldl -lnsl -lm -lpthread -lrt
LIBS = -L$(NDDSHOME)/lib/x64Linux3gcc4.8.2 $(NDDSLIBS) $(SYSLIBS)

GENERATED := src/idl/Hello.h

all: generate pub sub

%.o: %.c**
	$(CXX) $(CXXFLAGS) -c -o obj/$(notdir $@) $<

generate: $(GENERATED)

$(GENERATED): src/Hello.idl
	@mkdir -p obj/
	@mkdir -p src/idl
	$(NDDSHOME)/bin/rtiddsgen -d src/idl src/Hello.idl -replace -language C++

pub: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(filter-out obj/sub.o, $(addprefix obj/,$(notdir $(OBJS)))) $(LIBS)

sub: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(filter-out obj/pub.o, $(addprefix obj/,$(notdir $(OBJS)))) $(LIBS)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c -o obj/$(notdir $@) $<

clean:
	@rm -rf obj src/idl
	@rm -f pub sub

