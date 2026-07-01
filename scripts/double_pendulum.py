import sympy as sp
from sympy import cos, sin
from scipy.linalg import solve_continuous_are
import numpy as np

def solve_lagrange_equation_for_qddot():
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
        [(M+m1+m2),                (m1+m2)*l1*cos(theta1),        m2*l2*cos(theta2)],
        [(m1+m2)*l1*cos(theta1),   (m1+m2)*l1**2,                 m2*l1*l2*cos(theta1 - theta2)],
        [m2*l2*cos(theta2),        m2*l1*l2*cos(theta1 - theta2), m2*l2**2],
    ])

    # f(q, q_dot, u)
    f_q_qdot_u = sp.Matrix([
        [(m1+m2)*l1*omega1**2*sin(theta1) + m2*l2*omega2**2*sin(theta2) + F],
        [(m1+m2)*g*l1*sin(theta1) - m2*l1*l2*omega2**2*sin(theta1 - theta2)],
        [m2*g*l2*sin(theta2) + m2*l1*l2*omega1**2*sin(theta1 - theta2)],
    ])

    # computations (system is M(q) * q_ddot = f(q, q_dot, u))

    qddot = sp.simplify(Mq.LUsolve(f_q_qdot_u))

    # output
    # sp.init_printing()
    # print(f"{qddot =}\n\n")


    print("C++ code to compute the accelerations:")

    print(f"float xddot = {sp.ccode(sp.simplify(qddot[0]))};")
    print(f"float alpha1 = {sp.ccode(sp.simplify(qddot[1]))};")
    print(f"float alpha2 = {sp.ccode(sp.simplify(qddot[2]))};")

def pre_solve_LQR_symbolic():
    # Symbol declaration
    M, m1, m2 = sp.symbols("M m1 m2")
    l1, l2 = sp.symbols("l1 l2")
    g = sp.symbols("g")
    x, theta1, theta2 = sp.symbols("x theta1 theta2")
    x_dot, omega1, omega2 = sp.symbols("x_dot omega1 omega2")
    F = sp.symbols("F")

    # solve for qddot in linear system
    Mq_lin = sp.Matrix([
        [(M+m1+m2), (m1+m2)*l1, m2*l2],
        [(m1+m2)*l1, (m1+m2)*l1**2, m2*l1*l2],
        [m2*l2, m2*l1*l2, m2*l2**2],
    ])

    rhs_lin = sp.Matrix([
        [F],
        [(m1+m2)*g*l1*theta1],
        [m2*g*l2*theta2]
    ])

    qddot = sp.simplify(Mq_lin.LUsolve(rhs_lin))

    print(f"xddot = {qddot[0]}")
    print(f"alpha1 = {qddot[1]}")
    print(f"alpha2 = {qddot[2]}")



def solve_LQR():
    M = float(input("M ?\n>"))
    m1 = float(input("m1 ?\n>"))
    m2 = float(input("m2 ?\n>"))
    l1 = float(input("l1 ?\n>"))
    l2 = float(input("l2 ?\n>"))
    g = 9.81

    # RESULT OF PRE_SOLVE_LQR_SYMBOLIC():
    # xddot = (F - g*m1*theta1 - g*m2*theta1)/M
    # alpha1 = (-F*m1 + M*g*m1*theta1 + M*g*m2*theta1 - M*g*m2*theta2 + g*m1**2*theta1 + g*m1*m2*theta1)/(M*l1*m1)
    # alpha2 = g*(-m1*theta1 + m1*theta2 - m2*theta1 + m2*theta2)/(l2*m1)

    # Xdot = AX + Bu
    # X state is [x, xdot, theta1, omega1, theta2, omega2]
    # u = F

    A = np.zeros((6, 6))
    # xdot, theta1_dot, theta2_dot 
    A[0, 1] = 1
    A[2, 3] = 1
    A[4, 5] = 1
    # xddot, omega1_dot, omega2_dot 
    A[1, 2] = -g*(m1+m2)/M
    A[3, 2] = (M*g*(m1+m2)+g*m1**2)/(M*l1*m1)
    A[3, 4] = -g*m2/(l1*m1)
    A[5, 2] = -g*(m1+m2)/(l2*m1)
    A[5, 4] = g*(m1 + m2)/(l2*m1)

    # B vector
    B = np.zeros((6, 1))
    B[1] = 1 / M
    B[3] = -1 / (M * l1)
    B[5] = 0

    Q = np.identity(6)
    R = np.identity(1)

    P = solve_continuous_are(A, B, Q, R)

    K = np.linalg.inv(R) @ B.T @ P

    print(K)
    # result : [[   1.            3.78963103 -173.55130299  -14.94810112  191.60489942  42.77882854]]


if __name__ == "__main__":

    # solve_lagrange_equation_for_qddot()

    # pre_solve_LQR_symbolic()

    solve_LQR()