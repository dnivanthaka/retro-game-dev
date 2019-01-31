#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <bios.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

word_t raw_scan_code;
word_t keyboard_state[128];
word_t keys_active;

//old keyboard isr
void _interrupt (_far *old_keyboard_isr)(...);

void _interrupt _far keyboard_driver(...)
{
	_asm{
		sti
		in al, KEY_BUFFER
		xor ah, ah
		mov raw_scan_code, ax
		in al, KEY_CONTROL
		or al, 82h
		out KEY_CONTROL, al
		and al, 7fh
		out KEY_CONTROL, al
		mov al, 20h
		out PIC_PORT, al
	}

	if(raw_scan_code < 128){
		if(keyboard_state[raw_scan_code] == KEY_UP){
			keys_active++;

			keyboard_state[raw_scan_code] = KEY_DOWN;
		}
	}else{
		if(keyboard_state[raw_scan_code] == KEY_DOWN){
			keys_active--;

			keyboard_state[raw_scan_code] = KEY_UP;
		}
	}
}

void keyboard_install_driver()
{
	int i;
	for(i=0;i<128;i++){
		keyboard_state[i] = 0;
	}

	old_keyboard_isr = _dos_getvect(KEYBOARD_INTERRUPT);

	_dos_setvect(KEYBOARD_INTERRUPT, keyboard_driver);
}

void keyboard_remove_driver()
{
	_dos_setvect(KEYBOARD_INTERRUPT, old_keyboard_isr);
}

byte_t get_key()
{
	if(_bios_keybrd(_KEYBRD_READY)){
		return ((byte_t)_bios_keybrd(_KEYBRD_READ));
	}else{
		return 0;
	}
}



int main(void){

	//setmode(VGA_256_COLOR_MODE);
	//vgafill(0x09);

	//while(!kbhit());
	//printf("%d\n", get_key());
	//byte_t key;
	//while((key = get_key()) == 0){}
	//printf("%d\n", key);
	keyboard_install_driver();
	//timer_start();
	while(!keyboard_state[MAKE_ESC]){
		timer_start();
		printf("%d\n", raw_scan_code);
		qword_t ticks = timer_getticks();
		// 1s = 18.2
		while(ticks < 18){
		  ticks = timer_getticks();
		}
	}
	keyboard_remove_driver();

	//setmode(TEXT_MODE);

	return 0;
}



