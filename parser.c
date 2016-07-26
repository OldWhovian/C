/* parser.c: simple parser for CS 530 Assignment 3 Spring 2015
 * grammar:
 *   <Z> ::= <S>{<S>}$
 *   <S> ::= char = <E>;
 *   <E> ::= <V> {( + | - ) <V>}
 *   <V> ::= <P> {( * | / ) <P>}
 *   <P> ::= <C> ^ <P> | <C>
 *   <C> ::= char | ( <E> ) | digit
 */

/*
 * Programmer: Michael Potts
 * Credit for Base Code: Professor Guy Leonard 
 * File(s): parser.c, Makefile, README
 * Due Date: 5/7/2015
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char next;

void Z(void);
void S(void);
void E(void);
void V(void);
void P(void);
void C(void);
void scan(void);
void enter(char);
void leave(char);
void spaces(int);
void error(int);
int level = 0;

void Z(void)
{
    enter('Z');
    while (next != '$'){
        S();
    }
    leave('Z');
}
void S(void)
{
    enter('S');
    if (isalpha(next)){
        scan();
	if (next == '='){
            scan();
	    E();
	    if (next == ';') {
                scan();
            }
	    else {
	        error(6);
	    }	
        }
	else{
	    error(3);
	}
    }
    else {
        error(2);
    }
    leave('S');
}
void E(void)
{
   enter('E');
   V();
   while (next == '+' || next == '-') {
      scan();
      V();
   }
   leave('E');
}

void V(void)
{
   enter('V');
   P();
   while (next == '*' || next == '/') {
      scan();
      P();
   }
   leave('V');
}

void P(void)
{
   enter('P');
   C();
   if (next == '^') {
      scan();
      P();
   }
   leave('P');
}

void C(void)
{
   enter('C');
   if (isalpha(next)) {
      scan();
   }
   else if (next == '(') {
      scan();
      E();
      if (next == ')') scan();
      else error(4);
   }
   else if (isdigit(next)){
       scan();
   }
   else {
      error(5);
   }
   leave('C');
}

void scan(void)
{
   while (isspace(next = getchar()));
}

void enter(char name)
{
   spaces(level++);
   printf("+-%c: Enter, \t", name);
   printf("Next == %c\n", next);
}

void leave(char name)
{
   spaces(--level);
   printf("+-%c: Leave, \t", name);
   printf("Next == %c\n", next);
}

void spaces(int local_level)
{
   while (local_level-- > 0)
      printf("| ");
}

void error(int n)
{
   printf("\n*** ERROR: %i\n", n);
   exit(1);
}

void main(void)
{
   scan();
   Z();
   if (next != '$') error(1);
   else printf("Successful parse\n");
}
