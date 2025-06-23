import torch
from torch.utils.data import DataLoader, TensorDataset
import pandas as pd
import argparse
from classifier import NN_MSN
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder


class Learning():
    def __init__(self,
                 data_path,
                 num_epochs,
                 batch_size
                ):
                
        self.model = NN_MSN()
        self.data_path = data_path
        self.num_epochs = num_epochs
        self.batch_size = batch_size
        self.loss_fn = torch.nn.CrossEntropyLoss()
        self.optimizer = torch.optim.Adam(self.model.parameters())

    def load_data(self):
        """
        """
        human_data = pd.read_csv(self.data_path)
        gyro_data, activity = human_data[['x-axis', 'y-axis', 'z-axis']], human_data['activity']
        x_train, x_test, y_train, y_test = train_test_split(gyro_data, activity, test_size=0.2, stratify=activity)

        x_train_tensor = torch.tensor(x_train.values, dtype=torch.float32)
        y_train_tensor = torch.tensor(LabelEncoder().fit_transform(y_train), dtype=torch.long)
        x_test_tensor = torch.tensor(x_test.values, dtype=torch.float32)
        y_test_tensor = torch.tensor(LabelEncoder().fit_transform(y_test), dtype=torch.long)

        return (x_train_tensor, y_train_tensor, x_test_tensor, y_test_tensor)
    
    def train(self, x_train_tensor, y_train_tensor, epoch):
        
        training_set = TensorDataset(x_train_tensor, y_train_tensor)
        loader = DataLoader(training_set, batch_size=self.batch_size)

        for epoch in range(self.num_epochs):
            total_loss = 0
            self.model.eval()
            for x_batch, y_batch in loader:
                self.optimizer.zero_grad()
                output = self.model(x_batch)

                loss = self.loss_fn(output, y_batch)
                total_loss += loss.item()
                loss.backward()
                self.optimizer.step()

                print(loss)

        # TODO: save model to file

        return 0

    def inference(self, x_test_tensor, y_test_tensor):
        # TODO: run inference to compute some metrics
        return 0

def main(data_path, num_epochs, batch_size):
    # TODO: add argparse to read config from command line


    learner = Learning(data_path=data_path, num_epochs=num_epochs, batch_size=batch_size)
    x_train_tensor, y_train_tensor, x_test_tensor, y_test_tensor = learner.load_data()
    learner.train(x_train_tensor=x_train_tensor, y_train_tensor=y_train_tensor, epoch=num_epochs)
if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('path', type=str, help='Path to dataset')
    parser.add_argument('epochs', type=int, help='Number of epochs')
    parser.add_argument('batch_size', type=int, help='Batch size')
    args = parser.parse_args()
    main(args.path, args.epochs, args.batch_size)