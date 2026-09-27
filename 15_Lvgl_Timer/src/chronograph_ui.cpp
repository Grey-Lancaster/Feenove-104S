// #include "main_ui.h"
#include "chronograph_ui.h"
#include "lv_img.h"

lvgl_chronograph_ui guider_chronograph_ui;
static uint16_t chronograph_timer_milliseconds = 0;
static uint16_t chronograph_timer_seconds = 0;
static uint16_t chronograph_timer_minutes = 0;
static uint16_t chronograph_timer_hours = 0;
static bool chronograph_timer_state= false;

static uint32_t timer_last_millis=0;
static uint32_t timer_current_millis=0;

// Separate fixed-width label per numeric field (HH/MM/SS/CS), rather than
// one big auto-sizing label for the whole "00:00:00:00" string. Even with
// that string zero-padded to a constant character COUNT, LVGL still
// re-measures and re-centers the rendered text on every lv_label_set_text()
// call -- and this project's font (LVGL's default, a proportional font, no
// tabular/fixed-width digits) doesn't give every digit the same pixel
// advance width, so the *measured* width still wobbles by a few pixels
// tick to tick even at constant length, and centered text re-anchors on
// that wobble every redraw. Giving each field its own small fixed-width,
// center-aligned label bounds that wobble to within that one field instead
// of shifting the whole row.
static lv_obj_t *chronograph_label_hh = NULL;
static lv_obj_t *chronograph_label_mm = NULL;
static lv_obj_t *chronograph_label_ss = NULL;
static lv_obj_t *chronograph_label_cs = NULL;

static void chronograph_imgbtn_home_event_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  switch (code)
  {
  case LV_EVENT_CLICKED:
  {
    Serial.println("Clicked the logo button.");
  }
  break;
  case LV_EVENT_RELEASED:
  {
    /*
    if (!lv_obj_is_valid(guider_main_ui.main))
      setup_scr_main(&guider_main_ui);
    lv_scr_load(guider_main_ui.main);
    lv_obj_del(guider_music_ui.music);
    */
  }
  break;
  default:
    break;
  }
}

static void chronograph_imgbtn_play_event_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  switch (code)
  {
    case LV_EVENT_CLICKED:
    {
      Serial.println("Clicked the play button.");
    }
    break;
    case LV_EVENT_RELEASED:
    {
      if(chronograph_timer_state==false)
      {
        Serial.println("Resume the timer.");
        chronograph_timer_state=true;
        lv_timer_resume(guider_chronograph_ui.chronograph_timer);
        timer_last_millis = millis();
        lv_img_set_src(guider_chronograph_ui.chronograph_imgbtn_play, &img_playing);
      }
      else
      {
        Serial.println("Pause the timer.");
        chronograph_timer_state=false;
        lv_timer_pause(guider_chronograph_ui.chronograph_timer);
        lv_img_set_src(guider_chronograph_ui.chronograph_imgbtn_play, &img_pause);
      }
    }
    break;
    default:
      break;
  }
}

