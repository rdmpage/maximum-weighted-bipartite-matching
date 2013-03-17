# $Id: Makefile.am,v 1.1.1.1 2007/10/28 08:36:53 rdmp1c Exp $

GRAPHDIR	= graph
LIBS		= -lGTL -L$(GRAPHDIR) -lgraph 
INCLUDES 	= -I$(GRAPHDIR) 

AM_CXXFLAGS=-Wno-deprecated
AM_CFLAGS=-Wno-deprecated

SUBDIRS = graph

# The actual programs
bin_PROGRAMS = matching
matching_SOURCES = matching.cpp

EXTRA_DIST = graph/mygraph.h graph/mygraph.cpp graph/mytree.h graph/mytree.cpp \
	graph/mincut.h graph/mincut.cpp graph/mwbmatching.h graph/mwbmatching.cpp \
	graph/fheap.h graph/fheap.c graph/tokenise.h graph/tokenise.cpp \
	graph/gport.h graph/gport.cpp graph/gdefs.h \
	graph/examples/leda.7.46.gml examples/bipartite.gml

