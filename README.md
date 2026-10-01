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
| Helix | `helix/rev3_5rows:via`, `helix/rev3_4rows:via` | pendiente |

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
lineas de keycodes y tres efectos RGB.

- `MASTER_LEFT` y `SPLIT_USB_DETECT`.
- Se fuerza `RGBLIGHT_ENABLE = yes` / `RGB_MATRIX_ENABLE = no`: **upstream
  cambio el default de rev1 a RGB_MATRIX**, y los teclados ya vendidos corren
  underglow.
- Los 10 efectos RGBLIGHT del arbol viejo. El keymap oficial deja `RGB_TEST`,
  `ALTERNATING` y `TWINKLE` comentados.
- Encoders/capa 3: `RGB_TOG`->`UG_TOGG`, `RGB_MOD`->`UG_NEXT`, y los seis
  hue/sat/val a `UG_*`.
- Se quitaron `RGBLED_NUM`, `RGBLED_SPLIT` y `RGBLIGHT_LIMIT_VAL`: hoy los
  aportan `crkbd/rev1/keyboard.json` (54 LEDs, 27/27, pin D3) y
  `crkbd/info.json` (`max_brightness: 120`). Upstream absorbio exactamente lo
  que el arbol viejo tenia parchado a mano en `rev1/config.h`.
- Se quitaron `SWAP_HANDS_ENABLE` y `SPLIT_KEYBOARD`.
- `lib/host_led_state_reader.c` del arbol viejo usaba `USB_LED_NUM_LOCK`, que ya
  no existe en QMK. No importa: el keymap `via` nunca lo compilaba.

Alternativa medida para el Corne, si algun dia se quiere pasar a per-key:
RGB_MATRIX da 23742 (82%, 4930 libres) contra 26434 (92%) de RGBLIGHT. Es mas
chico porque upstream compila menos animaciones por defecto que los 10 efectos
de underglow. Cambiarlo resetea la configuracion de luces guardada en EEPROM.

## Uso

```
qmk config user.overlay_dir="$HOME/qmk-userspace-zelvoq"
qmk userspace-compile
```

Un target suelto:

```
qmk compile -kb sofle/rev1 -km via
```

Variante RP2040 del Corne:

```
qmk compile -kb crkbd/rev1 -km via -e CONVERT_TO=promicro_rp2040
```

## Respaldo

Los binarios del arbol congelado (QMK 0.23.9, commit `7df44ffb75`) estan en
`~/qmk-emergency-flash/`, con checksums. Son la via de reflasheo si algo de
esta migracion sale mal.