static void chronograph_imgbtn_stop_event_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  switch (code)
  {
    case LV_EVENT_CLICKED:
    {
      Serial.println("Clicked the stop button.");
    }
    break;
    case LV_EVENT_RELEASED:
    {

        Serial.println("Reset the timer.");
        chronograph_timer_state=false;
        lv_timer_reset(guider_chronograph_ui.chronograph_timer);
        lv_timer_pause(guider_chronograph_ui.chronograph_timer);
        lv_img_set_src(guider_chronograph_ui.chronograph_imgbtn_play, &img_pause);
        chronograph_timer_milliseconds = 0;
        chronograph_timer_seconds = 0;
        chronograph_timer_minutes = 0;
        chronograph_timer_hours = 0;
        lv_label_set_text(chronograph_label_hh, "00");
        lv_label_set_text(chronograph_label_mm, "00");
        lv_label_set_text(chronograph_label_ss, "00");
        lv_label_set_text(chronograph_label_cs, "00");
    }
    break;
    default:
      break;
  }
}
static void chronograph_timer_event_handler(lv_timer_t *timer)
{
  char buf[8];
  timer_current_millis = millis();
  if(timer_current_millis > timer_last_millis)
  {
    chronograph_timer_milliseconds = chronograph_timer_milliseconds + (timer_current_millis - timer_last_millis);
    timer_last_millis = timer_current_millis;
  }
  if (chronograph_timer_milliseconds >= 1000)
  {
    chronograph_timer_milliseconds = chronograph_timer_milliseconds - 1000;
    chronograph_timer_seconds++;
  }
  if (chronograph_timer_seconds >= 60)
  {
    chronograph_timer_seconds = 0;
    chronograph_timer_minutes++;
  }
  if (chronograph_timer_minutes >= 60)
  {
    chronograph_timer_minutes = 0;
    chronograph_timer_hours++;
  }
  if (chronograph_timer_hours >= 24)
  {
    chronograph_timer_hours = 0;
  }
  // Each field updated independently (in its own fixed-width label) rather
  // than rebuilding one big string -- see the field labels' declaration
  // above for why.
  lv_snprintf(buf, sizeof(buf), "%02d", chronograph_timer_hours);
  lv_label_set_text(chronograph_label_hh, buf);
  lv_snprintf(buf, sizeof(buf), "%02d", chronograph_timer_minutes);
  lv_label_set_text(chronograph_label_mm, buf);
  lv_snprintf(buf, sizeof(buf), "%02d", chronograph_timer_seconds);
  lv_label_set_text(chronograph_label_ss, buf);
  lv_snprintf(buf, sizeof(buf), "%02d", chronograph_timer_milliseconds/10);
  lv_label_set_text(chronograph_label_cs, buf);
}

