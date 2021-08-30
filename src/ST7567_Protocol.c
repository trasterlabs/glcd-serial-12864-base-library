/*
 *
 * Trasfile: ST7567_Protocol.c
 *
 * All rights reserved.
 *
 * All the text and images presented here belongs to Trasterlabs, only for portfolio purposes.
 *
 * Do not use in your projects without permission.
 *
 * ¡Rompe poco, pero trastea todo lo que puedas!
 *
 */

#include <stdint.h>
#include "communication_stm32f103_SPI.h"

enum select_operation_type
{
  get, set
};

/*
 +--------------------+----+----------+----+----+----+----+----+----+----+----+------------------------+
 |                    |    |          |             COMMAND BYTE              |                        |
 +--------------------+----+----------+----+----+----+----+----+----+----+----+------------------------+
 |    INSTRUCTION     | A0 | R/W(RWR) | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |      DESCRIPTION       |
 +--------------------+----+----------+----+----+----+----+----+----+----+----+------------------------+
 | (2) Set Start Line |  0 |        0 |  0 |  1 | S5 | S4 | S3 | S2 | S1 | S0 | Set display start line |
 +--------------------+----+----------+----+----+----+----+----+----+----+----+------------------------+
 This instruction sets the line address of the Display Data RAM to determine the initial display line. The display data of the
 specified line address is displayed at the top row (COM0) of the LCD panel.
 */

typedef struct s_set_start_line
{
  union
  {
    struct
    {
      unsigned int line_address :6;
      unsigned int identifier :2;
    };
    uint8_t command_byte;
  };
  unsigned int A0 :1;
} set_start_line_t;

void set_start_line_element(enum select_operation_type type,
    set_start_line_t **the_element)
{
  static set_start_line_t internal_element;
  switch (type)
  {
  case get:
    the_element[0] = &internal_element;
    break;
  default:
    break;
  }
}

void init_set_start_line_instruction(void)
{
  set_start_line_t *set_start_line = NULL;
  set_start_line_element(get, &set_start_line);
  set_start_line->A0 = 0;
  set_start_line->identifier = 0b01;
}

void set_line_address_for_set_start_line_instruction(uint8_t line_address)
{
  set_start_line_t *set_start_line = NULL;
  set_start_line_element(get, &set_start_line);
  set_start_line->line_address = line_address;
}

void send_set_start_line_instruction(void)
{
  set_start_line_t *set_start_line = NULL;
  set_start_line_element(get, &set_start_line);
  send_A0(set_start_line->A0);
  uint8_t element_to_send = set_start_line->command_byte;
  start_send_buffer(&element_to_send, 1);
}

/*
 +-----------------------+----+----------+----+----+----+----+----+----+----+----+------------------+
 |                       |    |          |             COMMAND BYTE              |                  |
 +-----------------------+----+----------+----+----+----+----+----+----+----+----+------------------+
 |      INSTRUCTION      | A0 | R/W(RWR) | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |   DESCRIPTION    |
 +-----------------------+----+----------+----+----+----+----+----+----+----+----+------------------+
 | (3) Set Page Address  |  0 |        0 |  1 |  0 |  1 |  1 | Y3 | Y2 | Y1 | Y0 | Set page address |
 +-----------------------+----+----------+----+----+----+----+----+----+----+----+------------------+
 This instruction sets the line address of the Display Data RAM to determine the initial display line. The display data of the
 specified line address is displayed at the top row (COM0) of the LCD panel.
 */

typedef struct s_page_address_set
{
  union
  {
    struct
    {
      unsigned int page_address :4;
      unsigned int identifier :4;
    };
    uint8_t command_byte;
  };
  unsigned int A0 :1;
} page_address_set_t;

void page_address_set_element(enum select_operation_type type,
    page_address_set_t **the_element)
{
  static page_address_set_t internal_element;
  switch (type)
  {
  case get:
    the_element[0] = &internal_element;
    break;
  default:
    break;
  }
}

void init_page_address_set_instruction(void)
{
  page_address_set_t *page_address_set = NULL;
  page_address_set_element(get, &page_address_set);
  page_address_set->A0 = 0;
  page_address_set->identifier = 0b1011;
}

void set_page_address_for_page_address_set_instruction(uint8_t page_address)
{
  page_address_set_t *page_address_set = NULL;
  page_address_set_element(get, &page_address_set);
  page_address_set->page_address = page_address;
}

void send_page_address_set_instruction(void)
{
  page_address_set_t *page_address_set = NULL;
  page_address_set_element(get, &page_address_set);
  send_A0(page_address_set->A0);
  uint8_t element_to_send = page_address_set->command_byte;
  start_send_buffer(&element_to_send, 1);
}

