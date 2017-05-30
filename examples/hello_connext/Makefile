ARCH=x64Linux3gcc4.8.2

CXX = g++
CXXFLAGS = -DRTI_UNIX -DRTI_LINUX -DRTI_64BIT -m64
CXXLD = g++
CXXLDFLAGS = -m64 -static-libgcc -Wl,--no-as-needed
SYSLIBS = -ldl -lnsl -lm -lpthread -lrt

ifeq ($(NDDSHOME), )
all:
	@echo "***************************************************************"
	@echo "The environment variable 'NDDSHOME' is not set!"
	@echo "To use this makefile you need to set NDDSHOME to the directory"
	@echo "where you have RTI Connext installed."
	@echo "***************************************************************"
	@false
endif


INCLUDES = -Iinclude -Isrc/idl -I$(NDDSHOME)/include -I$(NDDSHOME)/include/ndds

NDDSLIBS = -lnddscppz -lnddscz -lnddscorez

LIBS = -L$(NDDSHOME)/lib/$(ARCH) $(NDDSLIBS) $(SYSLIBS)

SOURCES = src/HelloPublisher.cpp        \
          src/HelloSubscriber.cpp

SOURCES_IDL = src/idl/HelloWorld.cxx    \
          src/idl/HelloWorldPlugin.cxx  \
          src/idl/HelloWorldSupport.cxx

HEADERS = include/HelloPublisher.h          \
          include/HelloSubscriber.h

HEADERS_IDL = src/idl/HelloWorld.h      \
          src/idl/HelloWorldPlugin.h    \
          src/idl/HelloWorldSupport.h

DIRECTORIES   = objs.dir
EXECUTABLE    = HelloPublisher HelloSubscriber
SOURCES_NODIR = $(notdir $(SOURCES))
SOURCES_IDL_NODIR = $(notdir $(SOURCES_IDL))
OBJECTS       = $(SOURCES_NODIR:%.cpp=objs/%.o) $(SOURCES_IDL_NODIR:%.cxx=objs/%.o)


objs/%.out: objs/%.o  objs/HelloWorld.o objs/HelloWorldPlugin.o objs/HelloWorldSupport.o
	$(CXXLD) $(CXXLDFLAGS) $^ -o $(@:%.out=%) $(LIBS)

objs/HelloWorld.o: src/idl/HelloWorld.cxx $(HEADERS_IDL)
	$(CXX) $(CXXFLAGS) -o $@ $(DEFINES) $(INCLUDES) -c $<

objs/HelloWorldPlugin.o: src/idl/HelloWorldPlugin.cxx $(HEADERS_IDL)
	$(CXX) $(CXXFLAGS) -o $@ $(DEFINES) $(INCLUDES) -c $<

objs/HelloWorldSupport.o: src/idl/HelloWorldSupport.cxx $(HEADERS_IDL)
	$(CXX) $(CXXFLAGS) -o $@ $(DEFINES) $(INCLUDES) -c $<

objs/%.o: src/%.cpp $(HEADERS) $(HEADERS_IDL)
	$(CXX) $(CXXFLAGS) -o $@ $(DEFINES) $(INCLUDES) -c $<

$(SOURCES_IDL) $(HEADERS_IDL): src/HelloWorld.idl
	@mkdir -p src/idl
	$(NDDSHOME)/bin/rtiddsgen -d src/idl src/HelloWorld.idl -replace -language C++

generate: $(SOURCES_IDL) $(HEADERS_IDL)

%.dir :
	@echo "Checking directory $*"
	@if [ ! -d $* ]; then \
		echo "Making directory $*"; \
		mkdir -p $* ; \
	fi;

clean:
	@rm -Rf objs/
	@echo "Successfully deleted object and executable files"
	@echo "To delete ALL the architectures and any generated file use target 'veryclean'"

veryclean:
	@rm -Rf objs
	@rm -Rf src/idl
	@echo "Deleted all executables, objects and generated files"
