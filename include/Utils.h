#pragma once

#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <random>

struct ThreadData
{
    ThreadData() = delete;

    bool isTerminated = false;
    boost::process::child currentProcess;
};

int programArguments(int argc, char *argv[]);

