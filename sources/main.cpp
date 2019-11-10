#include <async++.h>
#include <memory>
#include <boost/process.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/iostreams/stream.hpp>

#include "LogSetup.h"
#include "Settings.h"
#include "Timer.h"
#include "Utils.h"
#include "Command.h"

void startProcess(const Command::ArgList &commandArgs, std::unique_ptr<ThreadData> &data)
{
    using namespace boost::process;

    if (data && data->isTerminated) {
        return;
    }

    // Start
    BOOST_LOG_TRIVIAL(info) << "Command: cmake";
    for (const auto &arg : commandArgs) {
        BOOST_LOG_TRIVIAL(info) << "                " << arg;
    }
    BOOST_LOG_TRIVIAL(info) << "\n";

    ipstream stream;

    child child{search_path("cmake"),
                args(commandArgs),
                std_out > stream};

    // Update data
    if (!data) {
        data = std::make_unique<ThreadData>(ThreadData{false, std::move(child)});
    } else {
        data->currentProcess = std::move(child);
    }
    BOOST_LOG_TRIVIAL(debug) << "Data updated";

    // Get output
    for (std::string line; data->currentProcess.running() && std::getline(stream, line);) {
        BOOST_LOG_TRIVIAL(info) << line;
    }

    // Wait until exit
    data->currentProcess.wait();

    auto exitCode = data->currentProcess.exit_code();
    BOOST_LOG_TRIVIAL(info) << "Exit code: " << exitCode;

    if (exitCode != 0) {
        BOOST_LOG_TRIVIAL(error) << "Non zero exit code. Exiting...";
        data->isTerminated = true;
    }
}

int main(int argc, char *argv[])
{
    if (auto returnCode = programArguments(argc, argv); returnCode != 0) {
        return returnCode;
    }

    LogSetup::init();

    std::unique_ptr<ThreadData> data{nullptr};

    auto timer = async::spawn(boost::bind(&Timer::create, std::ref(data)));

    auto build = async::spawn(
        boost::bind(startProcess, Command::getConfig(), std::ref(data))
    ).then(
        boost::bind(startProcess, Command::getBuild(), std::ref(data))
    );

    if (Settings::isInstallEnabled) {
        build = build.then(
            boost::bind(startProcess, Command::getInstall(), std::ref(data))
        );
    }
    if (Settings::isPackEnabled) {
        build = build.then(
            boost::bind(startProcess, Command::getPack(), std::ref(data))
        );
    }
    build = build.then([&data]() {
        data->isTerminated = true;
    });

    build.wait();
    timer.wait();
}