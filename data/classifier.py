from torch import nn

class NN_MSN(nn.Module):
    """
    Simple class implementing a neural network for multi-class classification
    Inherits from the torch NN base class
    """

    def __init__(self):
        super(NN_MSN, self).__init__()
        self.fc1 = nn.Linear(3, 16)  
        self.fc2 = nn.Linear(16, 16)
        self.fc3 = nn.Linear(16, 3)
        self.dropout = nn.Dropout(p=0.3)
        self.relu = nn.ReLU()
    

    def forward(self, x):
        """
        Forward of sequences through the network

        Args:
            x (Tensor): Input tensor of shape (batch_size, input_size)

        Returns:
            Tensor: Output logits in shape (batch_size, num_classes)
        """
        x = self.relu(self.fc1(x))
        x = self.dropout(x)
        x = self.relu(self.fc2(x))
        x = self.dropout(x)
        return self.fc3(x)