# ex-int-tcl-shvfslib
A minimum example for customizing Tclsh and embedding core Tcl library.

Build in Linux:

```shell
$ mkdir build-debug
$ cd build-debug
$ cmake .. -DCMAKE_BUILD_TYPE=Debug
$ cmake --build .
$ ./tclshvfslib
% history
     1  history
%
```

Build in Windows:

```shell
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build . --config Debug
$ cd Debug
$ tclshvfslib
% history
     1  history
%
```
