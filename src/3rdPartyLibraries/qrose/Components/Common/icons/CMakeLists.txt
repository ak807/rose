
include_directories(${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### install files ###############

install(FILES  cachebroadcast.xpm     doquery.xpm       method_npublic_decl.xpm     source_c.xpm     cacheclear.xpm      empty.xpm        method_npublic_defn.xpm      target.xpm     cachecollect.xpm       func_decl.xpm      method_public_decl.xpm     typedf.xpm     cacheview.xpm        func_defn.xpm     method_public_defn.xpm      var.xpm     class_decl.xpm      gotoline.xpm       no.xpm             yes.xpm           clear_results.xpm      highlight.xpm      project.xpm        zoomin.xpm       default.xpm        lookup.xpm         setdomain.xpm      zoomout.xpm DESTINATION ${INCLUDE_INSTALL_DIR} )



#original Makefile.am contents follow:

#include $(top_srcdir)/config/Makefile.for.ROSE.includes.and.libs
#
#if ROSE_USE_QT
#
#INCLUDES = $(ROSE_INCLUDES) $(QT_INCLUDES) 
#
#  
#METASOURCES = auto
#
#CLEANFILES = 
#
#iconsdir = $(prefix)/include/icons
#
#icons_DATA= \
#   cachebroadcast.xpm \
#   doquery.xpm   \
#   method_npublic_decl.xpm \
#   source_c.xpm \
#   cacheclear.xpm  \
#   empty.xpm    \
#   method_npublic_defn.xpm  \
#   target.xpm \
#   cachecollect.xpm   \
#   func_decl.xpm  \
#   method_public_decl.xpm \
#   typedf.xpm \
#   cacheview.xpm    \
#   func_defn.xpm \
#   method_public_defn.xpm  \
#   var.xpm \
#   class_decl.xpm  \
#   gotoline.xpm   \
#   no.xpm         \
#   yes.xpm       \
#   clear_results.xpm  \
#   highlight.xpm  \
#   project.xpm    \
#   zoomin.xpm   \
#   default.xpm    \
#   lookup.xpm     \
#   setdomain.xpm  \
#   zoomout.xpm
#endif
#
#EXTRA_DIST = \
#   cachebroadcast.xpm \
#   doquery.xpm   \
#   method_npublic_decl.xpm \
#   source_c.xpm \
#   cacheclear.xpm  \
#   empty.xpm    \
#   method_npublic_defn.xpm  \
#   target.xpm \
#   cachecollect.xpm   \
#   func_decl.xpm  \
#   method_public_decl.xpm \
#   typedf.xpm \
#   cacheview.xpm    \
#   func_defn.xpm \
#   method_public_defn.xpm  \
#   var.xpm \
#   class_decl.xpm  \
#   gotoline.xpm   \
#   no.xpm         \
#   yes.xpm       \
#   clear_results.xpm  \
#   highlight.xpm  \
#   project.xpm    \
#   zoomin.xpm   \
#   default.xpm    \
#   lookup.xpm     \
#   setdomain.xpm  \
#   zoomout.xpm
