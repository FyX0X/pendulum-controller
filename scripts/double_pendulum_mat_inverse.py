import sympy as sp
from sympy import cos, sin


# Symbol declaration
M, m1, m2 = sp.symbols("M m1 m2")
l1, l2 = sp.symbols("l1 l2")
g = sp.symbols("g")
x, theta1, theta2 = sp.symbols("x theta1 theta2")
x_dot, omega1, omega2 = sp.symbols("x_dot omega1 omega2")
F = sp.symbols("F")


# matrix declarations:
# M(q) mass matrix
Mq = sp.Matrix([
    [-(M+m1+m2),                -(m1+m2)*l1*cos(theta1),        -m2*l2*cos(theta2)],
    [-(m1+m2)*l1*cos(theta1),   -(m1+m2)*l1**2,                 -m2*l1*l2*cos(theta1 - theta2)],
    [-m2*l2*cos(theta2),        -m2*l1*l2*cos(theta1 - theta2), -m2*l2**2],
])

# f(q, q_dot, u)
f_q_qdot_u = sp.Matrix([
    [(m1+m2)*omega1**2*sin(theta1) + m2*l2*omega2**2*sin(theta2) + F],
    [(m1+m2)*g*l1*sin(theta1) - m2*l1*l2*omega2**2*sin(theta1 - theta2)],
    [m2*g*l2*sin(theta2) - m2*l1*l2*omega1**2*sin(theta1 - theta2)],
])

# computations (system is M(q) * q_ddot = f(q, q_dot, u))
invMq = sp.simplify(Mq.inv())

qddot = sp.simplify(invMq * f_q_qdot_u)

# output
sp.init_printing()

print(f"{invMq =}\n\n")

print(f"{qddot =}\n\n")


print("C++ code to compute the accelerations:")

print("xdd: ")
print(sp.ccode(sp.simplify(qddot[0])))


print("alpha1: ")
print(sp.ccode(sp.simplify(qddot[1])))

print("alpha2: ")
print(sp.ccode(sp.simplify(qddot[2])))

