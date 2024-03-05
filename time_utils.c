/**
 * @file time_utils.c
 * @author Christian Goertz (chris.goertz@gmx.de)
 * @brief Some helper functions to deal with time
 * @version 0.1
 * @date 2024-01-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "time_utils.h"
#include <stdint.h>
#include <stdlib.h>
// #include <string.h>
#include <stdio.h>

// useful macros

#define FAIL_IF(EXP) ({if(EXP){return TIME_UTIL_ERROR;} })
#define FAIL_IF_RETURN(EXP, RET) ({if(EXP){return RET;} })
// Test arguments for NULL pointer
#define FAIL_IF_NULL(ARG) ({if(NULL == ARG){return TIME_UTIL_ARGUMENT_NULL_ERROR;} })

// ###################################################################
/**
 * @brief Initialize the time stuct.
 *
 * @param time: TIME_UTIL_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_init(TIME_UTIL_t *time)
{
    FAIL_IF_NULL(time);

    time->days = TIME_UTILS_MIN;
    time->hours = TIME_UTILS_MIN;
    time->minutes = TIME_UTILS_MIN;
    time->seconds = TIME_UTILS_MIN;
    time->milliseconds = TIME_UTILS_MIN;
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief Incement days.
 *
 * @param time: TIME_UTIL_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_increment_days(TIME_UTIL_t *time)
{
    FAIL_IF_NULL(time);

    time->days++;
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief Decement days.
 *
 * @param time: TIME_UTIL_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_decrement_days(TIME_UTIL_t *time)
{
    /* check if timestruct is valid */
    FAIL_IF_NULL(time);

    /* check if days is eq 0*/
    FAIL_IF_RETURN(time->days == 0, TIME_UTIL_ERROR);

    time->days--;
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief add amount to days 
 * 
 * @param time: TIME_UTIL_t
 * @param amount: uint32_t
 * @return TIME_UTIL_Error_t 
 */
