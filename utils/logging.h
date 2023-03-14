#ifndef ERHION_ENGINE_LOGGING_H
#define ERHION_ENGINE_LOGGING_H

#include <iostream>
#include <string>

using std::string;

namespace Erhion::Utils {
    enum Severity {
        DONE,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    inline void Log(Severity severity, string tag, string message) {
        string severityName = "UNKNOWN";
        string ansiColor = "0";

        switch (severity) {
            case DONE:
                severityName = "DONE";
                ansiColor = "94";
                break;
            case INFO:
                severityName = "INFO";
                ansiColor = "38";
                break;
            case WARNING:
                severityName = "WARN";
                ansiColor = "93";
                break;
            case ERROR:
                severityName = "FAIL";
                ansiColor = "31";
                break;
            case CRITICAL:
                severityName = "CRIT";
                ansiColor = "91";
                break;
        }

        std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
        std::cout << "\033[1;" << ansiColor << "m[" + severityName + "|" + tag + "] \033[0;" << ansiColor << "m";

        if (!message.ends_with(".") && !message.ends_with("!") && !message.ends_with("?"))
            message += ".";

        std::cout << message + "\033[0m" << std::endl;

        if (severity == Severity::CRITICAL)
            exit(EXIT_FAILURE);
    };
}

#endif //ERHION_ENGINE_LOGGING_H
