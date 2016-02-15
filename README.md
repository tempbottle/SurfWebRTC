REQUIRED DEPENDENCIES:
=====================

The "ws-server" program expects the following header & libraries:

Libraries:

- /usr/local/lib/libresipares.a
- /usr/local/lib/librutil.a
- /usr/local/lib/libresip.a
- /usr/local/lib/libdum.a

Headers

- /usr/local/include/rutil/dns/ares
- /usr/local/include/rutil
- /usr/local/include/resip/stack
- /usr/local/include/resip/dum

It could be insalled on Ubuntu as follows:
      sudo apt-get install libresiprocate-1.9 libresiprocate-1.9-dev

COMPILATION STEPS:
=================

1. Compile resiprocate-1.10.1 
      a) autoreconf --install
      b) ./configure
      c) make
      d) make install

2. Compile application "ws-server"
      a) make

