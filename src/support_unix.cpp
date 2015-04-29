#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>
#ifndef Q_OS_WIN32
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#endif // !Q_OS_WIN32

#include <QtCore/QCoreApplication>
#include <QtCore/QDateTime>

#include <execinfo.h>
#include <cxxabi.h>

/** Print a demangled stack backtrace of the caller function to FILE* out. */
static inline void print_stacktrace(FILE *out = stderr, unsigned int max_frames = 63) {
    fprintf(out, "stack trace:\n");

    // storage array for stack trace address data
    void* addrlist[max_frames+1];

    // retrieve current stack addresses
    int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));

    if (addrlen == 0) {
        fprintf(out, "  <empty, possibly corrupt>\n");
        return;
    }

    // resolve addresses into strings containing "filename(function+address)",
    // this array must be free()-ed
    char** symbollist = backtrace_symbols(addrlist, addrlen);

    // allocate string which will be filled with the demangled function name
    size_t funcnamesize = 256;
    char* funcname = (char*)malloc(funcnamesize);

    // iterate over the returned symbol lines. skip the first, it is the
    // address of this function.
    for (int i = 1; i < addrlen; i++)
    {
        char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

        // find parentheses and +address offset surrounding the mangled name:
        // ./module(function+0x15c) [0x8048a6d]
        for (char *p = symbollist[i]; *p; ++p)
        {
            if (*p == '(')
                begin_name = p;
            else if (*p == '+')
                begin_offset = p;
            else if (*p == ')' && begin_offset) {
                end_offset = p;
                break;
            }
        }

        if (begin_name && begin_offset && end_offset
            && begin_name < begin_offset)
        {
            *begin_name++ = '\0';
            *begin_offset++ = '\0';
            *end_offset = '\0';

            // mangled name is now in [begin_name, begin_offset) and caller
            // offset in [begin_offset, end_offset). now apply
            // __cxa_demangle():

            int status;
            char* ret = abi::__cxa_demangle(begin_name,
                                            funcname, &funcnamesize, &status);
            if (status == 0) {
                funcname = ret; // use possibly realloc()-ed string
                fprintf(out, "  %s : %s+%s\n",
                        symbollist[i], funcname, begin_offset);
            }
            else {
                // demangling failed. Output function name as a C function with
                // no arguments.
                fprintf(out, "  %s : %s()+%s\n",
                        symbollist[i], begin_name, begin_offset);
            }
        }
        else
        {
            // couldn't parse the line? print the whole line.
            fprintf(out, "  %s\n", symbollist[i]);
        }
    }

    free(funcname);
    free(symbollist);
}

static void printBacktrace(const QString &header)
{
        if (header.isEmpty())
                fprintf(stderr, "\nbacktrace:\n");
        else
                fprintf(stderr, "\nbacktrace: ('%s')\n", qPrintable(header));
        void *bt_array[100];
        char **bt_strings;
        int num_entries;
        if ((num_entries = backtrace(bt_array, 100)) < 0) {
                fprintf(stderr, "could not generate backtrace\n");
                return;
        }
        if ((bt_strings = backtrace_symbols(bt_array, num_entries)) == NULL) {
                fprintf(stderr, "could not get symbol names for backtrace\n");
                return;
        }
        fprintf(stderr, "======= BEGIN OF BACKTRACE =====\n");
        for (int i = 0; i < num_entries; ++i)
                fprintf(stderr, "[%d] %s\n", i, bt_strings[i]);
        fprintf(stderr, "======= END OF BACKTRACE  ======\n");
        free(bt_strings);
        fflush(stderr);
}

static void kadu_signal_handler(int signal)
{
        fprintf(stderr, "%d\n", signal);

        static int sigsegvCount = 0;

        if (sigsegvCount > 1)
        {
                fprintf(stderr, "sigsegv recursion: %d\n", sigsegvCount);
                abort();
        }

        if (signal == SIGSEGV)
        {
                ++sigsegvCount;
                fprintf(stderr, "Indigo crashed :(\n");


                QString backtraceFileName = QLatin1String("indigo.backtrace.") + QDateTime::currentDateTime().toString("yyyy.MM.dd.hh.mm.ss");
                void *backtraceArray[100];
                char **backtraceStrings;
                int numEntries;


                fprintf(stderr, "\n======= BEGIN OF BACKTRACE =====\n");
                print_stacktrace(stderr, 100);
                fprintf(stderr, "======= END OF BACKTRACE  ======\n");
                fflush(stderr);

                FILE *backtraceFile = fopen(qPrintable(backtraceFileName), "w");
                if (backtraceFile)
                {
                        fprintf(backtraceFile, "======= BEGIN OF BACKTRACE =====\n");
                        print_stacktrace(backtraceFile, 100);
                        fprintf(backtraceFile, "======= END OF BACKTRACE  ======\n");

                        fprintf(backtraceFile, "Qt compile time version: %s\nQt runtime version: %s\n",
                                        QT_VERSION_STR, qVersion());
#ifdef __GNUC__
                        fprintf(backtraceFile, "GCC version: %d.%d.%d\n",
                                        __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif // __GNUC__
                        fprintf(backtraceFile, "EOF\n");

                        fclose(backtraceFile);
                }

                free(backtraceStrings);

                abort();
        }
        else if (signal == SIGINT || signal == SIGTERM)
                QCoreApplication::quit();
}

void enableSignalHandling()
{
        char *d = getenv("SIGNAL_HANDLING");
        bool signalHandlingEnabled = d ? (atoi(d) != 0) : true;

        if (signalHandlingEnabled)
        {
                signal(SIGSEGV, kadu_signal_handler);
                signal(SIGINT, kadu_signal_handler);
                signal(SIGTERM, kadu_signal_handler);
                signal(SIGUSR1, kadu_signal_handler);
                signal(SIGPIPE, SIG_IGN);
        }
}
