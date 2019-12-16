#ifndef FT_ERROR_HANDLER_H
# define FT_ERROR_HANDLER_H
#include "stack.h"

const char	G_ERROR_MSGS[PARSE_ERROR_NEAR + 1][42] = {
		[UNCLOSED_SEQUENCE] = "syntax error: unexpected end of file\n",
		[PARSE_ERROR_NEAR] = "parse error near '"
};


#endif
