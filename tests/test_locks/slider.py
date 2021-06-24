#! /usr/bin/env python
""" save parameters obtained from sliders into a toml_file, using a write lock to avoid another process to read while the file is updated """


from tkinter import *
from filelock import FileLock

FILE = "params.toml"

# params= {
#     'square_length': 354,
#     'square_color': 0xFF56,
#     'circle_radius': 50,
#     'circle_color': 0x000043,
#     'background_color': 0xFFFFFFFFF
#     }


def write_params_to_file():
    with FileLock(FILE + ".lock") as lock:
        with lock.acquire(timeout=1):
            with open(FILE, "w") as f:
                f.write(f"square_length = {sl1.get()}\n" +
                        f"circle_radius = {sl2.get()}\n" +
                        "circle_color = 0x000000FF\n" +
                        "square_color = 0xFFFFFFFF\n" +
                        "background_color = 0xFFFFFFFF\n"
                        )


master = Tk()
sl1 = Scale(master, from_=0, to=42, orient=HORIZONTAL)
sl1.pack()
sl2 = Scale(master, from_=0, to=200, orient=HORIZONTAL)
sl2.pack()
Button(master, text='Save', command=write_params_to_file).pack()

mainloop()
