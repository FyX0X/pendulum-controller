from stable_baselines3 import PPO
import numpy as np
from pendulum_env import PendulumEnv
import matplotlib.pyplot as plt

ROOT = "models"

model = PPO.load(f"{ROOT}/pendulum_ai_controller")
env = PendulumEnv(1, 0.5, 1)

dt: float = 1/60
time = np.arange(0, 30, dt)
iterations = len(time)

x = np.zeros_like(time)
xdot = np.zeros_like(time)
theta = np.zeros_like(time)
omega = np.zeros_like(time)

obs, _ = env.reset()
for i in range(iterations):
    action, _states = model.predict(obs)
    obs, rewards, dones, info, _ = env.step(action)
    x[i], xdot[i], theta[i], omega[i] = obs



fig, (ax1, ax2) = plt.subplots(2, 1)
fig.suptitle("Pendulum AI controller")

ax1.plot(time, theta)
ax1.set_ylabel("Theta [rad]")

ax2.plot(time, x)
ax2.set_xlabel('time (s)')
ax2.set_ylabel('x [m]')

plt.show()