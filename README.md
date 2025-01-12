## Overview

Paraphrase Generator is a C-based application designed to rephrase input text, providing alternative expressions while preserving the original meaning.

## Features

- Accepts any text and synonym dictionary as inputs, as long as they are in the same language
- Implements an efficient algorithm based on binary trees to search for a synonym of each word
- Provides a file with the redesigned text
- Compares the performance of using a simple BST with using a Splay tree.

## Installation

Step-by-step instructions on how to get the development environment running.

### 1. Prerequisites
Before installing the project, ensure that you have a C compiler installed on your system. Here’s how to install a compiler for different platforms:

#### Linux
1. Open your terminal.
2. Install GCC (GNU Compiler Collection) using your package manager:
    ```bash
    sudo apt update
    sudo apt install build-essential
    ```
3. Verify the Installation with:
    ```bash
    gcc --version
    ```

#### macOS
1. Install the Xcode Command Line Tools:
    ```bash
    xcode-select --install
    ```
2. Verify the Installation with:
    ```bash
    gcc --version
    ```

#### Windows
1. Download and install [MinGW](https://sourceforge.net/projects/mingw/), which provides the GCC compiler.
2. During installation, ensure you select the "mingw32-gcc-g++" and "mingw32-base" packages.
3. Add the MinGW `bin` directory (e.g., `C:\MinGW\bin`) to your system's PATH environment variable.
4. Verify the Installation with:
    ```bash
    gcc --version
    ```

### 2. Clone the Repository

```bash
# Clone the repository
git clone https://github.com/J-Moro/graph-coloring.git

# Navigate to the project directory
cd paraphrase-generator
```

### 3. Compile the Application
The project includes a `Makefile` to simplify the compilation process. To compile the program, run:
```bash
make
```
This will generate an executable file named `paraphrase-generator`.

## Usage

### Input format

This program takes two files as inputs: the the synonym dictionary, and text to be paraphrased. 
- The dictionary should be provided in a plain text file where each line contains a word and its synonym, separated by a space.
- The text should be provided in a plain text file in any format.

Both of them are meant to be `.txt` files. Other file formats may not work as expected.

### Running the program
|To paraphrase a text, run the following command:
```bash
.\main --dictionary --text --output
```
- `--dictionary`: Path to the input file containing the dictionary
- `--text`: Path to the input file containing the text to be paraphrased
- `--output`: Path to the output file

### Output

The program outputs a plain text file with the paraphrased text, that is, the same text as input, but with each word replaced by its synonym. Words that do not have a synonym in the provided dictionary are unchanged.

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a new branch (`git checkout -b feature-branch`)
3. Make your changes
4. Commit your changes (`git commit -m 'Add some feature'`)
5. Push to the branch (`git push origin feature-branch`)
6. Open a pull request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

- Julia - [moronunes.julia@gmail.com](mailto:moronunes.julia@gmail.com)
- Rafael - [ralexandrini2@gmail.com](mailto:ralexandrini2@gmail.com)
- Project Link: [https://github.com/J-Moro/graph-coloring](https://github.com/J-Moro/graph-coloring)

## Aknowledgements

This project was made with help from Chat GPT and Github Copilot.