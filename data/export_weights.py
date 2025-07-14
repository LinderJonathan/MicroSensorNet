import argparse
import torch
from classifier import NN_MSN
import json

FRAC_BITS = 8

def quantize_weights(weights):
    """
    Quantizing a list and/or 2D list of weights 

    Args:
        weights (list), (list of list): weights and bias arrays extracted from neural network

    Returns:
        weights (list), (list of list): Quantized weights and bias arrays in coherence with c++ fixed-point representations
    """

    scale = 1 << FRAC_BITS
    return (scale * weights).round().astype(int).tolist()

def export_weights(model_path, weight_path):
    """
    Obtaining the trained model state dictionary, quantizing and exporting 
    parameters to JSON.  

    Args:
        model_path (string): relative path to the trained model file 
        weight_path (string): relative path to .JSON file to write quantized weights 

    Returns:
        weights (list), (list of list): Quantized weights and bias arrays in coherence with c++ fixed-point representations
    """
    state_dict = torch.load(model_path)
    model = NN_MSN()
    model.load_state_dict(state_dict)

    all_weights = {}

    for name, _ in model.named_parameters():
        params = quantize_weights(state_dict[name].numpy())
        all_weights[name] = params

    with open(weight_path, "w") as f:
            json.dump(all_weights, f, indent=4)

def main(model_path, weight_path):
    export_weights(model_path=model_path, weight_path=weight_path)

    return 0

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('model_path', type=str, help='Path to saved model')
    parser.add_argument('weight_path', type=str, help='Path to JSON file for weights')
    args = parser.parse_args()
    main(args.model_path, args.weight_path)
