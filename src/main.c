/*
Example of:
  1) drawing primitive graphics
  2) changing palette of various lines with copper effects
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include <agon/vdp.h>
#include "copper.h"
#include <agon/timer.h>

const uint8_t screen_mode = 19;     // 1024x768 4 cols
const uint16_t num_palettes = 4;    // number of palettes to define
const uint8_t num_colours = 4;      // number of colours in palette
const uint16_t signalListBuffer = 2001;

#define RAND256 rand() % 256  // used as quick hack in random colours

int main(void) {
  vdp_mode(screen_mode);
  vdp_cursor_enable(false);
  vdp_clear_screen();
  vdp_set_pixel_coordinates();

  printf("AgonDev Primative Copper Effects Example\n\n");
  printf("Press ESC to Exit\n\n");

  srand(time(NULL));              // set rand seed 
  vdp_adv_clear_buffer(65535);    // clear all buffers as good measure
  vdp_copper_enable();            // set flag to enable copper effects

  vdp_copper_delete_palette(65535); // clear all in case
  vdp_copper_create_palette(1);     // create a palette to use (only 1 in this example, plus default)

  // set a random palette
  vdp_copper_set_palette_entry(1, 0, RAND256,   RAND256  , RAND256);
  vdp_copper_set_palette_entry(1, 1, RAND256,   RAND256  , RAND256);
  vdp_copper_set_palette_entry(1, 2, RAND256,   RAND256  , RAND256);
  vdp_copper_set_palette_entry(1, 3, RAND256,   RAND256  , RAND256);

// define copper signal lists
// need to set some buffers with lists in
// [row offset; paletteID;]
// need to do this better with an array, but quick char hack for now

  char signalList[]={ 16,   0,      0,  0,
                    1,    0,      1,  0,
                    1,    0,      0,  0,
                    1,    0,      1,  0,
                    1,    0,      0,  0,
                    1,    0,      1,  0,
                    1,    0,      0,  0,
                    1,    0,      1,  0,
                    1,    0,      0,  0,
                    1,    0,      1,  0,
                    20,   0,      0,  0,                  
                    100,  0,      1,  0,
                    50,   0,      0,  0,
                    100,  0,      1,  0,
                    200,  0,      0,  0,
                    100,  0,      1,  0
                  };

   // put signal list into a buffer
  vdp_adv_write_block_data(signalListBuffer, sizeof(signalList), signalList);
  
  // draw some shapes on the screen, colour 0 black background

  //tringle red colour 1
  vdp_set_graphics_fg_colour( 0, 1 );
  vdp_filled_triangle( 1023,0 ,1023,767 , 0, 767 );

  // rectangle yellow colour 2
  vdp_set_graphics_fg_colour( 0, 2 );
  vdp_filled_rectangle( 100,200, 420,630 );

  // circle white colour 3
  vdp_set_graphics_fg_colour( 0, 3 );
  vdp_filled_circle( 400,150 ,80 );

  //tringle red colour 1
  vdp_set_graphics_fg_colour( 0, 1 );
  vdp_filled_triangle( 200,0 ,200,50 , 100, 50 );


  // now wait for user to ESC else flip the signal list every second

  while(true) {
    if(vdp_getKeyCode() == 27) break;
    delay(1000);
    vdp_copper_set_signal_list(signalListBuffer);
    if(vdp_getKeyCode() == 27) break;
    delay(1000);
    vdp_copper_reset_signal_list();
  }

  // all done, try to exit cleanly

  vdp_copper_reset_signal_list();
  vdp_mode(1);
  vdp_clear_screen();
  vdp_cursor_enable(true);

  return 0; 
}

