VIA_ENABLE      = yes
MOUSEKEY_ENABLE = no
LTO_ENABLE      = yes

# Upstream cambio el default del Corne rev1 de RGBLIGHT a RGB_MATRIX. Los
# teclados ya vendidos corren RGBLIGHT (underglow), asi que se fuerza aqui
# para no cambiarles el comportamiento.
RGBLIGHT_ENABLE   = yes
RGB_MATRIX_ENABLE = no

# SWAP_HANDS_ENABLE y SPLIT_KEYBOARD estaban en el arbol viejo: el primero no
# lo usa ningun keymap del catalogo, el segundo lo aporta rev1/keyboard.json.
