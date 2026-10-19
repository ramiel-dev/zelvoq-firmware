# Definiciones de VIA

VIA no decide el panel de iluminacion por lo que soporte el firmware, sino por
la **definicion del teclado**: un JSON que la app carga segun el VID/PID. Si la
definicion no declara el menu correcto, el icono de iluminacion aparece pero
sale **vacio**, por mucho que el firmware responda.

Por eso existen estos archivos. Son la definicion oficial de
[the-via/keyboards](https://github.com/the-via/keyboards) con el menu corregido.

| Archivo | Que cambia respecto a la oficial | Por que |
|---|---|---|
| `corne-zelvoq.json` | `menus`: `["qmk_rgblight"]` -> `["qmk_rgb_matrix"]` | El firmware de Zelvoq usa RGB_MATRIX (21 LEDs por tecla por mitad). La oficial consulta el canal 2 y el firmware responde por el 3. |
| `lily58-zelvoq.json` | `menus`: **no existia** -> `["qmk_rgblight"]` | La definicion oficial no declara ningun menu, asi que VIA nunca mostro controles de luz. Es la causa de raiz de que estos teclados llevaran firmware de Sofle. |

## Como se cargan

En VIA: **Settings -> Show Design tab**, y en **Design** cargar el JSON. VIA lo
usa en vez de la definicion oficial mientras este cargado.

Es tambien lo que habria que entregarle al cliente junto con el teclado, o lo
que habria que resolver de forma definitiva si en algun momento se usa un
VID/PID propio de Zelvoq en vez del del diseño original.

## Pendiente

Sofle y Helix no aparecen en `v3/` ni en `src/` del repo de VIA por los nombres
obvios. Hay que localizar sus definiciones antes de dar por cerrado el tema de
iluminacion en esos dos modelos.
