export LD_LIBRARY_PATH=/home/yury/work/QTFinal/src/nzmqt/bin:/home/yury/work/QTFinal/src/:../modules/protos/bin:../modules/bin:$LD_LIBRARY_PATH
ulimit -c unlimited
#export LD_DEBUG=libs
./tests --gtest_filter='BBOX.*'
