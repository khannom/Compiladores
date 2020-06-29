%{
#include "tokens.h"
%}

%%
[ \n\t]     ;
>           return MAYOR;
\<           return MENOR;
;           return PUNTOYCOMA;
\(           return PARI;
\)           return PARD;
\[          return CORCHETEI;
\]          return CORCHETED;
\{          return LLAVEI;
\}          return LLAVED;
=           return ASIGNACION;
,           return COMA;
#           return HASHTAG;
\".*\"    return STRING;
(int|char|float|bool)   return TYPE;
[a-zA-Z][a-zA-Z0-9]*    return ID;
[+-]?[0-9]*\.[0-9]* return FLOAT;
[+-]?[0-9]+   return INTEGER;
.           return UNDEFINED;
%%

int yywrap()
{
      return 1;
}
