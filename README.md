# ATmega32_Drivers
> ### *Highly configurable and abstracted Drivers for full control of the main peripherals of ATmega32 MCU.*

This repository contains a collection of modular, layered, and clean-coded drivers for various modules of the Atmega32 microcontroller. <br/>
Each driver is highly configurable and provides an interface to interact with specific peripherals or modules.

## Supported Modules
The following modules are currently supported by the drivers in this repository:

- Digital Input/Output (DIO)
- Analog-to-Digital Converter (ADC)
- External Interrupts (EXTI)
- General Interrupt Enable (GIE)
- Timer 0
- Timer 1
- Timer 2
- Input Capture Unit (ICU)
- Pulse Width Modulation (PWM)
- Watchdog Timer (WDT)
- Universal Asynchronous Receiver-Transmitter (UART)
- Serial Peripheral Interface (SPI)
- Two-Wire Interface (TWI/I2C)
- Electrically Erasable Programmable Read-Only Memory (EEPROM)<br/><br/>

#### Also there is hardware drivers for *LCD* and *Keypad*
## Features
- Modular design: Each driver is implemented as a separate module, allowing easy integration and customization.
- Layered architecture: The drivers follow a layered architecture, separating the hardware-specific details from the application logic.
- Clean code: The drivers are implemented using clean and maintainable code, following **Misra-C** coding standards and best practices.
- High configurability: The drivers provide configuration options to adapt to various requirements and hardware setups.

## Getting Started
To use the Atmega32 drivers in your project, follow these steps:

1- Clone the repository to your local machine.<br/><br/>
2- Copy the required driver modules to your project folder this is easy as each driver own files are gathered in one place.<br/><br/>
3- You need only to Include the Interface files of you required drivers into your source files.(ex. Timer1_interface.h file)<br/><br/>
4- Configure the drivers according to your specific needs by modifying the configuration object in the *_Config.c File.<br/><br/>
5- Use the Enums and Helpers from the *_Config.h files to configure the Configuration object.<br/><br/>
6- Implement the application logic using the provided driver APIs just type the name of the module and auto-complete will show you all available functions and helpers as everything that is related to a module     always starts with its name.<br/><br/>
7- In Initialization Functions you can use the Configuration object address directly as it is already extended with the interface file.<br/><br/>
7- Build and upload your project to the Atmega32 microcontroller.<br/><br/>

## Notes
- Always make sure that the Libraries and the MCAL folders are set in a similar way else you will haave to change the inclusion of their related files in all occurences through all drivers
- Always use the Helpers for the interfaces parameters to avoid wrong usage or unexpected behaviours
- Always use the Configration object pre-defined in the module to avoid un-needed memory usage

## Contributing
Contributions to this repository are welcome! If you find any issues, have suggestions, or would like to add support for additional modules, please feel free to contact me or submit a pull request or open an issue.

## License
This repository is licensed under the GNU General Public License v3.0 .
