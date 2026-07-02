import gymnasium as gym
import numpy as np
import pendulum_pysim


class PendulumEnv(gym.Env):

    DT: float = 1/60
    MAX_DOWN_TIME: float = 5
    UPRIGHT_THRESHOLD = 0.9

    def __init__(self, cart_mass: float, pendulum_mass: float, length: float, start_up: bool = True) -> None:
        self.start_up = start_up

        self.sim = pendulum_pysim.Pendulum(cart_mass, pendulum_mass, length)

        self.observation_space = gym.spaces.Box(
            low= np.array([-10, -20, -1, -1, -20]),
            high= np.array([10, 20, 1, 1, 20]),
            dtype=np.float32
        )

        self.action_space = gym.spaces.Box(
            low=-10.0, high=10.0, shape=(1,), dtype=np.float32
        )

        self.time_since_upright = 0
    
    def reset(self, seed=None):
        # start hanging up/down with small random perturbation
        start = np.pi * (not self.start_up)
        self.sim.set_state(0, 0, start + np.random.uniform(-0.1, 0.1), 0)
        return self._obs(), {}
    
    def step(self, action):
        self.sim.add_force(float(action[0]))
        self.sim.update(PendulumEnv.DT)

        obs = self._obs()
        reward = self._reward(obs)

        x, xdot, cos, sin, omega = obs
        out_of_bound = abs(x) > 9.5
        too_fast = abs(xdot) > 19
        rotate_too_fast = abs(omega) > 19

        self.time_since_upright += PendulumEnv.DT
        if cos > self.UPRIGHT_THRESHOLD:
            self.time_since_upright = 0
        too_long_since_upright = self.time_since_upright > PendulumEnv.MAX_DOWN_TIME

        terminated: bool = out_of_bound or too_fast or rotate_too_fast or too_long_since_upright

        return obs, reward, terminated, False, {}
    
    def _obs(self):
        x, xdot, theta, omega = self.sim.get_state()
        observation = np.array([x, xdot, np.cos(theta), np.sin(theta), omega])
        return observation
    
    def _reward(self, obs) -> float:
        x, xdot, cos_theta, sin_theta, omega = obs
        return (cos_theta - 0.00 * omega**2 - 0.01 * (x**2 + abs(x)))
