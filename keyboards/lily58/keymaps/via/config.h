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

/* Handedness.
 *
 * SPLIT_USB_DETECT es obligatorio aqui, no cosmetico: sin el, el OLED se
 * inicializa y muere a los pocos milisegundos. Con MASTER_LEFT a secas, la
 * mitad que lleva el USB se cree esclava si es la derecha, y en ese estado la
 * pantalla no sobrevive. Comprobado: el keymap via oficial tampoco lo declara
 * y falla igual; el firmware de Sofle si lo lleva y por eso ahi se veia.
 *
 * MASTER_LEFT se mantiene como preferencia cuando la deteccion no decide. */
#define SPLIT_USB_DETECT
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define QUICK_TAP_TERM 0
#define TAPPING_TERM 100

/* Underglow (RGBLIGHT).
 *
 * El conteo de LEDs (12) y el pin de datos (D3) los aporta
 * keyboards/lily58/rev1/keyboard.json de upstream. Lo que upstream NO declara
 * es el reparto por mitad, y sin el la mitad esclava se queda a oscuras:
 * RGBLIGHT_SPLIT + RGBLED_SPLIT son lo que hace que el master le mande datos.
 *
 * Son 6 LEDs por mitad en la strip de este modelo.
 */
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT { 6, 6 }

#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
/* SNAKE (282 B) y KNIGHT (266 B) quedan fuera: son los dos efectos mas caros
 * del set y los menos pedidos. Reactivarlos cuesta ~550 bytes de los que hay
 * libres; medir antes. */
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

/* Fuente OLED con el logo de Zelvoq en los glifos del logo. Reemplaza a
 * keyboards/lily58/lib/glcdfont_lily.c y ocupa lo mismo: no cuesta flash.
 * Se regenera con herramientas/gen-oled-logo.py.
 *
 * El #undef es necesario: keyboards/lily58/config.h ya define OLED_FONT_H. */
#undef OLED_FONT_H
#define OLED_FONT_H "glcdfont_zelvoq.c"
