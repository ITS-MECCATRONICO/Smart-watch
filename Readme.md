## PINOUT SPONDA

PIN | FUNZIONE |
----|----------|
0 | NONE
1 | NONE
2 | EMERGENZA
3 | GIU'
4 | RELE' C
5 | RELE' LED
6 | RELE' B
7 | SU
8 | RELE' A
9 | RELE' D
10 | FINECORSA SINISTRA SU
11 | FINECORSA SINISTRA GIU
12 | FINECORSA DESTRA SU
13 | FINECORSA DESTRA GIU
|
A0 | NONE
A1 | NONE
A2 | NONE
A3 | NONE
A4 | NONE
A5 | NONE

## REGOLE SPONDA

PREMO EMERGENZA
- STACCO R_C, R_D CONTEMPORANEAMENTE.
- LAMPEGGIO R_LED 2 SEC

RIARMO EMERGENZA
- ATTACCO R_D CONTEMPORANEAMENTE
- ATTENDO COMANDO MANUALE DA PULSANTIRA PER ATTACCARE R_C E SWITCCARE R_A, R_B

PREMO SU
- CONTROLLO FINECORSA
- STACCO R_C
- ATTACCO R_A, R_B CONTEMPORANEAMENTE
- ATTACCO R_C

PREMO GIU
- CONTROLLO FINECORSA
- STACCO R_C
- STACCO R_A, R_B CONTEMPORANEAMENTE
- ATTACCO R_C

FINECORSA
- STACCO R_C


## DIMENSIONE ZENER

TENSIONE DI ALIMENTAZIONE - TESIONE DI ZENER
12V - 3,3V = 8,7v
20mA in ingresso

R = V / I
R = 8,7 / 0,02 = 435 ohm --> 470 ohm
