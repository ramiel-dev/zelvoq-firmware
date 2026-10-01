/*
This is the c configuration file for the keymap
Migrado al External Userspace de Zelvoq desde QMK 0.23.9.

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

//#define USE_MATRIX_I2C

/* Select hand configuration.
 * Unica diferencia real respecto al keymap via oficial: el arbol 0.23.9
 * forzaba master = mitad izquierda. Se conserva para no cambiar el
 * comportamiento de los teclados ya vendidos. */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define QUICK_TAP_TERM 0
#define TAPPING_TERM 100

// Underglow (bloque inactivo, igual que en 0.23.9).
// RGBLED_NUM paso a llamarse RGBLIGHT_LED_COUNT en QMK moderno.
/*
#undef RGBLIGHT_LED_COUNT
#define RGBLIGHT_LED_COUNT 14    // Number of LEDs
#define RGBLIGHT_SLEEP
*/
