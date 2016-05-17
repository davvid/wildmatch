wildmatch
=========
Match filename or pathname patterns with an extended syntax.

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
boundaries.  `WM_WILDSTAR` implies `WM_PATHNAME` and `WM_PERIOD`.

The `WM_` flags are the named the same as their `FNM_` fnmatch counterparts
and are compatible in behavior to fnmatch(3) in the absence of `WM_WILDSTAR`.

The flags argument defaults to wild::WILDSTAR in the C++ API.

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
Git's wildmatch code originally came from Rsync.

The spec for wildmatch, and many of its test cases, came from the Git project,
but the wildmatch implementation here does not share any code or lineage with
Git or Rsync.

Wildmatch was originally based on OpenBSD's fnmatch implementation.
It was then extended to support wildmatch semantics in a backwards-compatible
fashion by introducing an additional `WM_WILDSTAR` flag to enable the new
behavior.


SEE ALSO
--------
fnmatch(3)

[Git](https://github.com/git/git)

LICENSE
-------
[BSD License](LICENSE)
