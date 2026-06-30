from scipy.linalg import solve_continuous_are
import numpy as np

m = float(input("m ?\n>"))
M = float(input("M ?\n>"))
l = float(input("l ?\n>"))
g = 9.81

A = np.zeros((4, 4))
A[0, 1] = 1
A[1, 2] = - m*g/M
A[2, 3] = 1
A[3, 2] = (M + m) * g / (M * l)

B = np.zeros((4, 1))
B[1] = 1 / M
B[3] = -1 / (M * l)

Q = np.identity(4)
R = np.identity(1)

P = solve_continuous_are(A, B, Q, R)

K = np.linalg.inv(R) @ B.T @ P

print(K)

# result for l, M, m = 1, 1, 0.5:
# K = [[ -1.          -2.54999051 -41.70452522 -11.68284606]]