#ifndef CORE_SYSTEM_H
#define CORE_SYSTEM_H

#define CPU_FREQ    (64000000)
#define SYSTIC_FREQ (1000)

#include "../common-defines.h"

void     system_setup(void);
uint64_t system_get_ticks(void);

#endif /* CORE_SYSTEM_H */
