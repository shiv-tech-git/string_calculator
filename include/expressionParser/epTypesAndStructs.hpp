#pragma once

typedef float num_t;
typedef char oper_t;
typedef char par_t;

enum class TokenType {num_tok, l_par_tok, r_par_tok, oper_tok};

typedef struct token {
	TokenType type;
	union {
		num_t num;
		oper_t oper;
	};
} token_t;