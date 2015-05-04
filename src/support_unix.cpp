#define GNU_SOURCE

#include <stdlib.h>
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

#include <dlfcn.h>
#include <execinfo.h>
#include <cxxabi.h>

#include <QString>
#include <QDateTime>
#include <QCoreApplication>

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

    Dl_info dlinfo;
    const char *symname;
    char *demangled;
    int status = 0;

    // iterate over the returned symbol lines. skip the first, it is the
    // address of this function.
    for (int i = 2; i < addrlen; i++)
    {
        if(!dladdr(addrlist[i], &dlinfo))
            continue;

        symname = dlinfo.dli_sname;

        demangled = abi::__cxa_demangle(symname, NULL, 0, &status);
        if(status == 0 && demangled)
            symname = demangled;

        if (!strstr(dlinfo.dli_fname, "libgtest")) {
            fprintf(out, "lib: %s, fn: %s\n", dlinfo.dli_fname, symname);
            char buf[255];
            memset(buf, 0, 255);
            snprintf(buf, 255, "addr2line -C -e \"%s\" 0x%lx | grep -v ??", dlinfo.dli_fname, (char *) addrlist[i] - (char *) dlinfo.dli_fbase);
            FILE *row = popen(buf, "r");
            while (!feof(row)) {
                char buf2[255];
                memset(buf2, 0, 255);
                fgets(buf2, 255, row);
                fprintf(out, "%s", buf2);
            }
            fclose(row);
        }

        if (demangled)
            free(demangled);
    }
}

static void kadu_signal_handler(int signal)
{
        fprintf(stderr, "%d\n", signal);

        char str[255];
        //  | cut -d ' ' -f 1
        snprintf(str, 255, "pmap %d | grep indigo | head -n 1 | cut -d ' ' -f 1", getpid());
        FILE *pmap = popen(str, "r");
        do {
            fgets(str, 255, pmap);
            fputs(str, stderr);
        } while (!feof(pmap));
        fclose(pmap);

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
