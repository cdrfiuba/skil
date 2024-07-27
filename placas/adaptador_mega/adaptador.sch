EESchema Schematic File Version 2  date jue 25 ago 2011 13:33:18 ART
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:mainboard-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title "noname.sch"
Date "25 aug 2011"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATMEGA88-P IC?
U 1 1 4E567841
P 4950 3550
F 0 "IC?" H 4250 4800 50  0000 L BNN
F 1 "ATMEGA88-P" H 5250 2150 50  0000 L BNN
F 2 "DIL28" H 4350 2200 50  0001 C CNN
	1    4950 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4E567840
P 3950 4850
F 0 "#PWR?" H 3950 4850 30  0001 C CNN
F 1 "GND" H 3950 4780 30  0001 C CNN
	1    3950 4850
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 4E56783F
P 3850 2350
F 0 "#PWR?" H 3850 2440 20  0001 C CNN
F 1 "+5V" H 3850 2440 30  0000 C CNN
	1    3850 2350
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 4E56783E
P 3250 3050
F 0 "C?" H 3300 3150 50  0000 L CNN
F 1 "100n" H 3300 2950 50  0000 L CNN
	1    3250 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4E56783D
P 3250 3350
F 0 "#PWR?" H 3250 3350 30  0001 C CNN
F 1 "GND" H 3250 3280 30  0001 C CNN
	1    3250 3350
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 4E56783C
P 3900 3300
F 0 "C?" H 3950 3400 50  0000 L CNN
F 1 "100n" H 3950 3200 50  0000 L CNN
	1    3900 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4E56783B
P 3900 3600
F 0 "#PWR?" H 3900 3600 30  0001 C CNN
F 1 "GND" H 3900 3530 30  0001 C CNN
	1    3900 3600
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL SW?
U 1 1 4E56783A
P 6900 4050
F 0 "SW?" H 7050 4160 30  0000 C CNN
F 1 "SW_PUSH_SMALL" H 6900 3971 30  0000 C CNN
	1    6900 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4E567839
P 7000 4550
F 0 "#PWR?" H 7000 4550 30  0001 C CNN
F 1 "GND" H 7000 4480 30  0001 C CNN
	1    7000 4550
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4E567838
P 6700 3600
F 0 "R?" V 6780 3600 50  0000 C CNN
F 1 "10k" V 6700 3600 50  0000 C CNN
	1    6700 3600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 4E567837
P 6700 3300
F 0 "#PWR?" H 6700 3390 20  0001 C CNN
F 1 "+5V" H 6700 3390 30  0000 C CNN
	1    6700 3300
	1    0    0    -1  
$EndComp
Text Label 6350 3300 2    60   ~ 0
OjitoA
Text Label 6350 3400 2    60   ~ 0
OjitoB
Text Label 6350 3500 2    60   ~ 0
OjitoC
Text Label 6350 4350 2    60   ~ 0
RecepD
Text Label 6350 4250 2    60   ~ 0
RecepC
Text Label 6350 4150 2    60   ~ 0
RecepB
Text Label 6350 4050 2    60   ~ 0
RecepA
Text Label 6350 4550 2    60   ~ 0
PwmI_1
Text Label 6350 4650 2    60   ~ 0
PwmI_2
Text Label 6350 2550 2    60   ~ 0
PwmD_1
Text Label 6350 2650 2    60   ~ 0
PwmD_2
Text Label 6350 2450 2    60   ~ 0
nFault
Text Label 6350 3150 2    60   ~ 0
nSleep
Text Label 6350 3050 2    60   ~ 0
nReset
$Comp
L CONN_3X2 P?
U 1 1 4E567836
P 6950 2200
F 0 "P?" H 6950 2450 50  0000 C CNN
F 1 "CONN_3X2" V 6950 2250 40  0000 C CNN
	1    6950 2200
	1    0    0    -1  
