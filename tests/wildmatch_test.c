/* Many of the test cases below are based on
 * https://github.com/vmeurisse/wildmatch/blob/master/test/git/t3070-wildmatch.js
 * which is itself based on t/t3070-wildmatch.sh from Git.
 *
 * The test cases are GPL 2.0-licensed, like Git itself.
 */
#include <wildmatch/wildmatch.h>
#include "test-wildmatch.h"

#define make_test(pattern, string, flags, expect) {{ \
    int actual = wildmatch(pattern, string, flags); \
    assert_equal(expect, actual); \
}}

#define match(pattern, string) {{ \
    make_test(pattern, string, 0, WM_MATCH); \
}}

#define nomatch(pattern, string) {{ \
    make_test(pattern, string, 0, WM_NOMATCH); \
}}

#define wmatch(pattern, string) {{ \
    make_test(pattern, string, WM_WILDSTAR, WM_MATCH); \
}}

#define wnomatch(pattern, string) {{ \
    make_test(pattern, string, WM_WILDSTAR, WM_NOMATCH); \
}}

#define imatch(pattern, string) {{ \
    make_test(pattern, string, WM_CASEFOLD, WM_MATCH); \
}}

#define run(expr) {{ \
    if ((expr)) { \
        return 1; \
    } \
}}


int basic_tests()
{
    /* Basic fnmatch-like features */
    match("foo", "foo");
    nomatch("foo", "bar");
    match("", "");
    match("???", "foo");
    nomatch("??", "foo");
    match("*", "foo");
    match("f*", "foo");
    nomatch("*f", "foo");
    match("*foo*", "foo");
    match("*ob*a*r*", "foobar");
    match("*ab", "aaaaaaabababab");
    match("foo\\*", "foo*");
    nomatch("foo\\*bar", "foobar");
    match("f\\\\oo", "f\\oo");
    match("*[al]?", "ball");
    match("*[l]?", "ball");
    nomatch("[ten]", "ten");
    match("**[!te]", "ten");  /* Improvement over Git's implementation */
    nomatch("**[!ten]", "ten");
    match("t[a-g]n", "ten");
    nomatch("t[!a-g]n", "ten");
    match("t[!a-g]n", "ton");
    match("t[^a-g]n", "ton");
    match("a[]]b", "a]b");
    match("a[]-]b", "a-b");
    match("a[]-]b", "a]b");
    nomatch("a[]-]b", "aab");
    match("a[]a-]b", "aab");
    match("]", "]");
    return 0;
}

int additional_tests()
{
    /* Various additional tests */
    nomatch("a[c-c]st", "acrt");
    match("a[c-c]rt", "acrt");
    nomatch("[!]-]", "]");
    match("[!]-]", "a");
    nomatch("", "\\");
    nomatch("\\", "");
    match("\\\\", "\\");
    nomatch("\\", "\\");
    make_test("\\", "\\", WM_NOESCAPE, WM_MATCH);
    nomatch("*/\\", "XXX/\\");
    make_test("*/\\", "XXX/\\", WM_NOMATCH, WM_MATCH);
    match("*/\\\\", "XXX/\\");
    match("@foo", "@foo");
    nomatch("foo", "@foo");
    nomatch("@foo", "foo");
    match("\\[ab]", "[ab]");
    match("[[]ab]", "[ab]");
    match("[[:]ab]", "[ab]");
    match("\\??\\?b", "?a?b");
    /* nomatch("[[::]ab]", "[ab]"); */ /* TODO */
    match("\\a\\b\\c", "abc");
    nomatch("", "foo");
    match("**/t[o]", "foo/bar/baz/to");
    return 0;
}

