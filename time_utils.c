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
//#include <string.h>
#include <stdio.h>

#define FAIL_IF(EXP) ({if(EXP){return TIME_UTIL_ERROR;}})
//###################################################################
/**
 * @brief Initialize the time stuct.
 * 
 * @param time: TIME_UTIL_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_init(TIME_UTIL_t* time){
    FAIL_IF(NULL == time);

    time->days = TIME_UTILS_MIN;
    time->hours = TIME_UTILS_MIN;
    time->minutes = TIME_UTILS_MIN;
    time->seconds = TIME_UTILS_MIN;
    time->milliseconds = TIME_UTILS_MIN;
    return TIME_UTIL_OK;
}

//###################################################################
/**
 * @brief Incement days.
 * 
 * @param time: TIME_UTIL_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_increment_days(TIME_UTIL_t* time){
    FAIL_IF(NULL == time);

    time->days++;
    return TIME_UTIL_OK;
}

//###################################################################
/**
 * @brief Decement days.
 * 
 * @param time: TIME_UTIL_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_decrement_days(TIME_UTIL_t* time){
    /* check if timestruct is valid */
    FAIL_IF(NULL == time);

    /* check if days is gt 0*/
    FAIL_IF(time->days <= 0);

    time->days--;
    return TIME_UTIL_OK;
}

//###################################################################
/**
 * @brief Increment hours.
 * 
 * @param time: TIME_UTILS_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_increment_hours(TIME_UTIL_t* time){
    FAIL_IF(NULL == time);

    if(time->hours < TIME_UTILS_HOURS_MAX){
        time->hours++;
        return TIME_UTIL_OK;
    }
    time->hours = TIME_UTILS_MIN;
    time_util_increment_days(time);
    return TIME_UTIL_OK;
}

//###################################################################
/**
 * @brief Decrement hours.
 * 
 * @param time: TIME_UTILS_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_decrement_hours(TIME_UTIL_t* time){
    /* chekc if time struct is valid */
    FAIL_IF(NULL == time);

    if(time->hours <= TIME_UTILS_MIN){
        time->hours = 23;
        time_util_decrement_days(time);
        return TIME_UTIL_OK;
    }
    time->hours--;
    
    return TIME_UTIL_OK;
}

//###################################################################
/**
 * @brief Increment minutes.
 * 
 * @param time: TIME_UTILS_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_increment_minutes(TIME_UTIL_t* time){
    FAIL_IF(NULL == time);

    if(time->minutes < TIME_UTILS_MINUTES_MAX){
        time->minutes++;
        return TIME_UTIL_OK;
    }
    time->minutes = TIME_UTILS_MIN;
    time_util_increment_hours(time);
    return TIME_UTIL_OK;
}
//###################################################################
/**
 * @brief Decrement minutes.
 * 
 * @param time: TIME_UTILS_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_decrement_minutes(TIME_UTIL_t* time){
    FAIL_IF(NULL == time);

    if(time->minutes <= TIME_UTILS_MIN){
        time->minutes = 59;
        time_util_decrement_hours(time);
        return TIME_UTIL_OK;
    }
    time->minutes--;
    return TIME_UTIL_OK;
}

//###################################################################
/**
 * @brief Incement seconds.
 * 
 * @param time: TIME_UTILS_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_increment_seconds(TIME_UTIL_t* time){
    FAIL_IF(NULL == time);

    if(time->seconds < TIME_UTILS_SECONDS_MAX){
        time->seconds++;
        return TIME_UTIL_OK;
    }
    time->seconds = TIME_UTILS_MIN;
    time_util_increment_minutes(time);
    return TIME_UTIL_OK;
}

//###################################################################
/**
 * @brief Decement seconds.
 * 
 * @param time: TIME_UTILS_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_decrement_seconds(TIME_UTIL_t* time){
    FAIL_IF(NULL == time);

    if(time->seconds < TIME_UTILS_MIN){
        time->seconds = 59;
        time_util_decrement_minutes(time);
        return TIME_UTIL_OK;
    }
    time->seconds--;
    return TIME_UTIL_OK;
}

//###################################################################
/**
 * @brief Increment milliseconds.
 * 
 * @param time: TIME_UTILS_t*
 * @return TIME_UTIL_Error_t
 */
