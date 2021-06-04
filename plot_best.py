import matplotlib.pyplot as plt

N = int(input())

vet = []

lixo = float(input())

for i in range(N-1):
    best = float(input())
    vet.append(best)

print(vet)

plt.plot( 0,1,vet)
plt.show()
