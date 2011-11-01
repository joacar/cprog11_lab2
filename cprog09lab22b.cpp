/*
 * Driver for cprog06lab22b. Written 2006-10-03 by Gunnar Kreitz <gkreitz>
 *
 * If you need to modify this file to solve the assignment, you're most likely
 * solving it the wrong way.
 */

#include "gregorian.h"
#include "kattistime.h"
#include "gregorian.h"
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <stdexcept>

using std::size_t;
using std::cout;
using std::endl;

using lab2::Gregorian;
using lab2::Date;

static int linenr = 0;

// Anonymous namespace for local variables and functions
namespace {
	std::vector<Date *> dates;

	/*
	 * There is no way in standard C++ to read a size_t. The way we do it is
	 * scanf("%zu", &ret) which is legal in C99 and thus most likely will be OK in
	 * C++0x. It's already supported by most compilers.
	 */
	size_t read_idx_or_die() {
		size_t ret;
		if(scanf("%zu", &ret) != 1) {
			assert(!"Tried to read idx but failed");
		}
		assert(ret < dates.size());
		return ret;
	}

	int read_int_or_die() {
		int ret;
		if(scanf("%d", &ret) != 1) {
			assert(!"Tried to read int but failed");
		}
		return ret;
	}

	template<class D> void new_date() {
		int y, m, d;

		try {
			if(scanf("%d%d%d", &y, &m, &d) == 3) {
				dates.push_back(new D(y,m,d));
			} else {
				dates.push_back(new D());
			}
			cout << "L" << linenr << ";" << *dates[dates.size()-1] << endl;
		} catch (std::out_of_range oor) {
			cout << "L" << linenr << ";" <<"exception_in_constructor" << endl;
		}
	}

	template<class D> void new_date_copy() {
		const size_t idx = read_idx_or_die();
		try {
			dates.push_back(new D(*const_cast<const Date*>(dates[idx])));
			cout << "L" << linenr << ";" << *dates[dates.size()-1] << endl;
		} catch (std::out_of_range oor) {
			cout << "L" << linenr << ";" <<"exception_in_copy_constructor" << endl;
		}
	}
}

