import math
START_range = int(math.pow(10,4))
END_range = int(math.pow(10,5))
START_limit = int(math.pow(START_range,0.25))
END_limit = int(math.pow(END_range,0.25))
sqrt_limit = int(math.sqrt(END_limit)+1)
prime_del = [bool(1)] * sqrt_limit
divisors = []
allPrime = []
len_is_prime = int(END_limit - START_limit)
ITOG = []

prime_del[0] = bool(0)
prime_del[1] = bool(0)
is_prime = [bool(True)] * int(len_is_prime)


#нахождение простых делителей
for p in range (2, sqrt_limit):
    if (prime_del[p] == bool(1)):
        i = p*p
        for i in range (p*p, sqrt_limit, p):
            prime_del[i] = False
            i += p
print (prime_del)          
#записываем постые делители в список
for i in range (0, len(prime_del)):
    if (prime_del[i] == True):
        divisors.append (i)

#Находим все простые числа
if START_limit % 2 == 0:
    START_limit += 1
    is_prime[0] = bool(False)
k = 0
for m in range (START_limit, END_limit+1):
    if m % 2 == 0 and m % 3 == 0:
        is_prime[k]= bool(False)
    else:
        for n in range (0, len(divisors)):
            if m % divisors[n] == 0:
                is_prime[k]= bool(False)
    k+=1

#записываем постые числа в список
for i in range (0, len(is_prime)):
    if (is_prime[i] == True):
        allPrime.append (i+START_limit)
print (allPrime)


for i in range (START_range, END_range):
    count = 0
    if i % 2 == 0:
        count += 1
    if i % 3 ==0:
        count += 1
    for j in range (2, len(allPrime)):
        if i % allPrime[j] == 0:
            count += 1
    if count == 4:
        ITOG.append(i)

print (ITOG)
