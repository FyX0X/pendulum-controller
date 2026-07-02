from stable_baselines3 import PPO
import pendulum_env
import model_exporter


ROOT = "models"


cart_mass = 1
pendulum_mass = 0.5
length = 1

start_up = False
name = "down"


if __name__ == "__main__":

    env = pendulum_env.PendulumEnv(cart_mass, pendulum_mass, length, start_up)

    model = PPO("MlpPolicy", env, verbose=1)
    model.learn(total_timesteps=1000000)
    model.save(f"{ROOT}/{name}")
    model_exporter.export(f"{ROOT}/{name}")

