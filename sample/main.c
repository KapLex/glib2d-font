// Control object properties.



#include <pspkernel.h>
#include <pspctrl.h>
#include "../src/glib2d.h"
#include "../src/glib2d_font_hzk.h"
#include "../src/glib2d_font_ascii.h"

#define TEXSIZE 256;
PSP_MODULE_INFO("App",0,1,1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

/* Callbacks */
int exit_callback(int arg1, int arg2, void *common) {
  sceKernelExitGame();
  return 0; }
int CallbackThread(SceSize args, void *argp) {
  int cbid;
  cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
  sceKernelRegisterExitCallback(cbid);
  sceKernelSleepThreadCB();
  return 0; }
int SetupCallbacks() {
  int thid = 0;
  thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
  if(thid >= 0) sceKernelStartThread(thid, 0, 0);
  return thid; }

/**/





int main()
{


  SetupCallbacks();
  g2dFont* font=g2dLoadFont("HZK16");
  g2dFont_ASCII* asc_font=g2dLoadFont_ASCII("ASC16");  
 // g2dInitFont();

  while (1)
  {
    // Display

    g2dClear(BLACK); 


   g2dFontBegin(font);
   g2dSetScaleWH(32,32);
   g2dSetText("你好，中文世界！");
   g2dFontAdd();
   
   
   g2dEnd();
   
   g2dFontBegin_ASCII(asc_font);
   g2dSetCoordXY(0,100);
   g2dSetScaleWH(20,20);

   g2dSetColor(GREEN);
   g2dSetText_ASCII("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
   g2dFontAdd_ASCII();
      
   g2dSetRotationRad(1.14); 
   g2dSetCoordXY(200,150);
   g2dSetText_ASCII("Hello");
   g2dFontAdd_ASCII();  



   g2dEnd();   
   
   
   
   g2dFlip(G2D_VSYNC);
   }
   
  g2dFreeFont(font);
  sceKernelExitGame();
  return 0;
}
