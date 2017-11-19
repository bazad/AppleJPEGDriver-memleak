//
//  IOKit.h
//  AppleJPEGDriver-memleak
//
//  Created by Brandon Azad on 11/18/17.
//

#ifndef IOKit_h
#define IOKit_h

#include <CoreFoundation/CoreFoundation.h>
#include <mach/mach.h>

typedef mach_port_t     io_object_t;

typedef io_object_t     io_connect_t;
typedef io_object_t     io_enumerator_t;
typedef io_object_t     io_iterator_t;
typedef io_object_t     io_registry_entry_t;
typedef io_object_t     io_service_t;

#define IO_OBJECT_NULL  ((io_object_t) 0)

extern
const mach_port_t kIOMasterPortDefault;

kern_return_t
IOObjectRelease(
	io_object_t     object );

io_service_t
IOServiceGetMatchingService(
	mach_port_t     masterPort,
	CFDictionaryRef matching );

kern_return_t
IOServiceOpen(
	io_service_t    service,
	task_port_t     owningTask,
	uint32_t        type,
	io_connect_t  * connect );

kern_return_t
IOServiceClose(
	io_connect_t    connect );

kern_return_t
IOConnectCallMethod(
	mach_port_t      connection,
	uint32_t         selector,
	const uint64_t * input,
	uint32_t         inputCnt,
	const void *     inputStruct,
	size_t           inputStructCnt,
	uint64_t *       output,
	uint32_t *       outputCnt,
	void *           outputStruct,
	size_t *         outputStructCnt );

CFMutableDictionaryRef
IOServiceMatching(
	const char *    name );

#endif /* IOKit_h */
