#pragma once

#include <list>
#include <string>

class Command
{
public:
    using ArgList = std::list<std::string>;

    static const std::string DIRECTORY_BUILD;
    static const std::string DIRECTORY_INSTALL;

    static ArgList getConfig();

    static ArgList getBuild();

    static ArgList getInstall();

    static ArgList getPack();
};