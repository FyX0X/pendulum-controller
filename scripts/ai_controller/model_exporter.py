from stable_baselines3 import PPO
import numpy as np
import json

ROOT = "models"


def export(path: str) -> None:
    # inspect the policy architecture
    model = PPO.load(path)
    print(model.policy)

    # extract weights layer by layer
    params = {name: param.detach().numpy() 
            for name, param in model.policy.named_parameters()}

    for name, w in params.items():
        print(f"{name}: {w.shape}")
    

    weights = {
        "W1": params["mlp_extractor.policy_net.0.weight"].tolist(),
        "b1": params["mlp_extractor.policy_net.0.bias"].tolist(),
        "W2": params["mlp_extractor.policy_net.2.weight"].tolist(),
        "b2": params["mlp_extractor.policy_net.2.bias"].tolist(),
        "W3": params["action_net.weight"].tolist(),
        "b3": params["action_net.bias"].tolist(),
    }

    with open(f"{path}.json", "w") as f:
        json.dump(weights, f)

if __name__ == "__main__":

    # export(f"{ROOT}/pendulum_ai_controller")
    export(f"{ROOT}/stabilize")