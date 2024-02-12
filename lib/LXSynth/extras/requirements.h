

/** CONTROLLERS:
 * 
 * @brief
 * Controllers exist to read current values from hardware of software(mock hardware)
 * Controllers are managed in a central repository called a ControllerManager
 * 
 * REQUIREMENTS:
 * Measure and store values from hardware / software
 * Be pollable via the "Update()" method
 * Track whether changed since last poll
 * Track which parameters the controller is assigned to
 * can connect to one or more parameter values
 * update connected parameter values
 * debouncing (i.e. ignore changes for 'x' milliseconds after a change has occurred)
 * 
 * be re-assignable to any parameters on the fly
 * handle digital and analog hardware readings (switchable) / determined by explicit controller class
 * 
 * HWCONTROLLER:
 * Derived classes for Buttons, Rotary Knobs, Potentiometers
 * Poll on digital interrupt trigger
 * Poll on analog interrupt trigger
 * 
 * MIDICONTROLLER:
 * read values from MidiCC
 * 
 * SWCONTROLLER:
 * generate random readings in the absence of hardware
 * Read Soft-inputs
 */

/** REQUIREMENTS:...MODULES:
 * @brief
 * A Module is a synthesizer module which is a collection of parameters and audio library components
 * Changes to the value of parameters should cause the necessary changes to connected audio library components.
 * 
*/

/** REQUIREMENTS:...PARAMETERS:
 * 
 * 
 * 
 * 
 * 
 * 
 * 
*/

/**
 * REQUIREMENTS:
 * SYNTH:
 * Manages a list of all: 
 *      modules
 *      controllers
 *      parameters
 *      scenes
 */

//TODO