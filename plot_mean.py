import matplotlib.pyplot as plt

N = int(input())

vet = []

lixo = float(input())
for i in range(N-1):
    best = float(input())

lixo = float(input())
for i in range(N-1):
    mean = float(input())
    vet.append(mean)

print(vet)

plt.plot( 0,1,vet)
plt.show()
