#ifndef __CHRONOGRAPH_UI_H
#define __CHRONOGRAPH_UI_H

#include "public.h"

typedef struct lvgl_chronograph
{
	lv_obj_t *chronograph;
  lv_obj_t *chronograph_home;

  lv_obj_t *chronograph_imgbtn_play;
  lv_obj_t *chronograph_imgbtn_stop;
  lv_obj_t *chronograph_btn_show;

  // Time readout is four separate fixed-width field labels
  // (chronograph_label_hh/mm/ss/cs, file-scope statics in
  // chronograph_ui.cpp) rather than one member here -- see their
  // declaration in that file for why.
  lv_timer_t *chronograph_timer;
}lvgl_chronograph_ui;

extern lvgl_chronograph_ui guider_chronograph_ui;    //chronograph ui structure 

void setup_scr_chronograph(lvgl_chronograph_ui *ui); //Parameter configuration function on the chronograph screen

#endif
