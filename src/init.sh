yacc -dv nectar_syntax
flex nectar_lexer.l
gcc -Wall lex.yy.c y.tab.c nectar_semantics.c -o nectarc
