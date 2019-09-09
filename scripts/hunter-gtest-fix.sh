#! /bin/sh

# Cause: https://github.com/hunter-packages/googletest/issues/27
set -ex

FILES=$(find "${HOME}/.hunter/_Base/" -wholename "*/GTest/hunter.cmake")

for f in $FILES
do
  sed -i '/if(HUNTER_GTest_VERSION/i \
hunter_add_version( \
    PACKAGE_NAME \
    GTest \
    VERSION \
    "1.8.1" \
    URL \
    "https://github.com/google/googletest/archive/release-1.8.1.tar.gz" \
    SHA1 \
    152b849610d91a9dfa1401293f43230c2e0c33f8 \
) \
' "${f}"
done

FILES=$(find "${HOME}/.hunter/_Base/" -wholename "*/configs/default.cmake")

for f in $FILES
do
  sed -i -E 's/hunter_default_version\(GTest VERSION 1\.8\.0.+\)/hunter_default_version(GTest VERSION 1.8.1)/' "${f}"
done