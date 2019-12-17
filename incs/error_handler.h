#ifndef FT_ERROR_HANDLER_H
# define FT_ERROR_HANDLER_H
#include "stack.h"

const char	G_ERROR_MSGS_PREFIX[PARSE_ERROR_NEAR + 1][54] = {
		[UNEXPECTED_EOF] = "unexpected EOF while looking for matching `",
		[PARSE_ERROR_NEAR] = "parse error near '"
};

const char	G_ERROR_MSGS_SUFFIX[PARSE_ERROR_NEAR + 1][42] = {
		[UNEXPECTED_EOF] = "`\n",
		[PARSE_ERROR_NEAR] = "'\n"
};

#endif
