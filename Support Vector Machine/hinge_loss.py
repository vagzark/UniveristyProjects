import numpy as np
import pickle
import os
import time

def load_cifar10_data(data_dir):
    def unpickle(file):
        with open(file, 'rb') as fo:
            dict = pickle.load(fo, encoding='bytes')
        return dict

    train_data = []
    train_labels = []
    for i in range(1, 6):
        batch = unpickle(os.path.join(data_dir, f"data_batch_{i}"))
        train_data.append(batch[b'data'])
        train_labels += batch[b'labels']
    train_data = np.vstack(train_data).astype(np.float32) / 255.0
    train_labels = np.array(train_labels)

    test_batch = unpickle(os.path.join(data_dir, "test_batch"))
    test_data = test_batch[b'data'].astype(np.float32) / 255.0
    test_labels = np.array(test_batch[b'labels'])

    return train_data, train_labels, test_data, test_labels


def hinge_loss(y_true, y_pred):
   
    return np.mean(np.maximum(0, 1 - y_true * y_pred))


def hinge_loss_derivative(y_true, y_pred):

    grad = np.zeros_like(y_pred)
    mask = (1 - y_true * y_pred > 0)
    grad[mask] = -y_true[mask]
    return grad


def relu(x):
    return np.maximum(0, x)


def relu_derivative(x):
    return (x > 0).astype(float)


def create_batches(X, y, batch_size):
    num_samples = X.shape[0]
    indices = np.arange(num_samples)
    np.random.shuffle(indices)
    X = X[indices]
    y = y[indices]

    batches = []
    for i in range(0, num_samples, batch_size):
        X_batch = X[i:i+batch_size]
        y_batch = y[i:i+batch_size]
        batches.append((X_batch, y_batch))
    return batches


def preprocess_data(train_data, train_labels, test_data, test_labels):
   
    num_classes = 10
    train_labels_one_hot = -1 * np.ones((train_labels.size, num_classes))
    train_labels_one_hot[np.arange(train_labels.size), train_labels] = 1

    test_labels_one_hot = -1 * np.ones((test_labels.size, num_classes))
    test_labels_one_hot[np.arange(test_labels.size), test_labels] = 1

    return train_data, train_labels_one_hot, test_data, test_labels_one_hot

class NeuralNetwork:
    def __init__(self, input_size, hidden_sizes, output_size, learning_rate=0.01):
        self.learning_rate = learning_rate
        self.weights = []
        self.biases = []

        layer_sizes = [input_size] + hidden_sizes + [output_size]
        for i in range(len(layer_sizes) - 1):
            self.weights.append(np.random.randn(layer_sizes[i], layer_sizes[i+1]) * np.sqrt(2 / layer_sizes[i]))
            self.biases.append(np.zeros((1, layer_sizes[i+1])))

    def forward(self, X):
        self.activations = [X]
        self.z_values = []

        for i in range(len(self.weights)):
            z = np.dot(self.activations[-1], self.weights[i]) + self.biases[i]
            self.z_values.append(z)
            if i == len(self.weights) - 1:
                self.activations.append(z)
            else:
                self.activations.append(relu(z))
        return self.activations[-1]

    def backward(self, X, y_true):
        gradients_w = []
        gradients_b = []

        delta = hinge_loss_derivative(y_true, self.activations[-1])
        for i in reversed(range(len(self.weights))):
            grad_w = np.dot(self.activations[i].T, delta) / X.shape[0]
            grad_b = np.sum(delta, axis=0, keepdims=True) / X.shape[0]
            gradients_w.insert(0, grad_w)
            gradients_b.insert(0, grad_b)

            if i != 0:
                delta = np.dot(delta, self.weights[i].T) * relu_derivative(self.z_values[i-1])

        for i in range(len(self.weights)):
            self.weights[i] -= self.learning_rate * gradients_w[i]
            self.biases[i] -= self.learning_rate * gradients_b[i]

    def train(self, X_train, y_train, X_test, y_test, epochs=10, batch_size=128):
        best_epoch = None
        best_accuracy = 0
        best_stats = {}

        start_time = time.time()

        for epoch in range(epochs):
            train_batches = create_batches(X_train, y_train, batch_size)
            train_loss, train_correct = 0, 0

            for X_batch, y_batch in train_batches:
                predictions = self.forward(X_batch)
                train_loss += hinge_loss(y_batch, predictions)
                train_correct += np.sum(np.argmax(predictions, axis=1) == np.argmax(y_batch, axis=1))
                self.backward(X_batch, y_batch)

            test_predictions = self.forward(X_test)
            test_loss = hinge_loss(y_test, test_predictions)
            test_accuracy = np.mean(np.argmax(test_predictions, axis=1) == np.argmax(y_test, axis=1))

            train_loss /= len(train_batches)
            train_accuracy = train_correct / X_train.shape[0]

            if test_accuracy > best_accuracy:
                best_accuracy = test_accuracy
                best_epoch = epoch + 1
                best_stats = {
                    "train_loss": train_loss,
                    "test_loss": test_loss,
                    "train_accuracy": train_accuracy * 100,
                    "test_accuracy": test_accuracy * 100,
                }

            total_time = time.time() - start_time
            print(f"Epoch {epoch + 1}/{epochs}")
            print(f"Training Loss: {train_loss:.4f}, Training Accuracy: {train_accuracy * 100:.2f}%")
            print(f"Testing Loss: {test_loss:.4f}, Testing Accuracy: {test_accuracy * 100:.2f}%")
            print(f"Total time until epoch {epoch + 1}: {total_time:.2f} seconds")
            print("-" * 50)

        print("\nBest Results:")
        print(f"Epoch: {best_epoch}")
        print(f"Training Loss: {best_stats['train_loss']:.4f}, Training Accuracy: {best_stats['train_accuracy']:.2f}%")
        print(f"Testing Loss: {best_stats['test_loss']:.4f}, Testing Accuracy: {best_stats['test_accuracy']:.2f}%")

    def evaluate(self, X, y):
        predictions = np.argmax(self.forward(X), axis=1)
        accuracy = np.mean(predictions == np.argmax(y, axis=1))
        print(f"Accuracy: {accuracy * 100:.2f}%")

if __name__ == "__main__":
    start_time = time.time()

    data_dir = os.path.expanduser("~/Desktop/Second_Neural_Networks_project")
    train_data, train_labels, test_data, test_labels = load_cifar10_data(data_dir)
    train_data, train_labels, test_data, test_labels = preprocess_data(train_data, train_labels, test_data, test_labels)

    input_size = train_data.shape[1]
    hidden_sizes = [512]
    output_size = 10

    nn = NeuralNetwork(input_size, hidden_sizes, output_size, learning_rate=0.01)
    nn.train(train_data, train_labels, test_data, test_labels, epochs=400, batch_size=128)
    nn.evaluate(test_data, test_labels)

    end_time = time.time()
    print(f"\nTotal Execution Time: {end_time - start_time:.2f} seconds")