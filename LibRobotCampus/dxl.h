#ifndef DXL_H
#define DXL_H

// Protocol definition
#define DXL_BROADCAST   0xFE

// Size limit for a buffer containing a dynamixel packet
#define DXL_BUFFER_SIZE 300

// Maximum parameters in a packet
#define DXL_MAX_PARAMS 140

// Direction pin
#if defined(BOARD_opencm904)
// 1: TX
// 0: RX
#define DXL_DIRECTION  28
#define DXL_DEVICE     Serial1
#define DXL_AVAILABLE
#endif

// Instructions
#define DXL_CMD_PING    0x01

typedef unsigned char ui8;

/**
 * A dynamixel packet
 */
struct dxl_packet {
    ui8 id; 
    union {
        ui8 instruction;
        ui8 error;
    };  
    ui8 parameter_nb;
    ui8 parameters[DXL_MAX_PARAMS];
    bool process;
    ui8 dxl_state;
};

void dxl_packet_init(struct dxl_packet *packet);
void dxl_packet_push_byte(struct dxl_packet *packet, ui8 b);
int dxl_write_packet(struct dxl_packet *packet, ui8 *buffer);
void dxl_copy_packet(struct dxl_packet *from, struct dxl_packet *to);
ui8 dxl_compute_checksum(struct dxl_packet *packet);

// Send a packet on the dynamixel bus
void dxl_send(struct dxl_packet *packet);

// Initialize dynamixel system (if available)
void dxl_init(int baudrate);

// Run the dynamixel forward
void dxl_forward();

// Incoming packet
extern struct dxl_packet incoming_packet;

// Get the reply of last packet sent
struct dxl_packet *dxl_get_reply();

// Tick (read data from the bus)
void dxl_tick();

// Sends a packet and wait for the reply
struct dxl_packet *dxl_send_reply(struct dxl_packet *packet);

// Pings a servo with the given ID
bool dxl_ping(ui8 id);

#endif // DXL_H
