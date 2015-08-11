#include <QCoreApplication>
#include <QDebug>

#define _BSD_SOURCE 1

#include <fcntl.h>
#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <sys/stat.h>
#include <syslog.h>
#include <termios.h>
#include <unistd.h>


#include "./gps-indigo.h"

#ifdef OLD_LOGGER
    #include "./log-indigo.h"
    static Logger *logger = LoggerFactory::getLogger("gsm-poller");
#endif
#define DEFAULT_SPEED	B115200
#define SERIAL_PORT	"/dev/gsmtty3"

int exit_pipe[2];
FILE *output_file;

#define GSM_TALK_BUF_SIZE 1024
char buf[GSM_TALK_BUF_SIZE];

static sig_atomic_t exit_flag = 0;

void bye(int signum)
{
    (void) signum;
    exit_flag = 1;
}

static bool verbose = false;
static const char *device_name = SERIAL_PORT;
#define ERROR_STRING_SIZE 255
static char error_string[255];

struct option options[] = {
    {"device", 1, NULL, static_cast<int>('d')},
    {"verbose", 0, NULL, static_cast<int>('v')},
};

static void print_usage() {
    qDebug() << "./gsm-poller -v\n";
}

static void parse_options(int argc, char **argv) {
    int opt = 0;
    while ((opt = getopt_long(argc, argv, "d:v", options, NULL)) != -1) {
        switch (opt) {
        case 'd':
            device_name = optarg;
            break;
        case 'v':
            verbose = true;
#ifdef OLD_LOGGER
            LoggerFactory::setVerbosityForApp(verbose);
#endif
            break;
        case '?':
#ifdef OLD_LOGGER
            logger_error("unknown option");
#else
            print_usage();
#endif
            exit(-1);
            break;
        default:
            break;
        }
    }
}

void output(const char *buf) {
    time_t my_time;
    char output_buffer[300];
    char time_buffer[300];

    if (strlen(buf) <= 2)
        return;

    if (strstr(buf, "AT+"))
        return;

    if (strstr(buf, "OK"))
        return;

    time(&my_time);
    ctime_r(&my_time, time_buffer);
    time_buffer[strlen(time_buffer) - 1] = '\0';
    snprintf(output_buffer, 300, "%s %s", time_buffer, buf);
    fputs(output_buffer, output_file);
}

bool drain_data_fd(int fd)
{
    fd_set read_fds;
    struct timeval timeout;
    char dummy[255];
    unsigned int i = 0;
    bool result = false;

    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);

    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    while (select(fd + 1, &read_fds, NULL, NULL, &timeout) != 0) { /* until first timeout */
        /* while possible, collect read bytes in an array */
        if (i < sizeof(dummy)) {
            read(fd, &dummy[i], 1);
            /* whenever \n is encountered, output it to screen */
            if (dummy[i] == '\n') {
                output(dummy);
                memset(dummy, 0, sizeof(dummy));
                i = 0;
            } else {
                i++;
            }
        } else {
            /* upon buffer fill, clean it */
            memset(dummy, 0, sizeof(dummy));
            read(fd, &dummy[0], 1);
            i = 0;
        }
        result = true;

        FD_ZERO(&read_fds);
        FD_SET(fd, &read_fds);

        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
    }

    return result;
}



void talk(int fd, const char *cmd) {
    int bytes_written = 0;

    bytes_written = write(fd, cmd, strlen(cmd));
    if (bytes_written == -1) {
        qCritical() << "serial port write error";
        return;;
    } else if (bytes_written == 0) {
        qDebug() << "zero bytes written to fd\n";
        exit(-500);
    }

    drain_data_fd(fd);

}

int main(int argc, char **argv)
{
    int fd;
    int err = 0;

    Record currentPosition;
    GPS *gps = new GPS_real();

    struct termios ts;
#ifdef OLD_LOGGER
    atexit(loggers_cleanup);
#endif
    parse_options(argc, argv);

    signal(SIGHUP, SIG_IGN);
    signal(SIGTERM, bye);

    output_file = fopen("/var/log/gsm.log", "a");
    if (!output_file) {
        snprintf(error_string, ERROR_STRING_SIZE, "output_file\n");
        goto out;
    }

    /* open the serial port connected to the modem */
    fd = open(device_name, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd == -1) {
        snprintf(error_string, ERROR_STRING_SIZE, "cannot open serial port: %s\n", device_name);
        goto out;
    }
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) & ~O_NONBLOCK);

    if (!isatty(fd)) {
        snprintf(error_string, ERROR_STRING_SIZE, "fatal: descriptor opened is not a serial device\n");
        goto out;
    }

    err = tcgetattr(fd, &ts);
    if (err < 0) {
        snprintf(error_string, ERROR_STRING_SIZE, "tcgetattr");
        goto out;
    }

    cfmakeraw(&ts);
    ts.c_iflag = ts.c_iflag & ~CRTSCTS & ~IXON;
    ts.c_lflag = ts.c_lflag & ~ECHO;

    err = cfsetspeed(&ts, DEFAULT_SPEED);
    if (err < 0) {
        snprintf(error_string, ERROR_STRING_SIZE, "fatal: coudln't set 115200 baud rate");
        goto out;
    }

    err = tcsetattr(fd, TCSAFLUSH, &ts);
    if (err < 0) {
        snprintf(error_string, ERROR_STRING_SIZE, "fatal: coudln't tcsetattr TCSAFLUSH");
        goto out;
    }

    while (!exit_flag) {
        int dummy = 0, charge_percent = 0, voltage = 0;
        (void) (dummy + charge_percent + voltage);

        talk(fd, "AT+CBC\r\n");
        sleep(1);
        talk(fd, "AT+CSQ\r\n");
        sleep(1);
        talk(fd, "AT+CGATT?\r\n");
        sleep(1);

        gps->readRecord(&currentPosition);
        if (currentPosition.isValid) {
            char buf[255];
            snprintf(buf, 255, "lon lat %lf %lf\n", currentPosition.fix.latitude, currentPosition.fix.longitude);
            output(buf);
        } else {
            output("no gps coordinates\n");
        }
        sleep(60);
    }

    /* and wait for ever to keep the line discipline enabled */
    //daemon(0, 0);

    fclose(output_file);

    close(fd);
    if (gps)
        delete gps;

    return 0;

out:
    if (gps)
        delete gps;

    qCritical() << "gsm poller failed, you're loser with next error:\n   " << error_string;


    return 1;
}
