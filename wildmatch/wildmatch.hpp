#pragma once

#include <string>

namespace wild {

/* Flags */
constexpr int FNMATCH = 0x00; /* No flags, fnmatch behavior. */
constexpr int NOESCAPE = 0x01; /* Disable backslash escaping. */
constexpr int PATHNAME = 0x02; /* Slash must be matched by slash. */
constexpr int PERIOD = 0x04; /* Period must be matched by period. */
constexpr int LEADING_DIR = 0x08; /* Ignore /<tail> after Imatch. */
constexpr int CASEFOLD = 0x10; /* Case insensitive search. */
constexpr int WILDSTAR = 0x40; /* Double-asterisks ** matches slash too. */

bool match(const char *pattern, const char *string, int flags=WILDSTAR);
bool match(const std::string& pattern, const std::string& string, int flags=WILDSTAR);

}
