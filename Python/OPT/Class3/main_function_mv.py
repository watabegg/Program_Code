import numpy as np
import random
import functions_mv as functions

random_seed = 777
random.seed(random_seed)
np.random.seed(random_seed)
dimensions = 2

f = functions.squared_f
x = np.random.rand(dimensions, 1)
functions.squared_f(x)
xv = []

for i in range(10):
    r = np.random.rand(dimensions, 1)
    xv.append(r)

print("Squared")
fx = [functions.squared_f(x) for x in xv]
xpa_s = [functions.squared_df_analytic(x) for x in xv]  
xpg_s = [functions.gradient(x, f) for x in xv]
for i in range(len(xv)):
    print("---")
    print(xv[i], xpa_s[i], xpg_s[i])

print("Hessian Squared")
print(xv[0])
print(xpg_s[0])
print(functions.hessian(xv[0], f))

f = functions.rastrigin

xpa_r = [functions.rastrigin_df_analytic(e) for e in xv]  
xpg_r = [functions.gradient(e, f) for e in xv]
print()
print("Rastrigin")
for i in range(len(xv)):
    print("---")
    print(xv[i], xpa_r[i], xpg_r[i])

print("Hessian Rastrigin")
print(xv[0])
print(xpg_r[0])
print(functions.hessian(xv[0], f))
