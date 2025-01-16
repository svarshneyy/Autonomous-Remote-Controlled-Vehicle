//------------------------------------------------------------------------------

//  Description: Contains functions that initialize serial configurations for UCA0 and UCA1,
//  UCA0 and UCA1 interrupt configurations,
//  and a function that process transmissions from UCA0 (IOT module).

//  Sanchit Varshney
//  Nov 2024
//  Built with Code Composer Version: 12.8

//------------------------------------------------------------------------------


#include  "msp430.h"
#include  <string.h>
#include  "macros.h"

extern volatile unsigned int Time_Sequence;
extern volatile unsigned char display_changed;
extern unsigned char state;
volatile unsigned char iot_receive;
volatile unsigned char IOT_Ring_Rx[LARGE_RING_SIZE];
volatile unsigned char iot_TX_buf[LARGE_RING_SIZE];
volatile unsigned int iot_tx;
volatile unsigned char usb_value;
volatile unsigned char USB_Ring_Rx[SMALL_RING_SIZE];
volatile unsigned char AT[5][LARGE_RING_SIZE] = {
                                    "AT+SYSSTORE=0\r\n",
                                    "AT+CIPMUX=1\r\n",
                                    "AT+CIPSERVER=1,8888\r\n",
                                    "AT+CIFSR\r\n",
                                    "AT+PING=\"www.google.com\"\r\n"
};
unsigned int character;
unsigned int currCharacter;
unsigned int line;
unsigned int nextline;
int ipLine;
unsigned int boot_state;
extern char display_line[4][11];
volatile unsigned char IOT_Data[4][PROCESS_SIZE];
int IOT_parse;
unsigned int IOT_state;
unsigned int ip_address_found;
volatile unsigned char ip_address[17];
int test_Value;
volatile unsigned char IOT_2_PC[SMALL_RING_SIZE];
volatile unsigned int iot_rx_wr;
unsigned int iot_rx_rd; // Only used in Main
unsigned int direct_iot; // Only used it Interrupt
volatile unsigned char PC_2_IOT[SMALL_RING_SIZE];
volatile unsigned int usb_rx_wr;
unsigned int usb_rx_rd; // Only used in Main
unsigned int direct_usb; // Only used it Interrupt
unsigned int currentAT;
extern volatile unsigned int Time_Sequence1;
unsigned int cmd;
unsigned int cmdLine;
unsigned int thousand;
unsigned int hundred;
unsigned int ten;
unsigned int one;
unsigned int travelTime;
extern unsigned int seconds;
extern unsigned int moveTimer;
extern unsigned char state;
unsigned int movement;
extern unsigned int detect;
extern unsigned int ping;
extern unsigned int caliStatus;


void Init_Serial_UCA0(char speed){          // Initialize configurations for UCA0

    //------------------------------------------------------------------------------
    // TX error (%) RX error (%)
    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
    // 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
    // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
    // 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
    // 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
    // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
    // 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
    //------------------------------------------------------------------------------

    // Configure eUSCI_A0 for UART mode
    UCA0CTLW0 = 0;
    UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
    UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
    UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
    UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
    UCA0CTLW0 &= ~UCPEN; // No Parity
    UCA0CTLW0 &= ~UCSYNC;
    UCA0CTLW0 &= ~UC7BIT;
    UCA0CTLW0 |= UCMODE_0;
    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
    // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
    // UCA?MCTLW = UCSx + UCFx + UCOS16

    //UCA0BRW = 4 ; // 115,200 baud
    //UCA0MCTLW = 0x5551 ;

    switch (speed) {
    case '1':  // 4800 baud
        UCA0BRW = 104;
        UCA0MCTLW = 0xD621;
        break;
    case '2':  // 9600 baud
        UCA0BRW = 52;
        UCA0MCTLW = 0x4911;
        break;
    case '3':  // 19200 baud
        UCA0BRW = 26;
        UCA0MCTLW = 0xB601;
        break;
    case '4':  // 57600 baud
        UCA0BRW = 8;
        UCA0MCTLW = 0xF711;
        break;
    case '5':  // 115200 baud
        UCA0BRW = 4;
        UCA0MCTLW = 0x5551;
        break;
    case '6':  // 460800 baud
        UCA0BRW = 17;
        UCA0MCTLW = 0x4A00;
        break;
    default:   // Default to 115200 baud if unknown speed
        UCA0BRW = 4;
        UCA0MCTLW = 0x5551;
        break;
    }

    UCA0CTLW0 &= ~UCSWRST ; // release from reset
    UCA0TXBUF = 0x00; // Prime the Pump
    UCA0IE |= UCRXIE; // Enable RX interrupt
    //------------------------------------------------------------------------------
}

