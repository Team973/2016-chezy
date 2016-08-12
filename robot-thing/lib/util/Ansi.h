/*
 * Ansi.h
 *
 * Standard ansi string abreviations
 *
 * Created on: Sep 1 2008
 * Author: Mike Tsang
 */

#ifndef FRCLIB_ANSI_H_
#define FRCLIB_ANSI_H_

#ifdef _USE_COLORFONT

#define ESC_PREFIX              "\x1b["
#define ESC_SUFFIX              "m"
#define ESC_SEP                 ";"

#define SGR_RESET               "0"
#define SGR_BRIGHT              "1"
#define SGR_DIM                 "2"
#define SGR_ITALIC              "3"
#define SGR_UNDERLINE           "4"
#define SGR_BLINKSLOW           "5"
#define SGR_BLINKFAST           "6"
#define SGR_REVERSE             "7"
#define SGR_HIDDEN              "8"
#define SGR_CROSSEDOUT          "9"

#define SGR_FG_BLACK            "30"
#define SGR_FG_RED              "31"
#define SGR_FG_GREEN            "32"
#define SGR_FG_YELLOW           "33"
#define SGR_FG_BLUE             "34"
#define SGR_FG_MAGENTA          "35"
#define SGR_FG_CYAN             "36"
#define SGR_FG_WHITE            "37"
 
#define SGR_BG_BLACK            "40"
#define SGR_BG_RED              "41"
#define SGR_BG_GREEN            "42"
#define SGR_BG_YELLOW           "43"
#define SGR_BG_BLUE             "44"
#define SGR_BG_MAGENTA          "45"
#define SGR_BG_CYAN             "46"
#define SGR_BG_WHITE            "47"
 
#define ESC_NORMAL              ESC_PREFIX ESC_SUFFIX
#define ESC_BLINKSLOW           ESC_PREFIX SGR_BLINKSLOW ESC_SUFFIX
#define ESC_BLINKFAST           ESC_PREFIX SGR_BLINKFAST ESC_SUFFIX

#define ESC_FG_BLACK            ESC_PREFIX SGR_FG_BLACK    ESC_SUFFIX
#define ESC_FG_RED              ESC_PREFIX SGR_FG_RED      ESC_SUFFIX
#define ESC_FG_GREEN            ESC_PREFIX SGR_FG_GREEN    ESC_SUFFIX
#define ESC_FG_YELLOW           ESC_PREFIX SGR_FG_YELLOW   ESC_SUFFIX
#define ESC_FG_BLUE             ESC_PREFIX SGR_FG_BLUE     ESC_SUFFIX
#define ESC_FG_MAGENTA          ESC_PREFIX SGR_FG_MAGENTA  ESC_SUFFIX
#define ESC_FG_CYAN             ESC_PREFIX SGR_FG_CYAN     ESC_SUFFIX
#define ESC_FG_WHITE            ESC_PREFIX SGR_FG_WHITE    ESC_SUFFIX

#define ESC_BG_BLACK            ESC_PREFIX SGR_BG_BLACK    ESC_SUFFIX
#define ESC_BG_RED              ESC_PREFIX SGR_BG_RED      ESC_SUFFIX
#define ESC_BG_GREEN            ESC_PREFIX SGR_BG_GREEN    ESC_SUFFIX
#define ESC_BG_YELLOW           ESC_PREFIX SGR_BG_YELLOW   ESC_SUFFIX
#define ESC_BG_BLUE             ESC_PREFIX SGR_BG_BLUE     ESC_SUFFIX
#define ESC_BG_MAGENTA          ESC_PREFIX SGR_BG_MAGENTA  ESC_SUFFIX
#define ESC_BG_CYAN             ESC_PREFIX SGR_BG_CYAN     ESC_SUFFIX
#define ESC_BG_WHITE            ESC_PREFIX SGR_BG_WHITE    ESC_SUFFIX

