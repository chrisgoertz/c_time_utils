#ifndef __NCDF_TIME_UTILS_H__
#define __NCDF_TIME_UTILS_H__
/**
 * @file time_utils.h
 * @author Christian Goertz (chris.goertz@gmx.de)
 * @brief Some helper functions to deal with time
 * @version 0.1
 * @date 2024-01-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

#define TIME_UTILS_MIN              (0)
#define TIME_UTILS_HOURS_MAX        (23)
#define TIME_UTILS_MINUTES_MAX      (59)
#define TIME_UTILS_SECONDS_MAX      (59)
#define TIME_UTILS_MILLISECONDS_MAX (999)

/**
 * @brief Error codes. 
 */
typedef enum{
    TIME_UTIL_OK = 0x00,            // no error.
    TIME_UTIL_ERROR = 0x01,         // Generic error.
}TIME_UTIL_Error_t;

typedef struct{
    uint8_t milliseconds;
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint32_t days;
}TIME_UTIL_t;

TIME_UTIL_Error_t time_util_init(TIME_UTIL_t* time);

/* time arithmetics */
TIME_UTIL_Error_t time_util_increment_days(TIME_UTIL_t* time);
TIME_UTIL_Error_t time_util_decrement_days(TIME_UTIL_t* time);
TIME_UTIL_Error_t time_util_increment_hours(TIME_UTIL_t* time);
TIME_UTIL_Error_t time_util_decrement_hours(TIME_UTIL_t* time);
TIME_UTIL_Error_t time_util_increment_minutes(TIME_UTIL_t* time);
TIME_UTIL_Error_t time_util_decrement_minutes(TIME_UTIL_t* time);
TIME_UTIL_Error_t time_util_increment_seconds(TIME_UTIL_t* time);
TIME_UTIL_Error_t time_util_decrement_seconds(TIME_UTIL_t* time);
TIME_UTIL_Error_t time_util_increment_milliseconds(TIME_UTIL_t* time);

/* transforming time data*/
TIME_UTIL_Error_t time_util_timeToString(TIME_UTIL_t* time, char* destination, uint32_t destination_len);
TIME_UTIL_Error_t time_util_shortTimeToString(TIME_UTIL_t* time, char* destination, uint32_t destination_len);
TIME_UTIL_Error_t time_util_fromMilliSeconds(TIME_UTIL_t* time, uint32_t seconds);

/* GETTERS */
uint8_t time_util_get_days(TIME_UTIL_t* time);
uint8_t time_util_get_hours(TIME_UTIL_t* time);
uint8_t time_util_get_minutes(TIME_UTIL_t* time);
uint8_t time_util_get_seconds(TIME_UTIL_t* time);
uint8_t time_util_get_milliseconds(TIME_UTIL_t* time);

/* SETTERS */
TIME_UTIL_Error_t time_util_set_days(TIME_UTIL_t* time, uint8_t d);
TIME_UTIL_Error_t time_util_set_hours(TIME_UTIL_t* time, uint8_t h);

#ifdef __cpluplus
}
#endif

#endif