$EndComp
Text Label 7700 2150 2    60   ~ 0
AT_mosi
Text Label 6200 2050 0    60   ~ 0
AT_miso
Text Label 6200 2150 0    60   ~ 0
AT_sck
Text Label 6200 2250 0    60   ~ 0
AT_rst
Text Label 6350 2750 2    60   ~ 0
AT_mosi
Text Label 6350 2850 2    60   ~ 0
AT_miso
Text Label 6350 2950 2    60   ~ 0
AT_sck
Text Label 6900 3900 0    60   ~ 0
AT_rst
$Comp
L +5V #PWR?
U 1 1 4E567835
P 7450 2000
F 0 "#PWR?" H 7450 2090 20  0001 C CNN
F 1 "+5V" H 7450 2090 30  0000 C CNN
	1    7450 2000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4E567834
P 7450 2300
F 0 "#PWR?" H 7450 2300 30  0001 C CNN
F 1 "GND" H 7450 2230 30  0001 C CNN
	1    7450 2300
	1    0    0    -1  
$EndComp
Text Label 6450 3700 2    60   ~ 0
OjitosEmit1
Text Label 6450 3800 2    60   ~ 0
OjitosEmit2
Text Label 6350 4450 2    60   ~ 0
Sole
Text Label 6350 4750 2    60   ~ 0
PULS
Text Label 6450 3600 2    60   ~ 0
EmisPiso
$Comp
L C C?
U 1 1 4E567833
P 6700 4250
F 0 "C?" H 6750 4350 50  0000 L CNN
F 1 "100n" H 6750 4150 50  0000 L CNN
	1    6700 4250
	1    0    0    -1  
$EndComp
Connection ~ 7000 4500
Wire Wire Line
	7000 4550 7000 4150
Wire Wire Line
	6700 4500 6700 4450
Wire Wire Line
	6350 4350 5950 4350
Wire Wire Line
	6350 4150 5950 4150
Wire Wire Line
	7700 2150 7350 2150
Wire Wire Line
	7450 2050 7350 2050
Wire Wire Line
	7450 2000 7450 2050
Wire Wire Line
	5950 3900 6900 3900
Wire Wire Line
	6200 2150 6550 2150
Wire Wire Line
	5950 4550 6350 4550
Wire Wire Line
	5950 3050 6350 3050
Wire Wire Line
	5950 2850 6350 2850
Wire Wire Line
	5950 2650 6350 2650
Wire Wire Line
	5950 2450 6350 2450
Wire Wire Line
	5950 2550 6350 2550
Wire Wire Line
	5950 2750 6350 2750
Wire Wire Line
	5950 2950 6350 2950
Wire Wire Line
	5950 3150 6350 3150
Connection ~ 6700 3900
Wire Wire Line
	6450 3800 5950 3800
Wire Wire Line
	6450 3600 5950 3600
Wire Wire Line
	6350 3400 5950 3400
Wire Wire Line
	3850 2750 3850 2350
Wire Wire Line
	4050 2750 3850 2750
Wire Wire Line
	3900 3500 3900 3600
Wire Wire Line
	3250 2450 3250 2850
Wire Wire Line
	3250 3250 3250 3350
Connection ~ 3950 4750
Wire Wire Line
	4050 4750 3950 4750
Connection ~ 3850 2450
Wire Wire Line
	3950 4650 4050 4650
Wire Wire Line
	3950 4850 3950 4650
Wire Wire Line
	3900 3050 4050 3050
Wire Wire Line
	3900 3100 3900 3050
Wire Wire Line
	4050 2450 3250 2450
Wire Wire Line
	6350 3300 5950 3300
Wire Wire Line
	6350 3500 5950 3500
Wire Wire Line
	6450 3700 5950 3700
Wire Wire Line
	6700 3300 6700 3350
Wire Wire Line
	5950 4650 6350 4650
Wire Wire Line
	6200 2250 6550 2250
Wire Wire Line
	6200 2050 6550 2050
Wire Wire Line
	6800 3900 6800 3950
Connection ~ 6800 3900
Wire Wire Line
	7450 2250 7350 2250
Wire Wire Line
	7450 2300 7450 2250
Wire Wire Line
	6350 4050 5950 4050
Wire Wire Line
	6350 4250 5950 4250
Wire Wire Line
	5950 4450 6350 4450
Wire Wire Line
	6350 4750 5950 4750
Wire Wire Line
	6700 4050 6700 3850
Wire Wire Line
	7000 4500 6700 4500
$EndSCHEMATC
