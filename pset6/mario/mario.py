# Prints out a double half-pyramid of a specified height
import cs50

while True:
    h = cs50.get_int("Height: ") + 1
    if h-1 > 0 and h-1 < 9:
        break
        
# Print pyramid    
for i in range(h-1, 0, -1):
    spaces = (i - 1) * " "
    blocks = (h - i) * "#"
    print(f"{spaces}{blocks}  {blocks}")