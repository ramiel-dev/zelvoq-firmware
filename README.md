# qmk-userspace-zelvoq

External Userspace de QMK para el firmware de produccion de Zelvoq
(FutuMaster Electronics SPA).

## Por que existe

Hasta ahora el firmware se construia editando archivos **dentro** del arbol de
`qmk_firmware`. Eso hacia imposible actualizar QMK: cada `git pull` chocaba con
esas ediciones. Ademas, en **QMK 0.26.0 (ago 2024)** upstream elimino todos los
keymaps `via` del repositorio, asi que `keyboards/<kb>/keymaps/via` dejo de
existir y se perdia en cualquier actualizacion.

Aqui los keymaps viven en un repo propio. `qmk_firmware` queda limpio y
actualizable.

## Estado

| Teclado | Target | Estado |
|---|---|---|
| Sofle | `sofle/rev1:via` | migrado |
| Lily58 | `lily58/rev1:via` | migrado |
| Corne | `crkbd/rev1:via` (+ RP2040) | migrado |
| Helix 5 filas | `helix/rev3:via` | migrado |
| Helix 4 filas | `helix/rev3:via_4row` | migrado |

## Que se conservo del arbol 0.23.9

**Sofle** — el layout quedo identico al original; solo cambio lo que QMK renombro.

- `SPLIT_USB_DETECT` y `TAPPING_TERM 100`.
- `RGBLIGHT` (underglow), **no** `RGB_MATRIX`. El keymap `via` oficial usa
  matrix; se eligio underglow para no cambiar el comportamiento de los teclados
  ya vendidos. El PCB soporta ambos sobre el mismo pin D3.
- Efectos RGB tal cual, con `RGBLIGHT_EFFECT_TWINKLE` deshabilitado.
- `oled.c` propio (pantalla con capa activa y CapsLock).
- Encoders: keycodes renombrados al esquema nuevo de underglow.
  `RGB_HUD`→`UG_HUED`, `RGB_HUI`→`UG_HUEU`, `RGB_SAD`→`UG_SATD`,
  `RGB_SAI`→`UG_SATU`, `RGB_VAD`→`UG_VALD`, `RGB_VAI`→`UG_VALU`,
  `RGB_RMOD`→`UG_PREV`, `RGB_MOD`→`UG_NEXT`.
- Se quitaron `WS2812_DI_PIN`, `RGBLED_NUM` y `RGBLED_SPLIT`: hoy los aporta
  `keyboards/sofle/info.json` de upstream. (`RGBLED_NUM` ademas se renombro a
  `RGBLIGHT_LED_COUNT`.)
- Se quito `SWAP_HANDS_ENABLE`: ningun keymap del catalogo lo usa, y upstream
  ya no lo declara para Sofle. Era peso muerto en flash.

**Lily58** — el `keymap.c` es identico al oficial. Un solo cambio real:

- `#define MASTER_LEFT`, que el arbol viejo forzaba.

**Corne** — el layout quedo identico; difiere del keymap `via` oficial en dos
lineas de keycodes.

- `MASTER_LEFT` y `SPLIT_USB_DETECT`.
- **RGB_MATRIX**, que es el default de upstream para rev1. El Corne de Zelvoq
  puebla los 54 LEDs completos: por mitad, 6 de underglow y **21 por tecla**.
  Con RGBLIGHT esos 21 serian un tramo mas de una tira lineal y un barrido
  pasaria por debajo sin relacion con las teclas.
- `RGB_MATRIX_KEYPRESSES` y `SPLIT_TRANSPORT_MIRROR`, que upstream no declara
  para crkbd. Sin el segundo, las pulsaciones de una mitad no iluminan nada en
  la otra y los efectos reactivos quedan a medias.
- Diez animaciones. Las seis reactivas (heatmap, los tres solid reactive,
  splash y solid splash) son las que el arbol 0.23.9 ya tenia descomentadas en
  `crkbd/r2g/config.h`; upstream no activa ninguna, solo color solido.
- Encoders/capa 3 en `RM_*`.
- Se quitaron `RGBLED_NUM`, `RGBLED_SPLIT` y `RGBLIGHT_LIMIT_VAL`: hoy los
  aportan `crkbd/rev1/keyboard.json` (54 LEDs, 27/27, pin D3) y
  `crkbd/info.json` (`max_brightness: 120`). Upstream absorbio exactamente lo
  que el arbol viejo tenia parchado a mano en `rev1/config.h`.
- Se quitaron `SWAP_HANDS_ENABLE` y `SPLIT_KEYBOARD`.
- `lib/host_led_state_reader.c` del arbol viejo usaba `USB_LED_NUM_LOCK`, que ya
  no existe en QMK. No importa: el keymap `via` nunca lo compilaba.

**Helix** — el caso mas invasivo, y el unico donde no se pudo preservar el
comportamiento.

- Upstream **unifico** `rev3_4rows` y `rev3_5rows` en un solo `helix/rev3` con
  dos layouts. De ahi los dos keymaps: `via` (5 filas) y `via_4row` (4 filas).
  `LAYOUT(` paso a `LAYOUT_5row(` / `LAYOUT_4row(`.
