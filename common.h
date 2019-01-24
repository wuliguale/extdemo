/*
 * common.h
 *
 *  Created on: 2019-1-23
 *      Author: sam
 */

#ifndef EXT_EXTDEMO_COMMON_H_
#define EXT_EXTDEMO_COMMON_H_

#include <php.h>
#include <sys/time.h>

#ifndef NULL
#define NULL   ((void *) 0)
#endif

long get_time_mills()
{
	 struct timeval tv;
	  gettimeofday(&tv, NULL);
	  return (tv.tv_sec*1000 + tv.tv_usec/1000);
}

#endif /* EXT_EXTDEMO_COMMON_H_ */


