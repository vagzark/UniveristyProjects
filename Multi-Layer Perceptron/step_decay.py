import numpy as np
import pickle
import os
import time  # Για τον υπολογισμό του χρόνου εκτέλεσης

# Φόρτωση των δεδομένων CIFAR-10
def load_cifar10_data(data_dir):
    def unpickle(file):
        with open(file, 'rb') as fo:
            dict = pickle.load(fo, encoding='bytes')
        return dict

    train_data = []  # αποθηκεύει τα δεδομένα εικόνας
    train_labels = []  # αποθηκεύει τις ετικέτες για κάθε εικόνα
    for i in range(1, 6):
        batch = unpickle(os.path.join(data_dir, f"data_batch_{i}"))
        train_data.append(batch[b'data'])  # δεδομένα εικόνας
        train_labels += batch[b'labels']  # ετικέτες
    train_data = np.vstack(train_data).astype(np.float32) / 255.0  # κανονικοποίηση στο [0,1]
    train_labels = np.array(train_labels)

    test_batch = unpickle(os.path.join(data_dir, "test_batch"))
    test_data = test_batch[b'data'].astype(np.float32) / 255.0
    test_labels = np.array(test_batch[b'labels'])

    return train_data, train_labels, test_data, test_labels

# Συναρτήσεις ενεργοποίησης
def relu(x):
    return np.maximum(0, x)

def relu_derivative(x):
    return (x > 0).astype(float)

def softmax(x):
    exp_x = np.exp(x - np.max(x, axis=1, keepdims=True))
    return exp_x / np.sum(exp_x, axis=1, keepdims=True)

# Συνάρτηση Cross Entropy
def cross_entropy_loss(y_true, y_pred):
    return -np.sum(y_true * np.log(y_pred + 1e-8)) / y_true.shape[0]

def cross_entropy_derivative(y_true, y_pred):
    return y_pred - y_true

# Δημιουργία mini-batches
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

class NeuralNetwork:
    def __init__(self, input_size, hidden_sizes, output_size, learning_rate=0.01):
        self.learning_rate = learning_rate
        self.weights = []
        self.biases = []
        # Αρχικοποίηση με He initialization
        layer_sizes = [input_size] + hidden_sizes + [output_size]
        for i in range(len(layer_sizes) - 1):
            self.weights.append(np.random.randn(layer_sizes[i], layer_sizes[i+1]) * np.sqrt(2 / layer_sizes[i]))
            self.biases.append(np.zeros((1, layer_sizes[i+1])))

    # Forward propagation
    def forward(self, X):
        self.activations = [X]
        self.z_values = []

        for i in range(len(self.weights) - 1):
            z = np.dot(self.activations[-1], self.weights[i]) + self.biases[i]
            self.z_values.append(z)
            self.activations.append(relu(z))
        
        z = np.dot(self.activations[-1], self.weights[-1]) + self.biases[-1]
        self.z_values.append(z)
        self.activations.append(softmax(z))
        return self.activations[-1]

    # Backward propagation
    def backward(self, X, y_true):
        gradients_w = []
        gradients_b = []

        delta = cross_entropy_derivative(y_true, self.activations[-1])
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

    # Εκπαίδευση με Step Decay
    def train(self, X_train, y_train, X_test, y_test, epochs=10, batch_size=128, step_size=10, decay_rate=0.5):
        best_epoch = None
        best_accuracy = 0
        best_stats = {}
        start_time = time.time()

        for epoch in range(epochs):
            # Μείωση Learning Rate κάθε step_size εποχές
            if epoch % step_size == 0 and epoch != 0:
                self.learning_rate *= decay_rate
                print(f"Epoch {epoch}: Reduced learning rate to {self.learning_rate:.5f}")

            train_batches = create_batches(X_train, y_train, batch_size)

            train_loss, train_correct = 0, 0
            for X_batch, y_batch in train_batches:
                predictions = self.forward(X_batch)
                train_loss += cross_entropy_loss(y_batch, predictions)
                train_correct += np.sum(np.argmax(predictions, axis=1) == np.argmax(y_batch, axis=1))
                self.backward(X_batch, y_batch)

            test_predictions = self.forward(X_test)
            test_loss = cross_entropy_loss(y_test, test_predictions)
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

# Μετατροπή ετικετών σε one-hot encoding
def preprocess_data(train_data, train_labels, test_data, test_labels):
    train_labels_one_hot = np.eye(10)[train_labels]
    test_labels_one_hot = np.eye(10)[test_labels]
    return train_data, train_labels_one_hot, test_data, test_labels_one_hot

if __name__ == "__main__":
    start_time = time.time()

    data_dir = os.path.expanduser("~/Desktop/Neural_Networks_project")
    train_data, train_labels, test_data, test_labels = load_cifar10_data(data_dir)
    train_data, train_labels, test_data, test_labels = preprocess_data(train_data, train_labels, test_data, test_labels)

    input_size = train_data.shape[1]
    hidden_sizes = [256,128]
    output_size = 10

    nn = NeuralNetwork(input_size, hidden_sizes, output_size, learning_rate=0.01)
    nn.train(train_data, train_labels, test_data, test_labels, epochs=500, batch_size=128, step_size=5, decay_rate=0.95)
    nn.evaluate(test_data, test_labels)

    end_time = time.time()
    print(f"\nTotal Execution Time: {end_time - start_time:.2f} seconds")