TIME_UTIL_Error_t time_util_add_days(TIME_UTIL_t *time, uint32_t amount){

    /* check if timestruct is valid */
    FAIL_IF_NULL(time);
    time->days += amount;
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief Increment hours.
 *
 * @param time: TIME_UTIL_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_increment_hours(TIME_UTIL_t *time)
{
    FAIL_IF_NULL(time);

    if (time->hours < TIME_UTILS_HOURS_MAX)
    {
        time->hours++;
    }
    else
    {
        time->hours = TIME_UTILS_MIN;
        time_util_increment_days(time);
    }
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief Decrement hours.
 *
 * @param time: TIME_UTILS_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_decrement_hours(TIME_UTIL_t *time)
{
    /* check if time struct is valid */
    FAIL_IF_NULL(time);

    if (time->hours <= TIME_UTILS_MIN)
    {
        time->hours = 23;
        time_util_decrement_days(time);
    }
    else
    {
        time->hours--;
    }
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief Add amount to hours
 * 
 * @param time: TIME_UTIL_t
 * @param amount: uint32_t
 * @return TIME_UTIL_Error_t 
 */
TIME_UTIL_Error_t time_util_add_hours(TIME_UTIL_t *time, uint32_t amount)
{
    /* check if time struct is valid */
    FAIL_IF_NULL(time);
    
    // add remainder from division by HOURS_MAX to days
    uint32_t add_days = amount % TIME_UTILS_HOURS_MAX+1;
    time_util_add_days(time, add_days);
    
    // add hours
    uint32_t add_hours = amount / TIME_UTILS_HOURS_MAX+1;
    time->hours += add_hours;
    
    // if hours theoretically overflows, correct value
    if(time->hours > TIME_UTILS_HOURS_MAX){
        time_util_increment_days(time);
        time->hours -= TIME_UTILS_HOURS_MAX+1;
    }
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief Increment minutes.
 *
 * @param time: TIME_UTILS_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_increment_minutes(TIME_UTIL_t *time)
{
    FAIL_IF_NULL(time);

    if (time->minutes < TIME_UTILS_MINUTES_MAX)
    {
        time->minutes++;
    }
    else
    {
        time->minutes = TIME_UTILS_MIN;
        time_util_increment_hours(time);
    }
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief Decrement minutes.
 *
 * @param time: TIME_UTILS_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_decrement_minutes(TIME_UTIL_t *time)
{
    FAIL_IF_NULL(time);

    if (time->minutes <= TIME_UTILS_MIN)
    {
        time->minutes = TIME_UTILS_MINUTES_MAX;
        time_util_decrement_hours(time);
    }
    else
    {
        time->minutes--;
    }
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief Add mount to minutes.
 * 
 * @param time: TIME_UTIL_t
 * @param amount: uint32_t
 * @return TIME_UTIL_Error_t 
 */
TIME_UTIL_Error_t time_util_add_minutes(TIME_UTIL_t *time, uint32_t amount)
{
    /* check if time struct is valid */
    FAIL_IF_NULL(time);
    
    // add remainder from division by HOURS_MAX to days
    uint32_t add_hours = amount % TIME_UTILS_MINUTES_MAX+1;
    time_util_add_hours(time, add_hours);
    
    // add hours
    uint32_t add_minutes = amount / TIME_UTILS_MINUTES_MAX+1;
    time->minutes += add_minutes;
    
    // if hours theoretically overflows, correct value
    if(time->minutes > TIME_UTILS_MINUTES_MAX){
        time_util_increment_hours(time);
        time->minutes -= TIME_UTILS_MINUTES_MAX+1;
    }
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief Incement seconds.
 *
 * @param time: TIME_UTILS_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_increment_seconds(TIME_UTIL_t *time)
{
    FAIL_IF_NULL(time);

    if (time->seconds < TIME_UTILS_SECONDS_MAX)
    {
        time->seconds++;
    }
    else
    {
        time->seconds = TIME_UTILS_MIN;
        time_util_increment_minutes(time);
    }
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief Decement seconds.
 *
 * @param time: TIME_UTILS_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_decrement_seconds(TIME_UTIL_t *time)
{
    FAIL_IF_NULL(time);

    if (time->seconds < TIME_UTILS_MIN)
    {
        time->seconds = 59;
        time_util_decrement_minutes(time);
    }
    else
    {
        time->seconds--;
    }
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief Add amount to seconds.
 * 
 * @param time: TIME_UTIL_t
 * @param amount: uint32_t
 * @return TIME_UTIL_Error_t 
 */
TIME_UTIL_Error_t time_util_add_seconds(TIME_UTIL_t *time, uint32_t amount)
{
    /* check if time struct is valid */
    FAIL_IF_NULL(time);
    
    // add remainder from division by HOURS_MAX to days
    uint32_t add_minutes = amount % TIME_UTILS_SECONDS_MAX+1;
    time_util_add_minutes(time, add_minutes);
    
    // add hours
    uint32_t add_seconds = amount / TIME_UTILS_SECONDS_MAX+1;
    time->minutes += add_seconds;
    
    // if hours theoretically overflows, correct value
    if(time->seconds > TIME_UTILS_SECONDS_MAX){
        time_util_increment_minutes(time);
        time->seconds -= TIME_UTILS_SECONDS_MAX+1;
    }
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief Increment milliseconds.
 *
 * @param time: TIME_UTILS_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_increment_milliseconds(TIME_UTIL_t *time)
{
    FAIL_IF_NULL(time);

    if (time->milliseconds < TIME_UTILS_MILLISECONDS_MAX)
    {
        time->milliseconds++;
    }
    else
    {
        time->milliseconds = TIME_UTILS_MIN;
        time_util_increment_seconds(time);
    }
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief Add amount to milliseconds
 * 
 * @param time: TIME_UTIL_t
 * @param amount: uint32_t
 * @return TIME_UTIL_Error_t 
 */
TIME_UTIL_Error_t time_util_add_milliseconds(TIME_UTIL_t *time, uint32_t amount)
{
    /* check if time struct is valid */
    FAIL_IF_NULL(time);
    
    // add remainder from division by HOURS_MAX to days
    uint32_t add_seconds = amount % TIME_UTILS_MILLISECONDS_MAX+1;
    time_util_add_seconds(time, add_seconds);
    
    // add hours
    uint32_t add_milliseconds = amount / TIME_UTILS_MILLISECONDS_MAX+1;
    time->milliseconds += add_milliseconds;
    
    // if hours theoretically overflows, correct value
    if(time->seconds > TIME_UTILS_MILLISECONDS_MAX){
        time_util_increment_seconds(time);
        time->seconds -= TIME_UTILS_MILLISECONDS_MAX+1;
    }
    return TIME_UTIL_OK;
}

// ###################################################################
/**
 * @brief copy string representation of the time struct into
 * a char array. Format DD-HH:MM:SS:mSmS
 *
 * @param time: TIME_UTIL_t*
 * @param destination: char*
 * @param destination_len: uint32_t
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_timeToString(TIME_UTIL_t *time, char *destination, uint32_t destination_len)
{
    FAIL_IF_NULL(time);
    // calculate length of possible string
    uint32_t string_length = 13;
    if (time->days >= 10000)
        string_length++;
    if (time->days >= 1000)
        string_length++;
    if (time->days >= 100)
        string_length++;
    if (time->days >= 10)
        string_length++;
    if (time->days >= 1)
        string_length++;

    // test, if string fits into destination.
    FAIL_IF((string_length + 1) >= destination_len);

    // copy string into destination.
    sprintf(destination, "%d-%02d:%02d:%02d:%04d",
            time->days,
            time->hours,
            time->minutes,
            time->seconds,
            time->milliseconds);

    return TIME_UTIL_OK;
}
// ###################################################################
/**
 * @brief copy a shorter string representation of the time struct into
 * a char array. Format HH:MM:SS
 *
 * @param time: TIME_UTIL_t*
 * @param destination: char*
 * @param destination_len: uint32_t
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_shortTimeToString(TIME_UTIL_t *time, char *destination, uint32_t destination_len)
{
    FAIL_IF_NULL(time);
    const uint32_t string_length = 8;
    // test, if string fits into destination.
    FAIL_IF((string_length + 1) >= destination_len);

    sprintf(destination, "%02d:%02d:%02d",
            time->hours,
            time->minutes,
            time->seconds);

    return TIME_UTIL_OK;
}

/**
 * @brief Calculate time from seconds.
 *
 * @param time: TIME_UTIL_t*
 * @param seconds: uint32_t
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_fromMilliSeconds(TIME_UTIL_t *time, uint32_t ms)
{
    FAIL_IF_NULL(time);

    time->milliseconds = ms % 1000; // 23450 % 1000 = 0
    uint32_t rest = ms / 1000;      // 23450
    time->seconds = rest % 60;
    rest = rest / 60;
    time->minutes = rest % 60;
    rest = rest / 60;
    time->hours = rest % 24;
    time->days = rest / 24;
    return TIME_UTIL_OK;
}

/* GETTERS */
/**
 * @brief Return the actual days.
 *
 * @param time: TIME_UTIL_t*
 * @return uint8_t
 */
uint8_t time_util_get_days(TIME_UTIL_t *time)
{
    FAIL_IF_NULL(time);

    return time->days;
}

/**
 * @brief Return the actual hours.
 *
 * @param time: TIME_UTIL_t*
 * @return uint8_t
 */
uint8_t time_util_get_hours(TIME_UTIL_t *time)
{
    FAIL_IF_NULL(time);

    return time->hours;
}

/**
 * @brief Return the actual minutes.
 *
 * @param time: TIME_UTIL_t*
 * @return uint8_t
 */
uint8_t time_util_get_minutes(TIME_UTIL_t *time)
{
    FAIL_IF_NULL(time);

    return time->minutes;
}

/**
 * @brief Return the actual seconds.
 *
 * @param time: TIME_UTIL_t*
 * @return uint8_t
 */
uint8_t time_util_get_seconds(TIME_UTIL_t *time)
{
    FAIL_IF_NULL(time);

    return time->seconds;
}

/**
 * @brief Return the actual milliseonds.
 *
 * @param time: TIME_UTIL_t*
 * @return uint8_t
 */
uint16_t time_util_get_milliseconds(TIME_UTIL_t *time)
{
    FAIL_IF_NULL(time);

    return time->milliseconds;
}
/**
 * @brief Set the days in time struct.
 *
 * @param time: TIME_UTIL_t* time struct.
 * @param d: uint8_t the new day value.
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_set_days(TIME_UTIL_t *time, uint8_t d)
{
    FAIL_IF_NULL(time);
    time->days = d;
    return TIME_UTIL_OK;
}

/**
 * @brief Set the hours in time struct.
 *
 * @param time: TIME_UTIL_t* time struct
 * @param h: uint8_t the new hour value.
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_set_hours(TIME_UTIL_t *time, uint8_t h)
{
    FAIL_IF_NULL(time);
    FAIL_IF_RETURN(h > TIME_UTILS_HOURS_MAX, TIME_UTIL_ARGUMENT_INVALID_ERROR);
    time->hours = h;
    return TIME_UTIL_OK;
}
/**
 * @brief Set the minutes in time struct.
 * 
 * @param time: TIME_UTIL_t* time struct
 * @param m: uint8_t the minutes value.
 * @return TIME_UTIL_Error_t 
 */
TIME_UTIL_Error_t time_util_set_minutes(TIME_UTIL_t *time, uint8_t m){
    FAIL_IF_NULL(time);
    FAIL_IF_RETURN(m > TIME_UTILS_MINUTES_MAX, TIME_UTIL_ARGUMENT_INVALID_ERROR);
    time->minutes = m;
    return TIME_UTIL_OK;
}

/**
 * @brief Set the seconds in time struct.
 * 
 * @param time: TIME_UTIL_t* time struct
 * @param s: uint8_t the minutes value.
 * @return TIME_UTIL_Error_t 
 */
TIME_UTIL_Error_t time_util_set_seconds(TIME_UTIL_t *time, uint8_t s){
    FAIL_IF_NULL(time);
    FAIL_IF_RETURN(s > TIME_UTILS_SECONDS_MAX, TIME_UTIL_ARGUMENT_INVALID_ERROR);
    time->seconds = s;
    return TIME_UTIL_OK;
}

/**
 * @brief Set the milliseconds in time struct
 * 
 * @param time: TIME_UTIL_t* time struct
 * @param ms: uint16_t the milliseconds value.
 * @return TIME_UTIL_Error_t 
 */
TIME_UTIL_Error_t time_util_set_milliseconds(TIME_UTIL_t *time, uint16_t ms){
    FAIL_IF(time);
    FAIL_IF_RETURN(ms > TIME_UTILS_MILLISECONDS_MAX, TIME_UTIL_ARGUMENT_INVALID_ERROR);
    time->milliseconds = ms;
    return TIME_UTIL_OK;
}
