.PHONY: all clean
VPATH := src:src/idl

# Compiler Configurations -----------------------------------------------------
# -pthread: Use pthread as C++11 <std::thread> implementation
# -ggdb:	Generate GDB Specific debug symbols
# -pipe:	Use pipe for compiler's internal temp files. instead of real temp files
CXX := g++
CXXFLAGS := -Wno-deprecated-declarations -Wall -W -Wpointer-arith \
			-fvisibility=hidden -fvisibility-inlines-hidden -fno-strict-aliasing \
			-pthread -ggdb -pipe \
			-D_GNU_SOURCE -D__ACE_INLINE__

INCS := -I$(ACE_ROOT) \
		-I$(TAO_ROOT) \
		-I$(DDS_ROOT) \
		-Isrc/idl

LDFLAG := -Wl,-E # Executable uses dynamically linked symbols
LIBS := -L$(ACE_ROOT)/lib \
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

OBJDIR := obj
SRCS := $(notdir $(shell find -name "*.cpp"))
OBJS := $(addprefix $(OBJDIR)/,$(SRCS:%.cpp=%.o))

# IDL Generater Configurations ------------------------------------------------
GENERATE := HelloWorldC.cpp
GENERATE_FLAGS := -Sa -St
GENERATE_INCS := -Wb,pre_include=ace/pre.h \
				-Wb,post_include=ace/post.h \
				-I$(TAO_ROOT) \
				-I$(DDS_ROOT) \
				-Isrc \
				-Isrc/idl
PUB := pub
SUB := sub

all: $(GENERATE) $(PUB) $(SUB)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCS) -c -o $@ $<

$(GENERATE): src/HelloWorld.idl
	@mkdir -p $(OBJDIR)
	@mkdir -p src/idl
	@# Generate TypeSupportor: HelloWorldTypeSupport.idl, HelloWorldTypeSupportImpl.*
	opendds_idl $(GENERATE_FLAGS) -o src/idl src/HelloWorld.idl
	@# Generate TypeSupport Specific Sources: HelloWorldTypeSupportC.*, HelloWorldTypeSupportS.*
	tao_idl $(GENERATE_INCS) $(GENERATE_FLAGS) -o src/idl src/idl/HelloWorldTypeSupport.idl
	@# Generate Type Specific Sources:  HelloWorldC.* HelloWorldS.*
	tao_idl $(GENERATE_INCS) $(GENERATE_FLAGS) -o src/idl src/HelloWorld.idl
	@make

generate: src/HelloWorld.idl
	@mkdir -p $(OBJDIR)
	@mkdir -p src/idl
	@# Generate TypeSupportor: HelloWorldTypeSupport.idl, HelloWorldTypeSupportImpl.*
	opendds_idl $(GENERATE_FLAGS) -o src/idl src/HelloWorld.idl
	@# Generate TypeSupport Specific Sources: HelloWorldTypeSupportC.*, HelloWorldTypeSupportS.*
	tao_idl $(GENERATE_INCS) $(GENERATE_FLAGS) -o src/idl src/idl/HelloWorldTypeSupport.idl
	@# Generate Type Specific Sources:  HelloWorldC.* HelloWorldS.*
	tao_idl $(GENERATE_INCS) $(GENERATE_FLAGS) -o src/idl src/HelloWorld.idl

$(PUB): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCS) $(LDFLAG) -o $@ $(filter-out obj/sub.o,$^) $(LIBS)

$(SUB): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCS) $(LDFLAG) -o $@ $(filter-out obj/pub.o,$^) $(LIBS)

clean:
	@rm -f pub sub
	@rm -rf $(OBJDIR) src/idl *.log *.ior

