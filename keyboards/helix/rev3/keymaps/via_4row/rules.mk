VIA_ENABLE = yes

# A diferencia del de 5 filas, el Helix de 4 filas si lleva encoder y teclas
# multimedia (asi estaba en el arbol 0.23.9).
EXTRAKEY_ENABLE = yes
ENCODER_ENABLE = yes

# Sin "SRC += oled_display.c": upstream absorbio esa pantalla en helix.c.

# Ningun keymap del catalogo usa keycodes de mouse. Desactivarlas recupera
# flash; el compromiso es el mismo que en el Sofle: si alguien asigna una tecla
# de mouse desde VIA, no hara nada.
MOUSEKEY_ENABLE = no
