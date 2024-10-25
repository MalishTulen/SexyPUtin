#ifndef COLOURFUL_HEADER
#define COLOURFUL_HEADER

#define DEF_FORMAT "\033[0;"
#define BOLD "\033[1"
#define KOSOY "\033[3"
#define UNDERLINE "\033[4"

#define DEF_COLOUR ";37"
#define RED ";31"
#define GREEN ";32"
#define YELLOW ";33"
#define BLUE ";34"
#define MAGENTA ";35"
#define CYAN ";36"

#define REDB ";41m"
#define GREENB ";42m"
#define YELLOWB ";43m"
#define BLUEB ";44m"
#define MAGENTAB ";45m"
#define CYANB ";46m"
#define DEF_B "m"

#define GIVE_MORE_COLOUR( type, colour, background ) type colour background
#define SET_DEFAULT_COLOUR "\033[0m"

#endif
