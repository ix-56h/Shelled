#ifndef FT_ERROR_HANDLER_H
# define FT_ERROR_HANDLER_H
#include "stack.h"

const char	G_ERROR_MSGS_PREFIX[PARSE_ERROR_NEAR + 1][54] = {
		[MATCH_LEX] = "unexpected EOF while looking for matching ",
		[PARSE_ERROR_NEAR] = "parse error near "
};

#endif
