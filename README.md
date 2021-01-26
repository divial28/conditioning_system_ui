# Conditioning system remote control UI

## Introduction

Application provides convenient interface to control conditioning system. Control UI oriented on touch screens so you can use it even on your smartphone. Also application save representation parameters (size, position, theme and information units) so you don't need to setup Control UI each time you start the application.

## User guide

The application window can be conditionally divided into three zones:
* control zone,
* information zone,
* status zone.

Control zone offers the operator buttons and sliders to change system states and application theme. 
|   Control element   | Description                                                 |
| ------------------- | ----------------------------------------------------------- |
| Power button        | Switches on and off the whole system and other controls     |
| Theme button        | Switches dark and light themes                              |
| Temperature slider  | Control system current temperature from 0&deg;C to 50&deg;C |
| Direction           | Set air direction from 0&deg; to 90&deg;                    |

Information zone represent current temperature, pressure and humidity. Moreover user can change temperature representation (&deg;C, &deg;F, K) and pressure representation (Pa, mm Hg). 

Status zone shows current system status and status of each of three blocks.
| Status color | Description              |
| Green        | Works finу               |
| Yellow       | Some problem was occured |
| Red          | Totally broken           |

## How to connect

Connection is automatic. Conrol UI request all data from system on bootup so you don't need to fo anything. If something goes wrong (status indicators are gray/black) you need to do the following:
* make sure the built-in interface of the air conditioner is working,
* make sure that nothing in your network takes port 5555 which is used to connect remote control with system,
* reboot application
