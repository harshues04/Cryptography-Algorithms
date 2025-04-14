# Cryptography-Algorithms

A React-based web application for exploring and implementing cryptographic algorithms, built as part of Semester-6 coursework for Cryptography Techniques. The app features a sleek, dark-themed interface with a forest-inspired color palette, providing an interactive way to encrypt and decrypt text using various ciphers.

**[Live Demo](https://harshues04.github.io/Cryptography-Algorithms)**

## Features

- **Multiple Cryptographic Algorithms**
  - Caesar Cipher
  - Atbash Cipher
  - August Cipher
  - Affine Cipher
  - Vigenère Cipher
  - Gronsfeld Cipher
  - Autokey Cipher
  - Beaufort Cipher
  - Running Key Cipher
  - Ngram cipher
  - Hill Cipher
  - Rail Fence Cipher (Zigzag)
  - Route Cipher
  - Myszkowiski Cipher
  
  

- **Interactive User Experience**
  - Real-time encryption/decryption
  - Input validation with visual feedback
  - Informative error handling (invalid keys shown in red)

## Technologies Used

- **Frontend**: React, TypeScript
- **Styling**: Custom CSS
- **Deployment**: GitHub Pages
- **Development**: Node.js, npm

## Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/harshues04/Cryptography-Algorithms.git
   cd Cryptography-Algorithms
   ```

2. **Install dependencies**
   ```bash
   npm install
   ```

3. **Start the development server**
   ```bash
   npm start
   ```
   The application will be available at `http://localhost:3000`

## Usage

1. Select a cipher algorithm from the available options
2. Enter your plaintext in the input field
3. Provide the required key (if applicable)
4. View the encrypted output in real-time
5. Switch between encryption and decryption as needed

## Project Structure

```
cryptography-algorithms/
├── public/
│   ├── index.html
│   └── ...
├── src/
│   ├── components/
│   │   ├── CipherInterface.tsx
│   │   └── ...
│   ├── algorithms/
│   │   ├── caesar.ts
│   │   ├── vigenere.ts
│   │   └── ...
│   ├── App.tsx
│   ├── index.tsx
│   └── ...
├── package.json
└── README.md
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Developed as part of the Semester-6 Cryptography Techniques coursework
- Thanks to all contributors and testers who helped improve this project

