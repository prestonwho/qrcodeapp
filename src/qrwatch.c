#include "qrwatch.h"


void click_handler(ClickRecognizerRef recognizer, void *context)
{
  
  if(click_recognizer_get_button_id(recognizer) == BUTTON_ID_UP)
  {
    qr_str = qr_str1;
    tick_timer_service_subscribe(SECOND_UNIT, update_time);
  }
    
  else
  {
    tick_timer_service_unsubscribe();
    
    if(click_recognizer_get_button_id(recognizer) == BUTTON_ID_SELECT)
      { qr_str = qr_str2; }
  
    if(click_recognizer_get_button_id(recognizer) == BUTTON_ID_DOWN)
      { qr_str = qr_str3; }
  }
  
  update_qr();  //layer_mark_dirty(qr_layer);
}


static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, click_handler);
}
  
  
  
void qr_draw(Layer *layer, GContext* ctx) {
	if(qr_width == 0) return;
	int byte = 0;
	int bit = 7;

	GRect layer_size = layer_get_bounds(layer);
	int block_size = layer_size.size.w / qr_width;
	int padding_x = (layer_size.size.w - (block_size * qr_width)) / 2;
	int padding_y = (layer_size.size.h - (block_size * qr_width)) / 2;

	void *data = layer_get_data(layer);
	for(int y=0;y<qr_width;++y) {
		for(int x=0;x<qr_width;++x) {
			int value = (*((unsigned char*)data + byte)) & (1 << bit);
			if(--bit < 0) {
				bit = 7;
				++byte;
			}

			if(value)
				graphics_fill_rect(ctx, (GRect){.origin={padding_x+x*block_size, padding_y+y*block_size}, .size={block_size, block_size}}, 0, GCornerNone);
		}
	}
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  qr_layer = layer_create_with_data((GRect) { .origin = {0, 0}, .size = {bounds.size.w, bounds.size.h} }, MAX_BITDATA);
  layer_set_update_proc(qr_layer, qr_draw);
  layer_add_child(window_layer, qr_layer);

  update_qr();
  
  
  
  //time_layer = text_layer_create((GRect) { .origin = {bounds.size.w/2 - 20, bounds.size.h/2 - 20}, .size = {30, 20}});

  //qr_layer = layer_create_with_data((GRect) { .origin = {0, 0}, .size = {bounds.size.w, bounds.size.h} }, MAX_BITDATA);

  
  /*
  time_layer = text_layer_create(GRect(0, 133, 144, 50));
  text_layer_set_text_color(time_layer, GColorBlack); // Create time TextLayer
  text_layer_set_background_color(time_layer, GColorClear);
  text_layer_set_text(time_layer, "00/00    00:00");
  
  

  // Improve the layout to be more like a watchface
  text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
  
  //layer_set_update_proc(qr_layer, qr_draw);
  //layer_add_child(window_layer, qr_layer);
  
  

  layer_add_child(window_layer, text_layer_get_layer(time_layer));
  
  */
  
  // time_layer = text_layer_create((GRect) { .origin = {bounds.size.w/2 - 20, bounds.size.h/2 - 20}, .size = {30, 20}});
  // layer_add_child(window_layer, text_layer_get_layer(time_layer));
}

static void window_unload(Window *window) {
	layer_destroy(qr_layer);
	//text_layer_destroy(time_layer);
}

static void update_qr()
{
  //unsigned char* data = layer_get_data(qr_layer);
  void *data = layer_get_data(qr_layer);
	qr_width = EncodeData(QR_LEVEL_L, 0, qr_str, 0, data);
	layer_mark_dirty(qr_layer);
}

static void update_time(struct tm *tick_time, TimeUnits units_changed) {
  
  char date_str[64];
  //SHA1Context sha;
  //int err;
  //uint8_t Message_Digest[20];
  
  //err = SHA1Reset(&sha);
  
  
  // Create a long-lived buffer
  //static char buffer[] = "00/00    00:00";
  
  
  //time_t temp = time(NULL); 
  //struct tm *tick_time_foo = localtime(&temp);
  
	/*
  // Create a long-lived buffer
  static char buffer[] = "00/00    00:00";
*/

  // Write the current hours and minutes into the buffer
  /*if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(buffer, sizeof("00/00    00:00"), "%m/%d    %H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(buffer, sizeof("00/00    00:00"), "%m/%d    %I:%M", tick_time);
  }*/
  
  //strcpy(qr_str1,buffer);

  // Display this time on the TextLayer
  //text_layer_set_text(time_layer, buffer);
  

  
  //data = layer_get_data(qr_layer);
  
	//pw - clock_copy_time_string(time_str, 6);
	
	strftime(date_str, 64, "%Y-%m-%d %H:%M:%S", tick_time);
  
  //err = SHA1Input(&sha,
  //                (unsigned char *) date_str,
  //                strlen(date_str));
  
  //err = SHA1Result(&sha, (unsigned char *) qr_str1);

	//strcpy(qr_str, time_str);
  // put the date in qr_str1... if qr_str happens to == qr_str1 then it'll be my qr code.
	
  strcpy(qr_str1, date_str);
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "error: %s", date_str);
  
  update_qr();
}








static void init(void) {
  
  window = window_create();
  
  //window_set_fullscreen(window, true);
  window_set_click_config_provider(window, click_config_provider);
  
  //qr_str1 = malloc(sizeof(char)*64);
  
  
  //qr_str2 = malloc(sizeof(char)*17);
  
  
  //qr_str3 = malloc(sizeof(char)*96);
  
  
  //if()
  
  strcpy(qr_str1,"pending...");
  strcpy(qr_str2,"http://3qr.org/a");
  strcpy(qr_str3,"aes=:=U2FsdGVkX1+qNAmRguomLb5NVs1f8BT2kvmZdmVSApzo8x5jaH9tNUqZqTIe02Kf9faW4EmwV4lpPVrCJFp69A==");

  
  qr_str = qr_str2;
  
  

  
  
  
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
  
  
  //strcpy(qr_str1,"pending...");
  
  

  
  
  //tick_timer_service_subscribe(MINUTE_UNIT, update_time);
  
  
  
}

static void deinit(void) {
  window_destroy(window);
  
  //free(qr_str1);
  //free(qr_str2);
  //free(qr_str3);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
