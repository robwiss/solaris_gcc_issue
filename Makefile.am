lib_LTLIBRARIES = libminimal.la

libminimal_la_SOURCES = test/Interface.h test/Impl.h test/Impl.cc \
	test/MyData.h test/MyData.cc test/Util.h
libminimal_la_CPPFLAGS = @XML_CPPFLAGS@
libminimal_la_LDFLAGS = @XML_LIBS@

bin_PROGRAMS = minimal

minimal_SOURCES = test/minimal.cc
minimal_LDFLAGS = libminimal.la

