# pill\_6502: emulated 8-bit 6502 CPU and 6850 ACIA for STM32F103 blue pill

[![CircleCI](https://circleci.com/gh/satoshinm/pill_6502.svg?style=svg)](https://circleci.com/gh/satoshinm/pill_6502)

[6502](https://en.wikipedia.org/wiki/MOS_Technology_6502) 8-bit CPU and
[6850](http://www.cpcwiki.eu/imgs/3/3f/MC6850.pdf) ACIA emulator for the
[STM32F103](https://www.reddit.com/r/stm32f103/) [blue pill](http://wiki.stm32duino.com/index.php?title=Blue_Pill)
microcontroller boards and similar. Turn your modern micro into a retrocomputing processor.

To build, run `make`, to install, flash `src/pill_6502.bin` to the blue pill.
Prebuilt binaries are available from [CircleCI](https://circleci.com/gh/satoshinm/pill_6502/).
Connect the board to your computer using USB, this will reset the CPU
and a virtual serial port should appear (e.g., `/dev/cu.usbmodem6502`),
connect using GNU Screen, and you should see the output from the emulated
ACIA communication interface chip. Type to send to the ACIA.

![screenshot](https://user-images.githubusercontent.com/26856618/34910886-d1869f5e-f872-11e7-8dd9-e034348619dd.png)

Special commands built-in, not passed to the ACIA and 6502:

| Keystroke | Action |
| --------- | ------ |
| ^V | Show `pill_6502` version |
| ^P | Pause/resume 6502 processor execution |
| ^F | Show frequency |
| ^R | Reset the 6502 processor (also reset on USB reset) |
| ^E | Local echo toggle, off by default |
| ^T | Show clock ticks and instruction count |
| ^G | Show help |

Intended to be somewhat compatible with [Grant Searle's Simple6502](http://searle.hostei.com/grant/6502/Simple6502.html),
and includes the Microsoft OSI BASIC ROM by default (C) Microsoft 1977. Other ROMs can be loaded
by replacing `ROM.HEX` and rebuilding. Memory map:

| Start  | End    | Usage |
| ------ | ------ | ----- |
| 0x0000 | 0x3fff | 16KB internal RAM |
| 0x4000 | 0x9fff | (unused) |
| 0xa000 | 0xbfff | 6850 ACIA serial comm interface, emulated connecting to USB CDC-ACM virtual serial port |
| 0xc000 | 0xffff | 16KB internal ROM |

Thanks to Mike Chambers for the [fake6502](http://rubbermallet.org/fake6502.c) processor emulation core.

For implementation notes see blog post *[pill_6502: 8-bit 6502 CPU and 6850 ACIA emulation on the STM32 blue pill to run Microsoft BASIC from 1977](https://satoshinm.github.io/blog/180113_stm32_6502_pill_6502_8_bit_6502_cpu_and_6850_acia_emulation_on_the_stm32_blue_pill_to_run_microsoft_basic_from_1977.html)*.