int main(int argc, char **argv) {
	char buf[101];
	while(scanf("%100s", buf) == 1) {
        linenr++;
		std::string command(buf);

		if(command == "gregorian") {
			new_date<Gregorian>();
		} else if(command == "gregoriancopy") {
			new_date_copy<Gregorian>();
		} else if(command == "copy") {
			const size_t from = read_idx_or_die();
			const size_t to = read_idx_or_die();
			try {
				(*dates[to]) = *const_cast<const Date*>(dates[from]);
				cout << "L" << linenr << ":D" << from << ",D" << to << ";" << "copy" << endl;
			} catch (std::out_of_range oor) {
				cout << "L" << linenr << ";" <<"exception_when_copying" << endl;
			}
		} else if(command == "delete") {
			const size_t idx = read_idx_or_die();
			delete dates[idx];
			dates[idx] = 0;
		} else if(command == "print") {
			const size_t idx = read_idx_or_die();
			cout << "L" << linenr << ":D" << idx << ";" << *const_cast<const Date*>(dates[idx]) << endl;
		} else if(command == "year") {
			const size_t idx = read_idx_or_die();
			cout << "L" << linenr << ":D" << idx << ";" <<const_cast<const Date*>(dates[idx])->year() << endl;
		} else if(command == "month") {
			const size_t idx = read_idx_or_die();
			cout << "L" << linenr << ":D" << idx << ";" <<const_cast<const Date*>(dates[idx])->month() << endl;
		} else if(command == "day") {
			const size_t idx = read_idx_or_die();
			cout << "L" << linenr << ":D" << idx << ";" <<const_cast<const Date*>(dates[idx])->day() << endl;
		} else if(command == "week_day") {
			const size_t idx = read_idx_or_die();
			cout << "L" << linenr << ":D" << idx << ";" <<const_cast<const Date*>(dates[idx])->week_day() << endl;
		} else if(command == "days_per_week") {
			const size_t idx = read_idx_or_die();
			cout << "L" << linenr << ":D" << idx << ";" <<const_cast<const Date*>(dates[idx])->days_per_week() << endl;
		} else if(command == "days_this_month") {
			const size_t idx = read_idx_or_die();
			cout << "L" << linenr << ":D" << idx << ";" <<const_cast<const Date*>(dates[idx])->days_this_month() << endl;
		} else if(command == "months_per_year") {
			const size_t idx = read_idx_or_die();
			cout << "L" << linenr << ":D" << idx << ";" <<const_cast<const Date*>(dates[idx])->months_per_year() << endl;
		} else if(command == "week_day_name") {
			const size_t idx = read_idx_or_die();
			cout << "L" << linenr << ":D" << idx << ";" <<const_cast<const Date*>(dates[idx])->week_day_name() << endl;
		} else if(command == "month_name") {
			const size_t idx = read_idx_or_die();
			cout << "L" << linenr << ":D" << idx << ";" <<const_cast<const Date*>(dates[idx])->month_name() << endl;
		} else if(command == "d++") {
			const size_t idx = read_idx_or_die();
			try {
				++(*dates[idx]);
				cout << "L" << linenr<< ":D" << idx << ";" << (*dates[idx]) << endl;
			} catch (std::out_of_range oor) {
				cout << "L" << linenr << ":D" << idx << ";" <<"exception_in_++" << endl;
			}
		} else if(command == "d--") {
			const size_t idx = read_idx_or_die();
			try {
				--(*dates[idx]);
				cout << "L" << linenr<< ":D" << idx << ";" << (*dates[idx]) << endl;
			} catch (std::out_of_range oor) {
				cout << "L" << linenr << ":D" << idx << ";" <<"exception_in_--" << endl;
			}
		} else if(command == "d+=") {
			const size_t idx = read_idx_or_die();
			const int val = read_int_or_die();
			try {
				(*dates[idx]) += val;
				cout << "L" << linenr << ":D" << idx << ";" << (*dates[idx]) << endl;
			} catch (std::out_of_range oor) {
				cout << "L" << linenr << ":D" << idx << ";" <<"exception_in_+=" << endl;
			}
		} else if(command == "d-=") {
			const size_t idx = read_idx_or_die();
			const int val = read_int_or_die();
			try {
				(*dates[idx]) -= val;
				cout << "L" << linenr << ":D" << idx << ";" << (*dates[idx]) << endl;
			} catch (std::out_of_range oor) {
				cout << "L" << linenr << ":D" << idx << ";" <<"exception_in_-=" << endl;
			}
		} else if(command == "chained") {
			const size_t idx = read_idx_or_die();
			try {
				/*
				 * Subtracts two days. The reason for doing it this very odd way
				 * is to test that prefix and postfix increment/decrement seem to
				 * work properly when chained.
				 *
				 * I know it's ugly, but adding parenthesis or spaces doesn't really
				 * help all that much. Sorry.
				 */
				----------++++++++--++--++--++(*dates[idx]);
				cout << "L" << linenr<< ":D" << idx << ";" << (*dates[idx]) << endl;
			} catch (std::out_of_range oor) {
				cout << "L" << linenr << ":D" << idx << ";" <<"exception_in_++--++" << endl;
			}
		} else if(command == "add_year") {
			const size_t idx = read_idx_or_die();
			int val;
			try {
				if(scanf("%d", &val) == 1) {
					dates[idx]->add_year(val);
				} else {
					dates[idx]->add_year();
				}
				cout << "L" << linenr << ":D" << idx << ";" << (*dates[idx]) << endl;
			} catch (std::out_of_range oor) {
				cout << "L" << linenr << ":D" << idx << ";" <<"exception_in_add_year" << endl;
			}
		} else if(command == "add_month") {
			const size_t idx = read_idx_or_die();
			int val;
			try {
				if(scanf("%d", &val) == 1) {
					dates[idx]->add_month(val);
				} else {
					dates[idx]->add_month();
				}
				cout << "L" << linenr << ":D" << idx << ";" << (*dates[idx]) << endl;
			} catch (std::out_of_range oor) {
				cout << "L" << linenr << ":D" << idx << ";" <<"exception_in_add_month" << endl;
			}
		} else if(command == "d==") {
			const size_t lhs = read_idx_or_die();
			const size_t rhs = read_idx_or_die();
			cout << "L" << linenr << ":D" << lhs << ",D" << rhs << ";" <<((*const_cast<const Date*>(dates[lhs])) == (*const_cast<const Date*>(dates[rhs]))) << endl;
		} else if(command == "d!=") {
			const size_t lhs = read_idx_or_die();
			const size_t rhs = read_idx_or_die();
			cout << "L" << linenr << ":D" << lhs << ",D" << rhs << ";" <<((*const_cast<const Date*>(dates[lhs])) != (*const_cast<const Date*>(dates[rhs]))) << endl;
		} else if(command == "d<") {
			const size_t lhs = read_idx_or_die();
			const size_t rhs = read_idx_or_die();
			cout << "L" << linenr << ":D" << lhs << ",D" << rhs << ";" <<((*const_cast<const Date*>(dates[lhs])) < (*const_cast<const Date*>(dates[rhs]))) << endl;
		} else if(command == "d<=") {
			const size_t lhs = read_idx_or_die();
			const size_t rhs = read_idx_or_die();
			cout << "L" << linenr << ":D" << lhs << ",D" << rhs << ";" <<((*const_cast<const Date*>(dates[lhs])) <= (*const_cast<const Date*>(dates[rhs]))) << endl;
		} else if(command == "d>") {
			const size_t lhs = read_idx_or_die();
			const size_t rhs = read_idx_or_die();
			cout << "L" << linenr << ":D" << lhs << ",D" << rhs << ";" <<((*const_cast<const Date*>(dates[lhs])) > (*const_cast<const Date*>(dates[rhs]))) << endl;
		} else if(command == "d>=") {
			const size_t lhs = read_idx_or_die();
			const size_t rhs = read_idx_or_die();
			cout << "L" << linenr << ":D" << lhs << ",D" << rhs << ";" <<((*const_cast<const Date*>(dates[lhs])) >= (*const_cast<const Date*>(dates[rhs]))) << endl;
		} else if(command == "d-") {
			const size_t lhs = read_idx_or_die();
			const size_t rhs = read_idx_or_die();
			cout << "L" << linenr << ":D" << lhs << ",D" << rhs << ";" <<((*const_cast<const Date*>(dates[lhs])) - (*const_cast<const Date*>(dates[rhs]))) << endl;
		} else if(command == "mod_julian_day") {
			const size_t lhs = read_idx_or_die();
			cout << "L" << linenr << ":D" << lhs << ";" <<const_cast<const Date*>(dates[lhs])->mod_julian_day() << endl;
		} else if(command == "set_k_time") {
			time_t time = 0;
			/* No standardized way to read time_t with scanf */
			if(!(std::cin >> time))
				assert(!"Can't read time");
			set_k_time(time);
		} else {
			assert(!"Unknown command");
		}
	}

	return 0;
}