TIME_UTIL_Error_t time_util_increment_milliseconds(TIME_UTIL_t* time){
    FAIL_IF(NULL == time);

    if(time->milliseconds < TIME_UTILS_MILLISECONDS_MAX){
        time->milliseconds++;
        return TIME_UTIL_OK;
    }
    time->milliseconds = TIME_UTILS_MIN;
    time_util_increment_seconds(time);
    return TIME_UTIL_OK;
}

//###################################################################
/**
 * @brief copy string representation of the time struct into 
 * a char array. Format DD-HH:MM:SS:mSmS
 * 
 * @param time: TIME_UTIL_t*
 * @param destination: char*
 * @param destination_len: uint32_t
 * @return TIME_UTIL_Error_t 
 */
TIME_UTIL_Error_t time_util_timeToString(TIME_UTIL_t* time, char* destination, uint32_t destination_len){
    FAIL_IF(NULL == time);
    //calculate length of possible string
    uint32_t string_length = 13;
    if(time->days >=10000) string_length++;
    if(time->days >=1000) string_length++;
    if(time->days >=100) string_length++;
    if(time->days >=10) string_length++;
    if(time->days >=1) string_length++;

    // test, if string fits into destination.
    FAIL_IF((string_length +1) >= destination_len);
    
    // copy string into destination.
    sprintf(destination, "%d-%02d:%02d:%02d:%04d",
        time->days,
        time->hours,
        time->minutes,
        time->seconds,
        time->milliseconds);
    
    return TIME_UTIL_OK;
}
//###################################################################
/**
 * @brief copy a shorter string representation of the time struct into 
 * a char array. Format HH:MM:SS
 * 
 * @param time: TIME_UTIL_t*
 * @param destination: char*
 * @param destination_len: uint32_t
 * @return TIME_UTIL_Error_t 
 */
TIME_UTIL_Error_t time_util_shortTimeToString(TIME_UTIL_t* time, char* destination, uint32_t destination_len){
    FAIL_IF(NULL == time);
    const uint32_t string_length = 8;
    // test, if string fits into destination.
    FAIL_IF((string_length +1) >= destination_len);

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
TIME_UTIL_Error_t time_util_fromMilliSeconds(TIME_UTIL_t* time, uint32_t ms){
    FAIL_IF(NULL == time);

    time->milliseconds = ms % 1000; // 23450 % 1000 = 0
    uint32_t rest = ms / 1000; // 23450
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
uint8_t time_util_get_days(TIME_UTIL_t* time){
    FAIL_IF(NULL == time);

    return time->days;
}

/**
 * @brief Return the actual hours.
 * 
 * @param time: TIME_UTIL_t*
 * @return uint8_t
 */
uint8_t time_util_get_hours(TIME_UTIL_t* time){
    FAIL_IF(NULL == time);

    return time->hours;
}

/**
 * @brief Return the actual minutes.
 * 
 * @param time: TIME_UTIL_t*
 * @return uint8_t
 */
uint8_t time_util_get_minutes(TIME_UTIL_t* time){
    FAIL_IF(NULL == time);

    return time->minutes;
}

/**
 * @brief Return the actual seconds.
 * 
 * @param time: TIME_UTIL_t*
 * @return uint8_t 
 */
uint8_t time_util_get_seconds(TIME_UTIL_t* time){
    FAIL_IF(NULL == time);

    return time->seconds;
}

/**
 * @brief Return the actual milliseonds.
 * 
 * @param time: TIME_UTIL_t*
 * @return uint8_t 
 */
uint8_t time_util_get_milliseconds(TIME_UTIL_t* time){
    FAIL_IF(NULL == time);

    return time->milliseconds;
}
/**
 * @brief Set the days in time struct.
 * 
 * @param time: TIME_UTIL_t* time struct.
 * @param d: uint8_t the new day value.
 * @return uint8_t 
 */
TIME_UTIL_Error_t time_util_set_days(TIME_UTIL_t* time, uint8_t d){
    FAIL_IF(NULL == time);
    time->days = d;
    return TIME_UTIL_OK;
}

/**
 * @brief Set the hours in time struct.
 * 
 * @param time: TIME_UTIL_t* time struct
 * @param h: uint8_t the new hour value.
 * @return uint8_t 
 */
TIME_UTIL_Error_t time_util_set_hours(TIME_UTIL_t* time, uint8_t h){
    FAIL_IF(NULL == time);
    FAIL_IF(h > TIME_UTILS_HOURS_MAX);

    time->hours = h;
    return TIME_UTIL_OK;
}