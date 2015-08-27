find -name '*.o' \
  -o -name 'moc_*.h' \
  -o -name '*.so*'  \
  -o -name '*.backtrace*' \
         -exec rm '{}' \;
rm tests/tests
rm app/app
rm tests/tmp.ini
rm -r modules/protos/lib
rm -r modules/protos/include
rm -r modules/protos/bin
