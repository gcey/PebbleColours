#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_text_layers[8][8];

static void main_window_load(Window *window) {
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      s_text_layers[i][j] = text_layer_create(GRect(18 * j, 21 * i, 18, 21));
      text_layer_set_background_color(s_text_layers[i][j], (GColor8){.argb = 192 + (8 * i) + j});
      layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layers[i][j]));
    }
  }
}

static void main_window_unload(Window *window) {
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      text_layer_destroy(s_text_layers[i][j]);
    }
  }
}

static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
}

static void deinit() {
    // Destroy main Window
    window_destroy(s_main_window);
}

int main(void) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Enter main()");
  init();
  app_event_loop();
  deinit();
}
