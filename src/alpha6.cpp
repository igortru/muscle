#include "myutils.h"
#include "kmerdist66.h"

// Amino acid groups according to MAFFT (sextet5)
// 0 =  A G P S T
// 1 =  I L M V
// 2 =  N D Q E B Z
// 3 =  R H K
// 4 =  F W Y
// 5 =  C
// 6 =  X . - U
//uint KmerDist66::m_LetterToGroup[20] =
//	{
//	0,		// AX_A,
//	5,		// AX_C,
//	2,		// AX_D,
//	2,		// AX_E,
//	4,		// AX_F,
//	0,		// AX_G,
//	3,		// AX_H,
//	1,		// AX_I,
//	3,		// AX_K,
//	1,		// AX_L,
//	1,		// AX_M,
//	2,		// AX_N,
//	0,		// AX_P,
//	2,		// AX_Q,
//	3,		// AX_R,
//	0,		// AX_S,
//	0,		// AX_T,
//	1,		// AX_V,
//	4,		// AX_W,
//	4,		// AX_Y,
//	};
uint KmerDist66::m_CharToGroup[256] =
	{
	0, //  0x00
	0, //  0x01
	0, //  0x02
	0, //  0x03
	0, //  0x04
	0, //  0x05
	0, //  0x06
	0, //  0x07
	0, //  0x08
	0, //  0x09
	0, //  0x0a
	0, //  0x0b
	0, //  0x0c
	0, //  0x0d
	0, //  0x0e
	0, //  0x0f
	0, //  0x10
	0, //  0x11
	0, //  0x12
	0, //  0x13
	0, //  0x14
	0, //  0x15
	0, //  0x16
	0, //  0x17
	0, //  0x18
	0, //  0x19
	0, //  0x1a
	0, //  0x1b
	0, //  0x1c
	0, //  0x1d
	0, //  0x1e
	0, //  0x1f
	0, //  ' '
	0, //  '!'
	0, //  '"'
	0, //  '#'
	0, //  '$'
	0, //  '%'
	0, //  '&'
	0, //  '''
	0, //  '('
	0, //  ')'
	0, //  '*'
	0, //  '+'
	0, //  ','
	0, //  '-'
	0, //  '.'
	0, //  '/'
	0, //  '0'
	0, //  '1'
	0, //  '2'
	0, //  '3'
	0, //  '4'
	0, //  '5'
	0, //  '6'
	0, //  '7'
	0, //  '8'
	0, //  '9'
	0, //  ':'
	0, //  ';'
	0, //  '<'
	0, //  '='
	0, //  '>'
	0, //  '?'
	0, //  '@'
	0, //  'A'
	0, //  'B'
	5, //  'C'
	2, //  'D'
	2, //  'E'
	4, //  'F'
	0, //  'G'
	3, //  'H'
	1, //  'I'
	0, //  'J'
	3, //  'K'
	1, //  'L'
	1, //  'M'
	2, //  'N'
	0, //  'O'
	0, //  'P'
	2, //  'Q'
	3, //  'R'
	0, //  'S'
	0, //  'T'
	0, //  'U'
	1, //  'V'
	4, //  'W'
	0, //  'X'
	4, //  'Y'
	0, //  'Z'
	0, //  '['
	0, //  '\'
	0, //  ']'
	0, //  '^'
	0, //  '_'
	0, //  '`'
	0, //  'a'
	0, //  'b'
	5, //  'c'
	2, //  'd'
	2, //  'e'
	4, //  'f'
	0, //  'g'
	3, //  'h'
	1, //  'i'
	0, //  'j'
	3, //  'k'
	1, //  'l'
	1, //  'm'
	2, //  'n'
	0, //  'o'
	0, //  'p'
	2, //  'q'
	3, //  'r'
	0, //  's'
	0, //  't'
	0, //  'u'
	1, //  'v'
	4, //  'w'
	0, //  'x'
	4, //  'y'
	0, //  'z'
	0, //  '{'
	0, //  '|'
	0, //  '}'
	0, //  '~'
	0, //  0x7f
	0, //  0x80
	0, //  0x81
	0, //  0x82
	0, //  0x83
	0, //  0x84
	0, //  0x85
	0, //  0x86
	0, //  0x87
	0, //  0x88
	0, //  0x89
	0, //  0x8a
	0, //  0x8b
	0, //  0x8c
	0, //  0x8d
	0, //  0x8e
	0, //  0x8f
	0, //  0x90
	0, //  0x91
	0, //  0x92
	0, //  0x93
	0, //  0x94
	0, //  0x95
	0, //  0x96
	0, //  0x97
	0, //  0x98
	0, //  0x99
	0, //  0x9a
	0, //  0x9b
	0, //  0x9c
	0, //  0x9d
	0, //  0x9e
	0, //  0x9f
	0, //  0xa0
	0, //  0xa1
	0, //  0xa2
	0, //  0xa3
	0, //  0xa4
	0, //  0xa5
	0, //  0xa6
	0, //  0xa7
	0, //  0xa8
	0, //  0xa9
	0, //  0xaa
	0, //  0xab
	0, //  0xac
	0, //  0xad
	0, //  0xae
	0, //  0xaf
	0, //  0xb0
	0, //  0xb1
	0, //  0xb2
	0, //  0xb3
	0, //  0xb4
	0, //  0xb5
	0, //  0xb6
	0, //  0xb7
	0, //  0xb8
	0, //  0xb9
	0, //  0xba
	0, //  0xbb
	0, //  0xbc
	0, //  0xbd
	0, //  0xbe
	0, //  0xbf
	0, //  0xc0
	0, //  0xc1
	0, //  0xc2
	0, //  0xc3
	0, //  0xc4
	0, //  0xc5
	0, //  0xc6
	0, //  0xc7
	0, //  0xc8
	0, //  0xc9
	0, //  0xca
	0, //  0xcb
	0, //  0xcc
	0, //  0xcd
	0, //  0xce
	0, //  0xcf
	0, //  0xd0
	0, //  0xd1
	0, //  0xd2
	0, //  0xd3
	0, //  0xd4
	0, //  0xd5
	0, //  0xd6
	0, //  0xd7
	0, //  0xd8
	0, //  0xd9
	0, //  0xda
	0, //  0xdb
	0, //  0xdc
	0, //  0xdd
	0, //  0xde
	0, //  0xdf
	0, //  0xe0
	0, //  0xe1
	0, //  0xe2
	0, //  0xe3
	0, //  0xe4
	0, //  0xe5
	0, //  0xe6
	0, //  0xe7
	0, //  0xe8
	0, //  0xe9
	0, //  0xea
	0, //  0xeb
	0, //  0xec
	0, //  0xed
	0, //  0xee
	0, //  0xef
	0, //  0xf0
	0, //  0xf1
	0, //  0xf2
	0, //  0xf3
	0, //  0xf4
	0, //  0xf5
	0, //  0xf6
	0, //  0xf7
	0, //  0xf8
	0, //  0xf9
	0, //  0xfa
	0, //  0xfb
	0, //  0xfc
	0, //  0xfd
	0, //  0xfe
	0, //  0xff
	};
