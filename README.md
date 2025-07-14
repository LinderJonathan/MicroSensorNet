# MicroSensorNet

**MicroSensorNet** is a lightweight C++ library and demo project for managing and processing sensor data in embedded or microcontroller-style applications. It uses `vcpkg` to manage dependencies and includes prebuilt artifacts via the `vcpkg-installed/` folder.

 

## 🚀 Features

The purpose and main features of this project is two-fold: building a multi-class classification feedforward neural network, and infering activity prediction in a c++ application for an embedded environment (Sports watch) with high resource limitations. 

### Neural Network: multi-class classification
1. Datasets and preprocessing
Dataset originates from Kaggle and contains roughly 1.07M samples, see https://www.kaggle.com/datasets/die9origephit/human-activity-recognition for the complete data specifics.

Each sample consists of an activity being one of (walking, jogging, sitting, standing, upstairs, downstairs) serving as true label, whereas remaining fields are user, timestamp, x-axis acceleration, y-axis acceleration and z-acceleration.

During preprocessing, the activities sitting, upstairs and downstairs were dropped, along with the user, and time-stamp field. Due to label imbalance the least represented class would limit the presence of the remaining classes, finally resulting in 145 180 samples.

The final dataset was split 50/50 allocated for model training and embedded c++ inference. 20% of model training data was allocated for a development set. While not used for the out-of-the-box model, it is advised to tune the model to achieve superior accuracy.

The reasoning behind the pre-processing was to investigate if simpler, more balanced data and thus a simpler multi-class classification model is sufficient to accurarely distingiush live human activity data.

2. Network architecture
Embedded environments introduce several hardware limitations, and for this reason the model was trained on a shallow, low-dimensional feed-forward neural network to make sure parameters would fit in memory. 

### Embedded application: Model inference in C++ environment



- **Fixed-point arithmetic** for efficient sensor data handling
- Modular architecture for easy integration into embedded systems
- Example demos to showcase capabilities

## 🔧 Prerequisites

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

