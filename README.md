# MicroSensorNet

**MicroSensorNet** is a lightweight C++ library and demo project for managing and processing sensor data in embedded or microcontroller-style applications. It uses `vcpkg` to manage dependencies and includes prebuilt artifacts via the `vcpkg-installed/` folder.

 

## 🚀 Features

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
Embedded environments introduce several hardware limitations, and for this reason the model was trained on a shallow, low-dimensional feed-forward neural network to avoid large amounts of memory usage to store parameters. The architecture consists of three hidden, fully connected layers of sizes (3,16), (16,16) and (16,3) and uses ReLu for activation. The final model then consists of no more than 387 paramters.

4. Training
The model was trained using PyTorch with the ADAM optimizer and cross-entropy loss for multi-class classification. A development set (20%) was held out from the training data using stratified sampling to preserve class balance. The network was trained on batches of size defined by the user over a user-specified number of epochs.

Each training epoch computes the total classification loss and the number of correctly predicted activities. After training, the model is saved in a lightweight state dictionary format for deployment.

### Embedded application: Model inference in C++ environment

1. Purpose and constraints
The embedded component of this project demonstrates how a trained neural network can be deployed in a resource-constrained C++ environment, such as a wearable or microcontroller device. The goal is to enable real-time prediction of human activity using sensor input, while keeping memory usage and computational demands low.

To meet these constraints, the model is re-implemented in C++ using fixed-point arithmetic and a minimal architecture that avoids dynamic memory allocations and floating-point operations.


2. Architecture and execution
The embedded model mirrors the trained feedforward network with three fully connected layers and ReLU activation functions. All model weights and biases are exported from Python and loaded at runtime from a JSON file.

3. Inference and benchmarking
An inference pipeline was created to load labeled sensor data from file, run multiple rounds of inference for each sample, and evaluate model performance.

The model achieved an accuracy of 81.6%, with an average inference time of 23.2 microseconds per sample over 10 repeated runs. This corresponds to a throughput of approximately 43,112 samples per second, validating the system’s ability to operate efficiently in real-time embedded environments.

## 🔧 Result reproduction & Prerequisites

- A C++17-capable compiler (e.g. GCC 9+, Clang 10+, MSVC 2019+)
- [CMake](https://cmake.org/) 3.21 or newer
- **vcpkg** (installed separately) for dependency management

> ⚠️ The repo includes `vcpkg-installed/`, which contains the build artifacts, but does **not** include the vcpkg tool itself.

### 📦 1. Install `vcpkg`

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh       # Linux/macOS
# or
.\bootstrap-vcpkg.bat      # Windows
```
### 2. Configure with CMake

### (Optional) x. Train your own model and export weights
