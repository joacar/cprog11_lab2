/*
 * Driver for cprog06lab22. Written 2006-09-27 by Gunnar Kreitz <gkreitz>
 *
 * If you need to modify this file to solve the assignment, you're most likely
 * solving it the wrong way.
 */

#include "calendar.h"
#include "julian.h"
#include "gregorian.h"
#include "kattistime.h"
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <stdexcept>
#include "gregorian.h"
#include "julian.h"
#include "calendar.h"

using std::size_t;
using std::cout;
using std::endl;

using lab2::Julian;
using lab2::Gregorian;
using lab2::Calendar;

static int linenr = 0;

// Anonymous namespace for local variables and functions
namespace {
	/*
	 * Class to do the calendar tests. We need to use templates since we want to
	 * be able to use both Calendar<Gregorian> and Calendar<Julian>. The reason
	 * for the second template argument is that we want to test assignment/copy
	 * construction between Calendars specialized on different date types.
	 *
	 * The idea is to make two instances of this class, each pointing to the other
	 * instance's cals-vector (set up by using set_companion).
	 */
	template<class T, class S>
	class CalendarTester {
		public:
			/*
			 * Warning: modifies argument!
			 */
			void set_companion(CalendarTester<S,T> &companion) {
				others = &companion.cals;
				companion.others = &cals;
			}

			void handle() {
				char buf[101];
				if(scanf("%100s", buf) != 1)
					assert(!"Failed reading command");
				std::string command(buf);

				if(command == "new") {
					cals.push_back(new Calendar<T>());
				} else if(command == "delete") {
					const size_t idx = read_idx_or_die();
					delete cals[idx];
					cals[idx] = 0;
				} else if(command == "newcopy") {
					const size_t idx = read_idx_or_die();
					cals.push_back(new Calendar<T>(*const_cast<const Calendar<T> *>(cals[idx])));
				} else if(command == "newcopyother") {
					const size_t idx = read_idx_or_die(true);
					cals.push_back(new Calendar<T>(*const_cast<const Calendar<S> *>((*others)[idx])));
				} else if(command == "copy") {
					const size_t from = read_idx_or_die();
					const size_t to = read_idx_or_die();
					(*cals[to]) = *const_cast<const Calendar<T> *>(cals[from]);
				} else if(command == "copyother") {
					const size_t from = read_idx_or_die(true);
					const size_t to = read_idx_or_die();
					(*cals[to]) = *const_cast<const Calendar<S> *>((*others)[from]);
				} else if(command == "print") {
					const size_t idx = read_idx_or_die();
					cout << "L" << linenr << ":C" << idx << ";print" << endl <<*const_cast<const Calendar<T> *>(cals[idx]);
					cout.flush();
				} else if(command == "set_date") {
					const size_t idx = read_idx_or_die();
					int y, m, d;
					if(scanf("%d%d%d", &y, &m, &d) != 3)
						assert(!"Failed to read date for set_date");
					cout << "L" << linenr << ":C" << idx << ";" <<cals[idx]->set_date(y,m,d) << endl;
				} else if(command == "add_event") {
					const size_t idx = read_idx_or_die();
					int y, m, d;
					if(scanf("%100s", buf) != 1)
						assert(!"Failed to read eventstring for add_event");
					const std::string event(buf);
					switch(scanf("%d%d%d", &d, &m, &y)) {
						case 0: case EOF: cout << "L" << linenr << ":C" << idx << ";" <<cals[idx]->add_event(event) << endl; break;
						case 1: cout << "L" << linenr << ":C" << idx << ";" <<cals[idx]->add_event(event, d) << endl; break;
						case 2: cout << "L" << linenr << ":C" << idx << ";" <<cals[idx]->add_event(event, d, m) << endl; break;
						case 3: cout << "L" << linenr << ":C" << idx << ";" <<cals[idx]->add_event(event, d, m, y) << endl; break;
						default:
								  assert(!"Unreachable code (add_event switch)");
					}
				} else if(command == "remove_event") {
					const size_t idx = read_idx_or_die();
					int y, m, d;
					if(scanf("%100s", buf) != 1)
						assert(!"Failed to read eventstring for remove_event");
					const std::string event(buf);
					switch(scanf("%d%d%d", &d, &m, &y)) {
						case 0: case EOF: cout << "L" << linenr << ":C" << idx << ";" <<cals[idx]->remove_event(event) << endl; break;
						case 1: cout << "L" << linenr << ":C" << idx << ";" <<cals[idx]->remove_event(event, d) << endl; break;
						case 2: cout << "L" << linenr << ":C" << idx << ";" <<cals[idx]->remove_event(event, d, m) << endl; break;
						case 3: cout << "L" << linenr << ":C" << idx << ";" <<cals[idx]->remove_event(event, d, m, y) << endl; break;
						default:
								  assert(!"Unreachable code (remove_event switch)");
					}
				} else if(command == "set_k_time") {
					time_t t = 0;
					/* No standardized way to read time_t with sca
nf */
					if(!(std::cin >> t))
						assert(!"Can't read time");
					set_k_time(t);
				} else {
					fprintf(stderr, "Got bad command: %s\n", command.c_str());
					assert(!"Unknown command");
				}
			}

			/*
			 *           * There is no way in standard C++ to read a size_t. The way we solve it here is to
			 *                     * read it as an unsigned long. This program will not be used with too large inputs.
			 *                               * Another way would be to use size_t ret; scanf("%zu", &ret); which is legal in C99
			 *                                         * and thus most likely will be OK in C++0x. It's already supported by most compilers.
			 *                                                   * If it was changed to using scanf instead, the sync_with_stdio(false)
			 *                                                             * would need to be removed.
			 *
			 */
			size_t read_idx_or_die(bool other = false) {
				unsigned long ret;
				std::cin >> ret;
				assert(std::cin);

				if(other) {
					assert(ret < others->size());
					assert((*others)[ret] != 0);
				} else {
					assert(ret < cals.size());
					assert(cals[ret] != 0);
				}
				return ret;
			}

			friend class CalendarTester<S,T>;

		private:
			std::vector<Calendar<T> *> cals;
			std::vector<Calendar<S> *> *others;
	};

}

int main(int argc, char **argv) {
	char buf[101];

	CalendarTester<Gregorian, Julian> g;
	CalendarTester<Julian, Gregorian> j;
	g.set_companion(j);

	while(scanf("%100s", buf) == 1) {
		std::string command(buf);
        linenr++;
		if(command == "g") {
			g.handle();
		} else if(command == "j") {
			j.handle();
		} else {
			fprintf(stderr, "Got bad type: %s\n", command.c_str());
			assert(!"Unknown type");
		}
	}

	return 0;
}