void Init_Serial_UCA1(char speed){          // Initialize configurations for UCA1

    //------------------------------------------------------------------------------
    // TX error (%) RX error (%)
    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
    // 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
    // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
    // 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
    // 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
    // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
    // 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
    //------------------------------------------------------------------------------
    // Configure eUSCI_A0 for UART mode
    UCA1CTLW0 = 0;
    UCA1CTLW0 |= UCSWRST ; // Put eUSCI in reset
    UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
    UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
    UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
    UCA1CTLW0 &= ~UCPEN; // No Parity
    UCA1CTLW0 &= ~UCSYNC;
    UCA1CTLW0 &= ~UC7BIT;
    UCA1CTLW0 |= UCMODE_0;
    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
    // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
    // UCA?MCTLW = UCSx + UCFx + UCOS16

    //UCA1BRW = 4 ; // 115,200 baud
    //UCA1MCTLW = 0x5551 ;

    switch (speed) {
    case '1':  // 4800 baud
        UCA1BRW = 104;
        UCA1MCTLW = 0xD621;
        break;
    case '2':  // 9600 baud
        UCA1BRW = 52;
        UCA1MCTLW = 0x4911;
        break;
    case '3':  // 19200 baud
        UCA1BRW = 26;
        UCA1MCTLW = 0xB601;
        break;
    case '4':  // 57600 baud
        UCA1BRW = 8;
        UCA1MCTLW = 0xF711;
        break;
    case '5':  // 115200 baud
        UCA1BRW = 4;
        UCA1MCTLW = 0x5551;
        break;
    case '6':  // 460800 baud
        UCA1BRW = 17;
        UCA1MCTLW = 0x4A00;
        break;
    default:   // Default to 115200 baud if unknown speed
        UCA1BRW = 4;
        UCA1MCTLW = 0x5551;
        break;
    }

    UCA1CTLW0 &= ~UCSWRST ; // release from reset
    UCA1TXBUF = 0x00; // Prime the Pump
    UCA1IE |= UCRXIE; // Enable RX interrupt
    //------------------------------------------------------------------------------
}


#pragma vector=EUSCI_A0_VECTOR          // Interrupt configurations for UCA0 receive and transmit
__interrupt void eUSCI_A0_ISR(void){

    switch(__even_in_range(UCA0IV,0x08)){

    case 0: // Vector 0 - no interrupt
        break;

    case 2:{ // Vector 2   Rx0IFG
        iot_receive = UCA0RXBUF;
        IOT_Ring_Rx[iot_rx_wr++] = iot_receive; // Add to Ring Buffer
        if(iot_rx_wr >= sizeof(IOT_Ring_Rx)){
            iot_rx_wr = BEGINNING;
        }
        //UCA1IE |= UCTXIE;
        //UCA1TXBUF = iot_receive;
    }break;

    case 4:{ // Vector 4   Tx0IFG
        UCA0TXBUF = iot_TX_buf[iot_tx];
        iot_TX_buf[iot_tx++] = 0;
        if(iot_TX_buf[iot_tx] == 0x00){
            UCA0IE &= ~UCTXIE;
            iot_tx = 0;
        }
    }break;


    default: break;

    }
}

#pragma vector = EUSCI_A1_VECTOR            // Interrupt configurations for UCA1 receive and transmit
__interrupt void eUSCI_A1_ISR(void){

    switch(__even_in_range(UCA1IV,0x08)){

    case 0: // Vector 0 - no interrupt
        break;

    case 2:{ // Vector 2 - Rx1IFG
        usb_value = UCA1RXBUF;
        USB_Ring_Rx[usb_rx_wr++] = usb_value; // Add to Ring Buffer
        if(usb_rx_wr >= sizeof(USB_Ring_Rx)){
            usb_rx_wr = BEGINNING;
        }
        //UCA0TXBUF = usb_value;
        //UCA0IE |= UCTXIE;
    }break;
    case 4:{ // Vector 4 - TX1IFG
        UCA1TXBUF = IOT_Ring_Rx[direct_iot++];
        // IOT_Ring_Rx[direct_iot++]= 0;
        if(direct_iot >= sizeof(IOT_Ring_Rx)){
            direct_iot = BEGINNING;
        }
        if(iot_rx_wr == direct_iot){
            UCA1IE &= ~UCTXIE;
        }
    }break;


    default: break;
    }
}


