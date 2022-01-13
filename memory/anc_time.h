#ifndef __ANC_TIME_H__
#define __ANC_TIME_H__
#include "anc_type.h"

unsigned long long AncGetTime(void);
void AncGetCurrentTimeStr(char *p_ctime);
void AncGetCurrentTimestamp(unsigned long long *p_time);
int AncStrfTime(char *p_dst, size_t dst_len);
#endif
