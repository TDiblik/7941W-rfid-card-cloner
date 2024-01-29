import tkinter as tk

def toggle_selection(row, col):
    if selected_fields[row][col].get():
        selected_fields[row][col].set(True)
    else:
        selected_fields[row][col].set(False)

def generate_bytes():
    print("static const uint8_t PROGMEM NAME_BITMAP[]")
    print("{ ", end="")
    for row in range(rows):
        row_str = "  "
        if (row == 0):
            row_str = ""
        row_str += "0b"
            
        for col in range(cols):
            row_str += "1" if selected_fields[row][col].get() else "0"

        if (row != rows-1):
            print(f"{row_str},")
        else:
            print(f"{row_str} }};")

root = tk.Tk()
root.title("8x8 bitmap generator")
root.resizable(False, False)

rows, cols = 8, 8
selected_fields = [[tk.BooleanVar() for _ in range(cols)] for _ in range(rows)]

for row in range(rows):
    for col in range(cols):
        checkbox = tk.Checkbutton(root, variable=selected_fields[row][col], onvalue=True, offvalue=False,
                                  command=lambda r=row, c=col: toggle_selection(r, c))
        checkbox.grid(row=row, column=col, padx=5, pady=5)

start_button = tk.Button(root, text="Generate", command=generate_bytes)
start_button.grid(row=rows, columnspan=cols, pady=10)

root.mainloop()