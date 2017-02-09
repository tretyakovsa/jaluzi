# Jalousie and esp8266 (Arduino)

![alt](https://raw.githubusercontent.com/tretyakovsa/jaluzi/master/tutorial/screen.png)

## Components

- IDs 	# 	Component 	Footprint 	Properties
- U1 	1 	ESP8266 (beta) 	ESP8266
- M1 	1 	Servo Type of geared motor that can only rotate 180 degrees. It's controlled by electronic pulses that tell the motor to which position it should move. 	servo header
- U2 	1 	3.3V Regulator [LD1117V33] 	TO220
- R1, R2 	2 	Resistor Resist the flow of electrical energy in a circuit, changing the voltage and current as a result. 	0617/17 	10 kohm
- S1 	1 	Pushbutton Momentary switches that close a circuit when pressed. 	TACTILE-PTH
- P1 	1 	Power Supply This is the component used to represent the power supply in the Electronics Workbench (the breadboard simulator). There are multiple footprints so if you are designing a PCB be sure to choose which footprint works best for your design. 	Power Header 0.1" through hole 2 	5 , 5



##Upload instruction

###[NodeMCU Flasher (Easy)](https://github.com/tretyakovsa/jaluzi/tree/master/build)

###[Arduino Windows (Video)](https://www.youtube.com/watch?v=jMK9mySGHio)

###[Arduino Linux (Video)](https://www.youtube.com/watch?v=1TAHlRqZ46k)


##Work example (Video)

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/LZI4Yu47LZI/0.jpg)](https://www.youtube.com/watch?v=LZI4Yu47LZI&list=PL6NJTNxbvy-IPTDQk8XjTV41oRrFafrRi)

##Construction
```
#define TACH_PIN 0        // Кнопка управления
#define SERVO_PIN 2       // Сервопривод
// If you use ESP8266 12 you can add
#define TURNSENSOR_PIN 14 // Сенсор оборотов
#define LED1_PIN 12       // индикатор движения вверх (Сюда можно подключить модуль управления мотором)
#define LED2_PIN 13       // индикатор движения вниз (Сюда можно подключить модуль управления мотором)
```

[https://circuits.io/circuits/2522119-jalousie-and-esp8266-arduino](https://circuits.io/circuits/2522119-jalousie-and-esp8266-arduino)

###Breadboard

![alt](https://raw.githubusercontent.com/tretyakovsa/jaluzi/master/tutorial/breadboard.gif)

###Schematic
![alt](https://raw.githubusercontent.com/tretyakovsa/jaluzi/master/tutorial/schematic.png)


##Othe...

####RGB: [https://github.com/renat2985/rgb](https://github.com/renat2985/rgb)

####Sonoff: [https://github.com/tretyakovsa/Sonoff_WiFi_switch](https://github.com/tretyakovsa/Sonoff_WiFi_switch)


####Themes you can download here: [http://bootswatch.com/](http://bootswatch.com/)


##Donation

If you like this project, you can give me a cup of coffee :)

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=W4PURUNKWMRJW&lc=AU&item_name=esp8266&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donate_SM%2egif%3aNonHosted)