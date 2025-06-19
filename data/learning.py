import torch
import pandas as pd
import numpy as np
import kagglehub
from classifier import NN_MSN

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
        df = pd.read_csv("data/time_series_data_human_activities.csv")
        df = df.sample(n=50000)
        print(len(df))
        labels = df['activity'].value_counts()
        print(labels)
    def train():
        return 0

def main():
    learner = Learning("test", 10)
    learner.load_data()
if __name__ == "__main__":
    main()