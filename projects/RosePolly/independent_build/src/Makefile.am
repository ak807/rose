
bin_PROGRAMS = rpolly
rpolly_SOURCES = \
	main.cpp \
	RosePollyInterface.cpp \
  	Kernel.cpp \
  	FlowGraph.cpp \
  	Nodes.cpp \
  	RosePollyModel.cpp \
  	data.cpp \
  	Utilities.cpp \
  	error.cpp \
  	access_pattern.cpp \
  	traversals.cpp \
  	RosePollyMath.cpp \
  	isl_interface.cpp \
  	simple_multi_graph.cpp \
  	RosePluto.cpp \
  	simple_matrix.cpp \
  	RoseCloog.cpp \
  	RosePollyCustom.cpp

include ../paths.mk

DFLAGS = -DCLOOG_INT_GMP -DISL
CPPFLAGS = -I../include -I$(ROSE_PATH)/include -I$(BOOST_PATH)/include -I$(ISL_PATH)/include -I$(CLOOG_PATH)/include $(DFLAGS)
LDFLAGS = -lgmp -L$(ISL_PATH)/lib -lisl -Wl,-rpath=$(ISL_PATH)/lib -L$(CLOOG_PATH)/lib -lcloog-isl -Wl,-rpath=$(CLOOG_PATH)/lib -L$(ROSE_PATH)/lib -lrose -Wl,-rpath-link=$(BOOST_PATH)/lib -Wl,-rpath=$(BOOST_PATH)/lib -Wl,-rpath-link=$(ROSE_PATH)/lib -Wl,-rpath=$(ROSE_PATH)/lib -Wl,-rpath=$(JAVA_PATH) -Wl,-rpath=/usr/local/lib
