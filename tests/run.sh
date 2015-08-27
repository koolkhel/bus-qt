export LD_LIBRARY_PATH=../src/nzmqt/bin:../src/:../modules/protos/bin:../modules/bin:$LD_LIBRARY_PATH
ulimit -c unlimited
#export LD_DEBUG=libs
./tests --gtest_filter='disptest.*'