int extended_tests()
{
    wnomatch("foo*bar", "foo/baz/bar");
    wnomatch("foo**bar", "foo/baz/bar");
    wnomatch("foo**bar", "foobazbar");
    wmatch("foo/**", "foo/baz/bar");
    wmatch("foo/**/bar", "foo/baz/bar");
    wmatch("foo/**/**/bar", "foo/baz/buz/bar");
    wmatch("foo/**/bar", "foo/b/a/z/bar");
    wmatch("foo/**/**/bar", "foo/baz/bar");
    wmatch("foo/**/**/*****/**/*******/**/bar", "foo/baz/bar");
    wmatch("foo/**/**/bar", "foo/b/a/z/bar");
    wmatch("foo/**/bar", "foo/bar");
    wmatch("**/bar", "foo/bar");
    wmatch("**", "foo/bar");
    wmatch("**", "");
    wmatch("foo/**/**/bar", "foo/bar");
    wnomatch("foo?bar", "foo/bar");
    wnomatch("foo[/]bar", "foo/bar");
    wnomatch("f[^eiu][^eiu][^eiu][^eiu][^eiu]r", "foo/bar");
    wmatch("f[^eiu][^eiu][^eiu][^eiu][^eiu]r", "foo-bar");
    wmatch("**/foo", "/foo");
    wnomatch("**/foo", "foo"); /* Differs from the js tests */
    wmatch("**/foo", "XXX/foo");
    wmatch("**/foo", "bar/baz/foo");
    wnomatch("*/foo", "bar/baz/foo");
    wnomatch("**/bar*", "foo/bar/baz");
    wmatch("**/bar/*", "deep/foo/bar/baz");
    wnomatch("**/bar/*", "deep/foo/bar/baz/");
    wmatch("**/bar/**", "deep/foo/bar/baz/");
    wnomatch("**/bar/*", "deep/foo/bar");
    wmatch("**/bar/**", "deep/foo/bar/");
    wmatch("**/bar**", "foo/bar/baz");  /* Differs from the js tests */
    wmatch("*/bar/**", "foo/bar/baz/x");
    wnomatch("*/bar/**", "deep/foo/bar/baz/x");
    wmatch("**/bar/*/*", "deep/foo/bar/baz/x");
    return 0;
}

int additional_malformed_tests()
{
    wmatch("[\\\\-^]", "]");
    wnomatch("[\\\\-^]", "[");
    wmatch("[\\-_]", "-");
    wmatch("[\\]]", "]");
    wnomatch("[\\]]", "\\]");
    wnomatch("[\\]]", "\\");
    wnomatch("a[]b", "ab");
    /* TODO
    wnomatch("a[]b", "a[]b");
    wnomatch("ab[", "ab[");
    */
    wnomatch("[!", "ab");
    wnomatch("[-", "ab");
    wmatch("[-]", "-");
    wnomatch("[a-", "-");
    wnomatch("[!a-", "-");
    wmatch("[--A]", "-");
    wmatch("[--A]", "5");
    wmatch("[ --]", " ");
    wmatch("[ --]", "$");
    wmatch("[ --]", "-");
    wnomatch("[ --]", "0");
    wmatch("[---]", "-");
    wmatch("[------]", "-");
    wnomatch("[a-e-n]", "j");
    wmatch("[a-e-n]", "-");
    wmatch("[!------]", "a");
    wnomatch("[]-a]", "[");
    wmatch("[]-a]", "^");
    wnomatch("[!]-a]", "^");
    wmatch("[!]-a]", "[");
    wmatch("[a^bc]", "^");
    wmatch("[a-]b]", "-b]");
    wnomatch("[\\]", "\\");
    wmatch("[\\\\]", "\\");
    wnomatch("[!\\\\]", "\\");
    wmatch("[A-\\\\]", "G");
    wnomatch("b*a", "aaabbb");
    wnomatch("*ba*", "aabcaa");
    wmatch("[,]", ",");
    wmatch("[\\\\,]", ",");
    wmatch("[\\\\,]", "\\");
    wmatch("[,-.]", "-");
    wnomatch("[,-.]", "+");
    wnomatch("[,-.]", "-.]");
    wmatch("[\\1-\\3]", "2");
    wmatch("[\\1-\\3]", "3");
    wnomatch("[\\1-\\3]", "4");
    wmatch("[[-\\]]", "\\");
    wmatch("[[-\\]]", "[");
    wmatch("[[-\\]]", "]");
    wnomatch("[[-\\]]", "-");
    return 0;
}

