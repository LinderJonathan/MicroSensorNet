import argparse
import torch
import os
from classifier import NN_MSN
def get_weights(model_path):
    state_dict = torch.load(model_path)

    model = NN_MSN()
    model.load_state_dict(state_dict)

    return model
def main(model_path):
    model = get_weights(model_path)
    for name, param in model.named_parameters():
        print(f"name: {name}")
        print(f"param: {param}")
    return 0

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('model_path', type=str, help='Path to saved model')
    args = parser.parse_args()
    main(args.model_path)
