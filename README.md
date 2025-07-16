# MicroSensorNet

**MicroSensorNet** is a simple C++ library that I built to simulate how well a feed-forward neural network can classify human activity/motion in an embedded environment. This was essentially done by training a multi-class classification model in python with the `pytorch` library, exporting the model weights for more performative inference in a C++ application environment, to lightly simulate how this could be done with sportswear hardware.

The application uses `vcpkg` to manage dependencies and includes prebuilt artifacts via the `vcpkg-installed/` folder, and eventual python dependencies are lightly managed through a simple `requirements.txt` file with pip.

## Features

The purpose and main features of this project is two-fold: building a multi-class classification feedforward neural network, and infering activity prediction in a c++ application for an embedded environment (Sports watch) with high resource limitations. 

### Neural Network: multi-class classification
1. Task
The classification task focuses on identifying human activity from raw accelerometer data. Each input sample contains three values — representing x, y, and z acceleration — and the goal is to classify this data into one of three target activities: walking, jogging, or standing.

This task simulates real-world use in embedded systems such as wearables, where low-latency and lightweight computation are critical.

2. Datasets and preprocessing
Dataset originates from Kaggle and contains roughly 1.07M samples, see https://www.kaggle.com/datasets/die9origephit/human-activity-recognition for the complete data specifics.

Each sample consists of an activity being one of (walking, jogging, sitting, standing, upstairs, downstairs) serving as true label, whereas remaining fields are user, timestamp, x-axis acceleration, y-axis acceleration and z-acceleration.

During preprocessing, the activities sitting, upstairs and downstairs were dropped, along with the user, and time-stamp field. Due to label imbalance the least represented class would limit the presence of the remaining classes, finally resulting in 145 180 samples.

The final dataset was split 50/50 allocated for model training and embedded c++ inference. 20% of model training data was allocated for a development set. While not used for the out-of-the-box model, it is advised to tune the model to achieve superior accuracy.

The reasoning behind the pre-processing was to investigate if simpler, more balanced data and thus a simpler multi-class classification model is sufficient to accurarely distingiush live human activity data.

3. Network architecture

The network inherits from the general pytorch (https://docs.pytorch.org/docs/stable/generated/torch.nn.Module.html) `nn.Module` base class for neural networks. Furthermore, Embedded environments introduce several hardware limitations, and for this reason the model was trained on a shallow, low-dimensional feed-forward neural network to avoid large amounts of memory usage to store parameters. The architecture consists of three hidden, fully connected layers of sizes (3,16), (16,16) and (16,3) and uses ReLu for activation. The final model then consists of no more than 387 paramters.

4. Training
The model was trained using PyTorch with the ADAM optimizer and cross-entropy loss for multi-class classification. A development set (20%) was held out from the training data using stratified sampling to preserve class balance. The network was trained on batches of size defined by the user over a user-specified number of epochs.

Each training epoch computes the total classification loss and the number of correctly predicted activities. After training, the model is saved in a lightweight state dictionary format for deployment.

### Embedded application: Model inference in C++ environment

1. Purpose and constraints
The embedded component of this project demonstrates how a trained neural network can be deployed in a resource-constrained C++ environment, such as a wearable or microcontroller device. The goal is to enable real-time prediction of human activity using sensor input, while keeping memory usage and computational demands low. To meet these constraints, the model is re-implemented in C++ using fixed-point arithmetic and a minimal architecture that avoids dynamic memory allocations and floating-point operations.

2. Architecture and execution
The embedded model mirrors the trained feedforward network with three fully connected layers and ReLU activation functions. All model weights and biases are exported from Python and loaded at runtime from a JSON file.

3. Inference and benchmarking
An inference pipeline was created to load labeled sensor data from file, run multiple rounds of inference for each sample, and evaluate model performance.

The model achieved an accuracy of 81.6%, with an average inference time of 23.2 microseconds per sample over 10 repeated runs. This corresponds to a throughput of approximately 43,112 samples per second, validating the system’s ability to operate efficiently in real-time embedded environments.

## Result reproduction & Prerequisites

- A C++17-capable compiler (e.g. GCC 9+, Clang 10+, MSVC 2019+)
- [CMake](https://cmake.org/) 3.21 or newer
- **vcpkg** (installed separately) for dependency management

### 1. Install `vcpkg`
Install vcpkg by navigating into a suitable directory (i.e. a tools folder under your user directory), and then clone the tool:
```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh       # Linux/macOS
# or
.\bootstrap-vcpkg.bat      # Windows
```

To get the project dependency managed with `vcpkg` through the `vcpkg.json` file, navigate back to the repository root directory, and install:

```bash
path/to/vcpkg/vcpkg install
```

### 2. Configure with CMake
From the root of the repository, configure your project to use vcpkg by passing the toolchain file to CMake.

```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
```
Replace `path/to/vcpkg/` with the proper path to your vcpkg installation. Then, build with `cmake --build build`, navigate to the newly created `./build` folder and run `./main.exe`
### 3. Build with Makefile (optional)
The project also includes a Makefile as an alternative build option. Navigate to the root of the repository and simply do `make`. For eventual build clean, do `make clean`.

### 4. Train your own model (optional)
Train your own model! There are plenty of future work and potential improvement regarding pre-processing and training strategy that can lead to accuracy improvements. Re-building is not necessary, since weights from the newly made model are loaded at runtime

Be advised that changing the network architecture (number of layers, layer sizes) or adding more fields from the original dataset is NOT compatible with the C++ application without re-writing parts of the C++ code.

To start training your own model, simply download the python dependencies by navigating to the repository and do `pip install -r requirements.txt`. Then, navigate to the `/data` directory:

```bash
python learning.py data_human_filtered/train.csv <number of epochs> <batch size> <model-creation-path.model>
```

Then, from the same directory, export the newly created model's weights to .json to then be used in the C++ application:

```bash
python export_weights.py <model-path.model> ../weights/weights.json
```

Then, you're good to go to run the classifaction inference of the model!