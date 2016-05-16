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

int main(int argc, char **argv)
{
    /* Based on
     * https://github.com/vmeurisse/wildmatch/blob/master/test/git/t3070-wildmatch.js
     * which is itself based on t3070-wildmatch.sh from Git.
     */

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

    /* TODO extended slash-matching features */
    /* TODO character-class tests */
    /* TODO malformed patterns */
    /* TODO recursion and abort code */
    /* TODO case-sensitivity features */
    /* TODO additional tests */

    /* Additional wildmatch tests */
    match("/test/*", "/test/path");
    make_test("/test/*", "/test/path", WM_PATHNAME, WM_MATCH);
    match("/test/**/a", "/test/a/bc/c/d/a");

    match("/test/*/a", "/test/a/bc/c/d/a");
    match("/test/**/a", "/test/a/bc/c/d/a");
    make_test("/test/**/a", "/test/a/bc/c/d/a", WM_PATHNAME, WM_NOMATCH);


    printf("success: all tests passed\n");
    return 0;
}
