#ifndef CONSTANTS_H
#define CONSTANTS_H

//#include "Logging.h"


/*****************************************************************************/
/* GENERAL                                                                   */
/*****************************************************************************/

// TOREMEMEBER: Version inical con dos motores. Se elimina la manopla, 
// que movería los tres dedos restantes de la mano

// Identifies open position
#define OPEN                  0
// Identifies close position
#define CLOSE                 1

// Number of finger elements
#define FINGERS               2

// Identifies mitten fingers
#define THUMB                 0
// Identifies forefinger finger 
#define FOREFINGER            1

//Identifies thumb finger
//#define MITTEM              2

/*************************************************************************/
/* STATES                                                                */
/*************************************************************************/

// TOREMEMEBER: Version inical con dos motores. Solamente tendremos los  
// estados STATE_INACTIVE, STATE_IDLE, STATE_TONGS (equivalente a abierto/cerrado).

// State Number
#define STATES_NUMBER                  3

// Para yuna versión inicial,
// Inactive state 
#define STATE_INACTIVE                 0
// Resting/Initial state. Open hand
#define STATE_IDLE                     1
// Tongs state. Thumb + forefinger
#define STATE_TONGS                    2
// Finger state. Forefinger
// #define STATE_FINGER                3
// Close state. Mitten + forefinger
// #define STATE_CLOSE                 4
// Fist state. Mitten + forefinger + thumb
//#define STATE_FIST                   5


/*************************************************************************/
/* TRANSITIONS                                                           */
/*************************************************************************/

// TOREMEMEBER: Version inical con dos motores. Solamente transicionaremos  
// entre STATE_INACTIVE, STATE_IDLE, STATE_TONGS (equivalente a abierto/cerrado).

// Transition Number
#define TRANSITIONS_NUMBER             3

// No identified movement intention
// or no movement to perform
#define TRANSITION_TO_NOTHING          -1
// Transition to inactive state
#define TRANSITION_TO_INACTIVE         0
// Transition to resting/initial state
#define TRANSITION_TO_IDLE             1
// Transition to Tongs state
#define TRANSITION_TO_TONGS            2
// Transition to finger state
// #define TRANSITION_TO_FINGER        3
// Transition to close state
// #define TRANSITION_TO_CLOSE         4
// Transition to fist state
// #define TRANSITION_TO_FIST          5
// No identified movement intention

// Fingers position matrix from states definition
// TOREMEMBER: Adaptada a los estados y motores actuales
const int FINGER_POSITION_MATRIX[STATES_NUMBER][FINGERS] = {

    //THUMB  FORE   
    { OPEN,  OPEN  },  // STATE_INACTIVE
    { OPEN,  OPEN  },  // STATE_IDLE
    { CLOSE, CLOSE }   // STATE_TONGS
};

/*************************************************************************/
/* MOTORS/FINGERS                                                        */
/*************************************************************************/

// ¿TODO?: Límites de velocidad de los motores
// ARDUINO
// Min Value for motors speed
#define MOTOR_SPEED_MIN   0
// Max Value for motors speed
#define MOTOR_SPEED_MAX  255
// CONFIGURABLE VALUE: Motor Speed
#define MOTOR_SPEED      100


/*************************************************************************/
/*  PID FUNCTION                                                         */
/*************************************************************************/
// TODO: Tuning PID parameters
// Initial Proportional Gain
#define PID_KP 6
// Initial Integral Gain
#define PID_KI 0
// Initial Differential Gain
#define PID_KD 0
// Defines how fast our PID loop runs
#define PID_LIMITS 30


/*****************************************************************************/
/* PIN DESCRIPTION                                                           */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* OUTPUT                                                                    */
/*---------------------------------------------------------------------------*/ 

// OUTPUT pin for LED RGB
#define PIN_LED_RGB      17

// THUMB MOTOR + POT
// INA
#define PIN_MOT_A_0      18
//INB
#define PIN_MOT_B_0      19
// PWM
#define PIN_MOT_EN_0      4
// POT
#define PIN_MPOT_0       27

// FOREFINGER MOTOR
// INA
#define PIN_MOT_A_1      25
// INB
#define PIN_MOT_B_1      14
// PWM
#define PIN_MOT_EN_1      5
// POT
#define PIN_MPOT_1       32

// Sensors
#define PIN_MSEN_0       12
#define PIN_MSEN_1       33

// Switch
#define PIN_SW_0         16

// I2C PWM CIRCUITS (motors activation)
// https://en.wikipedia.org/wiki/I%C2%B2C
// SDA: I2C Data
#define PIN_SDA          21
// SCL: I2C Clock
#define PIN_SCL          22


#define A 0
#define B 1
const int MOTOR_CONTROL_MATRIX[FINGERS][2] = {
      // THUMB      // FORE 
    { PIN_MOT_A_0, PIN_MOT_B_0},  // A 
    { PIN_MOT_A_1, PIN_MOT_B_1}   // B 
};


/*****************************************************************************/
/* Configuration - FUNCTION MODE                                             */
/*****************************************************************************/

// Pruebas unitarias con los difernetes elementos de la placa
#define TEST_MODE_BOARD             0

// Ploteo de la MYO (requiere conexión al brazalete)
#define TEST_MODE_MYO_EMG_OUTPUT    1

// Detección de estados con la MYO (requiere conexión al brazalete)
#define TEST_MODE_MYO_STATES       2

// Dentro del flujo de operación normal, transcionamos con el teclado
#define TEST_MODE_TRANSITIONS      3

//Myo operative control (requiere conexión al brazalete)
#define OPERATION_MODE             4


/*****************************************************************************/
/* Configuration - Constants                                                   */
/*****************************************************************************/
const int mode = TEST_MODE_TRANSITIONS;

/*****************************************************************************/
/* Configuration - BLE                                                        */
/*****************************************************************************/
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"


/*****************************************************************************/
/* Configuration - WIFI                                                      */
/*****************************************************************************/
#define MYO_SSID                "MIWIFI_6gJX"
#define MYO_PASSWORD            "pFh47rtH"
#define MYO_HOST                "esp32"

#endif
