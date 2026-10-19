#!/usr/bin/env python3
"""Genera un glcdfont con el logo de Zelvoq en los glifos del logo.

El OLED de QMK dibuja el "logo" de la mitad esclava como 63 glifos de la fuente:
0x80-0x94, 0xA0-0xB4 y 0xC0-0xD4. Son 21 glifos de 6x8 px por fila, 3 filas:
126x24 px en total.

Reemplazar esos glifos en la fuente cuesta CERO bytes de flash (la fuente ya
esta ahi y mantiene su tamanho), y pasa por el camino de texto del driver, que
respeta la rotacion del OLED. Un bitmap crudo con oled_write_raw() NO respeta la
rotacion: escribe directo al buffer, asi que saldria invertido en la esclava.

Uso:
    python3 -I gen-oled-logo.py <logo.png> <fuente-base.c> <salida.c>
"""
import re
import sys

from PIL import Image

GLYPH_W, GLYPH_H = 6, 8
COLS, ROWS = 21, 3
W, H = GLYPH_W * COLS, GLYPH_H * ROWS      # 126 x 24
ROW_STARTS = (0x80, 0xA0, 0xC0)
THRESHOLD = 110


def render(path):
    """Logo sobre negro, recortado al contenido y ajustado a 126x24."""
    im = Image.open(path).convert("RGBA")
    bg = Image.new("RGBA", im.size, (0, 0, 0, 255))
    bg.alpha_composite(im)
    gray = bg.convert("L")

    # El contenido claro (marca + wordmark); el fondo oscuro se descarta.
    mask = gray.point(lambda p: 255 if p > 100 else 0, mode="1")
    gray = gray.crop(mask.getbbox())

    # Ajustar por altura para no deformar: estirar a los 126 px completos
    # recorta la "q" y ensancha las letras.
    w = round(H * gray.size[0] / gray.size[1])
    canvas = Image.new("L", (W, H), 0)
    canvas.paste(gray.resize((min(w, W), H), Image.LANCZOS), (max(0, (W - w) // 2), 0))
    # Devolver la imagen, no su .load(): el accesor de pixeles no mantiene viva
    # a la imagen, y con una temporal PIL la libera y el accesor queda colgando.
    return canvas.point(lambda p: 255 if p > THRESHOLD else 0, mode="1")


def array_body(path):
    """El texto entre las llaves del array. Leer el archivo entero haria que
    cualquier 0x.. de un comentario entrara como dato y desplazara los glifos."""
    src = open(path).read()
    start = src.index("{", src.index("font[]"))
    return src[start + 1 : src.rindex("}")]


def slice_glyphs(img):
    """{indice de glifo: [6 bytes]}. Cada byte es una columna, bit 0 = arriba."""
    px = img.load()
    out = {}
    for row, start in enumerate(ROW_STARTS):
        for col in range(COLS):
            glyph = []
            for x in range(GLYPH_W):
                byte = 0
                for bit in range(GLYPH_H):
                    if px[col * GLYPH_W + x, row * GLYPH_H + bit]:
                        byte |= 1 << bit
                glyph.append(byte)
            out[start + col] = glyph
    return out


def main():
    logo, base, dest = sys.argv[1], sys.argv[2], sys.argv[3]

    new = slice_glyphs(render(logo))

    data = [int(b, 16) for b in re.findall(r"0x([0-9A-Fa-f]{2})", array_body(base))]
    if len(data) % GLYPH_W:
        sys.exit(f"la fuente base no es multiplo de {GLYPH_W}: {len(data)} bytes")
    glyphs = [data[i : i + GLYPH_W] for i in range(0, len(data), GLYPH_W)]

    for idx, g in new.items():
        if idx >= len(glyphs):
            sys.exit(f"el glifo 0x{idx:02X} no cabe en una fuente de {len(glyphs)}")
        glyphs[idx] = g

    with open(dest, "w") as f:
        f.write(
            "// Fuente OLED del Lily58 con el logo de Zelvoq.\n"
            "// Generada por herramientas/gen-oled-logo.py — no editar a mano.\n"
            f"// Base: {base}\n"
            f"// Logo: {logo}\n"
            "//\n"
            "// Solo cambian los 63 glifos del area de logo (filas que empiezan\n"
            "// en 80, A0 y C0 hex), o sea los 126x24 px que la mitad esclava\n"
            "// dibuja como logo. El resto es\n"
            "// la fuente ASCII original, asi que el tamanho en flash no cambia.\n\n"
            '#include "progmem.h"\n\n'
            "const unsigned char font[] PROGMEM = {\n"
        )
        for g in glyphs:
            f.write("  " + ", ".join(f"0x{b:02X}" for b in g) + ",\n")
        f.write("};\n")

    print(f"{dest}: {len(glyphs)} glifos, {len(glyphs) * GLYPH_W} bytes "
          f"({len(new)} reemplazados)")


if __name__ == "__main__":
    main()
