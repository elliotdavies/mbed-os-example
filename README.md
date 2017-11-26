# mbed OS example

Example mbed OS code for the STM32F4.

Toggles the LEDs and LCD background color when the 'User' button is pressed, and
prints coordinates to the screen when the touchscreen is pressed.

With reference to
[https://github.com/ARMmbed/mbed-os-example-blinky](https://github.com/ARMmbed/mbed-os-example-blinky).

## Build and deploy

The project uses `pipenv` and the `mbed-cli`.

Build:

    ./build.sh

Deploy to the STM device over USB:

    ./deploy.sh
