# Definiciones de VIA

VIA decide qué controles muestra según la **definición del teclado**: un JSON
que la aplicación carga por VID/PID. Si esa definición no declara el menú de
iluminación, el icono aparece pero el panel sale vacío, por mucho que el
firmware responda.

Las definiciones oficiales de estos dos teclados no coinciden con el firmware
que llevan, así que aquí están corregidas.

| Archivo | Qué cambia | Por qué |
|---|---|---|
| `corne-zelvoq.json` | `menus`: `["qmk_rgblight"]` → `["qmk_rgb_matrix"]` | Este Corne usa RGB_MATRIX, con 21 LEDs por tecla en cada mitad. La definición oficial pregunta por el canal del underglow y el firmware responde por el de matriz. |
| `lily58-zelvoq.json` | `menus`: no existía → `["qmk_rgblight"]` | La oficial no declara ningún menú, así que VIA nunca mostraba controles de luz. |

Parten de las definiciones de
[the-via/keyboards](https://github.com/the-via/keyboards); solo cambia el menú.

## No necesitas cargarlas

**https://keyboards.zelvoq.cl/configurador/** ya las sirve. Están aquí por
transparencia y por si prefieres usar otra instancia de VIA.

Si usas usevia.app u otra, cárgalas en **Settings → Show Design tab** y luego
en **Design**. Mientras estén cargadas, VIA las usa en lugar de las oficiales.
