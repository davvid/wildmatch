#!/usr/bin/env make
SH ?= sh
uname_S := $(shell $(SH) -c 'uname -s || echo system')
uname_R := $(shell $(SH) -c 'uname -r | cut -d- -f1 || echo release')
uname_M := $(shell $(SH) -c 'uname -m || echo cpu')
FLAVOR ?= optimize

platformdir ?= $(uname_S)-$(uname_R)-$(uname_M)-$(FLAVOR)
builddir ?= $(CURDIR)/build/$(platformdir)

prefix ?= $(CURDIR)/$(platformdir)
#DESTDIR =

ifdef V
    VERBOSE=1
    export VERBOSE
endif
CMAKE_FLAGS ?= -DCMAKE_INSTALL_PREFIX=$(prefix)
CMAKE_FILES = CMakeLists.txt

# The default target in this Makefile is...
all::

install: all
	$(MAKE) -C $(builddir) DESTDIR=$(DESTDIR) install
.PHONY: install

$(builddir)/stamp: $(CMAKE_FILES)
	mkdir -p $(builddir)
	cd $(builddir) && cmake $(CMAKE_FLAGS) ../..
	touch $@

all:: $(builddir)/stamp
	$(MAKE) -C $(builddir) $(MAKEARGS) all
.PHONY: all

clean: $(builddir)/stamp
	$(MAKE) -C $(builddir) $(MAKEARGS) clean
.PHONY: clean

test: all
	$(MAKE) -C $(builddir) $(MAKEARGS) test
.PHONY: test
