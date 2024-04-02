# max7219-esp8266-reminder-clock
After being disappointed by a couple of humidity monitors, I bought parts and made my own! I used [BME-280](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/) module. 
The module measures humidity, temperature, and atmospheric pressure. 
Video:
[![Youtube Video LLc_6Z9A93Y](https://img.youtube.com/vi/u_jhNoErJXI/0.jpg)](https://www.youtube.com/watch?v=u_jhNoErJXI)

## Components
I got the following but feel free to switch and swap based on availability and pricing.
* ESP8266 - https://www.amazon.ca/gp/product/B07S5Z3VYZ
* Buzzer Alarm Sound Module - https://www.amazon.com/dp/B07MPYWVGD
* I2C 2004 LCD - https://www.amazon.com/dp/B0C1G9GBRZ
* BME-280 - https://www.amazon.com/dp/B0CG95GVVD
* Breadboard - https://www.amazon.com/dp/B0CC2Q9HKD
* Micro usb to DIP module - https://www.amazon.ca/dp/B07X86YFFN
* Plastic box - I bought one from Dollarama. Any plastic box should do. They can typically be drilled and cut using a hot paper cutter.

## Assembly
* Connect the LCD 2004 and BME-280 on the ESP's I2C bus.
* I connected LCD to a separate Micro USB to DIP module to avoid power surge (not sure if it does cause a surge) on USB port.
* Connect BME-280 to ESP's 3.3v pins
* Connect Buzzer to ESP's 3.3v pins
* Connect Buzzer to D7 or your favorite GPIO pin, but you'd need to change RELAY_PIN in code if you connec it to a pin other than D7.
* Drill holes and mount everything!

Let me know if a diagram would help and I'd add one.

## Functionality
* Upon start, the program initializes the LCD, finds the sensor on I2C bus, and looks for Wifi (you'd have to configure Wifi credentials in code).
* Once connected to Wifi, it syncs time.
* The LCD shows day, and date in row 1.
* Time and alerts are shows in row 2.
* Temperature in both meteric and imperial unit is shown in row 3.
* Humidity and Atmospheric pressure is shown in row 4.
* The program refreshes these and checks for optimum humidity level (less than 40% or more than 60%).
* Alarm goes off in case humidity falls below 40 or rises above 60.
* The alarm continues until optimum humidity level is restored.

## Case
Due to projects being held up while waiting for library to print cases, I've given up on 3D printing for projects until I buy my own printer or find another way to print quickly.

In the meantime, I'll continue to drill and cut cheap plastic boxes for cases.

## FAQ
##### Why BME-280?
The other choice was DHT11. Compared from a price point, the BME-280 was more accurate and had a wider temperature range suited to Canadian weather.

##### Why LCD 2004?
While LCD 1602s are cheaper, LCD 2004 has more room to display text.

##### Why ESP8266?
Its cheap and has the Wifi functionality needed for this build. Also has a micro usb port for power or PC interfacing.

##### Why I2C and not SPI?
Frankly, never tried SPI. I2C was a satisfactory solution out of the box. I do have a LCD module project coming up that would have the LCD so let's see what happens!
