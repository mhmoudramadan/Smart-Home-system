
# Smart-Home-system

[![Status](https://camo.githubusercontent.com/52dc5b531aa6cee975068174b406b2b0b08f86be6e455386c8683db38d3601ec/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f7374617475732d6163746976652d737563636573732e737667)](https://github.com/mhmoudramadan/STM32F756ZG_Bootloader/blob/master)[![GitHub Issues](https://camo.githubusercontent.com/9a6266d1986b6043009223290255410e8d577c9fcea8d6049508825f9c08dd3d/68747470733a2f2f696d672e736869656c64732e696f2f6769746875622f6973737565732f6b796c656c6f626f2f5468652d446f63756d656e746174696f6e2d436f6d70656e6469756d2e737667)](https://github.com/kylelobo/The-Documentation-Compendium/issues)[![GitHub Pull Requests](https://camo.githubusercontent.com/44af8fbca480e9a96fa7f45c477860985aa7ff82ed96d7a0fa533a7d3cd01fda/68747470733a2f2f696d672e736869656c64732e696f2f6769746875622f6973737565732d70722f6b796c656c6f626f2f5468652d446f63756d656e746174696f6e2d436f6d70656e6469756d2e737667)](https://github.com/kylelobo/The-Documentation-Compendium/pulls)[![License](https://camo.githubusercontent.com/2bb6ac78e5a9f4f688a6a066cc71b62012101802fcdb478e6e4c6b6ec75dc694/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6c6963656e73652d4d49542d626c75652e737667)](https://github.com/mhmoudramadan/STM32F756ZG_Bootloader/blob/master/LICENSE.md)

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Repository Structure](#repository-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Configuration](#configuration)
- [Contributing](#contributing)
- [License](#license)

## Overview

This project is a Smart Home system using an ATmega32 microcontroller. It allows control of home appliances such as doors, air conditioners, LEDs, and a dimming LED remotely via a mobile app over Bluetooth or from a PC terminal. Emergency control is available via an LCD and Keypad.

## Features

- **Remote Control**: Operate home appliances via Bluetooth.
- **Admin and User Roles**: Admin can register/remove users and access all appliances; users have restricted access.
- **Persistent Login**: Usernames and passwords are stored in EEPROM.
- **Idle Display**: LCD shows running devices when idle.

## Repository Structure

- **project/**: Contains the main project files.
- **simulation/**: Contains simulation files for testing the system.

## Getting Started

### Prerequisites

- ATmega32 microcontroller.
- Bluetooth module.
- LCD and Keypad.
- Development environment with AVR-GCC and AVRDude.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/mhmoudramadan/Smart-Home-system.git
   ```

## Configuration

Modify the configuration parameters in the source code files to customize the system settings as needed.

## Contributing

Contributions are welcome! Please submit pull requests or open issues to help improve this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details.
