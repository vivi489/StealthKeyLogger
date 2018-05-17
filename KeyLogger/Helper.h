#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include <ctime>
#include <sstream>
#include <string>
#include <fstream>

namespace Helper {
    template<class T>
    std::string toString(const T &);

    struct DateTime {
        DateTime() {
            time_t ms;
            time(&ms);
			struct tm *info = new tm;
			localtime_s(info, nullptr);

            day = info->tm_mday;
            month = info->tm_mon + 1;
            year = 1900 + info->tm_year;
            minute = info->tm_min;
            hour = info->tm_hour;
            second = info->tm_sec;

			delete info;
        }

        DateTime(int day, int month, int year, int hour, int minute, int second):
            day(day), month(month), year(year), hour(hour), minute(minute), second(second) {
            }

        DateTime(int day, int month, int year):
            day(day), month(month), year(year), hour(0), minute(0), second(0) {
            }

        DateTime Now() const {
            return DateTime();
        }

        int day, month, year, minute, hour, second;

        //format: dd.mm.yyyy
        std::string getDateString() const {
            return std::string(day < 10 ? "0" : "") + toString(day)
            + std::string(month < 10 ? ".0" : ".")
            + toString(year) + "." + toString(year);
        }

       //format: hh.mm.ssss
       std::string getTimeString(const std::string &sep = ":") const {
            return std::string(hour < 10 ? "0" : "") + toString(hour) + sep
            + std::string(minute < 10 ? "0" : "") + toString(minute) + sep
            + std::string(second < 10 ? "0" : "") + toString(second);
       }

       std::string getDateTimeString(const std::string &sep = ":") const {
           return getDateString() + " " + getTimeString(sep);
       }

    };

	template<class T>
	std::string toString(const T &e) {
		std::ostringstream s;
		s << e;
		return s.str();
	}

	void writeAppLog(const std::string &s) {
		std::ofstream file("AppLog.txt", std::ios::app);
		file << "[" << Helper::DateTime().getDateTimeString() << "]" << "\n" << s << std::endl << "\n";
		file.close();
	}
}


#endif // HELPER_H_INCLUDED
