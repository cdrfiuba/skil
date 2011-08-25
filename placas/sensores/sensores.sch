EESchema Schematic File Version 2  date jue 25 ago 2011 15:59:27 ART
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
LIBS:cny70
LIBS:sensores-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title "Unamed"
Date "25 aug 2011"
Rev "1.0"
Comp "Club de Robotica"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	2500 5750 2500 5800
Connection ~ 3200 5350
Wire Wire Line
	3000 5250 3000 5350
Wire Wire Line
	3000 5350 6800 5350
Connection ~ 6150 5000
Wire Wire Line
	6150 4200 6150 5150
Wire Wire Line
	6150 5150 5950 5150
Connection ~ 3500 5350
Wire Wire Line
	3500 5300 3500 5350
Connection ~ 4550 5350
Wire Wire Line
	4550 5300 4550 5350
Connection ~ 5700 5350
Wire Wire Line
	5700 5300 5700 5350
Wire Wire Line
	6800 5350 6800 5300
Wire Wire Line
	3200 5350 3200 5150
Wire Wire Line
	3200 5150 3250 5150
Wire Wire Line
	6750 4250 6750 4200
Wire Wire Line
	5600 4250 5600 4200
Wire Wire Line
	4450 4250 4450 4200
Wire Wire Line
	3300 4750 3300 4800
Wire Wire Line
	2350 5900 2800 5900
Wire Wire Line
	4050 6000 3600 6000
Wire Wire Line
	3600 5800 4150 5800
Wire Wire Line
	7100 5900 6650 5900
Wire Wire Line
	5350 5900 5850 5900
Wire Wire Line
	6650 5800 7250 5800
Wire Wire Line
	2500 5800 2800 5800
Wire Wire Line
	7300 5000 6350 5000
Wire Wire Line
	3300 4800 2900 4800
Wire Wire Line
	4050 4800 4450 4800
Wire Wire Line
	5200 4800 5600 4800
Connection ~ 7300 2700
Wire Wire Line
	7700 2800 7700 2700
Wire Wire Line
	7700 2700 3850 2700
Connection ~ 6150 2700
Wire Wire Line
	6150 2700 6150 3000
Connection ~ 4450 2800
Wire Wire Line
	4450 2800 4450 3000
Wire Wire Line
	6750 3000 6750 2800
Wire Wire Line
	6750 2800 3300 2800
Wire Wire Line
	5600 2800 5600 3000
Connection ~ 5600 2800
Wire Wire Line
	3850 2700 3850 3000
Wire Wire Line
	7300 2700 7300 3000
Wire Wire Line
	5000 3000 5000 2700
Connection ~ 5000 2700
Wire Wire Line
	3300 3000 3300 2700
Connection ~ 3300 2800
Wire Wire Line
	3850 4200 3850 5000
Wire Wire Line
	6150 5000 5200 5000
Wire Wire Line
	5000 5000 4050 5000
Wire Wire Line
	3850 5000 2900 5000
Wire Wire Line
	6350 4800 6750 4800
Wire Wire Line
	5850 5800 5550 5800
Wire Wire Line
	4150 5800 4150 5850
Wire Wire Line
	5350 6000 5850 6000
Wire Wire Line
	7250 5800 7250 5850
Wire Wire Line
	7100 6000 6650 6000
Wire Wire Line
	4050 5900 3600 5900
Wire Wire Line
	2350 6000 2800 6000
Wire Wire Line
	3300 4250 3300 4200
Wire Wire Line
	4450 4800 4450 4750
Wire Wire Line
	5600 4800 5600 4750
Wire Wire Line
	6750 4800 6750 4750
Wire Wire Line
	3750 5150 3800 5150
Wire Wire Line
	3800 5150 3800 5000
Connection ~ 3800 5000
Wire Wire Line
	6550 5150 6500 5150
Wire Wire Line
	6500 5150 6500 5350
Connection ~ 6500 5350
Wire Wire Line
	5450 5150 5350 5150
Wire Wire Line
	5350 5150 5350 5350
Connection ~ 5350 5350
Wire Wire Line
	4300 5150 4200 5150
Wire Wire Line
	4200 5150 4200 5350
Connection ~ 4200 5350
Wire Wire Line
	4800 5150 5000 5150
Wire Wire Line
	5000 5150 5000 4200
Connection ~ 5000 5000
Wire Wire Line
	7050 5150 7300 5150
Wire Wire Line
	7300 5150 7300 4200
Connection ~ 7300 5000
Wire Wire Line
	5550 5800 5550 5750
$Comp
L VDD #PWR01
U 1 1 4E569B5F
P 3000 5250
F 0 "#PWR01" H 3000 5350 30  0001 C CNN
F 1 "VDD" H 3000 5360 30  0000 C CNN
	1    3000 5250
	1    0    0    -1  
$EndComp
$Comp
L POT RV4
U 1 1 4E569B00
P 6800 5150
F 0 "RV4" H 6800 5050 50  0000 C CNN
F 1 "POT" H 6800 5150 50  0000 C CNN
	1    6800 5150
	-1   0    0    1   
$EndComp
$Comp
L POT RV3
U 1 1 4E569AFD
P 5700 5150
F 0 "RV3" H 5700 5050 50  0000 C CNN
F 1 "POT" H 5700 5150 50  0000 C CNN
	1    5700 5150
	-1   0    0    1   
$EndComp
$Comp
L POT RV2
U 1 1 4E569AFA
P 4550 5150
F 0 "RV2" H 4550 5050 50  0000 C CNN
F 1 "POT" H 4550 5150 50  0000 C CNN
	1    4550 5150
	-1   0    0    1   
