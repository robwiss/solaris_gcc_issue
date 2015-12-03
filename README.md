# Bug description

`minimal.cc:17` calls `Impl::func` to read some xml with libxml2 and return the structure `MyData`.  Since the xml is malformed the read fails and the exception `MyException` is thrown by `Impl::func`. As the stack is unwound the destructor for `MyData` is called, as soon as this happens the program segfaults.

# Environment

OS:
```
-bash-3.2$ uname -a
SunOS sol 5.10 Generic_147148-26 i86pc i386 i86pc Solaris
```

environment variables for 64-bit build:
```
export CFLAGS="-m64"
export CXXFLAGS="-m64"
export CPPFLAGS="-I/opt/csw/include"
export LDFLAGS="-L/opt/csw/lib/64 -R/opt/csw/lib/64 -L/usr/local/lib -R/usr/local/lib"
export PKG_CONFIG_PATH="/opt/csw/lib/64/pkgconfig"
export PATH="/opt/csw/bin/amd64:$PATH"
```

## Compilers tested

* opencsw gcc 4.8.2 - issue does not occur
* opencsw gcc 4.9.0 - issue occurs
* opencsw gcc 4.9.2 - issue occurs
* opencsw gcc 5.2.0 - issue occurs

# Building and running

In source directory:
```
-bash-3.2$ autoreconf -fis
libtoolize: putting auxiliary files in `.'.
libtoolize: linking file `./ltmain.sh'
libtoolize: putting macros in AC_CONFIG_MACRO_DIR, `m4'.
libtoolize: linking file `m4/libtool.m4'
libtoolize: linking file `m4/ltoptions.m4'
libtoolize: linking file `m4/ltsugar.m4'
libtoolize: linking file `m4/ltversion.m4'
libtoolize: linking file `m4/lt~obsolete.m4'
libtoolize: Consider adding `-I m4' to ACLOCAL_AMFLAGS in Makefile.am.
configure.ac:13: installing './config.guess'
configure.ac:13: installing './config.sub'
configure.ac:7: installing './install-sh'
configure.ac:7: installing './missing'
Makefile.am: installing './depcomp'
```

In the directory where you'd like to build (doesn't have to be source directory, replace /projects/solaris_gcc_issue with path to configure):
```
-bash-3.2$ CXXFLAGS="$CXXFLAGS -g -O0" /projects/solaris_gcc_issue/configure
```

Run make:
```
-bash-3.2$ make
```

Run the program:
```
-bash-3.2$ ./minimal 
Segmentation Fault (core dumped)
```

Examine in gdb:
```
-bash-3.2$ libtool --mode=execute gdb ./minimal
GNU gdb (GDB) 7.7
Copyright (C) 2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "i386-pc-solaris2.10".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from /export/home/vagrant/solaris_gcc_issue/.libs/minimal...done.
(gdb) b minimal.cc:17
Breakpoint 1 at 0x401f65: file /projects/solaris_gcc_issue/minimal.cc, line 17.
(gdb) r
...
17              throw MyException("ohno");
(gdb) s
18          }
(gdb) s
std::shared_ptr<_xmlDoc>::~shared_ptr (this=0xfffffd7fffdffa20, 
    __in_chrg=<optimized out>)
    at /opt/csw/include/c++/4.9.0/bits/shared_ptr.h:93
93          class shared_ptr : public __shared_ptr<_Tp>
(gdb) fin
Run till exit from #0  std::shared_ptr<_xmlDoc>::~shared_ptr (
    this=0xfffffd7fffdffa20, __in_chrg=<optimized out>)
    at /opt/csw/include/c++/4.9.0/bits/shared_ptr.h:93
0xfffffd7fff347b83 in Impl::func (this=0xfffffd7fffdffa70, xml=...)
    at /projects/solaris_gcc_issue/Impl.cc:18
18          }
(gdb) s
19      }
(gdb) 
MyData::~MyData (this=0xfffffd7fffdffa80, __in_chrg=<optimized out>)
    at /projects/solaris_gcc_issue/MyData.h:7
7       struct MyData
(gdb) s
std::vector<std::string, std::allocator<std::string> >::~vector (
    this=0xfffffd7fffdffa80, __in_chrg=<optimized out>)
    at /opt/csw/include/c++/4.9.0/bits/stl_vector.h:425
425                           _M_get_Tp_allocator()); }
(gdb) fin
Run till exit from #0  std::vector<std::string, std::allocator<std::string> >::~vector (this=0xfffffd7fffdffa80, __in_chrg=<optimized out>)
    at /opt/csw/include/c++/4.9.0/bits/stl_vector.h:425

Program received signal SIGSEGV, Segmentation fault.
0xfffffd7fff2de5fd in __exchange_and_add (__val=-1, __mem=0x401f56 <_init+6>)
    at /home/maciej/src/opencsw/pkg/gcc4/trunk/work/solaris10-i386/build-isa-pentium_pro/objdir/i386-pc-solaris2.10/amd64/libstdc++-v3/include/ext/atomicity.h:49
49      /home/maciej/src/opencsw/pkg/gcc4/trunk/work/solaris10-i386/build-isa-pentium_pro/objdir/i386-pc-solaris2.10/amd64/libstdc++-v3/include/ext/atomicity.h: No such file or directory.
(gdb) 
```
