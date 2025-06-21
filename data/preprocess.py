import numpy
import os
import argparse
import pandas as pd


def preprocess(data_path, n_samples=100000):
    """
    Preprocessing of activity data

    Args:
        data_path (string): Path to dataset
        n_samples (int): subset of samples from the dataset. Default: 10000

    Returns:
        data_set (pdf.dataframe): Dataframe containing filtered set
    """

    # Random sample of n_samples. Keep wanted classes
    df = pd.read_csv(data_path).sample(n=n_samples).drop(columns=['user', 'timestamp'])
    df = df[df['activity'].isin(['Walking', 'Jogging', 'Standing'])]
    # Find under represented class and amount of such samples
    classes = df['activity'].value_counts()    
    min_class_sample = classes[classes.argmin()]

    # Return set of balanced classes
    print(df.groupby('activity', group_keys=False).sample(n=min_class_sample))
    return df.groupby('activity', group_keys=False).sample(n=min_class_sample)

def main(data_path):

    df = preprocess(data_path)
    file_name = 'data_human_filtered.csv'
    dir = os.path.dirname(os.path.abspath(__file__))
    file_path = os.path.join(dir, file_name)
    df.to_csv(file_path, index=False)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('path', type=str, help='Path to time human activities dataset')
    args = parser.parse_args()
    main(args.path)
