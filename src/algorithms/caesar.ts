import { Algorithm, Operation } from '../types';

const caesarCipher: Algorithm = {
  name: 'Caesar',
  keyRequired: true,
  func: (text: string, operation: Operation, key?: string) => {
    if (!key) throw new Error('Key is required for Caesar cipher');
    const shift = parseInt(key);
    if (isNaN(shift)) throw new Error('Key must be a number');

    const modShift = operation === 'encrypt' ? shift % 26 : -shift % 26;
    return text
      .toUpperCase()
      .replace(/[A-Z]/g, (char) => {
        const code = char.charCodeAt(0) - 65;
        const shifted = (code + modShift + 26) % 26;
        return String.fromCharCode(shifted + 65);
      });
  },
};

export default caesarCipher;