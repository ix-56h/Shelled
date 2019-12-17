#ifndef FT_ERROR_HANDLER_H
# define FT_ERROR_HANDLER_H
#include "stack.h"

const char	G_ERROR_MSGS_PREFIX[PARSE_ERROR_NEAR + 1][54] = {
		[UNEXPECTED_EOF] = "unexpected EOF while looking for matching `",
		[SQ_LEX] = "unexpected EOF while looking for matching `'`\n",
		[DQ_LEX] = "unexpected EOF while looking for matching `\"`\n",
		[BQ_LEX] = "unexpected EOF while looking for matching '`'\n",
		[PAREN_LEX] = "unexpected EOF while looking for matching '('\n",
		[PARSE_ERROR_NEAR] = "parse error near '"
};

#endif
