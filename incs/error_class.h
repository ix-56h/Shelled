#ifndef ERROR_CLASS_H
# define ERROR_CLASS_H

const char	G_ERROR_MSGS_PREFIX[PARSE_ERROR_NEAR + 1][54] = {
		[MATCH_LEX] = "unexpected EOF while looking for matching ",
		[UNEXPECTED_TOKEN] = "syntax error near unexpected ",
		[UNRECOGNIZED_TOKEN] = "syntax error near unrecognized token ",
		[PARSE_ERROR_NEAR] = "parse error near "
};
#endif
