find . -name "*.cpp" -print0 | grep -v moc | xargs -0 git add
find . -name "*.cc" -exec git add {} \;
find . -name "*.pro" -exec git add {} \;
find . -name "*.h" -exec git add {} \;
find . -name "*.sh" -exec git add {} \;
find . -name "*.ui" -exec git add {} \;

git commit
