/*
 *                             The MIT License
 *
 * Wavefront Alignments Algorithms
 * Copyright (c) 2017 by Santiago Marco-Sola  <santiagomsola@gmail.com>
 *
 * This file is part of Wavefront Alignments Algorithms.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * PROJECT: Wavefront Alignments Algorithms
 * AUTHOR(S): Santiago Marco-Sola <santiagomsola@gmail.com>
 * DESCRIPTION: Simple profile-timer for lightweight profiling
 */

#pragma once

#include "WFA/utils/commons.hpp"
#include "WFA/system/profiler_counter.hpp"

namespace wfa {

/*
 * Time (ms)
 */
#define TIME_DIFF_NS(start,end) ((end.tv_sec*1000000000 + end.tv_nsec) - (start.tv_sec*1000000000 + start.tv_nsec))
#define TIME_DIFF_S(start,end) ((end.tv_sec + end.tv_nsec/1E9) - (start.tv_sec + start.tv_nsec/1E9))

/*
 * Timers
 */
typedef struct {
  /* Timer */
  struct timespec begin_timer;     // Timer begin
  /* Total time & samples taken */
  profiler_counter_t time_ns;
  uint64_t accumulated;
} profiler_timer_t;

#define TIMER_CONVERT_NS_TO_US(time_ns) ((double)(time_ns)/1E3)
#define TIMER_CONVERT_NS_TO_MS(time_ns) ((double)(time_ns)/1E6)
#define TIMER_CONVERT_NS_TO_S(time_ns)  ((double)(time_ns)/1E9)
#define TIMER_CONVERT_NS_TO_M(time_ns)  ((double)(time_ns)/1E9/60.0)
#define TIMER_CONVERT_NS_TO_H(time_ns)  ((double)(time_ns)/1E9/3600.0)

void timer_start(profiler_timer_t* const timer);
void timer_stop(profiler_timer_t* const timer);
void timer_pause(profiler_timer_t* const timer);
void timer_continue(profiler_timer_t* const timer);
uint64_t timer_elapsed_ns(profiler_timer_t* const timer);
void timer_reset(profiler_timer_t* const timer);
void timer_restart(profiler_timer_t* const timer);

uint64_t timer_get_total_ns(const profiler_timer_t* const timer);
uint64_t timer_get_num_samples(const profiler_timer_t* const timer);
uint64_t timer_get_min_ns(const profiler_timer_t* const timer);
uint64_t timer_get_max_ns(const profiler_timer_t* const timer);
uint64_t timer_get_mean(const profiler_timer_t* const timer);
uint64_t timer_get_variance(const profiler_timer_t* const timer);
uint64_t timer_get_stddev(const profiler_timer_t* const timer);

void timer_print(
    FILE* const stream,
    const profiler_timer_t* const timer,
    const profiler_timer_t* const ref_timer);

#define TIMER_GET_TOTAL_US(timer) TIMER_CONVERT_NS_TO_US(TIMER_GET_TOTAL_NS(timer))
#define TIMER_GET_TOTAL_MS(timer) TIMER_CONVERT_NS_TO_MS(TIMER_GET_TOTAL_NS(timer))
#define TIMER_GET_TOTAL_S(timer)  TIMER_CONVERT_NS_TO_S(TIMER_GET_TOTAL_NS(timer))
#define TIMER_GET_TOTAL_M(timer)  TIMER_CONVERT_NS_TO_M(TIMER_GET_TOTAL_NS(timer))
#define TIMER_GET_TOTAL_H(timer)  TIMER_CONVERT_NS_TO_H(TIMER_GET_TOTAL_NS(timer))

}
