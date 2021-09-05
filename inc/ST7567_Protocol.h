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

/** @addtogroup ST7567_Protocol_display_on_off ST7567 Display ON/OFF
 * @{
 * |    INSTRUCTION     |
 * |:-------------------|
 * | (1) Display ON/OFF |
 * Turns on or off the display
 */

/**
 * @brief Initiates the instruction "Display ON/OFF"
 */
void ST7567_display_on_off__init_instruction(void);

/**
 * @brief Using the "Display ON/OFF" instruction, prepares to turn on the display
 */
void ST7567_prepare_to_turn_on_the_display(void);

/**
 * @brief Using the "Display ON/OFF" instruction, prepares to turn off the display
 */
void ST7567_prepare_to_turn_off_the_display(void);

/**
 * @brief Send the instruction "Display ON/OFF"
 */
void ST7567_display_on_off__send_instruction(void);

/**
 * @}
 */

/** @addtogroup ST7567_Protocol_set_start_line ST7567 Set Start Line
 * @{
 * |    INSTRUCTION     |
 * |:-------------------|
 * | (2) Set Start Line |
 * This instruction sets the line address of the Display Data RAM to determine the initial display line. The display data of the specified line address is displayed at the top row (COM0) of the LCD panel.
 */

/**
 * @brief Initiates the instruction "Set Start Line"
 */
void ST7567_set_start_line__init_instruction(void);

/**
 * @brief Adjust the line address for the instruction "Set Start Line"
 *
 * @param [in] line_address The specified line address. It must be from 0 to 63
 */
void ST7567_set_start_line__set_instruction(uint8_t line_address);

/**
 * @brief Send the instruction "Set Start Line"
 */
void ST7567_set_start_line__send_instruction(void);

/**
 * @}
 */

/** @addtogroup ST7567_Protocol_set_page_address ST7567 Set Page Address
 * @{
 * |     INSTRUCTION      |
 * |:---------------------|
 * | (3) Set Page Address |
 * Y [3:0] defines the Y address vector address of the display RAM.
 */

/**
 * @brief Initiates the instruction "Set Page Address"
 */
void ST7567_page_address_set__init_instruction(void);

/**
 * @brief Adjust the page address "Set Page Address"
 *
 * @param [in] page_address The Y address vector address of the display RAM. It must be from 0 to 7
 */
void ST7567_page_address_set__set_instruction(uint8_t page_address);

/**
 * @brief Send the instruction "Set Page Address"
 */
void ST7567_page_address_set__send_instruction(void);

/**
 * @}
 */

/** @addtogroup ST7567_Protocol_set_column_address ST7567 Set Column Address
 * @{
 * |      INSTRUCTION       |
 * |:-----------------------|
 * | (4) Set Column Address |
 * The range of column address is 0...131. The parameter is separated into 2 instructions. The column address is increased(+1)  after  each  byte  of  display  data  access  (read/write).  This  allows  MPU  accessing  DDRAM  content  continuously.  This feature stops at the end of each page (Column Address “83h”).
 */

/**
 * @brief Initiates the instruction "Set Column Address"
 */
void ST7567_set_column_address__init_instruction(void);
/**
 * @brief Adjust the electronic volume for the instruction "Set Column Address"
 *
 * @param [in] column_address The start column address.
 * @warning Range from 0 to 131
 */
void ST7567_set_column_address__set_instruction(uint8_t column_address);

/**
 * @brief Send the instruction "Set Column Address"
 */
void ST7567_set_column_address__send_instruction(void);

/**
 * @}
 */

/** @addtogroup ST7567_Protocol_read_modify_write ST7567 Read-modify-Write
 * @{
 * |      INSTRUCTION       |
 * |:-----------------------|
 * | (12) Read-modify-Write |
 *
 * This command is used paired with the “END” instruction. Once this command has been input, the display data read operation will not change the column address, but only the display data write operation will increase the column address (X[7:0]+1). This mode is maintained until the END command is input. This function makes it possible to reduce the load on the MPU when there are repeating data changes in a specified display region, such as a blanking cursor.
 */

/**
 * @brief Initiates the instruction "Read-modify-Write"
 */
void ST7567_read_modify_write__init_instruction(void);

/**
 * @brief Send the instruction "Read-modify-Write"
 */
void ST7567_read_modify_write__send_instruction(void);

/**
 * @}
 */

/** @addtogroup ST7567_Protocol_electronic_volume_set ST7567 Electronic volume
 * @{
 * | INSTRUCTION |
 * |:------------|
 * | (18) Set EV |
 * This is double byte instruction. The first byte set ST7567 into EV adjust mode and the following instruction will change the EV setting. That means these 2 bytes must be used together. They control the electronic volume to adjust a suitable V0 voltage for the LCD.
 */

/**
 * @brief Initiates the instruction "Electronic Volume Set"
 */
void ST7567_electronic_volume_set__init_instruction(void);
/**
 * @brief Adjust the electronic volume for the instruction "Electronic Volume Set"
 *
 * @param [in] electronic_volume The electronic volume to be adjusted.
 * @note Range from 0 to 63
 */
void ST7567_electronic_volume_set__set_instruction(uint8_t electronic_volume);

/**
 * @brief Send the instruction "Electronic Volume Set"
 */
void ST7567_electronic_volume_set__send_instruction(void);

/**
 * @}
 */

/**
 * @}
 */

#endif /* INC_ST7567_PROTOCOL_H_ */
