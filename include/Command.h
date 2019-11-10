#pragma once

#include <list>
#include <string>

class Command
{
public:
    static const std::string DIRECTORY_BUILD;
    static const std::string DIRECTORY_INSTALL;

    static std::string getConfig();

    static std::string getBuild();

    static std::string getInstall();

    static std::string getPack();
};