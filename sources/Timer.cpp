#include "Timer.h"

void Timer::create(std::unique_ptr<ThreadData> &data)
{
    using namespace std::chrono;

    if (Settings::timeout <= 0) {
        return;
    }

    std::this_thread::sleep_for(milliseconds{Settings::timeout});

    while (data->isTerminated) {
        static const int DATA_NULL_TIMEOUT = 1000;

        std::this_thread::sleep_for(milliseconds{DATA_NULL_TIMEOUT});
    }

    data->isTerminated = true;

    try {
        data->currentProcess.terminate();
    } catch (std::exception &exception) {
        BOOST_LOG_TRIVIAL(error) << exception.what();
    }
}
