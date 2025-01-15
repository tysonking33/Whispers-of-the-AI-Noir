import torch
import torch.nn as nn

class GPTConfig:
    def __init__(self, vocab_size, block_size, n_layer, n_head, n_embd):
        self.vocab_size = vocab_size
        self.block_size = block_size
        self.n_layer = n_layer
        self.n_head = n_head
        self.n_embd = n_embd

class GPT(nn.Module):
    def __init__(self, config):
        super(GPT, self).__init__()
        self.token_embed = nn.Embedding(config.vocab_size, config.n_embd)
        self.position_embed = nn.Parameter(torch.zeros(1, config.block_size, config.n_embd))
        self.layers = nn.ModuleList([
            nn.TransformerEncoderLayer(
                config.n_embd, 
                config.n_head, 
                dim_feedforward=4 * config.n_embd
            ) for _ in range(config.n_layer)
        ])
        self.ln_f = nn.LayerNorm(config.n_embd)
        self.head = nn.Linear(config.n_embd, config.vocab_size, bias=False)

    def forward(self, idx):
        b, t = idx.size()
        assert t <= self.position_embed.size(1), "Sequence length exceeds block size"
        token_embeddings = self.token_embed(idx)
        position_embeddings = self.position_embed[:, :t, :]
        x = token_embeddings + position_embeddings
        for layer in self.layers:
            x = layer(x)
        x = self.ln_f(x)
        logits = self.head(x)
        return logits
