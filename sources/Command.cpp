#include "Command.h"
#include "Settings.h"

const std::string Command::DIRECTORY_BUILD = ".build";

const std::string Command::DIRECTORY_INSTALL = ".install";

std::string Command::getConfig()
{
    return "cmake -H."
           "-B" + DIRECTORY_BUILD
        + " -DCMAKE_INSTALL_PREFIX=" + DIRECTORY_INSTALL
        + " -DCMAKE_BUILD_TYPE=" + Settings::buildConfig;
}

std::string Command::getBuild()
{
    return "cmake --build " + DIRECTORY_BUILD;
}

std::string Command::getInstall()
{
    return "cmake --build " + DIRECTORY_BUILD + " --target install";
}

std::string Command::getPack()
{
    return "cmake --build " + DIRECTORY_BUILD + " --target package";
}
