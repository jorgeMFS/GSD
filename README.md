# GSD (Genetic Sequence Distance)

A high-performance tool for measuring the similarity between genetic sequences using compression-based distance metrics.

## Overview

GSD uses compression-based distance metrics to calculate the similarity between DNA sequences. It implements the Normalized Compression Distance (NCD) algorithm, which is particularly useful for:

- Comparing genetic sequences without alignment
- Measuring evolutionary distance between sequences
- Identifying related sequences
- Analyzing sequence mutations and variations
- Clustering similar sequences

## Features


- Fast compression-based sequence comparison
- Support for FASTA format input
- Multi-threaded processing for improved performance
- Similarity scores from 0-100%
- Detailed distance metrics (SCD - Sequence Compression Distance)
- Memory-efficient processing of large sequences

## Requirements

- GCC compiler
- POSIX-compliant system (Linux, macOS, BSD)
- Python 3.x (for test scripts)

## Installation

1. Clone the repository:

```bash
git clone https://github.com/yourusername/GSD.git
cd GSD
```

2. Build the tool:

```bash
cd src
make
```


## Usage

### Basic Usage

Compare two DNA sequences:

```bash
./gsd -v --dna --threads 4 -m 12:50:0:1:0:0.9/2:10:0.9 -r reference.fa target.fa
```

The tool outputs in CSV format:

```bash
InputSeq,SeqReference,Similarity(%),SCD
target.fa,reference.fa,90.42,0.095828
```

### Parameters

- `-v`: Verbose mode
- `--dna`: DNA sequence mode
- `--threads N`: Number of threads (default: 4)
- `-m MODEL`: Model parameters (format: ctx:den:ir:edits:eDen:gamma/bet:size:rate)
- `-r FILE`: Reference sequence file

### Using Test Scripts

Generate and compare random DNA sequences:

```bash
cd scripts
python3 generate_dna.py
```

This will:

1. Generate random DNA sequences
2. Create mutations at different rates
3. Compare sequences using GSD
4. Output similarity scores

## Output Format

The tool outputs four columns:
- `InputSeq`: Name of the input sequence file
- `SeqReference`: Name of the reference sequence file
- `Similarity(%)`: Similarity percentage (0-100%)
- `SCD`: Sequence Compression Distance value (0-1+)

## Directory Structure

```bash
GSD/
├── src/         # Source code for the GSD tool
│   ├── main.c   # Main program
│   ├── ncd.c    # NCD implementation
│   └── ...      # Supporting modules
├── scripts/     # Python scripts for testing
└── examples/    # Example sequences
```

## Performance

- Memory usage scales linearly with sequence length
- Multi-threading provides near-linear speedup
- Can process sequences of several hundred MB in minutes

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

MIT License - see LICENSE file for details.