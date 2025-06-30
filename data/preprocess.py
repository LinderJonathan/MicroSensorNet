import numpy
import os
import argparse
import pandas as pd
from sklearn.model_selection import train_test_split

def preprocess(data_path, n_samples=None):
    """
    Preprocessing of activity data

    Args:
        data_path (string): Path to dataset
        n_samples (int): subset of samples from the dataset. Default: 100000

    Returns:
        data_set (pdf.dataframe): Dataframe containing filtered set
    """

    if n_samples:   
        df = pd.read_csv(data_path).sample(n=n_samples).drop(columns=['user', 'timestamp'])
    else:
        df = pd.read_csv(data_path).drop(columns=['user', 'timestamp'])  

    df = df[df['activity'].isin(['Walking', 'Jogging', 'Standing'])]
    
    classes = df['activity'].value_counts()    
    min_class_sample = classes.iloc[classes.argmin()]

    return df.groupby('activity', group_keys=False).sample(n=min_class_sample)

def main(data_path, process_path, split):

    df = preprocess(data_path)
    train, inference = train_test_split(df, test_size=split)
    os.makedirs(process_path, exist_ok=True)

    file_path_train = os.path.join(process_path, 'train.csv')
    file_path_inference = os.path.join(process_path, 'inference.csv')

    train.to_csv(file_path_train, index=False)
    inference.to_csv(file_path_inference, index=False)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('path', type=str, help='Path to time human activities dataset')
    parser.add_argument('process_path', type=str, help='Path to preprocessed data')
    parser.add_argument('--split', type=float, default=0.5, help='Split ratio between training and inference data')
    args = parser.parse_args()
    main(args.path, args.process_path, args.split)
