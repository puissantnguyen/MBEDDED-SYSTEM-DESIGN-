/*
 * menu.c
 *
 */

#include <stdbool.h>
#include <stdint.h>

#include "LCD_Nokia5110.h"
#include "eeprom.h"
#include "main.h"
#include "menu.h"

#define min(a, b) ((a) < (b) ? (a) : (b))

volatile mode_t mode = MENU;
void (*state_table[])(void) = {menu_init, list_song, octave_config, show_help};

char *menu_list[] = {" Piano", " Practice", " Config", " Help"};
char *song_list[] = {" ..", " JingleBell", " MarryLamb", " TwinkleStar"};
char *octave_list[] = {" ..", " Octave 4", " Octave 5"};

uint8_t num_of_items = sizeof(menu_list) / sizeof(char *);
uint8_t num_of_songs = sizeof(song_list) / sizeof(char *);
uint8_t num_of_octaves = sizeof(octave_list) / sizeof(char *);
uint8_t menu_index = 0;
uint8_t song_index = 0;
uint8_t octave_index = 0;
bool song_chosen = false;
extern octave_t octave;

void menu_init(void)
{
	LCD_clear();
	LCD_gotoXY(15, 0);
	LCD_write_str("MAIN MENU");
	LCD_gotoXY(3, 1);
	LCD_write_str("-------------");
	for (uint8_t i = 0; i < num_of_items; i++)
	{
		LCD_gotoXY(3, i + 2);
		LCD_write_char((i == menu_index) ? '>' : ' ');
		LCD_write_str(menu_list[i]);
	}
}

void list_song(void)
{
	LCD_clear();
	for (uint8_t i = 0; i < num_of_songs; i++)
	{
		LCD_gotoXY(0, i);
		LCD_write_char((i == song_index) ? '>' : ' ');
		LCD_write_str(song_list[i]);
	}
}

void octave_config(void)
{
	LCD_clear();
	for (uint8_t i = 0; i < num_of_octaves; i++)
	{
		LCD_gotoXY(0, i);
		LCD_write_char((i == octave_index) ? '>' : ' ');
		LCD_write_str(octave_list[i]);
	}
}

void show_help(void)
{
	LCD_clear();
	LCD_gotoXY(20, 0);
	LCD_write_str("HELP");
	LCD_gotoXY(0, 1);
	LCD_write_str("BTN:interface");
	LCD_gotoXY(0, 2);
	LCD_write_str("CONFIG:octave");
	LCD_gotoXY(0, 4);
	LCD_write_str("2 playing mode");
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(mode)
	{
	case MENU: case PIANO:
		if (GPIO_Pin == UP_BTN_Pin)
		{
			LCD_gotoXY(3, menu_index + 2);
			LCD_write_char(' ');

			menu_index--;
			if (menu_index == 0xFF) menu_index = 0;

			LCD_gotoXY(3, menu_index + 2);
			LCD_write_char('>');
//			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		}
		if (GPIO_Pin == DOWN_BTN_Pin)
		{
			LCD_gotoXY(3, menu_index + 2);
			LCD_write_char(' ');

			menu_index++;
			if (menu_index == num_of_items) menu_index = num_of_items - 1;

			LCD_gotoXY(3, menu_index + 2);
			LCD_write_char('>');
//			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		}
		if (GPIO_Pin == SELECT_BTN_Pin)
		{
			// Update mode
			mode = menu_index;
			state_table[mode]();
//			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		}
		break;

	case PRACTICE:
		if (GPIO_Pin == UP_BTN_Pin)
		{
			LCD_gotoXY(0, song_index);
			LCD_write_char(' ');

			song_chosen = false;
			song_index--;
			if (song_index == 0xFF) song_index = 0;

			LCD_gotoXY(0, song_index);
			LCD_write_char('>');
//			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		}
		if (GPIO_Pin == DOWN_BTN_Pin)
		{
			LCD_gotoXY(0, song_index);
			LCD_write_char(' ');

			song_chosen = false;
			song_index++;
			if (song_index == num_of_songs) song_index = num_of_songs - 1;

			LCD_gotoXY(0, song_index);
			LCD_write_char('>');
//			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		}
		if (GPIO_Pin == SELECT_BTN_Pin)
		{
			if (song_index == 0)
			{
				mode = MENU;
				state_table[mode + 1]();
			}
			else
			{
				song_chosen = true;
			}
		}
		break;

	case CONFIG:
		if (GPIO_Pin == UP_BTN_Pin)
		{
			LCD_gotoXY(0, octave_index);
			LCD_write_char(' ');
			octave_index--;
			if (octave_index == 0xFF) octave_index = 0;

			LCD_gotoXY(0, octave_index);
			LCD_write_char('>');
//			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		}
		if (GPIO_Pin == DOWN_BTN_Pin)
		{
			LCD_gotoXY(0, octave_index);
			LCD_write_char(' ');

			octave_index++;
			if (octave_index == num_of_octaves) octave_index = num_of_octaves - 1;

			LCD_gotoXY(0, octave_index);
			LCD_write_char('>');
//			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		}
		if (GPIO_Pin == SELECT_BTN_Pin)
		{
			if (octave_index == 0)
			{
				mode = MENU;
				state_table[mode + 1]();
			}
			else if (octave_index == 1)
			{
				uint8_t data = 0x04;
				Write_To_24LCxx(0x1AAA, &data, 1);
				update_octave(&octave, data);
			}
			else if (octave_index == 2)
			{
				uint8_t data = 0x05;
				Write_To_24LCxx(0x1AAA, &data, 1);
				update_octave(&octave, data);
			}

		}
		break;

	case HELP:
		if (GPIO_Pin == SELECT_BTN_Pin)
		{
			menu_index = 0;
			mode = MENU;
			state_table[mode + 1]();
		}
		break;
	}
}
