#include "anc_log.h"

#include <stdio.h>

#include "anc_memory.h"
#include "anc_memory_wrapper.h"
#include "anc_time.h"
#include "anc_type.h"
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#define LOG_TAG "anc_ta"

#define TIME_STR_LEN 256
#define LOG_MAX_BUFLEN 1024
#define LOG_LEN_MAX_TRIM 142

void AncLogSetMask(uint8_t pri_flags) { ANC_UNUSED(pri_flags); }

#define COLOR_NONE "\033[0m"
#define COLOR_WHITE "\033[38;5;231m"
#define COLOR_BLUE "\033[38;5;75m"
#define COLOR_GREEN "\033[38;5;40m"
#define COLOR_YELLOW "\033[38;5;166m"
#define COLOR_RED "\033[38;5;196m"
static char gp_curr_time[256];

void AncLog(uint8_t level, const char *tag, const char *format, ...) {
  char buffer[LOG_MAX_BUFLEN];

  AncMemset(buffer, 0, LOG_MAX_BUFLEN);

  if (format == NULL) {
    return;
  }

  va_list vl;
  va_start(vl, format);
  vsnprintf(buffer, LOG_MAX_BUFLEN, format, vl);
  va_end(vl);
  AncGetCurrentTimeStr(gp_curr_time);
  switch (level) {
  case ANC_LOG_INFO:
    printf(COLOR_GREEN "%s %2d %2d %s[I] %s\n", gp_curr_time, (int)getpid(),
           (int)gettid(), tag, buffer);
    break;
  case ANC_LOG_DEBUG:
    printf(COLOR_BLUE "%s %2d %2d %s[D] %s\n", gp_curr_time, (int)getpid(),
           (int)gettid(), tag, buffer);
    break;
  case ANC_LOG_WARNING:
    printf(COLOR_YELLOW "%s %2d %2d %s[W] %s\n" COLOR_NONE, gp_curr_time,
           (int)getpid(), (int)gettid(), tag, buffer);
    break;
  case ANC_LOG_ERROR:
    printf(COLOR_RED "%s %2d %2d %s[E] %s\n" COLOR_NONE, gp_curr_time,
           (int)getpid(), (int)gettid(), tag, buffer);
    break;
  default:
    break;
  }
}