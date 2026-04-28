// copper effects routines

#ifndef COPPER_H
#define COPPER_H


void vdp_copper_create_palette(uint16_t paletteID);
void vdp_copper_delete_palette(uint16_t paletteID);
void vdp_copper_set_palette_entry(uint16_t paletteID, uint8_t indx, uint8_t red, uint8_t green, uint8_t blue );
void vdp_copper_set_signal_list(uint16_t bufferID );
void vdp_copper_reset_signal_list(void );
void vdp_copper_enable(void);
void putword(uint16_t theWord);

#endif