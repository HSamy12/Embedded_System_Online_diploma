#@copyright: Hassan Samy
CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -mthumb -gdwarf-2
INCS= -I ./Inc
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
As=$(wildcard *.s)
AsOBJ=$(As:.s=.o)
Project_name=Final_Project1

all:$(Project_name).bin
	@echo "*"
	@echo "*******Build is done.*******"
	@echo "*"


%.o:%.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

$(Project_name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld -Map=Map_file.map $(LIBS) $(OBJ) $(AsOBJ) -o $@ 

$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *.map *.elf *.bin
	@echo "*******all clean.*******"

clean: 
	rm *.elf *.bin
