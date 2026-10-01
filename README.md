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
| Corne | `crkbd/rev1:via` | pendiente |
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

## Uso

```
qmk config user.overlay_dir="$HOME/qmk-userspace-zelvoq"
qmk userspace-compile
```

Un target suelto:

```
qmk compile -kb sofle/rev1 -km via
```

## Respaldo

Los binarios del arbol congelado (QMK 0.23.9, commit `7df44ffb75`) estan en
`~/qmk-emergency-flash/`, con checksums. Son la via de reflasheo si algo de
esta migracion sale mal.
