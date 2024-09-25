# STM32 FATFS SD CARD Reader Library


### Table of Contents
- [Description](#description)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](https://github.com/noumanimpra/STM32-SD-CARD-Library-Model-Rocket/blob/main/examples/main.c)
- [Contributing](#contributing)
- [License](#license)

---

### Description

<div align="center">
    This STM32 FATFS SD Card Reader library is tailored specifically for model rocket avionics systems. It provides functionality to parse and log flight data to an SD card, ensuring high-speed and reliable data storage during rocket flights. 
    <br><br>
    While the core functionality is in place, please note that the library might still lack certain features or complete documentation. 
    <b>Contributions are welcome! ⚠️</b>
</div>

### Features

- ✔️ Basic FATFS SD card read/write functionality
- ✔️ Optimized for STM32 microcontrollers
- ✔️ Reliable data logging for real-time systems
- ✔️ Supports standard SD cards
- ✔️ Model rocket specific logging features
- ⚠️ Continuous improvements and bug fixes in progress

---

### Getting Started

#### Prerequisites

- *STM32CubeIDE* or any IDE supporting STM32 development
- STM32 microcontroller (tested on STM32F4xx series)
- FATFS library integration in STM32 project (can be added via STM32CubeMX)
- SD card module connected to STM32

#### Installation

1. Clone this repository into your STM32 project directory:
 

2. Add the library files to your project and include them in your code:
    ```c
    #include "usr_fat_sd.h"
    #include "fatfs_sd.h"
    ```

3. Ensure that your STM32CubeMX configuration includes the FATFS middleware and the proper pin configuration for the SD card module.

---

### Contributing

Contributions, suggestions, and feedback are highly appreciated!

1. Fork the repository.
2. Create a new branch:
``` bash
git checkout -b feature-branch
``` 
4. Make your changes and commit them:
```bash
git commit -m "Added new feature"
```
5. Push to the branch:
```bash
git push origin feature-branch
```
6. Open a Pull Request.

Please ensure your changes include relevant tests and documentation updates if necessary.

---

### License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/noumanimpra/STM32-SD-CARD-Library-Model-Rocket/blob/main/LICENSE) file for details.

---

### Acknowledgments

Special thanks to the open-source community and all contributors for making this project possible. If you'd like to support this project, feel free to submit a contribution or provide feedback.

---

If you encounter any issues or have suggestions for improvement, feel free to open an issue on GitHub.
