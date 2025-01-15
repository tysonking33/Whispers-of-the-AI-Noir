# Import necessary libraries
import torch
import torch.nn as nn
from torch.utils.data import DataLoader, TensorDataset
from datasets import load_dataset
from transformers import GPT2Tokenizer
from nanogpt_module import GPTConfig, GPT

# Load dataset
dataset = load_dataset("wikitext", "wikitext-2-raw-v1")
train_text = dataset['train']['text']

# Tokenization
tokenizer = GPT2Tokenizer.from_pretrained("gpt2")
tokenizer.pad_token = tokenizer.eos_token  # Ensure padding works

# Tokenize and pad text
def tokenize_text(texts, max_length=128):
    return tokenizer(texts, truncation=True, padding='max_length', max_length=max_length, return_tensors="pt")

tokenized_data = [tokenize_text(text) for text in train_text if len(text) > 0]

# Prepare inputs and labels
inputs = torch.cat([data["input_ids"] for data in tokenized_data])
labels = inputs.clone()

# Create DataLoader
batch_size = 32
dataset = TensorDataset(inputs, labels)
dataloader = DataLoader(dataset, batch_size=batch_size, shuffle=True)

# Define the model
config = GPTConfig(
    vocab_size=tokenizer.vocab_size,
    block_size=128,
    n_layer=4,
    n_head=4,
    n_embd=128
)
model = GPT(config)

# Define loss function and optimizer
loss_fn = nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(model.parameters(), lr=3e-4)

# Training function
def train(model, dataloader, epochs, device):
    model.to(device)
    model.train()
    for epoch in range(epochs):
        total_loss = 0
        for inputs, labels in dataloader:
            inputs, labels = inputs.to(device), labels.to(device)
            optimizer.zero_grad()
            outputs = model(inputs)
            loss = loss_fn(outputs.view(-1, outputs.size(-1)), labels.view(-1))
            loss.backward()
            optimizer.step()
            total_loss += loss.item()
        print(f"Epoch {epoch+1}/{epochs}, Loss: {total_loss / len(dataloader)}")

# Train the model
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
train(model, dataloader, epochs=5, device=device)

# Save the model
torch.save(model.state_dict(), "./models/nanogpt_model")

# Load the model
model.load_state_dict(torch.load("./models/nanogpt_model"))

# Text generation
def generate_text(model, tokenizer, prompt, max_length=50, device="cpu"):
    model.eval()
    input_ids = tokenizer(prompt, return_tensors="pt")["input_ids"].to(device)
    for _ in range(max_length):
        outputs = model(input_ids)
        next_token = torch.argmax(outputs[:, -1, :], dim=-1)
        input_ids = torch.cat([input_ids, next_token.unsqueeze(-1)], dim=1)
    return tokenizer.decode(input_ids[0], skip_special_tokens=True)

# Test text generation
prompt = "Once upon a time"
generated_text = generate_text(model, tokenizer, prompt, max_length=100, device=device)
print(generated_text)
