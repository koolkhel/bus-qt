#include <gtest/gtest.h>

#include <QApplication>
#include <QCoreApplication>

void enableSignalHandling();
void print_stacktrace(FILE *out = stderr, unsigned int max_frames = 63);

void initPaths() {
    //printf("hello, world %s\n", qPrintable(qApp->applicationDirPath()));
    QString path = qApp->applicationDirPath();

    qApp->addLibraryPath("/usr/local/lib");
    qApp->addLibraryPath(path + "/../src/nzmqt/bin");
    qApp->addLibraryPath(path + "/../modules/bin");
    qApp->addLibraryPath(path + "/../modules/protos/bin");

    //printf("%s\n", qPrintable(qApp->libraryPaths().join(",")));
}

int main(int argc, char **argv) {
    enableSignalHandling();
    //QCoreApplication app(argc, argv);
    QApplication app(argc, argv);
    initPaths();

    int result = 0;
    try {
        ::testing::InitGoogleTest(&argc, argv);
        result = RUN_ALL_TESTS();
    } catch (std::exception &e) {
        std::cerr << e.what();
    }

    return result;
}
