#include <stdbool.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>

#include "acia6850.h"
#include "cdcacm.h"

extern usbd_device *usbd_dev;

// Motorola MC6850 Asynchronous Communications Interface Adapter (ACIA) emulation

// http://www.cpcwiki.eu/index.php/6850_ACIA_chip
// http://www.cpcwiki.eu/imgs/3/3f/MC6850.pdf
//

#define ACIAControl 0
#define ACIAStatus 0
#define ACIAData 1

// "MC6850 Data Register (R/W) Data can be read when Status.Bit0=1, and written when Status.Bit1=1."
#define RDRF (1 << 0)
#define TDRE (1 << 1)


static char input[256];
static int input_index = 0;
static int input_processed_index = 0;

void process_serial_input_byte(char b) {
    input[input_index++] = b;
    input_index %= sizeof(input);
}


uint8_t read6850(uint16_t address) {
	switch(address & 1) {
		case ACIAStatus: {
            // Always writable
            uint8_t flags = TDRE;

            // Readable if there is pending user input data which wasn't read
            if (input_processed_index < input_index) flags |= RDRF;

            return flags;
			break;
        }
		case ACIAData: {
            char data = input[input_processed_index++];
            input_processed_index %= sizeof(input);

            return data;
			break;
        }
		default:
            break;
	}

	return 0xff;
}

void write6850(uint16_t address, uint8_t value) {
	switch(address & 1) {
		case ACIAControl:
            // TODO: decode baudrate, mode, break control, interrupt
			break;
		case ACIAData: {
            static char buf[1];
            buf[0] = value;
            cdcacm_send_chunked_blocking(buf, sizeof(buf), usbd_dev);
			break;
        }
		default:
            break;
	}
}



