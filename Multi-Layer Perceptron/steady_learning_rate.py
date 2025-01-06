# κωδικας για σταθερο learning rate η

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

    train_data = [] # αποθηκευει τα δεδομενα εικονας
    train_labels = [] # αποθηκευει τις ετικετες για καθε εικονα 
    for i in range(1, 6):
        batch = unpickle(os.path.join(data_dir, f"data_batch_{i}"))
        train_data.append(batch[b'data']) # δεδομενα εικονας
        train_labels += batch[b'labels'] # label εικονας
    train_data = np.vstack(train_data).astype(np.float32) / 255.0 # κανονικοποιηση στο [0,1]
    train_labels = np.array(train_labels)

    test_batch = unpickle(os.path.join(data_dir, "test_batch"))
    test_data = test_batch[b'data'].astype(np.float32) / 255.0
    test_labels = np.array(test_batch[b'labels'])

    # επιστρεφονται τα δεδομένα εκπαίδευσης, οι ετικέτες εκπαίδευσης, τα δεδομένα δοκιμής 
    # και οι ετικέτες δοκιμής.
    return train_data, train_labels, test_data, test_labels

# συναρτηση ενεργοποιησης ReLU
# επιστρεφει x εαν x>0
# αλλιως επιστρεφει 0
def relu(x):
    return np.maximum(0, x)

# παραγωγος της ReLU
def relu_derivative(x):
    return (x > 0).astype(float)

# μετατροπη των εξοδων σε πιθανότητες
def softmax(x):
    exp_x = np.exp(x - np.max(x, axis=1, keepdims=True))
    return exp_x / np.sum(exp_x, axis=1, keepdims=True)

# υπολογισμος της αποκλισης μεταξυ των πραγματικων (y_true) και προβλεπώμενων τιμων y_pred 
# (υπολογισμος μεσου όρου loss για το batch)
# y_true.shape[0] αντιστοιχεί στον αριθμό των δειγμάτων  m  στο τρέχον (στην προκειμενη περιπτωση ειναι 128)
def cross_entropy_loss(y_true, y_pred):
    return -np.sum(y_true * np.log(y_pred + 1e-8)) / y_true.shape[0]

# παραγωγος της  cross entropy
def cross_entropy_derivative(y_true, y_pred):
    return y_pred - y_true