void IOT_Process(void) { // Processes IOT messages

    unsigned int i, j;
    unsigned int iot_rx_wr_temp;
    iot_rx_wr_temp = iot_rx_wr;

    if (!boot_state){
        if (Time_Sequence < 25) {
            strcpy(display_line[0], "   IOT    ");
            strcpy(display_line[1], "   OFF    ");
            display_changed = TRUE;
            P3OUT &= ~IOT_EN;
            P2OUT |= IOT_RUN_RED; // Red LED ON
            P3OUT &= ~IOT_LINK_GRN; // Green LED OFF
        }

        else if (Time_Sequence < 50) {
            strcpy(display_line[0], "   IOT    ");
            strcpy(display_line[1], "   ON     ");
            display_changed = TRUE;
            P3OUT |= IOT_EN;
            P2OUT &= ~IOT_RUN_RED; // Red LED OFF
            P3OUT |= IOT_LINK_GRN; // Green LED ON
        }
    }


    if (ip_address_found == 1){ //Place IP Address on display
        strcpy(display_line[2], "          ");
        strcpy(display_line[3], "          ");
        i = 0;
        while (ip_address[i] != '\0'){
            if (i < 10){
                display_line[2][i] = ip_address[i];
            }
            else{
                display_line[3][i-10] = ip_address[i];
            }
            i++;
        }
        if(!caliStatus){
            strcpy(display_line[0], "   ncsu   ");
            strcpy(display_line[1], "          ");
        }
        else{
            strcpy(display_line[0], " Waiting  ");
            strcpy(display_line[1], "for input ");
        }


        display_changed = TRUE;
        ip_address_found++;
        boot_state = 1;
    }

    if ((ping) && (currentAT == 5)){
        for (i = 0; i < 32; i++) {
            iot_TX_buf[i] = AT[4][i];
        }
        UCA0IE |= UCTXIE;
        ping = 0;
    }

    if (iot_rx_wr_temp != iot_rx_rd) { // Determine if IOT is available
        IOT_Data[line][character++] = IOT_Ring_Rx[iot_rx_rd++];
        if (iot_rx_rd >= sizeof(IOT_Ring_Rx)) {
            iot_rx_rd = BEGINNING;
        }
        currCharacter = character - 1;
        if (IOT_Data[line][currCharacter] == 0x0A){
            character = 0;
            if (currCharacter > 1){
                line++;
                if (line >= 4) {
                    line = 0;
                }
                nextline = line + 1;
                if (nextline >= 4) {
                    nextline = 0;
                }
            }
            else {
                IOT_Data[line][0] = '0';
                IOT_Data[line][1] = '0';
            }
        }
        else {
            switch (currCharacter) {
            case 1:
                if (IOT_Data[line][currCharacter] == 'K') { // "O" "K": Check which AT command to run after first
                    if ((0 < currentAT) && (currentAT < 4)) {
                        for (i = 0; i < 26; i++) {
                            iot_TX_buf[i] = AT[currentAT][i];
                        }
                        UCA0IE |= UCTXIE;
                    }
                    else if (currentAT == 4) {
                        for (i = 0; i < sizeof(ip_address); i++) {
                            ip_address[i] = 0;
                        }
                        ip_address_found++;
                        ipLine = line - 2;
                        if (ipLine < 0) ipLine += 4;

                        j = 0;
                        int copying = 0;

                        for (i = 0; i < sizeof(IOT_Data[ipLine]); i++) {

                            if (IOT_Data[ipLine][i] == 0x22) {

                                if (copying) {
                                    ip_address[j] = '\0';
                                    break;
                                }
                                else {
                                    copying = 1;
                                    continue;
                                }
                            }

                            if (copying) {
                                ip_address[j++] = IOT_Data[ipLine][i];
                            }
                        }
                    }
                    currentAT++;
                }


                break;

            case 5:
                if (IOT_Data[line][currCharacter] == 'G') { // WIFI "G"OT IP: start first AT command
                    for (i = 0; i < 26; i++) {
                        iot_TX_buf[i] = AT[currentAT][i];
                    }
                    UCA0IE |= UCTXIE;
                    currentAT++;
                }
                break;

            case 14:
                if (IOT_Data[line][currCharacter] == 'I'){

                    if ((IOT_Data[line][currCharacter - 5] == '^')
                            && (IOT_Data[line][currCharacter - 4] == '1')
                            && (IOT_Data[line][currCharacter - 3] == '6')
                            && (IOT_Data[line][currCharacter - 2] == '2')
                            && (IOT_Data[line][currCharacter - 1] == '9')){

                        state = BL_START;
                        Time_Sequence = 0;
                        detect = 0;

                    }
                }

                if (IOT_Data[line][currCharacter] == 'E'){

                    if ((IOT_Data[line][currCharacter - 5] == '^')
                            && (IOT_Data[line][currCharacter - 4] == '1')
                            && (IOT_Data[line][currCharacter - 3] == '6')
                            && (IOT_Data[line][currCharacter - 2] == '2')
                            && (IOT_Data[line][currCharacter - 1] == '9')){

                        state = BL_EXIT;
                        Time_Sequence = 0;
                    }
                }
                break;

            case 16:
                if (IOT_Data[line][currCharacter] == 0x0D){
                    if ((IOT_Data[line][currCharacter - 1] - '0') < 10 ){


                        if ((IOT_Data[line][currCharacter - 7] == '^')
                                && (IOT_Data[line][currCharacter - 6] == '1')
                                && (IOT_Data[line][currCharacter - 5] == '6')
                                && (IOT_Data[line][currCharacter - 4] == '2')
                                && (IOT_Data[line][currCharacter - 3] == '9')){


                            //print 0X on screen
                            strcpy(display_line[0], "Arrived 0X");
                            display_line[0][9] = IOT_Data[line][currCharacter - 1];

                            display_changed = TRUE;

                        }

                    }

                }
                break;


            case 19:{ //movement cmd
                if ((IOT_Data[line][currCharacter] - '0') < 10){


                    if ((IOT_Data[line][currCharacter - 9] == '^')
                            && (IOT_Data[line][currCharacter - 8] == '1')
                            && (IOT_Data[line][currCharacter - 7] == '6')
                            && (IOT_Data[line][currCharacter - 6] == '2')
                            && (IOT_Data[line][currCharacter - 5] == '9')){

                        thousand = ((IOT_Data[line][currCharacter - 3]) - '0') * 1000;
                        hundred =  ((IOT_Data[line][currCharacter - 2]) - '0') * 100;
                        ten =      ((IOT_Data[line][currCharacter - 1]) - '0') * 10;
                        one =      ((IOT_Data[line][currCharacter]) - '0');

                        travelTime = thousand + hundred + ten + one;
                        moveTimer = 0;

                        switch (IOT_Data[line][currCharacter - 4]) {
                        case 'F':
                            PWM_LF_RF_LR_RR('s', 's', 'o', 'o');
                            movement = 1;
                            break;

                        case 'B':
                            PWM_LF_RF_LR_RR('o', 'o', 's', 's');
                            movement = 1;
                            break;

                        case 'R':
                            PWM_LF_RF_LR_RR('o', 's', 'o', 'o');
                            movement = 1;
                            break;

                        case 'L':
                            PWM_LF_RF_LR_RR('s', 'o', 'o', 'o');
                            movement = 1;
                            break;

                        default:
                            break;
                        }

                        if (movement){


                            strcpy(display_line[0], "Arrived 0 ");
                            strcpy(display_line[1], " Sanchit  ");
                            strcpy(display_line[2], " Varshney ");
                            strcpy(display_line[3], "          ");
                            display_line[3][0] = IOT_Data[line][currCharacter - 4];
                            display_line[3][1] = IOT_Data[line][currCharacter - 3];
                            display_line[3][2] = IOT_Data[line][currCharacter - 2];
                            display_line[3][3] = IOT_Data[line][currCharacter - 1];
                            display_line[3][4] = IOT_Data[line][currCharacter];

                            display_changed = TRUE;

                        }
                    }
                }
            }

            default:
                break;
            }
        }
    }

    if ((travelTime <= moveTimer) && (movement)){
        PWM_LF_RF_LR_RR('o','o','o','o');
        travelTime = 0;
        movement = 0;
    }

}


