# DebugHelper
**Simple Debug Helper for Arduino and ESP8266/ESP32.**

This is a simple header file made to simplify debugging Arduino and Espressif (ESP8266 - ESP32) code.

With this helper you can output debug lines through Serial class with a "printf style" using **DEBUG_PRINT** or **DEBUG_PRINT_P** macro.<br />
The first is used with normal strings stored in SRAM, the second is used with strings stored in FLASH declared with PSTR(). The use of F() macro is not supported yet.<br />
The use of PSTR() is allowed only for the first format string. The strings passed as parameters must be stored in SRAM.

Here are some examples <br />
```
DEBUG_PRINT ("This is a DEBUG line\n");     
DEBUG_PRINT_P (PSTR("This is a DEBUG line\n")); 
DEBUG_PRINT_P (PSTR("PIN 2 is %s\n"), (digitalRead(2)?"ON":"OFF"));
DEBUG_PRINT ("Elasped time %lu\n", millis() - lastEvent);
DEBUG_PRINT ("Var 1: %d\nVar 2: %d\n", var1, var2);
DEBUG_PRINT ("\n");
```

**Printf and AVR platform**<br />
Printf is not implemented in AVR platform due to hardware limitations.<br />
In DebugHelper printf is wrapped as described in http://playground.arduino.cc/main/printf<br />
So using DebugHelper you can still use DEBUG_PRINT or DEBUG_PRINT_P within AVR code as well.<br />

In Arduino environment float numbers are not supported inside xxprintf() functions.<br />
Float and Doule variables, if you are using an AVR based board, can be debugged converting them in string

The line<br />
`DEUG_PRINT ("Float value: %4.2f\n", aDouble);`<br />
will work if using Espressif hardware and has to be converted in<br />
`DEBUG_PRINT ("Float value: %s\n", DEBUG_D2STR (aDouble, 4, 2));`<br />
if using AVR hardware.

Anyway, the second line will work also within Espressif code.

**How to use DebugHelper**

To use DebugHelper you just have to copy DebugHelper.h in your project folder and include it in your project<br />
`#include "DebugHelper.h"`<br />
if you save DebugHelper in a folder named DebugHelper stored in your Arduino libraries folder you can use<br />
`#include <DebugHelper.h>'`<br />
just as an Arduino library

If the preprocessor macro<br />
`#define DEBUG_ON`<br />
is defined, debug lines will be compiled otherwise not.<br />

If the preprocessor macro<br />
`#define DEBUG_TIME_MILLIS`<br />
is defined, before the output text DebugHelper will print a time stamp using millis() function.

Use the preprocessor macro<br />
`#define DEBUG_PREFIX`<br />
to define a string as PREFIX to be added in each line. This is done to better point out deug messages.<br />
Example

`#define DEBUG_PREFIX [DEBUG MSG]`<br />
