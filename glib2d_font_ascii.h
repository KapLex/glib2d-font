
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "glib2d.h"



typedef struct {
    //name of font file    
    char name[256];
    
    //font file
    FILE *ASC;
    
    //texture for writing data
    g2dImage *asc_texture;
    
    //charater map
    unsigned int ascii_map[256];
}g2dFont_ASCII;

g2dFont_ASCII * g2dLoadFont_ASCII(const char *name);

void g2dFontBegin_ASCII(g2dFont_ASCII* font);

void g2dSetText_ASCII(unsigned char *text);

void g2dFontAdd_ASCII(void);

void g2dFreeFont_ASCII(g2dFont_ASCII  * font);
