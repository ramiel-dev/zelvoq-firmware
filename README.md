# Firmware de los teclados Zelvoq

Código fuente del firmware [QMK](https://qmk.fm) que llevan los teclados de
[Zelvoq](https://zelvoq.cl). Se publica porque los teclados se venden con este
firmware ya instalado y la licencia te da derecho a él.

**Para configurar tu teclado no necesitas nada de esto.** Se hace desde el
navegador, sin instalar: **https://keyboards.zelvoq.cl/configurador/**

## Modelos

| Teclado | Target |
|---|---|
| Sofle | `sofle/rev1:via` |
| Lily58 | `lily58/rev1:via` |
| Corne | `crkbd/rev1:via` (también RP2040) |
| Helix 5 filas | `helix/rev3:via` |
| Helix 4 filas | `helix/rev3:via_4row` |

Todos con VIA, así que las teclas, capas, macros e iluminación se cambian en
caliente desde el configurador. Recompilar solo hace falta para cambiar algo
que VIA no expone.

## Compilar

Necesitas un [entorno de QMK](https://docs.qmk.fm/#/newbs_getting_started) y
una copia de `qmk_firmware`.

```sh
QMK_HOME=/ruta/a/qmk_firmware QMK_USERSPACE=$PWD qmk compile -kb sofle/rev1 -km via
```

El script `./zq` hace lo mismo con nombres cortos y fijando las rutas:

```sh
./zq build sofle     # compilar
./zq flash sofle     # compilar y flashear
./zq show helix4     # ver el comando, sin ejecutarlo
```

Modelos: `sofle`, `lily58`, `corne`, `corne-rp2040`, `helix5`, `helix4`, `todos`.

## Flashear

Los teclados son partidos: **cada mitad se flashea por separado**. Lanza el
comando, y cuando diga que espera, resetea esa mitad (puentear `RST` a `GND`
dos veces, o el botón de reset si el case lo tiene). Luego repite con la otra.

El Corne con RP2040 no usa avrdude: móntalo en modo BOOTSEL y copia el `.uf2`.

## Comprobar un teclado

```sh
python3 -I herramientas/via-check.py corne
```

Lee por HID, sin escribir nada: versión del protocolo VIA, tiempo encendido,
capas y los primeros keycodes guardados en el teclado. Sin argumentos prueba
todos los conectados.

No puede leer qué teclas pulsas: QMK lo bloquea a propósito, porque sería
registrar pulsaciones. Este firmware no lleva esa opción activada.

## Definiciones de VIA

En `via/` hay definiciones corregidas para el configurador. Lo explica
`via/README.md`.

## Licencia

Deriva de QMK y de los keymaps `via` de cada teclado, bajo **GPL-2.0**. Se
conservan los avisos de autoría de cada archivo; `LICENSE` es el texto íntegro.

Si tienes un teclado Zelvoq, este es el código correspondiente al firmware que
lleva. Si redistribuyes una versión modificada, la licencia te obliga a
publicar su código.

## Soporte

Escríbenos desde [zelvoq.cl](https://zelvoq.cl) indicando el modelo.