- **La iluminacion cambia a RGB_MATRIX a la fuerza.** Upstream dejo Helix solo
  con matrix: `keyboards/helix/helix.c` llama `rgb_matrix_get_mode()` y
  compañia **sin guardas `#ifdef`**, desde `oled_task_kb()`. Con OLED activo y
  `RGB_MATRIX_ENABLE = no` el arbol de upstream no compila. No es una eleccion
  nuestra ni se puede sortear desde el userspace.
- Por lo mismo se **elimino `oled_display.c`**: leia el estado del underglow
  (`rgblight_get_mode` / `_hue` / `_sat` / `_val`), que con matrix no aplica.
  No se pierde nada: upstream absorbio esa misma pantalla dentro de `helix.c`
  (logo Mac/Win, capa, NUM/CAP/SCR y estado del LED).
- `is_mac_mode()` vivia en `rev3_5rows.c` / `rev3_4rows.c`, archivos de placa que
  upstream borro al unificar. Se porto al `keymap.c` de cada variante: la usan
  las teclas **EISU y KANA** para conmutar entrada japonesa. No se portaron
  `set_mac_mode()` ni `dip_switch_update_kb()`, que dependian del dip switch
  (desactivado en este producto).
- Diferencia entre los dos modelos, heredada del arbol viejo: el de 5 filas va
  **sin encoder y sin extrakey**; el de 4 filas **con ambos**.
- El de 4 filas tiene 50 LEDs y upstream declara 64 para `rev3`. Verificado que
  es benigno: los 7 LEDs de la quinta fila de cada mitad caen **al final de la
  cadena** (indices 25-31 y 57-63), asi que 0-24 mapean correcto y los 7 extra
  son escrituras al vacio.
- Se quitaron `RGBLED_NUM`, `RGBLED_SPLIT`, `DIP_SWITCH_MATRIX_GRID` y
  `OLED_FONT_H`: hoy los aportan `helix/rev3/keyboard.json`, `helix/info.json` y
  `helix/config.h`. El `glcdfont.c` propio tenia **datos identicos** al de
  upstream, asi que no se arrastra.
- `MOUSEKEY_ENABLE = no` en ambos: ningun keymap usa keycodes de mouse, y
  recupera flash (el de 4 filas pasa de 96% a 92%).
- **`AVR_USE_MINIMAL_PRINTF` queda prohibido aqui**: el `oled_display.c`
  original usaba `snprintf` con `"%2d"` y el printf minimo no soporta ancho de
  campo. Si alguien reintroduce esa pantalla, no activar esa opcion.

Cabo suelto: `sin-usar/helix-futu-font.c` es un font propio (distinto del
`glcdfont.c` de upstream) que estaba en `keyboards/helix/common/futu.c` del
arbol viejo **sin que nada lo referenciara**. Se conserva por si era para
branding; no entra en ningun build.

## Uso

Usar `./zq`, que fija el arbol y el userspace:

```
./zq build sofle          # compila uno
./zq build todos          # los cinco AVR
./zq flash sofle          # compila y flashea (resetear una mitad)
./zq show helix4          # muestra el comando, sin ejecutar
```

Modelos: `sofle`, `lily58`, `corne`, `corne-rp2040`, `helix5`, `helix4`, `todos`.

### Por que un script y no `qmk` a secas

Dos trampas reales:

1. **`qmk` sin `QMK_HOME` apunta a `~/qmk_firmware`**, el arbol congelado en
   0.23.9. Un `qmk flash -kb sofle -km via -bl avrdude` suelto compila ahi **sin
   error y sin aviso**, y el archivo de salida se llama igual
   (`sofle_rev1_via.hex`). Es facil flashear la version vieja creyendo que es la
   nueva, o al reves.
2. **`-kb helix` resuelve a `helix/beta`, no a `helix/rev3`**, y falla. Hay que
   escribir la revision completa. (`-kb sofle` y `-kb crkbd` si resuelven bien,
   a `sofle/rev1` y `crkbd/rev1`.)

A mano, con las variables puestas, la linea de siempre sigue sirviendo:

```
QMK_HOME=~/qmk_firmware_new QMK_USERSPACE=~/qmk-userspace-zelvoq \
  qmk flash -kb sofle -km via -bl avrdude
```

`-bl avrdude` sigue siendo correcto. Los splits usan `MASTER_LEFT`, no
`EE_HANDS`, asi que se flashea cada mitad por separado reseteando una a la vez;
las variantes `avrdude-split-left` / `-right` son para `EE_HANDS` y aqui no
aplican. El Corne RP2040 no usa avrdude: montar la mitad en BOOTSEL y copiar el
`.uf2`.

## Respaldo

Los binarios del arbol congelado (QMK 0.23.9, commit `7df44ffb75`) estan en
`~/qmk-emergency-flash/`, con checksums. Son la via de reflasheo si algo de
esta migracion sale mal.
