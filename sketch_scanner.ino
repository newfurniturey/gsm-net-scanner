/**
 * Arduino GSM Network Scanner
 * 
 * This sketch, for the Arduino GSM shield, scans the available
 * GSM networks and displays their signal strength.
 * 
 * Circuit:
 * GSM shield attached to and Arduino
 * SIM card that can place/receive phone calls and
 *   send/receive SMS messages
 */

#include <GSM.h>

/**
 * Your SIM's PIN number, if it requires one
 * @var string
 */
#define PINNUMBER ""
 
/**
 * Library initialization
 */
GSM gsmAccess(true); // include a 'true' parameter for debug enabled
GSMScanner scanner;
GSMModem modemTest;

/**
 * The IMEI (unique identifier) for your GSM modem.
 * @var string
 */
String IMEI = "";

void setup() {
    // initialize serial comms on port 9600
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for the port to connect
    }
    
    Serial.println("GSM networks scanner");
    Serial.println("--------------------");

    // wait for the GSM connection
    Serial.print("Connecting to GSM Network");
    while (gsmAccess.begin(PINNUMBER) != GSM_READY) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("\nConnected!");
    
    // get modem parameters
    // IMEI, modem unique identifier
    Serial.print("Modem IMEI: ");
    IMEI = modemTest.getIMEI();
    IMEI.replace("\n", "");
    if (IMEI != NULL) {
        Serial.println(IMEI);
    }
    
    scanner.begin();
}

void loop() {
    // scan for existing networks, displays a list of networks
    Serial.println("Scanning available networks...");
    Serial.println(scanner.readNetworks());

    // display the network carrier we're currently connected to
    Serial.print("Current carrier: ");
    Serial.println(scanner.getCurrentCarrier());

    // read the signal strength for the current carrier
    // signal strength in 0-31 scale. 31 means power > 51dBm
    // BER is the Bit Error Rate. 0-7 scale. 99=not detectable
    Serial.print("Signal Strength: ");
    Serial.print(scanner.getSignalStrength());
    Serial.println(" [0-31]");
    
    delay(1000);
}
