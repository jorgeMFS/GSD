import random
import os

def generate_base_dna_sequence(size_mb=1):
    """Generate a random DNA sequence of specified size in MB"""
    bases = ['A', 'C', 'G', 'T']
    size_bytes = size_mb * 1024 * 1024  # Convert MB to bytes
    sequence = ''.join(random.choice(bases) for _ in range(size_bytes))
    return sequence

def create_similar_sequence(original, mutation_rate=0.01):
    """Create a similar sequence with controlled mutation rate"""
    bases = ['A', 'C', 'G', 'T']
    mutated = list(original)
    mutations = int(len(original) * mutation_rate)
    positions = random.sample(range(len(original)), mutations)
    
    for pos in positions:
        current = mutated[pos]
        # Choose a different base
        new_base = random.choice([b for b in bases if b != current])
        mutated[pos] = new_base
    
    return ''.join(mutated)

def write_fasta(filename, sequence, description):
    with open(filename, 'w') as f:
        f.write(f">{description}\n")
        # Write sequence in lines of 60 characters
        for i in range(0, len(sequence), 60):
            f.write(sequence[i:i+60] + '\n')

# Generate original sequence
original_seq = generate_base_dna_sequence(1)

# Test different mutation rates
mutation_rates = [0.0001, 0.01, 0.02, 0.03, 0.04, 0.10, 0.25, 0.50, 1.0]  # 0.01%, 1%, 2%, 3%, 4%, 10%, 25%, 50%, 100%

print("\nMutation_Rate,InputSeq,SeqReference,Similarity(%),SCD")
print("-" * 70)

for rate in mutation_rates:
    # Clean up previous files
    if os.path.exists('test_dna_1.fa'):
        os.remove('test_dna_1.fa')
    if os.path.exists('ALL.fa'):
        os.remove('ALL.fa')
        
    similar_seq = create_similar_sequence(original_seq, mutation_rate=rate)
    write_fasta(f'test_dna_1.fa', original_seq, 'RandomDNA_1MB_Original')
    write_fasta(f'ALL.fa', similar_seq, f'RandomDNA_1MB_Similar_{rate*100}pct')
    
    import subprocess
    cmd = '../src/gsd -v --dna --threads 4 -m 12:50:0:1:0:0.9/2:10:0.9 -r test_dna_1.fa ALL.fa'
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    
    # Parse the output directly
    output_lines = [line for line in result.stdout.strip().split('\n') if line.startswith('ALL.fa')]
    if output_lines:
        # Add mutation rate to the output
        print(f"{rate*100:.2f}%,{output_lines[0]}")  # The NCD tool now outputs in CSV format 