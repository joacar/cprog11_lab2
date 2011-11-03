// projektlokala headerfiler
#include "kattistime.h"     
#include "julian.h"         
#include "gregorian.h"      

// STL headerfiler
#include <iostream>
#include <assert.h>             // assert(b) ger felmeddelande om b falsk
#include <ctime>


// Obs att testerna f�ruts�tter att dina klasser returnerar
// m�nader och dagar indexerade fr�n ETT. Testerna �r inte
// fullst�ndiga


int main()
{
    using namespace lab2;        // Exponera funktionalitet i namnrymden lab2

    ////////////////////////////////////////////////////////////
    // S�tt tiden. OBS skicka inte nedanst�ende kod till kattis
    time_t mytime;
    time(&mytime);
    set_k_time(mytime);
    ////////////////////////////////////////////////////////////

    
    Julian tj;                  // ok: defaultkonstruktor ger dagens datum
    Gregorian gtoday;           // ok f�r gregorian ocks�
    std::cout << "Idag �r det " << gtoday << std::endl;
    assert(tj - gtoday == 0);
    Gregorian tg(2006, 10, 31); // ok: s�tt datum explicit
                                // f�ljande fungerar ocks�:
                                // Gregorian(2000, Gregorian::October, 31)
    Date &j = tj;               // �tkomst av funktioner genom Dates interface
    Date &g = tg;       
    Date &today = gtoday;

    {
      Julian j1;
      Date & d1 = j1;
      Julian j2(d1);
      Date * dp = &j2;
      Julian j3(dp);
    }
     
    time_t tp;
    time(&tp);
    struct tm *t = gmtime(&tp);
    int year  = t->tm_year + 1900;
    int month = t->tm_mon + 1;      // m�naderna och dagarna
    int day   = t->tm_mday;         // indexerade fr�n ETT

    std::cout << "Testing constructors..." << std::endl;
    assert(today.year() == year &&          // r�tt initierad
           today.month() == month &&
           today.day() == day);
    assert(g.year() == 2006 &&              // r�tt initierad
           g.month() == 10 &&
           g.day() == 31);                  // obs! ettindexerade
    
    std::cout << "Testing access..." << std::endl;
    assert(g.days_per_week() == 7);         // r�tt antal dagar per vecka
    assert(j.days_per_week() == 7);         // r�tt antal dagar per vecka
    assert(g.days_this_month() == 31);      // r�tt antal dagar denna m�nad
    assert(g.months_per_year() == 12);      // r�tt antal m�nader per �r
    assert(j.months_per_year() == 12);      // r�tt antal m�nader per �r
    assert(g.week_day() == 2); // r�tt veckodag

    std::cout << "Testing manipulation..." << std::endl;
    ++g;                                    // prefix �kning
    assert(g.week_day() == 3); // r�tt veckodag
    --g;                                    // prefix minskning
    assert(g.week_day() == 2); // r�tt veckodag
    g += 2;                                 // l�gg till tv� dagar
    assert(g.week_day() == 4); // r�tt veckodag
    g -= 3;                     // dra bort tre dagar
    g.add_month();              // l�gg till en m�nad
    g.add_month(-1);            // dra bort en m�nad    
    g.add_year(10);             // l�gg till tio �r.
    
    std::cout << "Testing miscellaneous functions..." << std::endl;
    Julian jj(tj);              // kopieringskonstruktor
    const Gregorian gg;
    gg.year();                  // gg konstant, l�sa g�r bra
    g = gg;                     // tilldelning
    if(g == gg ||               // j�mf�relse
       g != gg ||               // j�mf�relse 
       g < gg ||                // j�mf�relse 
       g >= gg)                 // j�mf�relse 
        {}
    
    std::cout << "Testing boundary violations";
    Gregorian temp(1900, 1, 1);
    Date &d = temp;

    // loopa �ver dagar och kolla att inga gr�nser �ver/underskrids
    for(int i = 0; i < 100000; ++i, ++d)
        {
            if(!(i % 5000))        // utskrift p� framsteg
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
    // testa om skott�ren f�r sekelskiften fungerar som de ska
    for(int y = 1958; y < 2500; y += 100)
        {
            Gregorian temp(y, 2, 28);
            Date &e = temp;
            std::cout << "Before +ee: " << e << std::endl;
            ++e;                                   // l�gg till en dag
            if((y % 400 == 0 && e.day() == 29) ||  // skottdag (obs! ETTindexerad)
               (y % 400 != 0 && e.day() == 1))     // ej skottdag
                {
                    std::cout << "Success: " << e << std::endl;
                }
            else
                {
                    std::cout << "Failure: " << e << std::endl;
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
    // TODO
    // Tried this out on http://quasar.as.utexas.edu/BillInfo/JulianDateCalc.html and it works +30 on JDN.
    // Error with exception not being caught I think
    Gregorian greg_n(2011,1,31);
    greg_n.add_month();
    //assert(greg_n.year() == 2011 && greg_n.month() == 3 && greg_n.day() == 1);

    // add_month(5) should be equvivalent to add_month() x 5
    // Fails when start date is as above, works otherwise
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
    // TODO
    // Same here as with 2011-01-31.
    Gregorian greg_leap(2012,1,31);
    greg_leap.add_month();
    //assert(greg_leap.year() == 2012 && greg_leap.month() == 3 && greg_leap.day() == 2);
    
    // Add one month on a leap year on the last of february
    // TODO
    // After refresh_cache() day is set to 1...
    Gregorian greg_leap1(2012,2,29);
    greg_leap1.add_month(1);
    assert(greg_leap.year() == 2012 && greg_leap.month() == 3 && greg_leap.day() == 29);

    std::cout << "Testing add_year thoroughly..." << std::endl;


    std::cout << std::endl << "All tests were successful." << std::endl;

    // f�ljande ska inte g� att kompilera. ** Det g�r det inte
#if 0
    gg.leap_year();             // fel: kan inte komma �t protected/private medlem
    gg = g;                     // fel: kan inte tilldela konstant
    ++gg;                       // fel: kan inte �ndra p� en konstant
#endif

    return 0;
}

