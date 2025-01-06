# polynomial kernel 

import numpy as np
import os
import pickle
from sklearn.svm import SVC
from sklearn.decomposition import PCA
from sklearn.metrics import accuracy_score
from sklearn.utils import shuffle
import time


def load_cifar10_data(data_dir, samples_per_batch=1000):
    def unpickle(file):
        with open(file, 'rb') as fo:
            dict = pickle.load(fo, encoding='bytes')
        return dict

    
    train_data = []
    train_labels = []
    for i in range(1, 6):  
        batch = unpickle(os.path.join(data_dir, f"data_batch_{i}"))
        train_data.append(batch[b'data'][:samples_per_batch])  
        train_labels += batch[b'labels'][:samples_per_batch]
    train_data = np.vstack(train_data).astype(np.float32) / 255.0  
    train_labels = np.array(train_labels)

  
    test_batch = unpickle(os.path.join(data_dir, "test_batch"))
    test_data = test_batch[b'data'][:samples_per_batch].astype(np.float32) / 255.0
    test_labels = np.array(test_batch[b'labels'][:samples_per_batch])


    meta = unpickle(os.path.join(data_dir, "batches.meta"))
    label_names = [x.decode('utf-8') for x in meta[b'label_names']]

    return train_data, train_labels, test_data, test_labels, label_names


program_start_time = time.time()


data_dir = os.path.expanduser("~/Desktop/Second_Neural_Networks_project")
print("Φόρτωση δεδομένων...")
X_train, y_train, X_test, y_test, label_names = load_cifar10_data(data_dir, samples_per_batch=10000)


print("Ανακατεύθυνση δεδομένων εκπαίδευσης...")
X_train, y_train = shuffle(X_train, y_train, random_state=42)


print(f"Διαθέσιμες κλάσεις: {', '.join(label_names)}")
print(f"Δεδομένα για εκπαίδευση: {len(y_train)}, Δεδομένα για δοκιμή: {len(y_test)}")


print("Εφαρμογή PCA για μείωση διάστασης...")
pca = PCA(0.92) 
X_train_pca = pca.fit_transform(X_train)
X_test_pca = pca.transform(X_test)

print(f"Αρχική διάσταση: {X_train.shape[1]}, Νέα διάσταση: {X_train_pca.shape[1]}")


C_values = [0.001, 0.01, 0.1, 1, 10]
gamma_values = [0.01, 0.1, 1]
degree_values = [2, 3]
best_testing_accuracy = 0
best_params = {}

print("\nΠειραματισμός με διαφορετικές τιμές των degree, C και gamma:")
for degree in degree_values:
    for C in C_values:
        for gamma in gamma_values:
            print(f"\nΕκπαίδευση SVM με degree={degree}, C={C}, gamma={gamma} (Polynomial Kernel)...")
            start_time = time.time()
            svm_poly = SVC(kernel='poly', C=C, gamma=gamma, degree=degree, decision_function_shape='ovo')
            svm_poly.fit(X_train_pca, y_train)
            train_time_seconds = time.time() - start_time
            train_minutes = int(train_time_seconds // 60)
            train_seconds = int(train_time_seconds % 60)

            y_pred_train = svm_poly.predict(X_train_pca)
            y_pred_test = svm_poly.predict(X_test_pca)
            train_accuracy = accuracy_score(y_train, y_pred_train) * 100
            test_accuracy = accuracy_score(y_test, y_pred_test) * 100

            print(f"Training Accuracy: {train_accuracy:.2f}%")
            print(f"Testing Accuracy: {test_accuracy:.2f}%")
            print(f"Χρόνος εκπαίδευσης: {train_minutes} λεπτά και {train_seconds} δευτερόλεπτα")

            if test_accuracy > best_testing_accuracy:
                best_testing_accuracy = test_accuracy
                best_params = {
                    'degree': degree,
                    'C': C,
                    'gamma': gamma,
                    'training_accuracy': train_accuracy,
                    'testing_accuracy': test_accuracy,
                    'train_time': f"{train_minutes} λεπτά και {train_seconds} δευτερόλεπτα"
                }


print("\nΑποτελέσματα:")
print(f"Καλύτερες Παράμετροι:")
print(f"Degree: {best_params['degree']}")
print(f"C: {best_params['C']}")
print(f"Gamma: {best_params['gamma']}")
print(f"Training Accuracy: {best_params['training_accuracy']:.2f}%")
print(f"Testing Accuracy: {best_params['testing_accuracy']:.2f}%")
print(f"Χρόνος Εκπαίδευσης: {best_params['train_time']}")


program_end_time = time.time()
total_time_seconds = program_end_time - program_start_time
total_minutes = int(total_time_seconds // 60)
total_seconds = int(total_time_seconds % 60)

print(f"\nΣυνολικός χρόνος εκτέλεσης προγράμματος: {total_minutes} λεπτά και {total_seconds} δευτερόλεπτα")