#include <stdio.h>

struct letter {
  int  byte1;
  int  byte2;
  char name [3];
};

/* This program reverses the following Russian UTF-8 => Translit
   trasnformation, with the following extra rules:

   Ye --- same as E
   Y without trailing e,a,o,u --- same as W
   H not picked by Z,S,C,E --- same as X,
   backquotes:
     \` => `
     otherwise backquotes ` toggle the conversion off and on 
*/

struct letter letter [] =
   { {0xd0, 0x81, "Yo"},
     {0xd0, 0x90, "A"},  {0xd0, 0x91, "B"},  {0xd0, 0x92, "V"},
     {0xd0, 0x93, "G"},  {0xd0, 0x94, "D"},  {0xd0, 0x95, "E"},
     {0xd0, 0x96, "Zh"}, {0xd0, 0x97, "Z"},  {0xd0, 0x98, "I"},
     {0xd0, 0x99, "J"},  {0xd0, 0x9a, "K"},  {0xd0, 0x9b, "L"},
     {0xd0, 0x9c, "M"},  {0xd0, 0x9d, "N"},  {0xd0, 0x9e, "O"},
     {0xd0, 0x9f, "P"},
     {0xd0, 0xa0, "R"},  {0xd0, 0xa1, "S"},  {0xd0, 0xa2, "T"},
     {0xd0, 0xa3, "U"},  {0xd0, 0xa4, "F"},  {0xd0, 0xa5, "X"},
     {0xd0, 0xa6, "C"},  {0xd0, 0xa7, "Ch"}, {0xd0, 0xa8, "Sh"},
     {0xd0, 0xa9, "S#"}, {0xd0, 0xaa, "Q"},  {0xd0, 0xab, "W"},
     {0xd0, 0xac, "\\'"}, {0xd0, 0xad, "Eh"}, {0xd0, 0xae, "Yu"},
     {0xd0, 0xaf, "Ya"},
     {0xd0, 0xb0, "a"},  {0xd0, 0xb1, "b"},  {0xd0, 0xb2, "v"},
     {0xd0, 0xb3, "g"},  {0xd0, 0xb4, "d"},  {0xd0, 0xb5, "e"},
     {0xd0, 0xb6, "zh"}, {0xd0, 0xb7, "z"},  {0xd0, 0xb8, "i"},
     {0xd0, 0xb9, "j"},  {0xd0, 0xba, "k"},  {0xd0, 0xbb, "l"},
     {0xd0, 0xbc, "m"},  {0xd0, 0xbd, "n"},  {0xd0, 0xbe, "o"},
     {0xd0, 0xbf, "p"},
     {0xd1, 0x80, "r"},  {0xd1, 0x81, "s"},  {0xd1, 0x82, "t"},
     {0xd1, 0x83, "u"},  {0xd1, 0x84, "f"},  {0xd1, 0x85, "x"},
     {0xd1, 0x86, "c"},  {0xd1, 0x87, "ch"}, {0xd1, 0x88, "sh"},
     {0xd1, 0x89, "s#"}, {0xd1, 0x8a, "q"},  {0xd1, 0x8b, "w"},
     {0xd1, 0x8c, "'"}, {0xd1, 0x8d, "eh"}, {0xd1, 0x8e, "yu"},
     {0xd1, 0x8f, "ya"},
     {0xd1, 0x91, "yo"}
   };

main ()
{
  int next, after, i;

  int conversion_on;

  conversion_on = 1;

  next = getchar ();
  while (next != EOF) {
    after = getchar ();

    if (next == '\\' && after == '`') {
      putchar ('`');
      next = getchar ();
      continue;
    }

    if (conversion_on == 0 || next == '`') {
      if (next == '`') {
        conversion_on = (!conversion_on);
      }
      else {
        putchar (next);
      }
      next = after;
      continue;      
    }

    i = -1;
    if (next == 'Y' && (after == 'o' || after == 'O'))
      i = 0;
    else if (next == 'Y' && (after == 'e' || after == 'E'))
      i = 6;
    else if (next == 'Z' && (after == 'h' || after == 'H'))
      i = 7;
    else if (next == 'C' && (after == 'h' || after == 'H'))
      i = 24;
    else if (next == 'S' && (after == 'h' || after == 'H'))
      i = 25;
    else if (next == 'S' && after == '#')
      i = 26;
    else if (next == '\\' && after == '\'')
      i = 29;
    else if (next == 'E' && (after == 'h' || after == 'H'))
      i = 30;
    else if (next == 'Y' && (after == 'u' || after == 'U'))
      i = 31;
    else if (next == 'Y' && (after == 'a' || after == 'A'))
      i = 32;
    else if (next == 'y' && after == 'e')
      i = 38;
    else if (next == 'z' && after == 'h')
      i = 39;
    else if (next == 'c' && after == 'h')
      i = 56;
    else if (next == 's' && after == 'h')
      i = 57;
    else if (next == 's' && after == '#')
      i = 58;
    else if (next == 'e' && after == 'h')
      i = 62;
    else if (next == 'y' && after == 'u')
      i = 63;
    else if (next == 'y' && after == 'a')
      i = 64;
    else if (next == 'y' && after == 'o')
      i = 65;

    if (i != -1) {
      putchar(letter[i].byte1);
      putchar(letter[i].byte2);
      next = getchar ();
    }
    else {
      if (next == 'A') i = 1;
      else if (next == 'B') i = 2;
      else if (next == 'V') i = 3;
      else if (next == 'G') i = 4;
      else if (next == 'D') i = 5;
      else if (next == 'E') i = 6;
      else if (next == 'Z') i = 8;
      else if (next == 'I') i = 9;
      else if (next == 'J') i = 10;
      else if (next == 'K') i = 11;
      else if (next == 'L') i = 12;
      else if (next == 'M') i = 13;
      else if (next == 'N') i = 14;
      else if (next == 'O') i = 15;
      else if (next == 'P') i = 16;
      else if (next == 'R') i = 17;
      else if (next == 'S') i = 18;
      else if (next == 'T') i = 19;
      else if (next == 'U') i = 20;
      else if (next == 'F') i = 21;
      else if (next == 'X') i = 22;
      else if (next == 'H') i = 22;
      else if (next == 'C') i = 23;
      else if (next == 'Q') i = 27;
      else if (next == 'W') i = 28;
      else if (next == 'Y') i = 28;
      else if (next == 'a') i = 33;
      else if (next == 'b') i = 34;
      else if (next == 'v') i = 35;
      else if (next == 'g') i = 36;
      else if (next == 'd') i = 37;
      else if (next == 'e') i = 38;
      else if (next == 'z') i = 40;
      else if (next == 'i') i = 41;
      else if (next == 'j') i = 42;
      else if (next == 'k') i = 43;
      else if (next == 'l') i = 44;
      else if (next == 'm') i = 45;
      else if (next == 'n') i = 46;
      else if (next == 'o') i = 47;
      else if (next == 'p') i = 48;
      else if (next == 'r') i = 49;
      else if (next == 's') i = 50;
      else if (next == 't') i = 51;
      else if (next == 'u') i = 52;
      else if (next == 'f') i = 53;
      else if (next == 'x') i = 54;
      else if (next == 'h') i = 54;
      else if (next == 'c') i = 55;
      else if (next == 'q') i = 59;
      else if (next == 'w') i = 60;
      else if (next == 'y') i = 60;
      else if (next == '\'') i = 61;

      if (i != -1) {
        putchar(letter[i].byte1);
        putchar(letter[i].byte2);
      }
      else {
        putchar(next);
      }

      next = after;
    }
  }
}

