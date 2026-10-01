VIA_ENABLE = yes
RGBLIGHT_ENABLE = yes
ENCODER_MAP_ENABLE = yes
CONSOLE_ENABLE = no

# OLED_ENABLE, ENCODER_ENABLE y EXTRAKEY_ENABLE ya vienen de
# keyboards/sofle/info.json (bloque "features"), y LTO de "build".

# Ahorro de flash. oled.c no usa sprintf/snprintf, asi que el printf minimo
# es gratis. COMMAND es la combinacion de consola de debug, no la necesita
# un teclado de produccion.
AVR_USE_MINIMAL_PRINTF = yes
COMMAND_ENABLE = no

# Mousekeys desactivadas: liberan 1372 bytes, que es lo que hace la diferencia
# entre 99% de flash (110 bytes libres, sin margen) y 94% (1482 libres).
# Compromiso: si un usuario asigna un keycode de mouse en VIA, no hara nada.
# Se eligio esto antes que recortar efectos RGB, que son visibles y parte de
# la propuesta del producto ("Sofle RGB").
# Alternativa medida: con mousekeys y sin SNAKE/CHRISTMAS/KNIGHT -> 27494 (95%).
MOUSEKEY_ENABLE = no
