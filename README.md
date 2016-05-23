wildmatch
=========
Match filename or path patterns with an extended syntax

SYNOPSIS
--------
    /* C API */
    #include <wildmatch/wildmatch.h>

    if (wildmatch("/a/**/z", "/a/b/c/d/z", WM_WILDSTAR) == WM_MATCH) {
        /* matched */
    }

    /* C++ API */
    #include <wildmatch/wildmatch.hpp>

    if (wild::match("/a/**/z", "/a/b/c/d/z")) {
        /* matched */
    }

DESCRIPTION
-----------
wildmatch is an extended pattern-matching library based on the fnmatch
implementation from OpenBSD.

wildmatch is an extension of function fnmatch(3) as specified in
POSIX 1003.2-1992, section B.6.

The wildmatch C API is fnmatch-compatible by default.  Its new features are
enabled by passing `WM_WILDSTAR` in flags, which makes `**` match across path
boundaries.  `WM_WILDSTAR` implies `WM_PATHNAME`.

The `WM_` flags are the named the same as their `FNM_` fnmatch counterparts
and are compatible in behavior to fnmatch(3) in the absence of `WM_WILDSTAR`.

The flags argument defaults to `wild::WILDSTAR` in the C++ API.
Pass `wild::FNMATCH` as the third `flags` argument if you want to enable the
`fnmatch(3)`-compatible behavior.

RETURN VALUE
------------
The C API returns `WM_MATCH` when string matches the pattern, and `WM_NOMATCH`
when the pattern does not match.

The C++ API returns a boolean `true` and `false`.

HISTORY
-------
Wildmatch is an independent, BSD-licensed implementation of the wildmatch spec,
and was developed based on Git's test cases only.


The name "wildmatch" came from the name of an internal library in the Git
project that is used for extended fnmatch-like pattern matching.
Git's wildmatch code originally came from rsync.

The spec for wildmatch, and its test suite, came from the Git project, but the
wildmatch implementation here does not share any code or lineage with Git or
rsync's wildmatch implementation.

Wildmatch is based on OpenBSD's fnmatch implementation.  It was extended to
support wildmatch semantics in a backwards-compatible fashion by introducing
an additional `WM_WILDSTAR` flag to enable the new behavior.

BUILD
-----
    make

TEST
----
    make test

The test suite is borrowed from the Git project and can be found in
`tests/t3070-wildmatch.sh`.  You can run the test script directly for closer
debugging.  We use [sharness](https://github.com/mlafeldt/sharness) to run
the tests.

Passing the `-v` flag to the test script increases its verbosity, and passing
the `--immediate` flag tells the test suite to stop on the first failure.

INSTALL
-------
    make prefix=/usr/local install

The install tree looks like the following:

    <prefix>
    ├── include
    │   └── wildmatch
    │       ├── wildmatch.h
    │       └── wildmatch.hpp
    ├── lib
    │   ├── libwildmatch-cxx.so
    │   └── libwildmatch.so
    └── share
        └── doc
            └── wildmatch
                └── README.md

The C++ API is provided by wildmatch.hpp and libwildmatch-cxx.so.
The C API is provided by wildmatch.h and libwildmatch.so.

The C++ API library is a super-set of the C API.  If you link against the C++
library then you can also use the C API functions if desired; there is no need
to link against both libraries.

REQUIREMENTS
------------
* [cmake](https://cmake.org/) is used for the build system
* A C++11-compatible compiler is needed to build and use the C++ API.
* A C89-compatible compiler is needed for the C API.

SEE ALSO
--------
fnmatch(3)

[Git](https://github.com/git/git)

LICENSE
-------
[BSD License](LICENSE)
