#ifdef ENABLE_RGB_MATRIX_RIVERFLOW_RGB
RGB_MATRIX_EFFECT(RIVERFLOW_RGB)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// inspired by @PleasureTek's Massdrop Alt LED animation

bool RIVERFLOW_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        HSV      hsv  = rgb_matrix_config.hsv;
        uint16_t time = scale16by8(g_rgb_timer + (i * 315), rgb_matrix_config.speed / 8);
        uint16_t rgb_time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 4, 1));
        hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
        hsv.h         = g_led_config.point[i].x - rgb_time;
        RGB rgb       = rgb_matrix_hsv_to_rgb(hsv);
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_RIVERFLOW_RGB