#ifndef _WESTERN_DATE_
#define _WESTERN_DATE_

class WesternDate
{
protected:
	static const int days_in_a_month[12];

	WesternDate() : Date() { this->init(); }

	int days_this_month();
	void init() { populate(); }

	void populate()
	{ 
		populate_week_days(); 
		populate_months(); 
	}

	void populate_week_days() {
		WEEK_DAYS = new std::string[7];
		WEEK_DAYS[0] = "sunday";
		WEEK_DAYS[1] = "monday";
		WEEK_DAYS[2] = "tuesday";
		WEEK_DAYS[3] = "wednesday";
		WEEK_DAYS[4] = "thursday";
		WEEK_DAYS[5] = "friday";
		WEEK_DAYS[6] = "saturday";
	}

	void populate_months() 
	{
		MONTHS = new std::string[12];
		MONTHS[0] = "january";
		MONTHS[1] = "february";
		MONTHS[2] = "march";
		MONTHS[3] = "april";
		MONTHS[4] = "may";
		MONTHS[5] = "june";
		MONTHS[6] = "july";
		MONTHS[7] = "august";
		MONTHS[8] = "september";
		MONTHS[9] = "october";
		MONTHS[10] = "november";
		MONTHS[11] = "december";	
	}

	// make static? same with week_days? More efficient?
	//months_name = new std::string[12] = 
	//	{"january", "february", "march", "april", "may", "june", 
	//		"july", "august", "september", "october", "november", "december"
	//	}

	virtual ~WesternDate() { delete [] WEEK_DAYS; delete [] MONTHS; }
};

const int days_in_a_month[12] =
	{
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};

#endif