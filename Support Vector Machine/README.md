# Support Vector Machine for Multi-Class Classification

This project explores the use of **Support Vector Machines (SVMs)** to solve the multi-class classification problem on the **CIFAR-10 dataset**, focusing on comparing various kernels and parameter configurations.

## Key Features of the Project

- **Dataset**: CIFAR-10, containing 50,000 training images and 10,000 test images across 10 categories.
- **Normalization**: Pixel values normalized to [0, 1].
- **Dimensionality Reduction**: Principal Component Analysis (PCA) was applied to retain the most significant features while reducing computational complexity.
- **SVM Kernels**:
  - **Linear Kernel**: Explores how the hyperplane separates linearly separable data.
  - **Polynomial Kernel**: Introduces non-linearity with various degrees of polynomial transformations.
  - **Radial Basis Function (RBF) Kernel**: Maps data to a higher-dimensional space for better separation.

---

## Methodology

### 1. Data Preprocessing
- **Normalization**: Scales input data to the [0, 1] range.
- **PCA**: Tested for variance retention levels (90%, 92%, and 100%).

### 2. SVM Training
- **Linear Kernel**: Tuned the penalty parameter \( C \).
- **Polynomial Kernel**: Tuned the degree of the polynomial, \( C \), and gamma.
- **RBF Kernel**: Tuned \( C \) and gamma.

### 3. Evaluation
- **Metrics**:
  - **Training Accuracy**
  - **Testing Accuracy**
  - **Training Time**
- **Prediction Strategies**:
  - **One-vs-One (OvO)**: Constructs a classifier for each pair of classes.
  - **One-vs-Rest (OvR)**: Constructs a classifier for each class against all others.

---

## Results Summary

| Method                   | Training Accuracy | Testing Accuracy | Training Time |
|--------------------------|-------------------|------------------|---------------|
| 1-NN                     | N/A               | 35.39%           | 40.2 min      |
| 3-NN                     | N/A               | 33.03%           | 33.03 min     |
| Nearest Centroid         | N/A               | 27.74%           | 0.01 min      |
| MLP with Hinge Loss      | 79.50%            | 52.18%           | 15.16 min     |
| SVM (Linear Kernel)      | 42.59%            | 41.49%           | 3.49 min      |
| SVM (Polynomial Kernel)  | 64.42%            | 49.53%           | 3.49 min      |
| SVM (RBF Kernel)         | 98.70%            | 56.15%           | 6.2 min       |

---

## Observations

1. **Kernel Performance**:
   - **RBF Kernel**: Achieved the highest testing accuracy (56.15%) with moderate training time, showcasing its adaptability to non-linear data.
   - **Linear Kernel**: Performed poorly for CIFAR-10 due to its inherent non-linear separability.
   - **Polynomial Kernel**: Good performance but sensitive to parameter tuning.

2. **Comparison with Other Classifiers**:
   - SVM with RBF Kernel outperformed both **Nearest Neighbor** and **Nearest Centroid** classifiers in accuracy and training efficiency.
   - **MLP**: Performed well but required longer training times than SVM with RBF.

3. **Impact of PCA**:
   - Retaining 100% variance improved accuracy slightly but significantly increased training time.
   - Retaining 92% variance offered the best balance between accuracy and computational cost.

---

## Conclusion

The **SVM with RBF Kernel** proved to be the most effective classifier for this task, balancing accuracy and efficiency. The results emphasize the importance of kernel selection and hyperparameter tuning when applying SVMs to complex, real-world datasets like CIFAR-10.
