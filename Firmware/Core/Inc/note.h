/*
 * note.h
 *
 */

#ifndef NOTE_H_
#define NOTE_H_

#define C4		3822
#define C4s		3608
#define D4 		3405
#define E4b		3214
#define E4 		3034
#define F4 		2863
#define F4s		2703
#define G4 		2551
#define G4s		2408
#define A4 		2273
#define B4b		2145
#define B4 		2025
#define C5		1911
#define C5s		1804
#define D5 		1703
#define E5b		1607
#define E5 		1517
#define F5 		1432
#define F5s		1432
#define G5 		1276
#define G5s		1204
#define A5 		1136
#define B5b		1073
#define B5 		1012
#define C6		956
#define C6s		902
#define D6 		851
#define E6b		804
#define E6 		758
#define F6 		716
#define F6s		676
#define G6 		638
#define G6s		602
#define A6 		568
#define B6b		536
#define B6 		506

typedef struct {
	unsigned short C;
	unsigned short D;
	unsigned short E;
	unsigned short F;
	unsigned short G;
	unsigned short A;
	unsigned short B;
} octave_t;

#endif /* NOTE_H_ */
