n = int(input())
a = [*range(1, n+1)]

for i in range(2, n):
    a[i], a[i//2] = a[i//2], a[i]

print(' '.join(map(str, a)))