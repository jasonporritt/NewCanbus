
#include <Arduino.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <pins_arduino.h>
#include <inttypes.h>
#include <global.h>
#include <mcp2515.h>
#include <defaults.h>
#include <NewCanbus.h>

// Default filter -- all open
const prog_uint8_t all_open_filters[] PROGMEM = 
{
	// Group 0
	MCP2515_FILTER(0),				// Filter 0
	MCP2515_FILTER(0),				// Filter 1
	
	// Group 1
	MCP2515_FILTER_EXTENDED(0),		// Filter 2
	MCP2515_FILTER_EXTENDED(0),		// Filter 3
	MCP2515_FILTER_EXTENDED(0),		// Filter 4
	MCP2515_FILTER_EXTENDED(0),		// Filter 5
	
	MCP2515_FILTER(0),				// Mask 0 (for group 0)
	MCP2515_FILTER_EXTENDED(0),		// Mask 1 (for group 1)
};

/* C++ wrapper */
NewCanbusClass::NewCanbusClass() {
}

void NewCanbusClass::set_filters(const prog_uint8_t *filter) {
  mcp2515_static_filter(filter);
}

//
// Get the full message, including id and data
//
char NewCanbusClass::message_rx(tCAN *message) {
	if (mcp2515_read_status(SPI_RX_STATUS)) {
    uint8_t result = mcp2515_get_message(message);
    if (result) {
      return 1;
    }
  }
  return 0;
}

char NewCanbusClass::message_rx(unsigned char *buffer) {
  tCAN message;

  if (mcp2515_check_message()) {
    if (mcp2515_get_message(&message)) {
      buffer[0] = message.data[0];
      buffer[1] = message.data[1];
      buffer[2] = message.data[2];
      buffer[3] = message.data[3];
      buffer[4] = message.data[4];
      buffer[5] = message.data[5];
      buffer[6] = message.data[6];
      buffer[7] = message.data[7];								
      return 1;
    }
  }
  return 0;

}

char NewCanbusClass::message_tx(uint16_t id, uint8_t data[]) {
	tCAN message;

  // May be a few defaults here that should be parameterized?
	message.id = id;
	message.header.rtr = 0;
	message.header.length = 8;
	message.data[0] = data[0];
	message.data[1] = data[1];
	message.data[2] = data[2];
	message.data[3] = data[3];
	message.data[4] = data[4];
	message.data[5] = data[5];
	message.data[6] = data[6];
	message.data[7] = data[7];
	
	if (mcp2515_send_message(&message)) {
		return 1;
	}

	return 0;
}

char NewCanbusClass::init(unsigned char speed) {
  return mcp2515_init(speed);
}

NewCanbusClass NewCanbus;
