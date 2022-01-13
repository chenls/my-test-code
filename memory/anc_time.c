#include "anc_time.h"

#include <stdio.h>
#include <sys/time.h>

#include "anc_log.h"
#include "anc_type.h"
// #include "anc_utils.h"

static long long g_diff_time = 0;

unsigned long long AncGetTime() {
    struct timeval tv;
    unsigned long long ms;
    gettimeofday(&tv, NULL);
    ms = (unsigned long long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    return ms;
}

void AncSetCATime(long long ms) {
    g_diff_time = (long long)((unsigned long long)ms - AncGetTime());
}

void AncGetCurrentTimeStr(char *p_ctime) {
    int hh = 0;
    int mi = 0;
    int ss = 0;
    unsigned long long sec;
    unsigned long long msec;

    // g_diff_time should is 0
    msec = AncGetTime();
    sec = msec / 1000;
    msec = msec % 1000;
    hh = sec / (60 * 60) % 24;
    mi = (sec / 60) % 60;
    ss = sec % 60;

    snprintf(p_ctime, 256, "%02d:%02d:%02d.%03llu", hh, mi, ss, msec);
}

void AncGetCurrentTimestamp(unsigned long long *p_time) {
    *p_time = AncGetTime();
}
