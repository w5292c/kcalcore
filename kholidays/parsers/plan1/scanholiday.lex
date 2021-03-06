/*
 * Taken from plan by Thomas Driemeyer <thomas@bitrot.de>
 * Adapted for use in KOrganizer by Preston Brown <pbrown@kde.org> and
 * Reinhold Kainhofer <reinhold@kainhofer.com>
 *
 * This is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Library General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version. This software is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Library
 * General Public License for more details.
 * 
 * For more licensing information, please read LICENSE.plan in this directory.
 */
%{
#include <string.h>
#include <stdlib.h>
#include "parseholiday.h"
#define YY_NO_UNPUT
%}

%option nomain
%option noyywrap
%option never-interactive
%option noalways-interactive
%option nostack

%%

#.*\n				;
^:.*\n				;
[ \t\r\n]				;
[-+*/%.!?:()\[\]]		{ return(*kcaltext); }

january				{ kcallval.ival =   1; return(MONTH); }
february			{ kcallval.ival =   2; return(MONTH); }
march				{ kcallval.ival =   3; return(MONTH); }
april				{ kcallval.ival =   4; return(MONTH); }
may				{ kcallval.ival =   5; return(MONTH); }
june				{ kcallval.ival =   6; return(MONTH); }
july				{ kcallval.ival =   7; return(MONTH); }
august				{ kcallval.ival =   8; return(MONTH); }
september			{ kcallval.ival =   9; return(MONTH); }
october				{ kcallval.ival =  10; return(MONTH); }
november			{ kcallval.ival =  11; return(MONTH); }
december			{ kcallval.ival =  12; return(MONTH); }

monday				{ kcallval.ival =   1; return(WDAY); }
tuesday				{ kcallval.ival =   2; return(WDAY); }
wednesday			{ kcallval.ival =   3; return(WDAY); }
thursday			{ kcallval.ival =   4; return(WDAY); }
friday				{ kcallval.ival =   5; return(WDAY); }
saturday			{ kcallval.ival =   6; return(WDAY); }
sunday				{ kcallval.ival =   7; return(WDAY); }

1st|first			{ kcallval.ival =   1; return(NUMBER); }
2nd|second			{ kcallval.ival =   2; return(NUMBER); }
3rd|third			{ kcallval.ival =   3; return(NUMBER); }
4th|fourth			{ kcallval.ival =   4; return(NUMBER); }
5th|fifth			{ kcallval.ival =   5; return(NUMBER); }
last				{ kcallval.ival = 999; return(NUMBER); }
any				{ kcallval.ival =   0; return(NUMBER); }

before				{ kcallval.ival =  -1; return(NUMBER); }
after				{ kcallval.ival =  -2; return(NUMBER); }

[0-9]+				{ kcallval.ival = atoi(kcaltext); return(NUMBER); }

\"[^"]*\"			{ kcallval.sval = strdup(kcaltext+1);
				  kcallval.sval[strlen(kcallval.sval)-1] = 0;
				  return(STRING); }

every				;
day				;
days				;
on				;
to				;
in				{ return(HOLIDAY_IN);    }
if				{ return(IF); }
plus				{ return(PLUS);  }
minus				{ return(MINUS); }
small				{ return(SMALL); }
year				{ return(CYEAR);  }
leapyear			{ return(LEAPYEAR); }
easter				{ return(EASTER); }
pascha				{ return(PASCHA); }
length				{ return(LENGTH); }
shift				{ return(SHIFT); }

black				{ kcallval.ival = 1; return(COLOR); }
red				{ kcallval.ival = 2; return(COLOR); }
green				{ kcallval.ival = 3; return(COLOR); }
yellow				{ kcallval.ival = 4; return(COLOR); }
blue				{ kcallval.ival = 5; return(COLOR); }
magenta				{ kcallval.ival = 6; return(COLOR); }
cyan				{ kcallval.ival = 7; return(COLOR); }
white				{ kcallval.ival = 8; return(COLOR); }
weekend				{ kcallval.ival = 9; return(COLOR); }

"=="				{ return(EQ); }
"!="				{ return(NE); }
"<="				{ return(LE); }
">="				{ return(GE); }
"<"				{ return(LT); }
">"				{ return(GT); }
"&&"				{ return(AND);}
"||"				{ return(OR); }

.				{ printf("holiday: bad char: %s \n", kcaltext); }

%%
