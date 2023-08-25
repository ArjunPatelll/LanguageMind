
import os

import tensorflow as tf
from tensorflow import keras

def get_newest_model_version(model_name: str):
    versions = [
        int(version_name) for version_name in os.listdir(model_name) if version_name.isdigit()
    ]
    return str(max(versions, default=0))

def mnist_model_fn(model_names):
    for model_name in model_names:
        model_path = f"{model_name}/{get_newest_model_version(model_name)}"
        if os.path.exists(model_path):
            model = keras.models.load_model(model_path)
            model = train_model(model)

def train_model(model):
    mnist = keras.datasets.mnist
    (x_train, y_train), (x_test, y_test) = mnist.load_data()
    x_train, x_test = x_train / 255.0, x_test / 255.0

    model.compile(optimizer="adam", loss="sparse_categorical_crossentropy", metrics=["accuracy"])
    model.fit(x_train, y_train, epochs=1)
    _, acc = model.evaluate(x_test, y_test)
    print(f"Model {model.name}: Accuracy {acc}")

if __name__ == "__main__":
    model_names = ["ni7n0fvs", "zvraldrj"]
    mnist_model_fn(model_names)


