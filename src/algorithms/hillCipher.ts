import { Algorithm, Operation } from '../types';

const hillCipher: Algorithm = {
  name: 'Hill Cipher',
  keyRequired: true,
  func: (text: string, operation: Operation, key?: string) => {
    if (!key) throw new Error('Key is required for Hill Cipher');
    const matrix = key.split(',').map(Number);
    if (matrix.length !== 4) throw new Error('Key must be a 2x2 matrix (4 numbers)');

    const det = matrix[0] * matrix[3] - matrix[1] * matrix[2];
    const modInverse = (a: number, m: number) => {
      for (let x = 1; x < m; x++) {
        if ((a * x) % m === 1) return x;
      }
      throw new Error('No modular inverse exists');
    };

    const textPairs = text
      .toUpperCase()
      .replace(/[^A-Z]/g, '')
      .match(/.{1,2}/g) || [];

    let result = '';
    for (let pair of textPairs) {
      if (pair.length < 2) pair += 'X';
      const [x1, x2] = pair.split('').map((c) => c.charCodeAt(0) - 65);
      let y1, y2;
      if (operation === 'encrypt') {
        y1 = (matrix[0] * x1 + matrix[1] * x2) % 26;
        y2 = (matrix[2] * x1 + matrix[3] * x2) % 26;
      } else {
        const detInv = modInverse(det % 26 < 0 ? det % 26 + 26 : det % 26, 26);
        const invMatrix = [
          (matrix[3] * detInv) % 26,
          (-matrix[1] * detInv + 26) % 26,
          (-matrix[2] * detInv + 26) % 26,
          (matrix[0] * detInv) % 26,
        ];
        y1 = (invMatrix[0] * x1 + invMatrix[1] * x2) % 26;
        y2 = (invMatrix[2] * x1 + invMatrix[3] * x2) % 26;
      }
      result += String.fromCharCode(y1 + 65, y2 + 65);
    }
    return result;
  },
};

export default hillCipher;