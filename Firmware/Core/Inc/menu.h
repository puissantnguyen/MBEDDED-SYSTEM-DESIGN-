/*
 * menu.h
 *
 */

#ifndef MENU_H_
#define MENU_H_

typedef enum {MENU = -1, PIANO = 0, PRACTICE = 1, CONFIG = 2, HELP = 3} mode_t;

// Function prototypes
void menu_init(void);
void list_song(void);
void octave_config(void);
void show_help(void);

#endif /* MENU_H_ */
