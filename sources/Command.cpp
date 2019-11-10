#include "Command.h"
#include "Settings.h"

const std::string Command::DIRECTORY_BUILD = ".build";

const std::string Command::DIRECTORY_INSTALL = ".install";

Command::ArgList Command::getConfig()
{
    return {"-H.",
            "-B" + DIRECTORY_BUILD,
            +"-DCMAKE_INSTALL_PREFIX=" + DIRECTORY_INSTALL,
            +"-DCMAKE_BUILD_TYPE=" + Settings::buildConfig};
}

Command::ArgList Command::getBuild()
{
    return {"--build", DIRECTORY_BUILD};
}

Command::ArgList Command::getInstall()
{
    return {"--build", DIRECTORY_BUILD,
            "--target", "install"};
}

Command::ArgList Command::getPack()
{
    return {"--build", DIRECTORY_BUILD,
            "--target", "package"};
}
