#!/usr/bin/env python3
"""Verifica por raw HID un teclado VIA recien flasheado. SOLO LECTURA.

Sirve para distinguir "el flasheo escribio bien" de "el flasheo escribio bien
pero la EEPROM quedo con datos del firmware anterior", y para confirmar que la
iluminacion que se compilo es la que se esperaba.

Uso:
    python3 -I via-check.py [modelo]

Sin argumento prueba todos los modelos conectados.
"""
import glob
import os
import select
import sys

# vid, pid por modelo. El nombre es el mismo que usa ./zq.
MODELOS = {
    "sofle":  (0xFC32, 0x0287),
    "lily58": (0x04D8, 0xEB2D),
    "corne":  (0x4653, 0x0001),
    "helix":  (0x3265, 0x0003),
}

CANALES = {2: "RGBLIGHT (underglow)", 3: "RGB_MATRIX (por tecla)"}
VALORES = ((1, "brillo"), (2, "efecto"), (3, "velocidad"))


def find_via(vid, pid):
    """La interfaz raw HID de VIA: usage page 0xFF60 en el descriptor.

    hidapi en Linux no rellena usage_page con el backend hidraw, asi que
    hid.enumerate() no sirve; hay que leer el descriptor de reporte.
    """
    tag = f"{vid:08X}:{pid:08X}"
    for d in sorted(glob.glob("/sys/class/hidraw/hidraw*")):
        try:
            if tag not in open(os.path.join(d, "device", "uevent")).read():
                continue
            rd = open(os.path.join(d, "device", "report_descriptor"), "rb").read()
        except OSError:
            continue
        if b"\x06\x60\xff" in rd:
            return "/dev/" + os.path.basename(d)
    return None


def cmd(fd, payload):
    os.write(fd, bytes(payload + [0x00] * (32 - len(payload))))
    ready, _, _ = select.select([fd], [], [], 2.0)
    return os.read(fd, 32) if ready else None


def check(nombre, vid, pid):
    path = find_via(vid, pid)
    if not path:
        return False
    print(f"\n### {nombre}  ({path})")
    fd = os.open(path, os.O_RDWR)
    try:
        r = cmd(fd, [0x01])
        if not r:
            print("  sin respuesta al comando de protocolo")
            return True
        ver = (r[1] << 8) | r[2]
        nota = {0x0C: "QMK 0.23.9", 0x0D: "QMK 0.34.6"}.get(ver, "desconocida")
        print(f"  protocolo VIA : 0x{ver:04X}  ({nota})")

        r = cmd(fd, [0x02, 0x01])
        if r:
            up = int.from_bytes(r[2:6], "big")
            print(f"  uptime        : {up / 1000:.1f} s")

        r = cmd(fd, [0x11])
        if r:
            print(f"  capas EEPROM  : {r[1]}")

        kc = []
        for col in range(6):
            r = cmd(fd, [0x04, 0x00, 0x00, col])
            if r:
                kc.append((r[4] << 8) | r[5])
        if kc:
            print("  capa 0, fila 0: " + " ".join(f"{k:04X}" for k in kc))

        # Iluminacion: responde el canal que se haya compilado.
        for canal, desc in CANALES.items():
            vals = {}
            for vid_, nombre_ in VALORES:
                r = cmd(fd, [0x08, canal, vid_])
                if r and r[0] == 0x08:
                    vals[nombre_] = r[3]
            if any(v for v in vals.values()):
                print(f"  iluminacion   : {desc}")
                print("                  " +
                      ", ".join(f"{k}={v}" for k, v in vals.items()))
    finally:
        os.close(fd)
    return True


def main():
    pedidos = sys.argv[1:] or list(MODELOS)
    encontrado = False
    for nombre in pedidos:
        if nombre not in MODELOS:
            print(f"modelo desconocido: {nombre}", file=sys.stderr)
            continue
        encontrado |= check(nombre, *MODELOS[nombre])
    if not encontrado:
        sys.exit("\nningun teclado conectado de los pedidos")


if __name__ == "__main__":
    main()
