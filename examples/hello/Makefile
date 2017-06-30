.PHONY: all clean
VPATH := src:src/idl_opendds

# Compiler Configurations -----------------------------------------------------
# -pthread: Use pthread as C++11 <std::thread> implementation
# -ggdb:	Generate GDB Specific debug symbols
# -pipe:	Use pipe for compiler's internal temp files. instead of real temp files
CXX := g++
CXXFLAGS := -w -Wno-deprecated-declarations -Wall -W -Wpointer-arith \
			-fvisibility=hidden -fvisibility-inlines-hidden -fno-strict-aliasing \
			-pthread -ggdb -pipe \
			-D_GNU_SOURCE -D__ACE_INLINE__

INCS := -I$(ACE_ROOT) \
		-I$(TAO_ROOT) \
		-I$(DDS_ROOT) \
		-Isrc/idl_opendds \
		-Iinclude

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
GENERATE := HelloC.cpp
GENERATE_FLAGS := -Sa -St
GENERATE_INCS := -Wb,pre_include=ace/pre.h \
				-Wb,post_include=ace/post.h \
				-I$(TAO_ROOT) \
				-I$(DDS_ROOT) \
				-Isrc/idl_opendds
PUB := pub
SUB := sub

all: $(GENERATE) $(PUB) $(SUB)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCS) -c -o $@ $<

$(GENERATE): src/Hello.idl
	@mkdir -p $(OBJDIR)
	@# Generate TypeSupportor: HelloTypeSupport.idl, HelloTypeSupportImpl.*
	opendds_idl $(GENERATE_FLAGS) -o src/idl_opendds src/idl_opendds/Hello.idl
	@# Generate TypeSupport Specific Sources: HelloTypeSupportC.*, HelloTypeSupportS.*
	tao_idl $(GENERATE_INCS) $(GENERATE_FLAGS) -o src/idl_opendds src/idl_opendds/HelloTypeSupport.idl
	@# Generate Type Specific Sources:  HelloC.* HelloS.*
	tao_idl $(GENERATE_INCS) $(GENERATE_FLAGS) -o src/idl_opendds src/idl_opendds/Hello.idl
	@make

generate: src/Hello.idl
	@mkdir -p $(OBJDIR)
	@# Generate TypeSupportor: HelloTypeSupport.idl, HelloTypeSupportImpl.*
	opendds_idl $(GENERATE_FLAGS) -o src/idl_opendds src/idl_opendds/Hello.idl
	@# Generate TypeSupport Specific Sources: HelloTypeSupportC.*, HelloTypeSupportS.*
	tao_idl $(GENERATE_INCS) $(GENERATE_FLAGS) -o src/idl_opendds src/idl_opendds/HelloTypeSupport.idl
	@# Generate Type Specific Sources:  HelloC.* HelloS.*
	tao_idl $(GENERATE_INCS) $(GENERATE_FLAGS) -o src/idl_opendds src/idl_opendds/Hello.idl

$(PUB): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCS) $(LDFLAG) -o $@ $(filter-out obj/sub.o,$^) $(LIBS)

$(SUB): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCS) $(LDFLAG) -o $@ $(filter-out obj/pub.o,$^) $(LIBS)

clean:
	@rm -f pub sub
	@rm -rf $(OBJDIR) *.log *.ior
	@rm -r src/idl_opendds/HelloC*
	@rm -r src/idl_opendds/HelloS*
	@rm -r src/idl_opendds/HelloType*

