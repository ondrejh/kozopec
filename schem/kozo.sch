EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Texas_MSP430:MSP430G2231IPW14 U?
U 1 1 5EFEB83B
P 5000 4650
F 0 "U?" H 5000 5631 50  0000 C CNN
F 1 "MSP430G2231IPW14" H 5450 5400 50  0000 C CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 4300 4000 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/msp430g2231.pdf" H 5000 4650 50  0001 C CNN
	1    5000 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5EFEC8F1
P 3950 4000
F 0 "R?" H 4009 4046 50  0000 L CNN
F 1 "10k" H 4009 3955 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 3950 4000 50  0001 C CNN
F 3 "~" H 3950 4000 50  0001 C CNN
	1    3950 4000
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5EFED37A
P 3950 3800
F 0 "#PWR?" H 3950 3650 50  0001 C CNN
F 1 "+3V3" H 3965 3973 50  0000 C CNN
F 2 "" H 3950 3800 50  0001 C CNN
F 3 "" H 3950 3800 50  0001 C CNN
	1    3950 3800
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5EFED89E
P 5000 3750
F 0 "#PWR?" H 5000 3600 50  0001 C CNN
F 1 "+3V3" H 5015 3923 50  0000 C CNN
F 2 "" H 5000 3750 50  0001 C CNN
F 3 "" H 5000 3750 50  0001 C CNN
	1    5000 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 3800 3950 3900
Wire Wire Line
	4050 4200 3950 4200
Wire Wire Line
	5000 3850 5000 3750
$Comp
L Device:R_POT_TRIM RV?
U 1 1 5EFEE97E
P 7600 4900
F 0 "RV?" H 7530 4854 50  0000 R CNN
F 1 "50k" H 7530 4945 50  0000 R CNN
F 2 "" H 7600 4900 50  0001 C CNN
F 3 "~" H 7600 4900 50  0001 C CNN
	1    7600 4900
	-1   0    0    1   
$EndComp
Wire Wire Line
	7350 4750 7350 4900
$Comp
L Device:C_Small C?
U 1 1 5EFF0E73
P 7350 5300
F 0 "C?" H 7442 5346 50  0000 L CNN
F 1 "100n" H 7442 5255 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 7350 5300 50  0001 C CNN
F 3 "~" H 7350 5300 50  0001 C CNN
	1    7350 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 5200 7350 4900
Connection ~ 7350 4900
Wire Wire Line
	7350 4900 7450 4900
$Comp
L power:+3V3 #PWR?
U 1 1 5EFF1E05
P 8500 3050
F 0 "#PWR?" H 8500 2900 50  0001 C CNN
F 1 "+3V3" H 8515 3223 50  0000 C CNN
F 2 "" H 8500 3050 50  0001 C CNN
F 3 "" H 8500 3050 50  0001 C CNN
	1    8500 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 5050 7600 5200
Wire Wire Line
	7350 5400 7350 5500
Wire Wire Line
	5000 5400 5000 5500
$Comp
L power:GND #PWR?
U 1 1 5EFF29B6
P 5000 5500
F 0 "#PWR?" H 5000 5250 50  0001 C CNN
F 1 "GND" H 5005 5327 50  0000 C CNN
F 2 "" H 5000 5500 50  0001 C CNN
F 3 "" H 5000 5500 50  0001 C CNN
	1    5000 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EFF2D2A
P 7350 5500
F 0 "#PWR?" H 7350 5250 50  0001 C CNN
F 1 "GND" H 7355 5327 50  0000 C CNN
F 2 "" H 7350 5500 50  0001 C CNN
F 3 "" H 7350 5500 50  0001 C CNN
	1    7350 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EFF30D9
P 7600 5500
F 0 "#PWR?" H 7600 5250 50  0001 C CNN
F 1 "GND" H 7605 5327 50  0000 C CNN
F 2 "" H 7600 5500 50  0001 C CNN
F 3 "" H 7600 5500 50  0001 C CNN
	1    7600 5500
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:L78L33_SOT89 U?
U 1 1 5EFF363F
P 2600 3100
F 0 "U?" H 2600 3342 50  0000 C CNN
F 1 "L78L33_SOT89" H 2600 3251 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-89-3" H 2600 3300 50  0001 C CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/15/55/e5/aa/23/5b/43/fd/CD00000446.pdf/files/CD00000446.pdf/jcr:content/translations/en.CD00000446.pdf" H 2600 3050 50  0001 C CNN
	1    2600 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EFF5539
P 2600 3500
F 0 "#PWR?" H 2600 3250 50  0001 C CNN
F 1 "GND" H 2605 3327 50  0000 C CNN
F 2 "" H 2600 3500 50  0001 C CNN
F 3 "" H 2600 3500 50  0001 C CNN
	1    2600 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5EFF6421
P 3000 3300
F 0 "C?" H 3092 3346 50  0000 L CNN
F 1 "4u7" H 3092 3255 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 3000 3300 50  0001 C CNN
F 3 "~" H 3000 3300 50  0001 C CNN
	1    3000 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 3400 2600 3500
