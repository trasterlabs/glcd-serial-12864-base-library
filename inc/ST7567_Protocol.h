/**
  ******************************************************************************
  * @file    ST7657_Protocol.h
  * @author  Trasterlabs
  * @brief   This file contains all the functions prototypes for the serial GLCD
  * layer using ST7567 protocol
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

#ifndef INC_ST7567_PROTOCOL_H_
#define INC_ST7567_PROTOCOL_H_


/** @addtogroup ST7567_Protocol_Driver Protocol driver for ST7567
  * @brief All the protocol parts for the ST7567 serial screen module
  * @{
  */

/** @addtogroup ST7567_Protocol_set_start_line ST7567 Set Start Line
  * @{
  * |    INSTRUCTION     |
  * |:-------------------|
  * | (2) Set Start Line |
  * This instruction sets the line address of the Display Data RAM to determine the initial display line. The display data of the
  * specified line address is displayed at the top row (COM0) of the LCD panel.
  */

/**
 * @brief Initiates the instruction "Set Start Line"
 */
void init_set_start_line_instruction ( void );

/**
 *  \brief Adjust the line address for the instruction Set Start Line
 *  
 *  \param [in] line_address The specified line address. It must be from 0 to 63
 */
void set_line_address_for_set_start_line_instruction ( uint8_t line_address );

/**
 *  \brief Send the instruction Set Start Line
 */
void send_set_start_line_instruction ( void );

/**
  * @}
  */

/**
  * @}
  */


#endif /* INC_ST7567_PROTOCOL_H_ */
