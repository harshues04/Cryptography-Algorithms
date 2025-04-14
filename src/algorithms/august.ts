import { Algorithm, Operation } from '../types';

const augustCipher: Algorithm = {
  name: 'August',
  keyRequired: false,
  func: (text: string, operation: Operation) => {
    const shift = operation === 'encrypt' ? 1 : -1;
    return text
      .toUpperCase()
      .replace(/[A-Z]/g, (char) => {
        const code = char.charCodeAt(0) - 65;
        const shifted = (code + shift + 26) % 26;
        return String.fromCharCode(shifted + 65);
      });
  },
};

export default augustCipher;