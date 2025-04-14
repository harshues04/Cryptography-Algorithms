import { Algorithm, Operation } from '../types';

const affineCipher: Algorithm = {
  name: 'Affine',
  keyRequired: true,
  func: (text: string, operation: Operation, key?: string) => {
    if (!key) throw new Error('Key is required for Affine cipher');
    const [a, b] = key.split(',').map(Number);
    if (isNaN(a) || isNaN(b)) throw new Error('Key must be two numbers (a,b)');

    const modInverse = (a: number, m: number) => {
      for (let x = 1; x < m; x++) {
        if ((a * x) % m === 1) return x;
      }
      throw new Error('No modular inverse exists for a');
    };

    return text
      .toUpperCase()
      .replace(/[A-Z]/g, (char) => {
        const x = char.charCodeAt(0) - 65;
        if (operation === 'encrypt') {
          const y = (a * x + b) % 26;
          return String.fromCharCode(y + 65);
        } else {
          const aInv = modInverse(a, 26);
          const y = (aInv * (x - b + 26)) % 26;
          return String.fromCharCode(y + 65);
        }
      });
  },
};

export default affineCipher;