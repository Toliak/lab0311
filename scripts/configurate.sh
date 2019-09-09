#! /bin/sh

set -ex

cmake -H. -B .build || 1
./scripts/hunter-gtest-fix.sh
