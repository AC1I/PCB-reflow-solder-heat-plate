# PCB reflow solder heat plate modifications by AC1I

## Introduction

I purchaced a manufactured unit off Tindie, powered it up, and promptly blew the internal fuse. 
The vendors reply was to the effect "Your power supply is too powerful, you need to purchace a 
power supply with a maximum output current of less than the rating of the fuse, then the fuse will stop blowing".
Since this is effectively the same as moving the overcurrent from the heat plate to the power supply, I looked for a better answer. 
What follows is my work around.

### Other Issues
My solder plate blew the IRLR8726TRPBF MOSFET shortly after arrival. This was most likely due to a cold solder 
joint on the source pin. I can see this happening as this component is a big heat sink and may not have been 
heated adequately during assembly. I would recommend that you reheat this components connections prior to use.

### Feature list

- User configurable maximum duty cycle (to limit the maximum current consumption).
- Improved temperature calculation based upon LMT85 data sheet (Still slugish)
- Enhanced debugging interface via the serial debugging interface supplied with the board.
- Support for additional digital sensors for temperature calibration.
- Use of the dual color LED (green = power, orange = heating, red = hot)

### Building your own

You will require the Arduino IDE, and a UDPI programmer (I used an Adafruit UPDI Friend). 
I did not update the Platform IO code.


Optionally, you may choose to install a DS18B20Z temperature sensor (temp2) and supply a DS18B20Z probe (temp3) if you desire 
to confirm/tweek the temperature calculations. A gerber file for the serial debugging interface is provided if you 
desire to utilize the serial debugger.

- Connect the UDPI programmer via a 3 pin male header to the PCB. (Do not solder the header, a friction fit is just fine),
- Build and upload the new firmware utilizing the configuration described in the README.MD
- You will be prompted for the board settings after upload. 

The board resistance should be written on the back of the PCB. 

The Maximum PWM value is the constraint that prevents us from drawing more the 5 amps. 0 indicates a 100% duty cycle, 
increasing values limit the duty cycle. If a value of 0 is used, the software will monitor the incoming voltage for a 
voltage drop, indicating the current is being limited by the supply and will automatically back off the duty cycle to 
prevent overloading the supply and tripping the fuse. This will work with constant current power supplies and should work 
if you use the vendor recommended undersized power supply. If you have an ammeter connected, the target current draw is 
ideally 4.75 amps.
- You may reenter the setup menus at any time by power cycling the board, and pressing both buttons during the 
logo display.

### Serial Commands
This software supports three serial debugging commands:
- 'c' Create a CSV file of temperature readings across the temperature range of the DS18B20Z (Limited to 125C). 
If you place the DS18B20Z temperature probe on the center of the PCB, you can use this to measure the temperature 
difference between the plate temperature and the indicated temperature from the LMT85 (which is locate along side 
the heated area).
- 'd' Toggle output of debug print messages.
- 'e' Run the evaluate_heat() routine
- 't' Print current temperature reading(s) of the LMT85 and the optional DS18B20Z.

## Conclusion
I can't say that I am happy with my purchace of this item. I spent numerous hours attempting to make it usable; But if 
you find yourself in the same situation as I, this should at least make the product functional.

I hope you find this useful.
