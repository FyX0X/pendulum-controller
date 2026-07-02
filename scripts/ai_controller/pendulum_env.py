import gymnasium as gym
import numpy as np
import pendulum_pysim


class PendulumEnv(gym.Env):

    DT: float = 1/60
    MAX_DOWN_TIME: float = 5
    def __init__(self, cart_mass: float, pendulum_mass: float, length: float) -> None:
        self.sim = pendulum_pysim.Pendulum(cart_mass, pendulum_mass, length)

        self.observation_space = gym.spaces.Box(
            low= np.array([-10, -20, -np.pi, -20]),
            high= np.array([10, 20, np.pi, 20]),
            dtype=np.float32
        )

        self.action_space = gym.spaces.Box(
            low=-10.0, high=10.0, shape=(1,), dtype=np.float32
        )

        self.time_since_upright = 0
    
    def reset(self, seed=None):
        # start hanging up with small random perturbation
        self.sim.set_state(0, 0, np.pi + np.random.uniform(-0.1, 0.1), 0)
        return self._obs(), {}
    
    def step(self, action):
        self.sim.add_force(float(action[0]))
        self.sim.update(PendulumEnv.DT)

        obs = self._obs()
        reward = self._reward(obs)
        out_of_bound = abs(obs[0]) > 9.5
        too_fast = abs(obs[1]) > 19
        rotate_too_fast = abs(obs[3]) > 19

        self.time_since_upright += PendulumEnv.DT
        if self.is_upright(theta=obs[2]):
            self.time_since_upright = 0
        too_long_since_upright = self.time_since_upright > PendulumEnv.MAX_DOWN_TIME

        terminated: bool = out_of_bound or too_fast or rotate_too_fast or too_long_since_upright

        return obs, reward, terminated, False, {}
    
    def _obs(self):
        return np.array(self.sim.get_state(), dtype=np.float32)
    
    def _reward(self, obs):
        x, xdot, theta, omega = obs
        return (np.cos(theta) - 0.00 * omega**2 - 0.00 * x**2)
    
    def is_upright(self, theta: float, threshold: float = 0.9) -> bool:
        return np.cos(theta) > threshold
