/***********************************************
 * PCX File Metadata structures
 * Author: D.Nivanthaka Amerasinghe
 *
 ***********************************************/
#ifndef PCX_HEADER_TYPE
#define PCX_HEADER_TYPE

#include "types.h"

typedef struct {
	word_t x_min;
	word_t y_min;
	word_t x_max;
	word_t y_max;
} pcxwindow_t;

/*typedef struct {
	byte_t red;
	byte_t green;
	byte_t blue;
} pcxtriple_t;*/

typedef rgb_t pcxtriple_t;

typedef struct {
	byte_t manufacturer;
	byte_t version;
	byte_t encording;
	byte_t bitsperpixel;
	pcxwindow_t pcx_window;
	word_t h_dpi;
	word_t v_dpi;
	pcxtriple_t triples[16];
	byte_t reserved;
	byte_t num_planes;
	word_t bytes_per_line;
	word_t palette_info;
	//word_t h_screen_size;
	//word_t v_screen_size;
	byte_t filler[58];
} pcx_header_t;

/*typedef struct {
	byte_t indicator;
	pcxtriple_t triples[256];
} pcxextrapalette_t;*/

// this holds the PCX header and the actual image
typedef struct {
	pcx_header_t header;         // the header of the PCX file
	rgb_palette_t palette;    // the palette data
	unsigned char *buffer; // a pointer to the byte buffer                                   // holding the decompressed image

} pcx_picture_t;

//

int read_header( FILE *, pcx_header_t * );
int read_data( FILE *, pcx_picture_t * );
int read_palette( FILE *, pcx_picture_t * );
int read_pcx( char const*, pcx_picture_t * );
void pcx_delete(pcx_picture_t *);
void pcx_to_image(pcx_picture_t *pcx, image_t *image);
#endif //PCX_HEADER_TYPE