/*
 +------------------------+----+----+----+----+----+----+----+----+----+--------------------------+
 |      INSTRUCTION       | A0 | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |       DESCRIPTION        |
 +------------------------+----+----+----+----+----+----+----+----+----+--------------------------+
 | (12) Read-modify-Write |  0 |  1 |  1 |  1 |  0 |  0 |  0 |  0 |  0 | Column address increment |
 +------------------------+----+----+----+----+----+----+----+----+----+--------------------------+
 This  command  is  used  paired  with  the  “END”  instruction.  Once  this  command  has  been  input,  the  display  data  read
 operation will not change the column address, but only the display data write operation will increase the column address
 (X[7:0]+1). This mode is maintained until the END command is input. This function makes it possible to reduce the load on
 the MPU when there are repeating data changes in a specified display region, such as a blanking cursor.
 */

typedef struct s_read_modify_write
{
  union
  {
    struct
    {
      unsigned int identifier :8;
    };
    uint8_t command_byte;
  };
  unsigned int A0 :1;
} read_modify_write_t;

void read_modify_write_element(enum select_operation_type type,
    read_modify_write_t **the_element)
{
  static read_modify_write_t internal_element;
  switch (type)
  {
  case get:
    the_element[0] = &internal_element;
    break;
  default:
    break;
  }
}

void init_read_modify_write_instruction(void)
{
  read_modify_write_t *init_element = NULL;
  read_modify_write_element(get, &init_element);
  init_element->A0 = 0;
  init_element->identifier = 0b11100000;
}

void send_read_modify_write_instruction(void)
{
  read_modify_write_t *element_to_be_sent = NULL;
  read_modify_write_element(get, &element_to_be_sent);
  send_A0(element_to_be_sent->A0);
  uint8_t element_to_send = element_to_be_sent->command_byte;
  start_send_buffer(&element_to_send, 1);
}

/*
 +-------------+----+----+----+-----+-----+-----+-----+-----+-----+---------------------------------------------------+
 | INSTRUCTION | A0 | D7 | D6 | D5  | D4  | D3  | D2  | D1  | D0  |                    DESCRIPTION                    |
 +-------------+----+----+----+-----+-----+-----+-----+-----+-----+---------------------------------------------------+
 | (18) Set EV |  0 |  1 |  0 | 0   | 0   | 0   | 0   | 0   | 1   | Double command!! Set electronic volume (EV) level |
 |             |  0 |  0 |  0 | EV5 | EV4 | EV3 | EV2 | EV1 | EV0 |                                                   |
 +-------------+----+----+----+-----+-----+-----+-----+-----+-----+---------------------------------------------------+
 This is double byte instruction. The first byte set ST7567 into EV adjust mode and the following instruction will change the
 EV setting. That means these 2 bytes must be used together. They control the electronic volume to adjust a suitable V0
 voltage for the LCD
 */

typedef struct s_electronic_volume_set
{
  union
  {
    struct
    {
      unsigned int electronic_volume :6;
      unsigned int command_identifier :2;
    };
    uint8_t command_byte;
  };
  union
  {
    struct
    {
      unsigned int instuction_identifier :8;
    };
    uint8_t instruction_byte;
  };
  unsigned int A0 :1;
} electronic_volume_set_t;

void electronic_volume_set_element(enum select_operation_type type,
    electronic_volume_set_t **the_element)
{
  static electronic_volume_set_t internal_element;
  switch (type)
  {
  case get:
    the_element[0] = &internal_element;
    break;
  default:
    break;
  }
}

void init_electronic_volume_set_instruction(void)
{
  electronic_volume_set_t *init_element = NULL;
  electronic_volume_set_element(get, &init_element);
  init_element->A0 = 0;
  init_element->instuction_identifier = 0b10000001;
  init_element->command_identifier = 0b00;
}

void set_electronic_volume_set_instruction(uint8_t electronic_volume)
{
  electronic_volume_set_t *init_element = NULL;
  electronic_volume_set_element(get, &init_element);
  init_element->electronic_volume = electronic_volume;
}

void send_electronic_volume_set_instruction(void)
{
  electronic_volume_set_t *element_to_be_sent = NULL;
  electronic_volume_set_element(get, &element_to_be_sent);
  send_A0(element_to_be_sent->A0);
  uint8_t element_to_send[2];
  element_to_send [0] = element_to_be_sent->instruction_byte;
  element_to_send [1] = element_to_be_sent->command_byte;
  start_send_buffer(element_to_send, 2);
}

