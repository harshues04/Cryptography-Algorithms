import { Algorithm, Operation } from '../types';

const atbashCipher: Algorithm = {
  name: 'Atbash',
  keyRequired: false,
  func: (text: string, _operation: Operation) => {
    return text
      .toUpperCase()
      .replace(/[A-Z]/g, (char) => {
        const code = char.charCodeAt(0) - 65;
        const mirrored = 25 - code;
        return String.fromCharCode(mirrored + 65);
      });
  },
};

export default atbashCipher;