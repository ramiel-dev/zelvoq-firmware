/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Migrado al External Userspace de Zelvoq desde QMK 0.23.9.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Select hand configuration. El arbol 0.23.9 forzaba master = izquierda. */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define SPLIT_USB_DETECT

/* Underglow (RGBLIGHT).
 *
 * El conteo de LEDs (54), el reparto por mitad (27/27), el pin de datos (D3) y
 * el brillo maximo (120) los aporta crkbd/rev1/keyboard.json y crkbd/info.json
 * de upstream. En 0.23.9 estaban a mano aqui y en rev1/config.h como
 * RGBLED_NUM / RGBLED_SPLIT / RGBLIGHT_LIMIT_VAL; ya no hace falta.
 *
 * Los efectos y los pasos de ajuste si siguen siendo cosa del keymap.
 * Se mantienen los 10 que tenia el arbol viejo: el keymap via oficial deja
 * RGB_TEST, ALTERNATING y TWINKLE comentados, nosotros no.
 */
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