$Comp
L power:GND #PWR?
U 1 1 5EFF78EA
P 3000 3500
F 0 "#PWR?" H 3000 3250 50  0001 C CNN
F 1 "GND" H 3005 3327 50  0000 C CNN
F 2 "" H 3000 3500 50  0001 C CNN
F 3 "" H 3000 3500 50  0001 C CNN
	1    3000 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3400 3000 3500
Wire Wire Line
	3000 3200 3000 3100
Wire Wire Line
	3000 3100 2900 3100
Wire Wire Line
	3000 3100 3000 3000
Connection ~ 3000 3100
$Comp
L power:+3V3 #PWR?
U 1 1 5EFF8253
P 3000 3000
F 0 "#PWR?" H 3000 2850 50  0001 C CNN
F 1 "+3V3" H 3015 3173 50  0000 C CNN
F 2 "" H 3000 3000 50  0001 C CNN
F 3 "" H 3000 3000 50  0001 C CNN
	1    3000 3000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 5EFF8ABB
P 1900 3200
F 0 "J?" H 1818 2875 50  0000 C CNN
F 1 "Conn_01x02" H 1818 2966 50  0000 C CNN
F 2 "" H 1900 3200 50  0001 C CNN
F 3 "~" H 1900 3200 50  0001 C CNN
	1    1900 3200
	-1   0    0    1   
$EndComp
Wire Wire Line
	2100 3100 2300 3100
$Comp
L power:GND #PWR?
U 1 1 5EFF9E6A
P 2200 3500
F 0 "#PWR?" H 2200 3250 50  0001 C CNN
F 1 "GND" H 2205 3327 50  0000 C CNN
F 2 "" H 2200 3500 50  0001 C CNN
F 3 "" H 2200 3500 50  0001 C CNN
	1    2200 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 3200 2200 3200
Wire Wire Line
	2200 3200 2200 3500
Wire Wire Line
	8600 4550 6550 4550
Wire Wire Line
	8600 4450 6350 4450
$Comp
L power:GND #PWR?
U 1 1 5EFFD6A0
P 8500 5500
F 0 "#PWR?" H 8500 5250 50  0001 C CNN
F 1 "GND" H 8505 5327 50  0000 C CNN
F 2 "" H 8500 5500 50  0001 C CNN
F 3 "" H 8500 5500 50  0001 C CNN
	1    8500 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 5500 8500 4750
Wire Wire Line
	8500 4750 8600 4750
$Comp
L Device:R_Small R?
U 1 1 5F000254
P 6350 3950
F 0 "R?" H 6409 3996 50  0000 L CNN
F 1 "10k" H 6409 3905 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 6350 3950 50  0001 C CNN
F 3 "~" H 6350 3950 50  0001 C CNN
	1    6350 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5F000AE7
P 6550 3950
F 0 "R?" H 6609 3996 50  0000 L CNN
F 1 "10k" H 6609 3905 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 6550 3950 50  0001 C CNN
F 3 "~" H 6550 3950 50  0001 C CNN
	1    6550 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5F000D13
P 6750 3950
F 0 "R?" H 6809 3996 50  0000 L CNN
F 1 "10k" H 6809 3905 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 6750 3950 50  0001 C CNN
F 3 "~" H 6750 3950 50  0001 C CNN
	1    6750 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 4050 6750 4650
Connection ~ 6750 4650
Wire Wire Line
	6750 4650 8600 4650
Wire Wire Line
	6550 4050 6550 4550
Connection ~ 6550 4550
Wire Wire Line
	6350 4050 6350 4450
Connection ~ 6350 4450
Wire Wire Line
	8600 3650 6950 3650
Wire Wire Line
	6950 3650 6950 4250
Connection ~ 8500 3150
Wire Wire Line
	8500 3150 7600 3150
Wire Wire Line
	8600 4050 7350 4050
Wire Wire Line
	7350 4050 7350 4750
Connection ~ 7350 4750
Wire Wire Line
	5950 4250 6950 4250
Wire Wire Line
	5950 4350 7050 4350
Wire Wire Line
	5950 4450 6350 4450
Wire Wire Line
	5950 4550 6550 4550
Wire Wire Line
	5950 4650 6750 4650
Wire Wire Line
	5950 4750 7350 4750
Wire Wire Line
	5950 4850 7150 4850
Text Notes 8900 3700 0    63   ~ 0
PUL+\nPUL-\nDIR+\nDIR-\nENA+\nENA-
$Comp
L Device:R_Small R?
U 1 1 5F036734
P 7600 4250
F 0 "R?" H 7659 4296 50  0000 L CNN
F 1 "4k7" H 7659 4205 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 7600 4250 50  0001 C CNN
F 3 "~" H 7600 4250 50  0001 C CNN
	1    7600 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 4350 7600 4750
