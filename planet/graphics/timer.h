//
//  timer.h
//  planet
//
//  Created by Thomas Malthouse on 5/8/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#ifndef timer_h
#define timer_h

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    uint64_t start;
    bool started;
} Timer;

Timer new_timer();
void start_timer(Timer *t);
void stop_timer(Timer *t);
uint64_t get_time(Timer *t);

#endif /* timer_h */
