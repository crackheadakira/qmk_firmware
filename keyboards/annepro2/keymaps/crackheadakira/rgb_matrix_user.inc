// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(gay_flag)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool gay_flag(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = 0; i <= 13; i++) {
        rgb_matrix_set_color(i, 0xff, 0x00, 0x00);
    }
    for (uint8_t i = 14; i <= 27; i++) {
        rgb_matrix_set_color(i, 0xff, 0xff, 0x00);
    }
    for (uint8_t i = 28; i <= 40; i++) {
        rgb_matrix_set_color(i, 0x00, 0xff, 0x00);
    }
    for (uint8_t i = 41; i <= 52; i++) {
        rgb_matrix_set_color(i, 0x00, 0x00, 0xff);
    }
    for (uint8_t i = 53; i <= 60; i++) {
        rgb_matrix_set_color(i, 0xff, 0x00, 0xff);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS