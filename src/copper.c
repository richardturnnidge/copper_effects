// copper effects routines

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include <agon/vdp.h>

// ---------------------------------------------------------------------------------
// put a word out to VDP in order LSB,MSB 
void putword(uint16_t theWord){
  putch(theWord % 256);      // minibitmap ID
  putch(theWord >> 8);       // word
}


// ---------------------------------------------------------------------------------



void vdp_copper_enable(void){
    // VDU 23, 0, &F8, &310; 0;
    putch(23);                   // vdu command
    putch(0);
    putch(0xF8);

    putword(0x0310);          // 

    putword(0);                    // command

}



void vdp_copper_create_palette(uint16_t paletteID){
  // VDU 23, 0, &C4, 0, <paletteID>;

    putch(23);                   // vdu command
    putch(0);
    putch(0xC4);

    putch(0);                    // command

    putword(paletteID);          // palette ID

}

void vdp_copper_delete_palette(uint16_t paletteID){
  // VDU 23, 0, &C4, 1, <paletteID>;

    putch(23);                    // vdu command
    putch(0);
    putch(0xC4);

    putch(1);                    // option

    putword(paletteID);          // palette ID

}

void vdp_copper_set_palette_entry(uint16_t paletteID, uint8_t indx, uint8_t red, uint8_t green, uint8_t blue ){
  // VDU 23, 0, &C4, 2, <paletteID>; <index>, <red>, <green>, <blue>

    putch(23);                    // vdu command
    putch(0);
    putch(0xC4);

    putch(2);                    // option

    putword(paletteID);          // palette ID

    putch(indx);                 // index

    putch(red);                  // colour value
    putch(green);                // colour value
    putch(blue);                 // colour value

}

void vdp_copper_set_signal_list(uint16_t bufferID ){
    // VDU 23, 0, &C4, 3, <bufferId>;

    putch(23);                    // vdu command
    putch(0);
    putch(0xC4);

    putch(3);                    // option

    putword(bufferID);          // palette ID

}

void vdp_copper_reset_signal_list(void ){
    // VDU 23, 0, &C4, 4

    putch(23);                    // vdu buffer command
    putch(0);
    putch(0xC4);

    putch(4);                    // option

}