#define ESC_FGB_BLACK           ESC_PREFIX SGR_FG_BLACK    \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX
#define ESC_FGB_RED             ESC_PREFIX SGR_FG_RED      \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX
#define ESC_FGB_GREEN           ESC_PREFIX SGR_FG_GREEN    \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX
#define ESC_FGB_YELLOW          ESC_PREFIX SGR_FG_YELLOW   \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX
#define ESC_FGB_BLUE            ESC_PREFIX SGR_FG_BLUE     \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX
#define ESC_FGB_MAGENTA         ESC_PREFIX SGR_FG_MAGENTA  \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX
#define ESC_FGB_CYAN            ESC_PREFIX SGR_FG_CYAN     \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX
#define ESC_FGB_WHITE           ESC_PREFIX SGR_FG_WHITE    \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX

#define ESC_BGB_BLACK           ESC_PREFIX SGR_BG_BLACK    \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX
#define ESC_BGB_RED             ESC_PREFIX SGR_BG_RED      \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX
#define ESC_BGB_GREEN           ESC_PREFIX SGR_BG_GREEN    \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX
#define ESC_BGB_YELLOW          ESC_PREFIX SGR_BG_YELLOW   \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX
#define ESC_BGB_BLUE            ESC_PREFIX SGR_BG_BLUE     \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX
#define ESC_BGB_MAGENTA         ESC_PREFIX SGR_BG_MAGENTA  \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX
#define ESC_BGB_CYAN            ESC_PREFIX SGR_BG_CYAN     \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX
#define ESC_BGB_WHITE           ESC_PREFIX SGR_BG_WHITE    \
                                ESC_SEP SGR_BRIGHT ESC_SUFFIX

#else

#define ESC_PREFIX
#define ESC_SUFFIX
#define ESC_SEP

#define SGR_RESET
#define SGR_BRIGHT
#define SGR_DIM
#define SGR_ITALIC
#define SGR_UNDERLINE
#define SGR_BLINKSLOW
#define SGR_BLINKFAST
#define SGR_REVERSE
#define SGR_HIDDEN
#define SGR_CROSSEDOUT

#define SGR_FG_BLACK
#define SGR_FG_RED
#define SGR_FG_GREEN
#define SGR_FG_YELLOW
#define SGR_FG_BLUE
#define SGR_FG_MAGENTA
#define SGR_FG_CYAN
#define SGR_FG_WHITE
 
#define SGR_BG_BLACK
#define SGR_BG_RED
#define SGR_BG_GREEN
#define SGR_BG_YELLOW
#define SGR_BG_BLUE
#define SGR_BG_MAGENTA
#define SGR_BG_CYAN
#define SGR_BG_WHITE
 
#define ESC_NORMAL
#define ESC_BLINKSLOW
#define ESC_BLINKFAST

#define ESC_FG_BLACK
#define ESC_FG_RED
#define ESC_FG_GREEN
#define ESC_FG_YELLOW
#define ESC_FG_BLUE
#define ESC_FG_MAGENTA
#define ESC_FG_CYAN
#define ESC_FG_WHITE

#define ESC_BG_BLACK
#define ESC_BG_RED
#define ESC_BG_GREEN
#define ESC_BG_YELLOW
#define ESC_BG_BLUE
#define ESC_BG_MAGENTA
#define ESC_BG_CYAN
#define ESC_BG_WHITE

#define ESC_FGB_BLACK
#define ESC_FGB_RED
#define ESC_FGB_GREEN
#define ESC_FGB_YELLOW
#define ESC_FGB_BLUE
#define ESC_FGB_MAGENTA
#define ESC_FGB_CYAN
#define ESC_FGB_WHITE

#define ESC_BGB_BLACK
#define ESC_BGB_RED
#define ESC_BGB_GREEN
#define ESC_BGB_YELLOW
#define ESC_BGB_BLUE
#define ESC_BGB_MAGENTA
#define ESC_BGB_CYAN
#define ESC_BGB_WHITE

#endif
 
#endif /* FRCLIB_ANSI_H_ */
