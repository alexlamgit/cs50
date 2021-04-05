from cs50 import get_float

Q = 25
D = 10
N = 5
P = 1 

while True:
    change = get_float("Change owned: ")
    if change >= 0:
        break

cents = round(change * 100)
owned = 0

numquarts = int(cents / Q)
cents -= int(numquarts * Q)
owned += int(numquarts)

numdimes = int(cents / D)
cents -= int(numdimes * D)
owned += int(numdimes)

numnickels = int(cents / N)
cents -= int(numnickels * N)
owned += int(numnickels)
    
numpennies = int(cents / P)
cents -= int(numpennies * P)
owned += int(numpennies)
    
print(owned)