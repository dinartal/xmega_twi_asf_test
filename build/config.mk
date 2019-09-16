#
# Copyright (c) 2010 Atmel Corporation. All rights reserved.
#
# \asf_license_start
#
# \page License
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. The name of Atmel may not be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# 4. This software may only be redistributed and used in connection with an
#    Atmel microcontroller product.
#
# THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# \asf_license_stop
#

# Path to top level ASF directory relative to this project directory.
#PRJ_PATH = $(HOME)/projects/asf
PRJ_PATH = /root/xdk-asf-3.35.1

# Microcontroller: atxmega128a1, atmega128, attiny261, etc.
MCU = atxmega256a3bu

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.

TARGET = test_app.elf

# C source files located from the top-level source directory
CSRCS = \
       common/services/clock/xmega/sysclk.c                                                   \
       common/services/usb/class/cdc/device/udi_cdc.c                                         \
       common/services/usb/class/cdc/device/udi_cdc_desc.c                                    \
       common/services/usb/udc/udc.c                                                          \
       common/services/sleepmgr/xmega/sleepmgr.c                                              \
       xmega/applications/xmega_twi_asf_test/test/bme280.c                \
       xmega/applications/xmega_twi_asf_test/test/bme280_port.c           \
       xmega/applications/xmega_twi_asf_test/test/main.c                                \
       xmega/applications/xmega_twi_asf_test/test/timer_delay.c             \
       xmega/drivers/tc/tc.c                                                                  \
       xmega/drivers/twi/twim.c                                                               \
       xmega/drivers/usb/usb_device.c                                                        \

# Assembler source files located from the top-level source directory
ASSRCS = \
       xmega/drivers/cpu/ccp.s                            \
       xmega/drivers/nvm/nvm_asm.s

# Include path located from the top-level source directory
INC_PATH = \
       xmega/applications/xmega_twi_asf_test/test                               \
       xmega/applications/xmega_twi_asf_test/test/src/config                    \
       xmega/applications/xmega_twi_asf_test/test/src                           \
       xmega/drivers/cpu                                                        \
       xmega/drivers/pmic                                                       \
       xmega/drivers/nvm                                                        \
       xmega/drivers/sleep                                                      \
       xmega/drivers/tc                                                         \
       xmega/drivers/twi                                                        \
       xmega/utils                                                              \
       xmega/utils/preprocessor                                                 \
       common/utils                                                             \
       common/boards                                                            \
       common/services/clock                                                    \
       common/services/sleepmgr                                                 \
       common/services/twi                                                      \
       common/services/usb                                                      \
       common/services/usb/udc                                                  \
       common/services/usb/class/cdc                                            \
       common/services/usb/class/cdc/device                                     \
       common/boards/user_board/

# Library paths from the top-level source directory
LIB_PATH = 
#../avr8-gnu-toolchain-linux_x86_64/avr/lib/ 

# Libraries to link with the project
LIBS =  

# Additional options for debugging. By default the common Makefile.in will
# add -gdwarf-2.
BUILD_DEBUG_LEVEL = 0
DBGFLAGS =

# Optimization settings
OPTIMIZATION = -Os

# Extra flags used when creating an EEPROM Intel HEX file. By default the
# common Makefile.in will add -j .eeprom
# --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0.
EEPROMFLAGS = 

# Extra flags used when creating an Intel HEX file. By default the common
# Makefile.in will add -R .eeprom -R .usb_descriptor_table.
FLASHFLAGS = 

# Extra flags to use when archiving.
ARFLAGS = 

# Extra flags to use when assembling.
ASFLAGS = 

# Extra flags to use when compiling.
CFLAGS = -Wpointer-arith                       \
         -fpack-struct                         \
         -fshort-enums                         

# Extra flags to use when preprocessing.
#
# Preprocessor symbol definitions
#   To add a definition use the format "-D name[=definition]".
#   To cancel a definition use the format "-U name".
#
# The most relevant symbols to define for the preprocessor are:
#   BOARD      Target board in use, see boards/board.h for a list.
#   EXT_BOARD  Optional extension board in use, see boards/board.h for a list.
CPPFLAGS = \
       -DBOARD=USER_BOARD                                \
       -DNDEBUG

# Extra flags to use when linking
LDFLAGS =  \
       -Wl,--section-start=.BOOT=0x40000,-u,vfprintf,-lprintf_flt              

# Pre- and post-build commands
PREBUILD_CMD = 
POSTBUILD_CMD = 
