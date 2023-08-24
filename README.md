project_idea.md

# Idea: Fine-tuning GPT for Code Completion

```python
import tensorflow as tf
from transformers import GPT2Config, GPT2Tokenizer, TFGPT2LMHeadModel

# Load pre-trained GPT-2 model and tokenizer
tokenizer = GPT2Tokenizer.from_pretrained('gpt2')
config = GPT2Config.from_pretrained('gpt2')
model = TFGPT2LMHeadModel.from_pretrained('gpt2', config=config)

# Task-specific fine-tuning
# This code assumes the availability of a dataset of code snippets for training

# Define the training data
train_data = [
    "def sum(a, b):\n    return a + b\n", 
    "def divide(a, b):\n    return a / b\n",
    "def multiply(a, b):\n    return a * b\n"
]

# Tokenize the training data
tokenized_train_data = [tokenizer.encode(data) for data in train_data]

# Prepare the training input
train_input_ids = tf.constant([data[:-1] for data in tokenized_train_data])
train_labels = tf.constant([data[1:] for data in tokenized_train_data])

# Fine-tuning settings
epochs = 10
batch_size = 32
learning_rate = 1e-4

# Create the training dataset
train_dataset = tf.data.Dataset.from_tensor_slices((train_input_ids, train_labels))
train_dataset = train_dataset.shuffle(len(train_data)).batch(batch_size)

# Fine-tune the GPT-2 model
optimizer = tf.keras.optimizers.Adam(learning_rate=learning_rate)

for epoch in range(epochs):
    for step, (input_ids, labels) in enumerate(train_dataset):
        with tf.GradientTape() as tape:
            outputs = model(input_ids, labels=labels)
            loss = outputs.loss

        gradients = tape.gradient(loss, model.trainable_variables)
        optimizer.apply_gradients(zip(gradients, model.trainable_variables))

        if step % 100 == 0:
            print(f"Epoch {epoch + 1}, Step {step + 1}: Loss = {loss.numpy()}")
  
# Code completion
prompt = "def add_numbers(a, b):\n    # Complete the function here\n"
tokenized_prompt = tokenizer.encode(prompt)

# Generate completions
generated = model.generate(tf.constant([tokenized_prompt]),
                           max_length=30,
                           num_return_sequences=3)

# Decode and print the completions
for sequence in generated:
    completed_code = tokenizer.decode(sequence)
    print(completed_code)
```
