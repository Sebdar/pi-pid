# PiPid quick start-up script

rm -rf ./build
mkdir build
cd build

cmake . \
    -DUNIT_TEST=ON \
    -DBUILD_TOOLS=ON \
    ..


