CLK = 8000000UL

# TARGET es el nombre del proyecto
TARGET = skil

TATAMI = TATAMI_NEGRO
# MMCU es el microcontralador para el target para el avr-gcc
# Para ver el listado de posibles opciones ir a:
#      http://avr-libc.nongnu.org/user-manual/index.html
MMCU = atmega88pa

# TARGET_P es el microcontrolador para el target del programador
# Para el Atemga88: m88
# Para ver el listado de posibles opciones hacer:
#      avrdude -p ?
TARGET_P = m88p

# HFUSE 
# Para el Atmega88 (pagina 299)
# 0xDF es el default
# 0xD7 para no borrar la eeprom con cada repgramado
HFUSE = 0xDF

# LFUSE
# Para el Atemega88 (pagina 301)
# 0x62 es el default, con clk_div = 8
# 0xE2 es el default  sin clk_div
LFUSE = 0xE2

# SRC contiene el nombre de todos los .c existentes en el directorio actual
SRC = motores.c skil.c sensores.c 
# INC contiene el nombre de todos los .h existentes en el directorio actual
INC = skil.h motores.h definiciones.h sensores.h 

# Flags de optimizacion '-Os' tamaño '-O3' velocidad
# Si se deja -O vacio el compilador elige '-01'
CFLAGS = -O2 -Wall

CDEFINES = -DF_CPU=$(CLK) -D$(TATAMI)
all: hex

tatamiblanco:
	@make 'TATAMI=TATAMI_BLANCO'

hex: $(SRC) $(INC)
	avr-gcc $(CFLAGS) $(CDEFINES) -mmcu=$(MMCU) -o $(TARGET).bin -I/usr/avr/include/ $(SRC)
	avr-objcopy -j .text -j .data -O ihex  $(TARGET).bin $(TARGET).hex
	avr-objdump -h -S $(TARGET).bin > "$(TARGET).lst"
	avr-size $(TARGET).bin

program: hex
	avrdude -c usbtiny -p $(TARGET_P) -U flash:w:$(TARGET).hex:i

fuses_write:
	avrdude -c usbtiny -p $(TARGET_P) -U hfuse:w:$(HFUSE):m
	avrdude -c usbtiny -p $(TARGET_P) -U lfuse:w:$(LFUSE):m

fuses_read:
	@ avrdude -c usbtiny -p $(TARGET_P) -U hfuse:r:hfuse.hex:h
	@ avrdude -c usbtiny -p $(TARGET_P) -U lfuse:r:lfuse.hex:h
#	@ avrdude -c usbtiny -p $(TARGET_P) -U efuse:r:efuse.hex:h
	@ echo "HFuse = "
	@ cat hfuse.hex
	@ echo "LFuse = " 
	@ cat lfuse.hex
#	@ echo "EFuse = "
#	@ cat efuse.hex

clean:
	rm -rf $(TARGET).hex $(TARGET).bin $(TARGET).s $(TARGET).lst hfuse.hex lfuse.hex efuse.hex eeprom.hex

editgvim:
	gvim -p $(SRC) $(INC) Makefile

eeprom_read:
	avrdude -c usbtiny -p $(TARGET_P) -U eeprom:r:eeprom.hex:r

eeprom_write:
	avrdude -c usbtiny -p $(TARGET_P) -U eeprom:w:eeprom.hex:r
