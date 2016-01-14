################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../actuatorFunctions.c \
../can.c \
../control.c \
../Robot_Actuator_Voja_2015.c \
../system.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
actuatorFunctions.o \
can.o \
control.o \
Robot_Actuator_Voja_2015.o \
system.o

OBJS_AS_ARGS +=  \
actuatorFunctions.o \
can.o \
control.o \
Robot_Actuator_Voja_2015.o \
system.o

C_DEPS +=  \
actuatorFunctions.d \
can.d \
control.d \
Robot_Actuator_Voja_2015.d \
system.d

C_DEPS_AS_ARGS +=  \
actuatorFunctions.d \
can.d \
control.d \
Robot_Actuator_Voja_2015.d \
system.d

OUTPUT_FILE_PATH +=Robot_Actuator_Voja_2015.elf

OUTPUT_FILE_PATH_AS_ARGS +=Robot_Actuator_Voja_2015.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler











./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 0.0.0
	$(QUOTE)C:\avr8-gnu-toolchain\avr\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG -DF_CPU=11059200ULL  -I"E:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\include"  -O0 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -Wall -pedantic  -mmcu=at90can128  -c -std=gnu99 -v -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 0.0.0
	$(QUOTE)C:\avr8-gnu-toolchain\avr\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Robot_Actuator_Voja_2015.map" -Wl,--start-group -Wl,-lm -Wl,-lQEI -Wl,-luart  -Wl,--end-group -Wl,-L"C:\Users\pkobi_000\Desktop\Robotika2015\Robot_Actuator_Voja_2015\Robot_Actuator_Voja_2015" -Wl,-L"C:\Users\pkobi_000\Desktop\Robotika2015\Kodovi\Robot_Actuator_Voja_2015\Robot_Actuator_Voja_2015"  -Wl,--gc-sections -mrelax  -mmcu=at90can128   
	@echo Finished building target: $@
	"C:\avr8-gnu-toolchain\avr\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Robot_Actuator_Voja_2015.elf" "Robot_Actuator_Voja_2015.hex"
	"C:\avr8-gnu-toolchain\avr\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Robot_Actuator_Voja_2015.elf" "Robot_Actuator_Voja_2015.eep" || exit 0
	"C:\avr8-gnu-toolchain\avr\bin\avr-objdump.exe" -h -S "Robot_Actuator_Voja_2015.elf" > "Robot_Actuator_Voja_2015.lss"
	"C:\avr8-gnu-toolchain\avr\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Robot_Actuator_Voja_2015.elf" "Robot_Actuator_Voja_2015.srec"
	"C:\avr8-gnu-toolchain\avr\bin\avr-size.exe" "Robot_Actuator_Voja_2015.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Robot_Actuator_Voja_2015.elf" "Robot_Actuator_Voja_2015.a" "Robot_Actuator_Voja_2015.hex" "Robot_Actuator_Voja_2015.lss" "Robot_Actuator_Voja_2015.eep" "Robot_Actuator_Voja_2015.map" "Robot_Actuator_Voja_2015.srec" "Robot_Actuator_Voja_2015.usersignatures"
	