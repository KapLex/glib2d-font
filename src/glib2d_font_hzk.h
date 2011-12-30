
#ifndef GLIB2D_FONT_HZK_H
#define GLIB2D_FONT_HZK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct {
    unsigned char incode[2];
    //x,y in the texture 
    //p for which texture
    unsigned int tx;
    unsigned int ty;
    unsigned int p;
    unsigned int id;
    bool     cached ;
}CHAR;

typedef struct {
    //name of font file    
    char name[256];    
    //font file
    FILE *HZK;    
    //texture for writing data
    g2dImage *hzk_texture;    
    //charater map
    CHAR* gbk_map[7425];

}g2dFont;


g2dFont* g2dLoadFont( char *name);

void g2dFreeFont(g2dFont * font);

void g2dFontBegin(g2dFont* font);

void g2dSetText( char *text);

void g2dFontAdd(void);

#ifdef __cplusplus
}
#endif

#endif
