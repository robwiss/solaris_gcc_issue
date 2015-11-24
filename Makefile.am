lib_LTLIBRARIES = libminimal.la

libminimal_la_SOURCES = Interface.h Impl.h Impl.cc \
	MyData.h MyData.cc Util.h
libminimal_la_CPPFLAGS = @XML_CPPFLAGS@
libminimal_la_LDFLAGS = @XML_LIBS@

bin_PROGRAMS = minimal

minimal_SOURCES = minimal.cc
minimal_LDFLAGS = libminimal.la

