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

/* Iluminacion: RGB_MATRIX.
 *
 * El Corne de Zelvoq puebla los 54 LEDs completos: por mitad, 6 de underglow
 * y 21 por tecla. RGB_MATRIX es lo que corresponde a ese hardware; con
 * RGBLIGHT los 21 por tecla serian un tramo mas de una tira lineal y un
 * barrido pasaria por debajo sin relacion con las teclas.
 *
 * El conteo (54), el reparto (27/27), el pin (D3) y el brillo maximo (120)
 * los aporta crkbd/rev1/keyboard.json y crkbd/info.json. rgb_matrix ya es el
 * default de upstream para rev1, asi que rules.mk no sobrescribe nada.
 */

/* Necesario para los efectos reactivos. SPLIT_TRANSPORT_MIRROR hace que la
 * mitad esclava reciba el estado de la matriz; sin el, las pulsaciones de una
 * mitad no iluminan nada en la otra. Upstream no lo declara para crkbd. */
#define RGB_MATRIX_KEYPRESSES
#define SPLIT_TRANSPORT_MIRROR

/* Ambientes. */
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON

/* Reactivos: son los que el arbol 0.23.9 ya tenia descomentados en
 * crkbd/r2g/config.h, o sea los que ya estaban elegidos. */
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