$Comp
L Device:R_Small R?
U 1 1 5F0384C8
P 7600 5300
F 0 "R?" H 7659 5346 50  0000 L CNN
F 1 "4k7" H 7659 5255 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 7600 5300 50  0001 C CNN
F 3 "~" H 7600 5300 50  0001 C CNN
	1    7600 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 5400 7600 5500
Wire Wire Line
	8500 3150 8500 3350
Wire Wire Line
	8500 3950 8600 3950
Text Notes 8900 4800 0    63   ~ 0
BACKWARD\nFORWARD\nRELEASE\nGND
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 5F03D693
P 8800 4650
F 0 "J?" H 8718 4225 50  0000 C CNN
F 1 "Conn_01x04" H 8718 4316 50  0000 C CNN
F 2 "" H 8800 4650 50  0001 C CNN
F 3 "~" H 8800 4650 50  0001 C CNN
	1    8800 4650
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 5F03DE39
P 8800 4050
F 0 "J?" H 8880 4092 50  0000 L CNN
F 1 "Conn_01x03" H 8880 4001 50  0000 L CNN
F 2 "" H 8800 4050 50  0001 C CNN
F 3 "~" H 8800 4050 50  0001 C CNN
	1    8800 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 4750 8500 4150
Wire Wire Line
	8500 4150 8600 4150
Connection ~ 8500 4750
Wire Wire Line
	7600 3150 7600 4150
Wire Wire Line
	6750 3850 6750 3750
$Comp
L power:+3V3 #PWR?
U 1 1 5F0523D4
P 6750 3750
F 0 "#PWR?" H 6750 3600 50  0001 C CNN
F 1 "+3V3" H 6765 3923 50  0000 C CNN
F 2 "" H 6750 3750 50  0001 C CNN
F 3 "" H 6750 3750 50  0001 C CNN
	1    6750 3750
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5F054CE8
P 6550 3750
F 0 "#PWR?" H 6550 3600 50  0001 C CNN
F 1 "+3V3" H 6565 3923 50  0000 C CNN
F 2 "" H 6550 3750 50  0001 C CNN
F 3 "" H 6550 3750 50  0001 C CNN
	1    6550 3750
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5F054F59
P 6350 3750
F 0 "#PWR?" H 6350 3600 50  0001 C CNN
F 1 "+3V3" H 6365 3923 50  0000 C CNN
F 2 "" H 6350 3750 50  0001 C CNN
F 3 "" H 6350 3750 50  0001 C CNN
	1    6350 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3750 6350 3850
Wire Wire Line
	6550 3750 6550 3850
$Comp
L Connector_Generic:Conn_01x06 J?
U 1 1 5F057126
P 8800 3450
F 0 "J?" H 8718 2925 50  0000 C CNN
F 1 "Conn_01x06" H 8718 3016 50  0000 C CNN
F 2 "" H 8800 3450 50  0001 C CNN
F 3 "~" H 8800 3450 50  0001 C CNN
	1    8800 3450
	1    0    0    1   
$EndComp
Wire Wire Line
	8500 3050 8500 3150
Wire Wire Line
	8500 3150 8600 3150
Wire Wire Line
	8600 3350 8500 3350
Connection ~ 8500 3350
Wire Wire Line
	8500 3350 8500 3550
Wire Wire Line
	7050 3250 8600 3250
Wire Wire Line
	7050 3250 7050 4350
Wire Wire Line
	8600 3450 7150 3450
Wire Wire Line
	7150 3450 7150 4850
Wire Wire Line
	8600 3550 8500 3550
Connection ~ 8500 3550
Wire Wire Line
	8500 3550 8500 3950
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 5F060DB8
P 6050 3450
F 0 "J?" V 6014 3262 50  0000 R CNN
F 1 "Conn_01x03" V 5923 3262 50  0000 R CNN
F 2 "" H 6050 3450 50  0001 C CNN
F 3 "~" H 6050 3450 50  0001 C CNN
	1    6050 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6050 3650 6050 4100
Wire Wire Line
	6050 4100 5950 4100
Wire Wire Line
	5950 3650 5950 3750
$Comp
L power:GND #PWR?
U 1 1 5F06B385
P 6150 5500
F 0 "#PWR?" H 6150 5250 50  0001 C CNN
F 1 "GND" H 6155 5327 50  0000 C CNN
F 2 "" H 6150 5500 50  0001 C CNN
F 3 "" H 6150 5500 50  0001 C CNN
	1    6150 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3650 6150 5500
Wire Wire Line
	3950 4100 3950 4200
Text GLabel 3850 4200 0    50   Input ~ 0
RESET
Wire Wire Line
	3850 4200 3950 4200
Connection ~ 3950 4200
Text GLabel 5850 3750 0    50   Input ~ 0
RESET
Wire Wire Line
	5850 3750 5950 3750
Text Notes 8900 4200 0    63   ~ 0
V+\nSPEED\nGND
Text Notes 6200 3350 1    63   ~ 0
RESET\nTEST\nGND
$EndSCHEMATC
