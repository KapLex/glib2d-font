#include "glib2d_font_ascii.h"
 
static const unsigned char EN_FONT_CHARSET []=

        " .,!?:;"
    	"0123456789"
    	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    	"abcdefghijklmnopqrstuvwxyz"
    	"@#\"?%^&*()[]{}<>/\\|~`+-=_~"

;

static g2dFont_ASCII * obj_font_ascii;

static char * obj_text_ascii;


void g2dFreeFont_ASCII(g2dFont_ASCII  * font){

     g2dTexFree(&font->asc_texture);
     free(font);
}


g2dFont_ASCII * g2dLoadFont_ASCII(const char *name){
    int i, xx, yy;
    int x=0; int y=0; 
    unsigned long offset;
    char ascii[16];

    g2dFont_ASCII* font=(g2dFont_ASCII*)malloc(sizeof(g2dFont_ASCII));
	strncpy(font->name,name,255);
    font->ASC=fopen(name,"rb");
    font->asc_texture=_g2dTexCreate(256,256,false);

    for (i = 0; i < sizeof(EN_FONT_CHARSET)-1; i++){
        font->ascii_map[EN_FONT_CHARSET[i]]=i;
        offset = EN_FONT_CHARSET[i]*16;
        fseek(font->ASC,offset,SEEK_SET);
        fread(ascii,16,1,font->ASC);              /* ¶ÁÈ¡16×Ö½Ú */
        if((x + 8) > 256){
              y +=16;
              x = 0;
        }
        if((y + 16) > 256){
              y=0;
        }
                
        for(yy=0;yy<16;yy++){
              for(xx=0;xx<8;xx++){
                  if(ascii[yy] & (0x80>>xx)){
                      //font->asc_texture->data[x+xx+(y+yy)*256]=WHITE;
                     // am I right?
                     memset(font->asc_texture->data+x+xx+(y+yy)*256,WHITE,sizeof(WHITE));                                                      
                  }
              }                
        }
        x+=8;              
    }


    return font;

    fclose(font->ASC);

}

void g2dFontBegin_ASCII(g2dFont_ASCII* font){
     g2dBeginRects(font->asc_texture);
     obj_font_ascii=font;
     g2dSetScaleWH(8,16);     
}
void g2dSetText_ASCII(unsigned char *text){
     obj_text_ascii=text;

}
void g2dFontAdd_ASCII(void){
    int i,tx=0,ty=0,length=0;
    g2dFont_ASCII* font=obj_font_ascii;
    char * text=obj_text_ascii;
    
    float size_w,size_h, x,y;
    
    length = strlen(text);   

    for(i = 0; i < length; i++){

        tx=font->ascii_map[text[i]&0xff]%32*8;
        ty=font->ascii_map[text[i]&0xff]/32*16;
        g2dSetCropWH(8,16); // Crop size of the texture (will draw only a part of the texture)
        g2dSetCropXY(tx,ty); // Crop position of the texture    
        g2dAdd();
        
        g2dGetScaleWH(&size_w,&size_h);
        g2dGetCoordXYZ(&x,&y,NULL);        
        if (x+size_w>480){
              g2dSetCoordXYRelative(-x,size_h);

        }
        else {
              g2dSetCoordXYRelative(size_w,0);
        }
        
    }

    obj_text_ascii="" ;
}
