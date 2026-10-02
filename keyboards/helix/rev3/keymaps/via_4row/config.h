/* Helix rev3, 4 filas — keymap VIA de Zelvoq, migrado desde QMK 0.23.9.
 *
 * Upstream unifico rev3_4rows y rev3_5rows en un solo `helix/rev3` con dos
 * layouts (LAYOUT_4row / LAYOUT_5row).
 */

#pragma once

#define SPLIT_USB_DETECT

/* Pasos de ajuste que tenia el arbol viejo. */
#define RGB_MATRIX_HUE_STEP 8
#define RGB_MATRIX_SAT_STEP 8
#define RGB_MATRIX_VAL_STEP 8
#define RGB_MATRIX_SPD_STEP 10

/* NO se declara RGBLIGHT: ver el README. Upstream dejo Helix solo con
 * RGB_MATRIX, y keyboards/helix/helix.c llama rgb_matrix_get_*() sin guardas
 * #ifdef, asi que OLED sin RGB_MATRIX no compila.
 *
 * Tampoco se declara OLED_FONT_H ni DIP_SWITCH_MATRIX_GRID: los aportan
 * keyboards/helix/config.h y helix/rev3/keyboard.json.
 */
