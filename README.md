### Sternenhimmel ###

Sternenhimmel is a little experimental idea that came to mind after 33c3. Some
diaspora\* users were trying to attach a view of diaspora\* with autorefresh
onto a projector. I decided to created a dedicated program for this. It's
written in C++ with Qt.

#### Build Instructions

To build Sternenhimmel your system must meet the following requirements:

  * C++ compiler with C++14 support.
  * Qt5 with QMake.
  * libmarkdown (AKA discount) with development headers.

To build on a UNIX-like system, do the following:

    mkdir build
    cd build
    qmake ..
    make
