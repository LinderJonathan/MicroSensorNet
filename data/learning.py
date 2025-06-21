import torch
import pandas as pd
import numpy as np
import kagglehub
from classifier import NN_MSN
from preprocess import preprocess

class Learning():
    def __init__(self,
                 data_path,
                 num_epochs,

                ):
                
        self.model = NN_MSN()
        self.data_path = data_path
        self.num_epochs = num_epochs
    


    def load_data(self):
        """

        """
        preprocess = preprocess()

    def train():
        return 0

def main():
    learner = Learning("test", 10)
    learner.load_data()
if __name__ == "__main__":
    main()