$EndComp
Text Label 2900 5000 0    60   ~ 0
ReceptorA
$Comp
L POT RV1
U 1 1 4E569A81
P 3500 5150
F 0 "RV1" H 3500 5050 50  0000 C CNN
F 1 "POT" H 3500 5150 50  0000 C CNN
	1    3500 5150
	-1   0    0    1   
$EndComp
$Comp
L R R4
U 1 1 4E569A5E
P 6750 4500
F 0 "R4" V 6830 4500 50  0000 C CNN
F 1 "100" V 6750 4500 50  0000 C CNN
	1    6750 4500
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 4E569A5C
P 5600 4500
F 0 "R3" V 5680 4500 50  0000 C CNN
F 1 "100" V 5600 4500 50  0000 C CNN
	1    5600 4500
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 4E569A59
P 4450 4500
F 0 "R2" V 4530 4500 50  0000 C CNN
F 1 "100" V 4450 4500 50  0000 C CNN
	1    4450 4500
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 4E569A46
P 3300 4500
F 0 "R1" V 3380 4500 50  0000 C CNN
F 1 "100" V 3300 4500 50  0000 C CNN
	1    3300 4500
	1    0    0    -1  
$EndComp
Text Label 2350 6000 0    60   ~ 0
ReceptorB
Text Label 2350 5900 0    60   ~ 0
EmisorB
Text Label 4050 5900 2    60   ~ 0
ReceptorA
Text Label 4050 6000 2    60   ~ 0
EmisorA
Text Label 7100 5900 2    60   ~ 0
ReceptorD
Text Label 7100 6000 2    60   ~ 0
EmisorD
Text Label 5350 6000 0    60   ~ 0
ReceptorC
Text Label 5350 5900 0    60   ~ 0
EmisorC
$Comp
L GND #PWR02
U 1 1 4E55787D
P 7250 5850
F 0 "#PWR02" H 7250 5850 30  0001 C CNN
F 1 "GND" H 7250 5780 30  0001 C CNN
	1    7250 5850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 4E557827
P 4150 5850
F 0 "#PWR03" H 4150 5850 30  0001 C CNN
F 1 "GND" H 4150 5780 30  0001 C CNN
	1    4150 5850
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR04
U 1 1 4E557820
P 5550 5750
F 0 "#PWR04" H 5550 5850 30  0001 C CNN
F 1 "VDD" H 5550 5860 30  0000 C CNN
	1    5550 5750
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR05
U 1 1 4E5577C8
P 2500 5750
F 0 "#PWR05" H 2500 5850 30  0001 C CNN
F 1 "VDD" H 2500 5860 30  0000 C CNN
	1    2500 5750
	1    0    0    -1  
$EndComp
$Comp
L CONN_3X2 P2
U 1 1 4E5573AF
P 6250 5950
F 0 "P2" H 6250 6200 50  0000 C CNN
F 1 "CONN_3X2" V 6250 6000 40  0000 C CNN
	1    6250 5950
	1    0    0    -1  
$EndComp
$Comp
L CONN_3X2 P1
U 1 1 4E55739B
P 3200 5950
F 0 "P1" H 3200 6200 50  0000 C CNN
F 1 "CONN_3X2" V 3200 6000 40  0000 C CNN
	1    3200 5950
	1    0    0    -1  
$EndComp
Text Label 6350 5000 0    60   ~ 0
ReceptorD
Text Label 6350 4800 0    60   ~ 0
EmisorD
Text Label 5200 5000 0    60   ~ 0
ReceptorC
Text Label 5200 4800 0    60   ~ 0
EmisorC
Text Label 4050 5000 0    60   ~ 0
ReceptorB
Text Label 4050 4800 0    60   ~ 0
EmisorB
Text Label 2900 4800 0    60   ~ 0
EmisorA
$Comp
L GND #PWR06
U 1 1 4E5570A3
P 7700 2800
F 0 "#PWR06" H 7700 2800 30  0001 C CNN
F 1 "GND" H 7700 2730 30  0001 C CNN
	1    7700 2800
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR07
U 1 1 4E557097
P 3300 2700
F 0 "#PWR07" H 3300 2800 30  0001 C CNN
F 1 "VDD" H 3300 2810 30  0000 C CNN
	1    3300 2700
	1    0    0    -1  
$EndComp
$Comp
L CNY70 U4
U 1 1 4E556FC3
P 7050 3600
F 0 "U4" H 7000 3150 60  0000 C CNN
F 1 "CNY70" H 7000 4050 60  0000 C CNN
	1    7050 3600
	1    0    0    -1  
$EndComp
$Comp
L CNY70 U3
U 1 1 4E556FBD
P 5900 3600
F 0 "U3" H 5850 3150 60  0000 C CNN
F 1 "CNY70" H 5850 4050 60  0000 C CNN
	1    5900 3600
	1    0    0    -1  
$EndComp
$Comp
L CNY70 U2
U 1 1 4E556FAE
P 4750 3600
F 0 "U2" H 4700 3150 60  0000 C CNN
F 1 "CNY70" H 4700 4050 60  0000 C CNN
	1    4750 3600
	1    0    0    -1  
$EndComp
$Comp
L CNY70 U1
U 1 1 4E556FA9
P 3600 3600
F 0 "U1" H 3550 3150 60  0000 C CNN
F 1 "CNY70" H 3550 4050 60  0000 C CNN
	1    3600 3600
	1    0    0    -1  
$EndComp
$EndSCHEMATC