# ανακατευω τα δεδομενα για να εξασφαλισω οτι το καθε batch θα ναι τυχαιο
# διαχωριζω τα δεδομενα σε μικρα batches
def create_batches(X, y, batch_size):
    # ανακατευω τα δεδομενα και τα labels με την βοηθεια των τυχαιων δεικτων
    num_samples = X.shape[0]
    indices = np.arange(num_samples)
    np.random.shuffle(indices)
    X = X[indices]
    y = y[indices]

    # διαδικασία διαχωρισμού σε batches
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
        # αρχικοποιηση των βαρων με He initialiazation
        # αρχικοποιηση του bias στο 0
        layer_sizes = [input_size] + hidden_sizes + [output_size]
        for i in range(len(layer_sizes) - 1):
            self.weights.append(np.random.randn(layer_sizes[i], layer_sizes[i+1]) * np.sqrt(2 / layer_sizes[i]))
            self.biases.append(np.zeros((1, layer_sizes[i+1])))

    # forward propagation
    def forward(self, X):
        self.activations = [X]
        self.z_values = []

        for i in range(len(self.weights) - 1):
            z = np.dot(self.activations[-1], self.weights[i]) + self.biases[i] # υπολογισμος εξοδου
            self.z_values.append(z)
            self.activations.append(relu(z)) # ενεργοποιηση με ReLU
        
        z = np.dot(self.activations[-1], self.weights[-1]) + self.biases[-1]
        self.z_values.append(z)
        self.activations.append(softmax(z))
        return self.activations[-1]

    # backward propagation
    def backward(self, X, y_true):
        gradients_w = []
        gradients_b = []

        # υπολογισμος σφαλματος εξοδου
        delta = cross_entropy_derivative(y_true, self.activations[-1])
        for i in reversed(range(len(self.weights))):
            # παραγωγοι για weights και biases
            grad_w = np.dot(self.activations[i].T, delta) / X.shape[0]
            grad_b = np.sum(delta, axis=0, keepdims=True) / X.shape[0]
            gradients_w.insert(0, grad_w)
            gradients_b.insert(0, grad_b)

            # υπολογισμος σφαλματος για hidden layers
            if i != 0:
                delta = np.dot(delta, self.weights[i].T) * relu_derivative(self.z_values[i-1])

        for i in range(len(self.weights)):
            self.weights[i] -= self.learning_rate * gradients_w[i]
            self.biases[i] -= self.learning_rate * gradients_b[i]

    def train(self, X_train, y_train, X_test, y_test, epochs=10, batch_size=128):
        best_epoch = None # εποχη με το καλυτερο test accuracy
        best_accuracy = 0 # υψηλότερη ακρίβεια στο test set
        best_stats = {} # στατιστικά της καλύτερης εποχής (train loss, test loss, train accuracy, test accuracy)
        
        start_time = time.time()  # Έναρξη συνολικού χρόνου εκτέλεσης

        for epoch in range(epochs):
            train_batches = create_batches(X_train, y_train, batch_size)

            # train_loss: συνολικό loss για όλα τα mini-batches
            # train_correct: το πλήθος των σωστών προβλέψεων
            train_loss, train_correct = 0, 0
            for X_batch, y_batch in train_batches:
                predictions = self.forward(X_batch) # υπολογισμος προβλεψεων νευρωνικου
                train_loss += cross_entropy_loss(y_batch, predictions) # loss για το τρεχον batch 
                train_correct += np.sum(np.argmax(predictions, axis=1) == np.argmax(y_batch, axis=1)) # υπολογισμος ακριβειας του 
                # batch συγκρινοντας τις προβλεψεις με τις πραγματικες ετικετες
                self.backward(X_batch, y_batch) # υπολογισμος και ενημερωση βαρων

            test_predictions = self.forward(X_test) # υπολογισμος προβλεψεων για τα δεδομενα δοκιμης 
            test_loss = cross_entropy_loss(y_test, test_predictions) # υπολογισμος συνολικου loss στο test set
            test_accuracy = np.mean(np.argmax(test_predictions, axis=1) == np.argmax(y_test, axis=1))

            train_loss /= len(train_batches) # μεσος όρος του loss για ολα τα batches 
            train_accuracy = train_correct / X_train.shape[0] # υπολογισμος ακριβειας

            # ενημερωση των καλυτερων αποτελεσματων
            if test_accuracy > best_accuracy:
                best_accuracy = test_accuracy
                best_epoch = epoch + 1
                best_stats = {
                    "train_loss": train_loss,
                    "test_loss": test_loss,
                    "train_accuracy": train_accuracy * 100,
                    "test_accuracy": test_accuracy * 100,
                }

            total_time = time.time() - start_time  # Συνολικός χρόνος εκτέλεσης μέχρι τώρα

            # εμφανιση αποτελεσματων
            print(f"Epoch {epoch + 1}/{epochs}")
            print(f"Training Loss: {train_loss:.4f}, Training Accuracy: {train_accuracy * 100:.2f}%")
            print(f"Testing Loss: {test_loss:.4f}, Testing Accuracy: {test_accuracy * 100:.2f}%")
            print(f"Total time until epoch {epoch + 1}: {total_time:.2f} seconds")
            print("-" * 50)

        # τελικη εμφανιση καλυτερων αποτελεσματων
        print("\nBest Results:")
        print(f"Epoch: {best_epoch}")
        print(f"Training Loss: {best_stats['train_loss']:.4f}, Training Accuracy: {best_stats['train_accuracy']:.2f}%")
        print(f"Testing Loss: {best_stats['test_loss']:.4f}, Testing Accuracy: {best_stats['test_accuracy']:.2f}%")

    def evaluate(self, X, y):
        predictions = np.argmax(self.forward(X), axis=1) # υπολογιζω τις προβλέψεις του δικτύου y μέσω της μεθόδου forward
        accuracy = np.mean(predictions == np.argmax(y, axis=1)) # συγκρινω τις προβλέψεις με τις 
        # πραγματικές ετικέτες y για τον υπολογισμο της ακριβειας
        print(f"Accuracy: {accuracy * 100:.2f}%")

# μετατροπη ετικετων σε one-hot encoding
def preprocess_data(train_data, train_labels, test_data, test_labels):
    train_labels_one_hot = np.eye(10)[train_labels] # 10*10 identity matrix
    test_labels_one_hot = np.eye(10)[test_labels]
    return train_data, train_labels_one_hot, test_data, test_labels_one_hot

if __name__ == "__main__":
    start_time = time.time()

    data_dir = os.path.expanduser("~/Desktop/Neural_Networks_project")
    train_data, train_labels, test_data, test_labels = load_cifar10_data(data_dir)
    train_data, train_labels, test_data, test_labels = preprocess_data(train_data, train_labels, test_data, test_labels)

    # ορισμός δικτύου
    input_size = train_data.shape[1] # αριθμος pixel (3072)
    hidden_sizes = [64]
    output_size = 10

    nn = NeuralNetwork(input_size, hidden_sizes, output_size, learning_rate=0.1)
    nn.train(train_data, train_labels, test_data, test_labels, epochs=500, batch_size=128)
    nn.evaluate(test_data, test_labels)

    end_time = time.time()
    print(f"\nTotal Execution Time: {end_time - start_time:.2f} seconds")