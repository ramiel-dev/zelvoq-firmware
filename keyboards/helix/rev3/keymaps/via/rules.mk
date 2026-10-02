VIA_ENABLE = yes

# El Helix de 5 filas se vende sin encoder y sin teclas multimedia, como en el
# arbol 0.23.9. Upstream los trae en "yes", de ahi la sobreescritura.
EXTRAKEY_ENABLE = no
ENCODER_ENABLE = no

# Sin "SRC += oled_display.c": upstream absorbio esa pantalla dentro de
# keyboards/helix/helix.c (logo Mac/Win, capa, NUM/CAP/SCR y estado del LED).

# Ningun keymap del catalogo usa keycodes de mouse. Desactivarlas recupera
# flash; el compromiso es el mismo que en el Sofle: si alguien asigna una tecla
# de mouse desde VIA, no hara nada.
MOUSEKEY_ENABLE = no
