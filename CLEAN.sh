find -name '*.o' \
  -o -name 'moc_*.h' \
  -o -name '*.so*'  \
  -o -name '*.backtrace*' \
         -exec rm '{}' \;
rm tests/tests
rm app/app
rm tests/tmp.ini
