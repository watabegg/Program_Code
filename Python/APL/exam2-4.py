count = 0
for n in range(10000):
    if n % 3 == 1 or n % 3 == 2:
        count += 1

print(count)
