/**
  ******************************************************************************
  * @file    ST7657_Protocol.c
  * @author  Trasterlabs
  * @brief   This file contains all the functions definitions for the serial
  * GLCD layer using ST7567 protocol
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 Trasterlabs.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Trasterlabs. You shall not use this
  * file without permission of the author.
  *
  * All the text and images presented here belongs to Trasterlabs, only for
  * portfolio purposes.
  *
  * Do not use in your projects without permission.
  *
  * ¡Rompe poco, pero trastea todo lo que puedas!
  *
  ******************************************************************************
  */

#include <stdint.h>
#include "communication_stm32f103_SPI.h"

enum select_operation_type
{
  get, set
};

/*
 +--------------------+----+----+----+----+----+----+----+----+----+------------------------+
 |                    |    |             COMMAND BYTE              |                        |
 +--------------------+----+----+----+----+----+----+----+----+----+------------------------+
 |    INSTRUCTION     | A0 | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |      DESCRIPTION       |
 +--------------------+----+----+----+----+----+----+----+----+----+------------------------+
 | (2) Set Start Line |  0 |  0 |  1 | S5 | S4 | S3 | S2 | S1 | S0 | Set display start line |
 +--------------------+----+----+----+----+----+----+----+----+----+------------------------+
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
  static set_start_line_t start_line_element;
  switch (type)
  {
  case get:
    the_element[0] = &start_line_element;
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
 +-----------------------+----+----+----+----+----+----+----+----+----+------------------+
 |                       |    |             COMMAND BYTE              |                  |
 +-----------------------+----+----+----+----+----+----+----+----+----+------------------+
 |      INSTRUCTION      | A0 | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |   DESCRIPTION    |
 +-----------------------+----+----+----+----+----+----+----+----+----+------------------+
 | (3) Set Page Address  |  0 |  1 |  0 |  1 |  1 | Y3 | Y2 | Y1 | Y0 | Set page address |
 +-----------------------+----+----+----+----+----+----+----+----+----+------------------+
 Y [3:0] defines the Y address vector address of the display RAM.
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
  static page_address_set_t start_line_element;
  switch (type)
  {
  case get:
    the_element[0] = &start_line_element;
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

