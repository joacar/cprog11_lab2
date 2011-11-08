// projektlokala headerfiler
#include "kattistime.h"     
#include "julian.h"         
#include "gregorian.h"      

// STL headerfiler
#include <iostream>
#include <assert.h>             // assert(b) ger felmeddelande om b falsk
#include <ctime>


// Obs att testerna förutsätter att dina klasser returnerar
// månader och dagar indexerade från ETT. Testerna är inte
// fullständiga


int main()
{
    using namespace lab2;        // Exponera funktionalitet i namnrymden lab2

    ////////////////////////////////////////////////////////////
    // Sätt tiden. OBS skicka inte nedanstående kod till kattis
    time_t mytime;
    time(&mytime);
    set_k_time(mytime);
    ////////////////////////////////////////////////////////////

    std::cout << std::endl << "\tTests from lab2.pdf" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    Gregorian gtoday_1;
    std::cout << "Gregorian: " << gtoday_1 << std::endl;
    Julian jtoday_1;
    std::cout << "Julian: " << jtoday_1 << std::endl;

    std::cout << "Today it is " << gtoday_1 << " gregorian and " << jtoday_1 << " julian";
    if (gtoday_1 - jtoday_1 == 0) std::cout << ". It is the same date" << std::endl;
    gtoday_1 = jtoday_1;
    if (gtoday_1 - jtoday_1 == 0) std::cout << "It is still the same date" << std::endl;

    std::cout << std::endl << "Test mod_julian_day" << std::endl;
    std::cout << "Gregorian 1858-11-17 and Julian 1858-11-05" << std::endl;
    Gregorian g_mod(1858, 11, 17);
    assert(g_mod.year() == 1858
        && g_mod.month() == 11
        && g_mod.day() == 17);

    Julian j_mod(1858, 11, 5);
    assert(j_mod.year() == 1858
        && j_mod.month() == 11
        && j_mod.day() == 5);

    assert(j_mod.mod_julian_day() == 0);
    assert(g_mod.mod_julian_day() == 0);

    --g_mod; --j_mod;
    assert(j_mod.mod_julian_day() == -1);
    assert(g_mod.mod_julian_day() == -1);
    ++g_mod; ++j_mod;
    assert(j_mod.mod_julian_day() == 0);
    assert(g_mod.mod_julian_day() == 0);
    ++g_mod; ++j_mod;
    assert(j_mod.mod_julian_day() == 1);
    assert(g_mod.mod_julian_day() == 1);
    

    std::cout << std::endl << "Test first and last" << std::endl;
    Julian first = Julian(1858,1,1);
    std::cout << first << " " << first.week_day_name() << std::endl;
    Julian last = Julian(2558,12,31);
    std::cout << last <<  " " << last.week_day_name() << std::endl;

    std::cout << "------------------------------------" << std::endl;
    
    std::cout << "\tdatetest" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    
    Julian tj;                  // ok: defaultkonstruktor ger dagens datum
    Gregorian gtoday;           // ok för gregorian också
    std::cout << "Idag är det " << gtoday << std::endl;
    assert(tj - gtoday == 0);
    Gregorian tg(2006, 10, 31); // ok: sätt datum explicit
                                // följande fungerar också:
                                // Gregorian(2000, Gregorian::October, 31)
    Date &j = tj;               // åtkomst av funktioner genom Dates interface
    Date &g = tg;       
    Date &today = gtoday;

    {
      Julian j1;
      Date & d1 = j1;
      Julian j2(d1);
      Date * dp = &j2;
      //Julian j3(dp);
    }
     
    time_t tp;
    time(&tp);
    struct tm *t = gmtime(&tp);
    int year  = t->tm_year + 1900;
    int month = t->tm_mon + 1;      // månaderna och dagarna
    int day   = t->tm_mday;         // indexerade från ETT

    std::cout << "Testing constructors..." << std::endl;
    assert(today.year() == year &&          // rätt initierad
           today.month() == month &&
           today.day() == day);
    assert(g.year() == 2006 &&              // rätt initierad
           g.month() == 10 &&
           g.day() == 31);                  // obs! ettindexerade
    
    std::cout << "Testing access..." << std::endl;
    assert(g.days_per_week() == 7);         // rätt antal dagar per vecka
    assert(j.days_per_week() == 7);         // rätt antal dagar per vecka
    assert(g.days_this_month() == 31);      // rätt antal dagar denna månad
    assert(g.months_per_year() == 12);      // rätt antal månader per år
    assert(j.months_per_year() == 12);      // rätt antal månader per år
    assert(g.week_day() == 2); // rätt veckodag

    std::cout << "Testing manipulation..." << std::endl;
    ++g;                                    // prefix ökning
    assert(g.week_day() == 3); // rätt veckodag
    --g;                                    // prefix minskning
    assert(g.week_day() == 2); // rätt veckodag
    g += 2;                                 // lägg till två dagar
    assert(g.week_day() == 4); // rätt veckodag
    g -= 3;                     // dra bort tre dagar
    g.add_month();              // lägg till en månad
    g.add_month(-1);            // dra bort en månad    
    g.add_year(10);             // lägg till tio år.
    
    std::cout << "Testing miscellaneous functions..." << std::endl;
    Julian jj(tj);              // kopieringskonstruktor
    const Gregorian gg;
    gg.year();                  // gg konstant, läsa går bra
    g = gg;                     // tilldelning
    if(g == gg ||               // jämförelse
       g != gg ||               // jämförelse 
       g < gg ||                // jämförelse 
       g >= gg)                 // jämförelse 
        {}
    
    std::cout << "Testing boundary violations";
    Gregorian temp(1900, 1, 1);
    Date &d = temp;

    // loopa över dagar och kolla att inga gränser över/underskrids
    for(int i = 0; i < 100000; ++i, ++d)
        {
            if(!(i % 5000))        // utskrift på framsteg
                {
                    std::cout << ".";
                    flush(std::cout);
                }
            int m[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if(d.year() >= 1900 && 
               d.month() >= 1 && d.month() <= 12 &&
               d.day() >= 1 && d.day() <= m[d.month() - 1])
                {}
            else
                {
                    std::cout << std::endl;
                    std::cout << "boundary checks failed: " << std::endl;
                    std::cout << d.year() << ", "
                              << d.month() << ", "
                              << d.day() << std::endl;
                    return 1;
                }
        }
    std::cout << std::endl;

    std::cout << "Testing leap years..." << std::endl;
    // testa om skottåren för sekelskiften fungerar som de ska
    for(int y = 1958; y < 2500; y += 100)
        {
            Gregorian temp(y, 2, 28);
            Date &e = temp;
            //std::cout << "Before +ee: " << e << std::endl;
            ++e;                                   // lägg till en dag
            if((y % 400 == 0 && e.day() == 29) ||  // skottdag (obs! ETTindexerad)
               (y % 400 != 0 && e.day() == 1))     // ej skottdag
                {
                    //std::cout << "Success: " << e << std::endl;
                }
            else
                {
                    //std::cout << "Failure: " << e << std::endl;
                    std::cout << std::endl << "leap day test failed: " << std::endl;
                    std::cout << e.year() << ", "
                              << e.month() << ", "
                              << e.day() << std::endl;
                    return 1;
                }
        }

    std::cout << "Testing add_month thoroughly..." << std::endl;
    // Add one month on a month containing 30 days 
    Gregorian greg(2011,9,1);
    greg.add_month();
    assert(greg.year() == 2011 && greg.month() == 10 && greg.day() == 1);
    
    // Add one month on a month containing 31 days
    Gregorian greg1(2011,5,31);
    greg1.add_month();
    assert(greg1.year() == 2011 && greg1.month() == 6 && greg1.day() == 30);

    // Add one month on a month containing 28 days
    Gregorian greg2(2011,2,28);
    greg2.add_month();
    assert(greg2.year() == 2011 && greg2.month() == 3 && greg2.day() == 28);

    // Add one month on January on a non-leap year
    Gregorian greg_n(2011,1,31);
    greg_n.add_month();
    assert(greg_n.year() == 2011 && greg_n.month() == 3 && greg_n.day() == 2);

    // add_month(5) should be equvivalent to add_month() x 5
    Gregorian greg_t(2011,3,1);
    greg_t.add_month(5);
    Gregorian greg_t1(2011,3,1);
    for(int i = 0; i < 5; i++)
    {
        greg_t1.add_month();
    }
    assert(greg_t1 == greg_t);

    // Test leap years
    // add_month() when date is last of january
    Gregorian greg_leap(2012,1,31);
    greg_leap.add_month();
    assert(greg_leap.year() == 2012 && greg_leap.month() == 3 && greg_leap.day() == 1);
    
    // Add one month on a leap year on the last of february
    Gregorian greg_leap1(2012,2,29);
    greg_leap1.add_month();
    assert(greg_leap1.year() == 2012 && greg_leap1.month() == 3 && greg_leap1.day() == 29);

    std::cout << "Testing add_year thoroughly..." << std::endl;
    //Leap day
    Gregorian leap_day(2012,2,29);
    leap_day.add_year();
    assert(leap_day.year() == 2013 && leap_day.month() == 2 && leap_day.day() == 28);

    Gregorian leap_day1(2012,2,29);
    leap_day1.add_year(1);
    leap_day1.add_year(-1);
    assert(leap_day1.year() == 2012 && leap_day1.month() == 2 && leap_day1.day() == 28); 

    ++leap_day1;
    leap_day1.add_year(4);
    assert(leap_day1.year() == 2016 && leap_day1.month() == 2 && leap_day1.day() == 29);

    Gregorian leap_day2(2012,2,29);
    for(int i = 0; i < 4; i++)
    {
        leap_day2.add_year();
    }
    assert(leap_day2.year() == 2016 && leap_day2.month() == 2 && leap_day2.day() == 28);

    std::cout << "Testing greg constructor with leap day" << std::endl;
    // Testing leap years for Gregorian
    set_k_time(109978914);

    for(int y = 1900; y < 2500; y += 100)
    {
        
        try {
            Gregorian temp(y, 2, 29);
        } catch(std::exception& e) {
                std::cout << y << "-02-29 exception in constructor" << std::endl;
            }
    }

    std::cout << std::endl << "Testing kattis error messages" << std::endl;
    // Below date and minus -28 months does not work
    Julian jk(1992,2,29);
    std::cout << jk << std::endl;
    jk.add_month(-1);
    std::cout << "jk.add_month(-1): " << jk << std::endl;
    jk.add_month(-27);
    std::cout << "jk.add_month(-27): " <<jk << std::endl;

    assert(jk.year() == 1989
        && jk.month() == 10
        && jk.day() == 27);

    std::cout << std::endl << "All tests were successful." << std::endl;

    // följande ska inte gå att kompilera. ** Det gör det inte
#if 0
    gg.leap_year();             // fel: kan inte komma åt protected/private medlem
    gg = g;                     // fel: kan inte tilldela konstant
    ++gg;                       // fel: kan inte ändra på en konstant
#endif

    return 0;
}

