/**
 * CAN BUS
 *
 * Copyright (c) 2010 Sukkin Pang All rights reserved.
 */
#include <mcp2515.h>

#ifndef newcanbus__h
#define newcanbus__h

#define CANSPEED_125 	  7		// CAN speed at 125 kbps
#define CANSPEED_250  	3		// CAN speed at 250 kbps
#define CANSPEED_500	  1		// CAN speed at 500 kbps

// 
// OBDII data definitions
#define ENGINE_COOLANT_TEMP 0x05
#define ENGINE_RPM          0x0C
#define VEHICLE_SPEED       0x0D
#define MAF_SENSOR          0x10
#define O2_VOLTAGE          0x14
#define THROTTLE			      0x11
#define MAP_SENSOR          0x0B
#define ENGINE_OIL_TEMP     0x5C            
#define FUEL_INJECTION_TIMING 0x5D

// OBDII request & response definitions
#define PID_REQUEST         0x7DF
#define PID_REPLY			      0x7E8

class NewCanbusClass
{
  public:

	NewCanbusClass();
  char init(unsigned char);
	char message_tx(uint16_t id, uint8_t data[]);
	char message_rx(unsigned char *buffer);
	char message_rx(tCAN *message);

  void set_filters(const prog_uint8_t *filter);

  private:
	
};

extern NewCanbusClass NewCanbus;
// extern tCAN message;

#endif
