#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <format>

using std::string;

#define DECLARE_LOG_CATEGORY(name) \
	namespace Erhion::LogCategories { \
		inline constexpr const char* const name = #name; \
	}

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define LOG(severity, category, format, ...) \
    Erhion::Utils::Log(Erhion::Utils::Severity::severity, Erhion::LogCategories::category, format, __FILE__, TOSTRING(__LINE__), ##__VA_ARGS__)

namespace Erhion::Utils {
    enum Severity {
        Done,
        Info,
        Warning,
        Error,
        Critical
    };

    template<typename... Args>
	inline void Log(Severity severity, const char* const category, const char* const format, string filePath, string lineNumber, Args... args) {
        string severityName = "UNKNOWN";
        string ansiColor = "0";
        std::ostream* out = &std::cout;

        switch (severity) {
            case Done:
                severityName = "DONE";
                ansiColor = "94";
                break;
            case Info:
                severityName = "INFO";
                ansiColor = "38";
                break;
            case Warning:
                severityName = "WARN";
                ansiColor = "93";
                break;
            case Error:
                severityName = "FAIL";
                ansiColor = "31";
                out = &std::cerr;
                break;
            case Critical:
                severityName = "CRIT";
                ansiColor = "91";
                out = &std::cerr;
                break;
        }

        size_t pos = filePath.find_last_of("\\/");
        std::string file = pos == std::string::npos ? filePath : filePath.substr(pos + 1);
        std::string message = std::vformat(format, std::make_format_args(args...));

        *out << "\033[1;" << ansiColor << "m[" + severityName + "|" + category + "] \033[0;" << ansiColor << "m"
             << message << "\033[0m" << " (" << file << ":" << lineNumber << ")" << std::endl;

        if (severity == Severity::Critical)
			std::abort();
    };
}