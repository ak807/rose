include $(top_srcdir)/config/Makefile.for.ROSE.includes.and.libs

INCLUDES = $(ROSE_INCLUDES)

noinst_LTLIBRARIES = libastVisualization.la

# DQ (2/26/2009): Added copyGraph.[hC], also note that copyGraph.C has
# a dependence on a TCLSH script that is located in the scripts directory.
libastVisualization_la_SOURCES = astGraph.C AstAttributeDOT.C wholeAST.C copyGraph.C walrus.C

#   colorFilesTraversal.C  colorMemoryPoolTraversal.C \
#   customAstDOTGeneration.C  customAstDOTGenerationData.C \
#   customMemoryPoolDOTGeneration.C  customMemoryPoolDOTGenerationData.C

libastVisualization_la_LIBADD       = 
libastVisualization_la_DEPENDENCIES = 

include_HEADERS = AstAttributeDOT.h  astGraph.h astGraphTemplateImpl.h wholeAST.h wholeAST_API.h copyGraph.h walrus.h


EXTRA_DIST = CMakeLists.txt
