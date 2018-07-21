ST,STM32-GPIOv2-pinmux
============

- `compatible`, required, list of strings:
  - [0], required, string, `ST,GPIOv2-pinmux`;
- `<pinmux-pin-name>` (`<pinmux-pin-name>` - string), optional - zero or more, mapping:
  - `port`, required, string, `GPIOx` (`x` - upper case character) - GPIO port to which this pin
is connected;
  - `pin`, required, integer, number of pin to which this pin is connected;
  - `function`, required, integer, index of alternate function to which this pin is connected;
  - `drive`, optional, string, type of output pin drive mode , one of: `push-pull` (default)
or `open-drain`;
  - `bias`, optional, string, type of pin bias, one of: `disable` (default) - disable any pin bias,
`pull-up` - pull up the pin, `pull-down` - pull down the pin; 
  - `slew-rate`, optional, integer, pin speed mode, one of: 3 - `very-high` (default) , 2 - `high`,
1 - `medium`, 0 - `low`;

Examples
--------

```
usart3Pins:
  compatible:
  - ST,STM32-GPIOv2-pinmux
  usart3Tx:
    port: GPIOB
    pin: 10
    function: 7
    drive: push-pull
    slew-rate: 3
  usart3Rx:
    port: GPIOB
    pin: 11
    function: 7
    drive: push-pull
    bias: pull-up
    slew-rate: 3
```
