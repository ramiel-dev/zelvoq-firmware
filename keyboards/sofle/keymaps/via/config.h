/* Copyright 2020 Josef Adamcik
 * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
 * Migrado al External Userspace de Zelvoq desde QMK 0.23.9.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* Comportamiento heredado del arbol congelado 0.23.9. */
#define SPLIT_USB_DETECT
#define TAPPING_TERM 100

/* Underglow (RGBLIGHT).
 *
 * El pin de datos (D3), el conteo de LEDs (72) y el reparto por mitad (36/36)
 * los aporta keyboards/sofle/info.json de upstream. NO redeclararlos aqui:
 * en 0.23.9 estaban en este config.h como WS2812_DI_PIN / RGBLED_NUM /
 * RGBLED_SPLIT, y RGBLED_NUM ya se llama RGBLIGHT_LED_COUNT.
 *
 * Se usa RGBLIGHT, no RGB_MATRIX, para conservar el comportamiento que
 * tienen hoy los teclados vendidos. El PCB soporta ambos sobre el mismo pin.
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
/* RGBLIGHT_EFFECT_TWINKLE queda deshabilitado a proposito, igual que en 0.23.9. */
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

/* --- Ahorro de flash (AVR ATmega32U4, 28672 bytes) ---
 *
 * QMK 0.34.6 crece ~780 bytes respecto a 0.23.9 y el build quedaba al 99%.
 * Lo de abajo no le quita ninguna funcion al usuario final:
 *
 * - LAYER_STATE_8BIT: VIA usa 4 capas; el default son 16. Nada que perder.
 * - LOCKING_SUPPORT: solo sirve con un switch Cherry MX Lock fisico.
 */
#define LAYER_STATE_8BIT
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
