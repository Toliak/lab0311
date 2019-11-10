#pragma once

#include <string>

struct Settings
{
    static std::string logLevel;
    static int timeout;
    static bool isInstallEnabled;
    static bool isPackEnabled;
    static std::string buildConfig;
};