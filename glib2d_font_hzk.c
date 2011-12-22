
#include "glib2d.h"
#include "glib2d_font_hzk.h"

#define TEXTURE_SIZE                512
#define GLYPH_WIDTH                 16
#define GLYPH_HEIGHT                16
#define MAX_ROW_PER_TEXTURE         TEXTURE_SIZE/GLYPH_WIDTH
#define MAX_LINE_PER_TEXTURE        TEXTURE_SIZE/GLYPH_HEIGHT

#define MAX_CHARCTER_PER_TEXTURE     MAX_ROW_PER_TEXTURE*MAX_LINE_PER_TEXTURE

#define TEXTURE_NUM         

#define HASH(word)  	((unsigned char)(word)[0]-176)*94 + (unsigned char)(word)[1] - 161
//#define MAX_WORD	    (unsigned char)(0xfe-176)*94 + (unsigned char)0xfe - 161
#define MAX_WORD	     7478

//TODO a font manage list

static unsigned int current_id=0;
static g2dFont * obj_font;
static char * obj_text;


g2dFont* g2dLoadFont(const char *name){
    g2dFont* font=(g2dFont*)malloc(sizeof(g2dFont));
	strncpy(font->name,name,255);	
    font->HZK=fopen(name,"rb");
    font->hzk_texture=_g2dTexCreate(512,512,false);
    return font;
}

void g2dFreeFont(g2dFont * font){
     fclose(font->HZK);
     g2dTexFree(&font->hzk_texture);
     free(font);
}



int g2dInitCHAR(CHAR* c, g2dFont* font){

	int x=c->tx, y=c->ty, xx, yy;
	int j, k;


	int qh,wh;	
	unsigned long offset;

	unsigned char mat[32]={0};
	
	qh=c->incode[0]-0xa0;
	wh=c->incode[1]-0xa0;

	offset = ( 94*(qh-1) + (wh-1) ) * 32;

	fseek(font->HZK,offset,SEEK_SET);
	fread(mat,32,1,font->HZK);

	for(yy=0;yy<16;yy++) {
		for(j=0;j<2;j++)
		{
			for(k=0;k<8;k++)
			{                
                xx=j*8+k;
				if(mat[yy*2+j] & (0x80>>k)){
                     //font->hzk_texture->data[(y+yy)*512+x+xx]=WHITE;
                     // am I right?
                     memset(font->hzk_texture->data+(y+yy)*512+x+xx,WHITE,sizeof(WHITE));
                }
			}
		}
	}
    return 0;
}


CHAR* g2dCacheCHAR(unsigned char word[2],g2dFont* font){
    int i=((unsigned char)(word)[0]-176)*94 + (unsigned char)(word)[1] - 161;
    if (font->gbk_map[i] == NULL)
    {
           font->gbk_map[i]=( CHAR*)malloc(sizeof(CHAR));
           font->gbk_map[i]->incode[0]=word[0];
	       font->gbk_map[i]->incode[1]=word[1];
	       font->gbk_map[i]->id=current_id;
	       font->gbk_map[i]->tx=current_id%16*16;
	       font->gbk_map[i]->ty=current_id/16*16;
	       font->gbk_map[i]->p=current_id/1024;	
	       font->gbk_map[i]->cached=true;

           g2dInitCHAR(font->gbk_map[i],font);

           current_id++;
    }
	return font->gbk_map[i];
}



void g2dCHARPrint(const CHAR *c){
    

    g2dSetCropWH(16,16); 
    g2dSetCropXY(c->tx,c->ty); 
    g2dAdd(); 
}

void g2dFontBegin(g2dFont* font){
     g2dBeginRects(font->hzk_texture);
     obj_font=font;
     g2dSetScaleWH(16,16);
}

void g2dSetText(unsigned char *text){
    obj_text=text;
}
void g2dFontAdd(void){
    CHAR* tmp;
    unsigned char word[2];
    char* text=obj_text;
    g2dFont* font=obj_font;
    float size_w,size_h, x,y;
    while(*text!=0){

           word[0]=*text;
           word[1]=*(text+1);
           
           tmp=g2dCacheCHAR (word,font);
           g2dCHARPrint(tmp);
           text+=2;
           
           g2dGetScaleWH(&size_w,&size_h);
           g2dGetCoordXYZ(&x,&y,NULL);           
           if (x+size_w>480){
              g2dSetCoordXYRelative(-x,size_h);
           }
           else {
              g2dSetCoordXYRelative(size_w,0);
           }


    } 
    obj_text="" ;
}
