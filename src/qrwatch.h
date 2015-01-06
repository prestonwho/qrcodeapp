#include <pebble.h>
#include "QR_Encode.h"
//#include "sha1.h"

static Window *window;
static Layer *qr_layer;
//static TextLayer *time_layer;

//static TextLayer *time_layer = NULL;
//static char time_str[6];
static char qr_str1[256];
static char qr_str2[256];
static char qr_str3[256];

char *qr_str;
//char *qr_str1;
//char *qr_str2;
//char *qr_str3;

static int qr_width;

//static unsigned char* data;

// TODO: Have this caluclated from font somehow, instead of hardcoding width and height?
#define TIME_SIZE_BLOCKS_W 6
#define TIME_SIZE_BLOCKS_H 3

  
void click_handler(ClickRecognizerRef recognizer, void *context);

static void click_config_provider(void *context);
  
  
  
void qr_draw(Layer *layer, GContext* ctx);

static void window_load(Window *window);

static void window_unload(Window *window);

static void update_qr();

static void update_time(struct tm *tick_time, TimeUnits units_changed);

static void init(void);

static void deinit(void);

int main(void);