// Parameter configuration function on the chronograph screen
void setup_scr_chronograph(lvgl_chronograph_ui *ui)
{
  // Write codes picture
  ui->chronograph = lv_obj_create(NULL);
  // Root screens default to scrollable in LVGL, which shows as a stray
  // arc at the screen edge if any child sits at/past the object's edge --
  // music_ui.cpp/echo_ui.cpp already disable this for their own screens.
  lv_obj_clear_flag(ui->chronograph, LV_OBJ_FLAG_SCROLLABLE);
  lv_coord_t screen_width = lv_obj_get_width(ui->chronograph);
  lv_coord_t screen_height = lv_obj_get_height(ui->chronograph);

  static lv_style_t bg_style;
  lv_style_init(&bg_style);
  lv_style_set_bg_color(&bg_style, lv_color_hex(0xffffff));
  lv_obj_add_style(ui->chronograph, &bg_style, LV_PART_MAIN);

  lv_img_home_init();
  lv_img_playing_init();
  lv_img_pause_init();
  lv_img_stop_init();

  ui->chronograph_home = lv_imgbtn_create(ui->chronograph);
  lv_obj_remove_style_all(ui->chronograph_home);
  lv_obj_set_size(ui->chronograph_home, 100, 100);  // FNK0104S value (matches lv_img.h's SELECT_IMG_HOME)
  lv_img_set_src(ui->chronograph_home, &img_home);
  lv_obj_align(ui->chronograph_home, LV_ALIGN_TOP_MID, 0, (screen_height - 180) / 4);
  static lv_style_t style_pr;             // Apply for a style
  lv_style_init(&style_pr);               // Initialize it
  lv_style_set_translate_y(&style_pr, 5); // Style: Every time you trigger, move down 5 pixels
  lv_obj_add_style(ui->chronograph_home, &style_pr, LV_STATE_PRESSED);

  ui->chronograph_btn_show = lv_btn_create(ui->chronograph);
  lv_obj_remove_style_all(ui->chronograph_btn_show);
  lv_obj_set_size(ui->chronograph_btn_show, (screen_width - 40), 40);
  lv_obj_align_to(ui->chronograph_btn_show, ui->chronograph_home, LV_ALIGN_OUT_BOTTOM_MID, 0, (screen_height - 180) / 4);
  static lv_style_t style_show;
  lv_style_init(&style_show);
  lv_style_set_border_width(&style_show, 2);
  lv_style_set_border_color(&style_show, lv_color_black());
  lv_obj_add_style(ui->chronograph_btn_show, &style_show, LV_PART_MAIN);

  // HH:MM:SS:CS as four separate fixed-width fields (see their declaration
  // above for why) in a centered flex row, rather than one label holding
  // the whole string.
  lv_obj_set_flex_flow(ui->chronograph_btn_show, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(ui->chronograph_btn_show, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

  static const lv_coord_t field_w = 34;
  static const lv_coord_t colon_w = 12;

  chronograph_label_hh = lv_label_create(ui->chronograph_btn_show);
  lv_obj_set_width(chronograph_label_hh, field_w);
  lv_obj_set_style_text_align(chronograph_label_hh, LV_TEXT_ALIGN_CENTER, 0);
  lv_label_set_text(chronograph_label_hh, "00");

  lv_obj_t *colon1 = lv_label_create(ui->chronograph_btn_show);
  lv_obj_set_width(colon1, colon_w);
  lv_obj_set_style_text_align(colon1, LV_TEXT_ALIGN_CENTER, 0);
  lv_label_set_text(colon1, ":");

  chronograph_label_mm = lv_label_create(ui->chronograph_btn_show);
  lv_obj_set_width(chronograph_label_mm, field_w);
  lv_obj_set_style_text_align(chronograph_label_mm, LV_TEXT_ALIGN_CENTER, 0);
  lv_label_set_text(chronograph_label_mm, "00");

  lv_obj_t *colon2 = lv_label_create(ui->chronograph_btn_show);
  lv_obj_set_width(colon2, colon_w);
  lv_obj_set_style_text_align(colon2, LV_TEXT_ALIGN_CENTER, 0);
  lv_label_set_text(colon2, ":");

  chronograph_label_ss = lv_label_create(ui->chronograph_btn_show);
  lv_obj_set_width(chronograph_label_ss, field_w);
  lv_obj_set_style_text_align(chronograph_label_ss, LV_TEXT_ALIGN_CENTER, 0);
  lv_label_set_text(chronograph_label_ss, "00");

  lv_obj_t *colon3 = lv_label_create(ui->chronograph_btn_show);
  lv_obj_set_width(colon3, colon_w);
  lv_obj_set_style_text_align(colon3, LV_TEXT_ALIGN_CENTER, 0);
  lv_label_set_text(colon3, ":");

  chronograph_label_cs = lv_label_create(ui->chronograph_btn_show);
  lv_obj_set_width(chronograph_label_cs, field_w);
  lv_obj_set_style_text_align(chronograph_label_cs, LV_TEXT_ALIGN_CENTER, 0);
  lv_label_set_text(chronograph_label_cs, "00");

  ui->chronograph_imgbtn_play = lv_imgbtn_create(ui->chronograph);
  lv_obj_set_size(ui->chronograph_imgbtn_play, 60, 60);
  lv_img_set_src(ui->chronograph_imgbtn_play, &img_pause);
  lv_obj_align_to(ui->chronograph_imgbtn_play, ui->chronograph_btn_show, LV_ALIGN_OUT_BOTTOM_MID, -(screen_width - 120) / 3, (screen_height - 180) / 4);
  lv_obj_add_style(ui->chronograph_imgbtn_play, &style_pr, LV_STATE_PRESSED);

  ui->chronograph_imgbtn_stop = lv_imgbtn_create(ui->chronograph);
  lv_obj_set_size(ui->chronograph_imgbtn_stop, 60, 60);
  lv_img_set_src(ui->chronograph_imgbtn_stop, &img_stop);
  lv_obj_align_to(ui->chronograph_imgbtn_stop, ui->chronograph_btn_show, LV_ALIGN_OUT_BOTTOM_MID, (screen_width - 120) / 3, (screen_height - 180) / 4);
  lv_obj_add_style(ui->chronograph_imgbtn_stop, &style_pr, LV_STATE_PRESSED);

  lv_obj_add_event_cb(ui->chronograph_home, chronograph_imgbtn_home_event_handler, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(ui->chronograph_imgbtn_play, chronograph_imgbtn_play_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui->chronograph_imgbtn_stop, chronograph_imgbtn_stop_event_handler, LV_EVENT_ALL, NULL);

  ui->chronograph_timer = lv_timer_create(chronograph_timer_event_handler, 1, NULL);
  lv_timer_pause(ui->chronograph_timer);
}