int recursions_tests()
{
    wmatch("-*-*-*-*-*-*-12-*-*-*-m-*-*-*", "-adobe-courier-bold-o-normal--12-120-75-75-m-70-iso8859-1");
    wnomatch("-*-*-*-*-*-*-12-*-*-*-m-*-*-*", "-adobe-courier-bold-o-normal--12-120-75-75-X-70-iso8859-1");
    wnomatch("-*-*-*-*-*-*-12-*-*-*-m-*-*-*", "-adobe-courier-bold-o-normal--12-120-75-75-/-70-iso8859-1");
    wmatch("XXX/*/*/*/*/*/*/12/*/*/*/m/*/*/*", "XXX/adobe/courier/bold/o/normal//12/120/75/75/m/70/iso8859/1");
    wnomatch("XXX/*/*/*/*/*/*/12/*/*/*/m/*/*/*", "XXX/adobe/courier/bold/o/normal//12/120/75/75/X/70/iso8859/1");
    wmatch("**/*a*b*g*n*t", "abcd/abcdefg/abcdefghijk/abcdefghijklmnop.txt");
    wnomatch("**/*a*b*g*n*t", "abcd/abcdefg/abcdefghijk/abcdefghijklmnop.txtz");
    wnomatch("*/*/*", "foo");
    wnomatch("*/*/*", "foo/bar");
    wmatch("*/*/*", "foo/bba/arr");
    wnomatch("*/*/*", "foo/bb/aa/rr");
    wmatch("**/**/**", "foo/bb/aa/rr");
    wmatch("*X*i", "abcXdefXghi");
    wnomatch("*X*i", "ab/cXd/efXg/hi");
    wmatch("*/*X*/*/*i", "ab/cXd/efXg/hi");
    wmatch("**/*X*/**/*i", "ab/cXd/efXg/hi");
    return 0;
}

int case_sensitivity_tests()
{
    wnomatch("[A-Z]", "a");
    wmatch("[A-Z]", "A");
    wnomatch("[a-z]", "A");
    wmatch("[a-z]", "a");
    wnomatch("[[:upper:]]", "a");
    /* TODO
    wmatch("[[:upper:]]", "A");
    */
    wnomatch("[[:lower:]]", "A");
    /* TODO
    wmatch("[[:lower:]]", "a");
    */
    wnomatch("[B-Za]", "A");
    wmatch("[B-Za]", "a");
    wnomatch("[B-a]", "A");
    wmatch("[B-a]", "a");
    wnomatch("[Z-y]", "z");
    wmatch("[Z-y]", "Z");

    imatch("[A-Z]", "a");
    imatch("[A-Z]", "A");
    imatch("[a-z]", "A");
    imatch("[a-z]", "a");
    /* TODO
    imatch("[[:upper:]]", "a");
    imatch("[[:upper:]]", "A");
    imatch("[[:lower:]]", "A");
    imatch("[[:lower:]]", "a");
    */
    imatch("[B-Za]", "A");
    imatch("[B-Za]", "a");
    imatch("[B-a]", "A");
    imatch("[B-a]", "a");
    imatch("[Z-y]", "z");
    imatch("[Z-y]", "Z");

    return 0;
}

int wildmatch_tests()
{
    match("/test/*", "/test/path");
    make_test("/test/*", "/test/path", WM_PATHNAME, WM_MATCH);
    match("/test/**/a", "/test/a/bc/c/d/a");

    match("/test/*/a", "/test/a/bc/c/d/a");
    match("/test/**/a", "/test/a/bc/c/d/a");
    make_test("/test/**/a", "/test/a/bc/c/d/a", WM_PATHNAME, WM_NOMATCH);

    wmatch("**", ".everything");
    wnomatch("*", ".hidden");
    wnomatch("**/*", "/a/b/.hidden");
    wmatch("/foo/**/2/3/*", "/foo/a/b/c/2/3/visible");
    wnomatch("/foo/**/2/3/*", "/foo/a/b/c/2/3/.hidden");

    wmatch("a//a**/c*.ext", "a//ac/a//b/cat.ext");
    return 0;
}

int main(int argc, char **argv)
{
    run(basic_tests());
    run(additional_tests());
    run(extended_tests());
    /* TODO character-class tests */
    run(additional_malformed_tests());
    run(recursions_tests());
    run(case_sensitivity_tests());
    /* TODO additional tests */
    run(wildmatch_tests());

    printf("success: all tests passed\n");
    return 0;
}
