#include <gtest/gtest.h>

#include <QCoreApplication>

void enableSignalHandling();
void print_stacktrace(FILE *out = stderr, unsigned int max_frames = 63);

int main(int argc, char **argv) {
    enableSignalHandling();
    QCoreApplication app(argc, argv);

    int result = 0;
    try {
        ::testing::InitGoogleTest(&argc, argv);
        result = RUN_ALL_TESTS();
    } catch (std::exception &e) {
        std::cerr << e.what();
    }

    return result;
}
