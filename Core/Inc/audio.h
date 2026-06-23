#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>

void Audio_Init(void);
void Audio_Play(uint16_t freq, uint16_t duration_ms);
void Audio_Update(void);

#endif
