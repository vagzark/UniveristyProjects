# Implementation of a Multilayer Perceptron (MLP) Neural Network

## Overview
This project involves the implementation of a feedforward neural network, specifically a **Multilayer Perceptron (MLP)**, trained using the backpropagation algorithm. The primary objective is to solve classification problems through supervised learning.

### MLP Architecture
- **Input Layer**: Accepts raw input data.
- **Hidden Layers**: Extract and learn abstract features from the data.
- **Output Layer**: Produces the final predictions.

The MLP is fully connected, meaning every neuron in one layer is connected to all neurons in the next layer. It uses the backpropagation algorithm to iteratively adjust its weights and minimize prediction errors.

## Dataset
The project uses the **CIFAR-10 dataset**, a standard benchmark for image classification. The dataset contains:
- **50,000 training images** and **10,000 testing images**.
- Images are 32x32 pixels across **10 classes** (e.g., animals, vehicles).

Preprocessing involves normalizing the dataset to the range [0,1] and splitting it into mini-batches for training.

## Implementation Highlights
1. **Activation Functions**:
   - **ReLU**: Introduces non-linearity in hidden layers.
   - **Softmax**: Converts outputs into probabilities for classification.
2. **Loss Function**:
   - **Cross-Entropy Loss**: Measures error between predicted probabilities and actual labels.
3. **Optimization**:
   - **He Initialization**: Efficient weight initialization.
   - **Forward and Backward Propagation**: Used for learning.

## Results
The model was evaluated on the CIFAR-10 dataset and compared against other classification methods:

| **Classifier**                  | **Accuracy** | **Training Time**  |
|---------------------------------|--------------|--------------------|
| **Nearest Neighbor**            | 35.39%       | 2412 seconds       |
| **Nearest Class Centroid**      | 27.74%       | 0.6 seconds        |
| **Multilayer Perceptron (MLP)** | ~55%         | 150 seconds        |

### Observations
- The MLP outperformed simpler classifiers like Nearest Neighbor and Nearest Class Centroid in terms of accuracy.
- Nearest Class Centroid was the fastest but had the lowest accuracy.
- The Nearest Neighbor classifier required significantly more time for computation compared to the MLP.

## Key Takeaways
- The **MLP demonstrated superior performance**, effectively balancing computational efficiency and accuracy.
- The project highlights the strength of neural networks in learning complex patterns in data and provides a solid foundation for exploring advanced architectures and optimization techniques.
