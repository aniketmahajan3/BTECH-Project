# BTECH-Project
Name: Battery Monitoring System using IoT
Battery Monitoring System is heart of Electric Vehicles. So we are adding a concept to monitor battery performance, 
using loT- cloud techniques, so that battery monitoring can be done using the Ubidots loT Cloud channel that
works for EV builder and battery manufacturer, laptop owner or mobile handset owner. For future analysis of battery,

We are monitoring following parameters of battery-

1. State of Charge (SOC)
2. Self Biasing
3. Battery Percentage
4. Battery Voltage
5. Battery Temperature
6. Battery Current

The Battery monitoring system for Electric Vehicles (EV) employs ATmega328p, loT, and a Wi-Fi module to
continuously monitor and analyze the performance parameters of lithium-ion cells. By measuring voltage,
temperature, and current, this system enables real-time monitoring and analysis of EV performance.
The collected data is then uploaded via the Wi-Fi module to an loT web page, allowing EV
manufacturers to easily monitor the parameters and take proactive measures if necessary. Simultaneously,
the parameters are displayed on an LCD screen.Through a comprehensive literature review, it was
determined that this embedded system effectively and continuously monitors EV parameters, providing
valuable insights for evaluating the battery system. Various sensors, including voltage, current, and
temperature sensors are utilized to accurately capture the parameters. The Arduino UNO software IDE serves
as the programming platform for this project, facilitating the development process.

The implementation involves integrating ATmega328p, LCD Display, Wi-Fi module, lithium-ion
cells, charger, voltage sensor, current sensor. To enable data uploading, the power of loT is harnessed.
The ATmega328p is connected to both the LCD display and the ESP8266 Wi-Fi module, while
appropriate libraries are installed for programming convenience. Each lithium ion cell is connected to
voltage, temperature, and current sensors to enable real-time data collection. The collected data is
graphically displayed on UBI DOTS, enabling a comprehensive analysis of the EV's performance
based on voltage. current, and temperature readings for cells. Below some screenshots of results on UBI
DOTS platform.