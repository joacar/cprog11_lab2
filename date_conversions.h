#ifndef _DATE_CONVERSIONS_
#define _DATE_CONVERSIONS_

namespace lab2 {

#ifdef PAPAL                    /* Pope Gregory XIII's decree */
#define LASTJULDATE 15821004L   /* last day to use Julian calendar */
#define LASTJULJDN  2299160L    /* jdn of same */
#else                           /* British-American usage */
#define LASTJULDATE 17520902L   /* last day to use Julian calendar */
#define LASTJULJDN  2361221L    /* jdn of same */
#endif

class DateConversions {
public:
    static long ymd_to_jdn(int y, int m, int d, int julian);
    static void jdn_to_ymd(long jdn, int *yy, int *mm, int *dd, int julian); 
};

}
#endif