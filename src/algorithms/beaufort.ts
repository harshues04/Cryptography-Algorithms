import { Algorithm, Operation } from '../types';

const beaufortCipher: Algorithm = {
  name: 'Beaufort',
  keyRequired: true,
  func: (text: string, operation: Operation, key?: string) => {
    if (!key) throw new Error('Key is required for Beaufort cipher');
    const keyUpper = key.toUpperCase().replace(/[^A-Z]/g, '');
    if (!keyUpper) throw new Error('Key must contain letters');

    let result = '';
    let keyIndex = 0;
    const cleanedText = text.toUpperCase();

    for (let char of cleanedText) {
      if (/[A-Z]/.test(char)) {
        const textCode = char.charCodeAt(0) - 65;
        const keyCode = keyUpper[keyIndex % keyUpper.length].charCodeAt(0) - 65;
        let newCode: number;
        if (operation === 'encrypt') {
          newCode = (keyCode - textCode + 26) % 26;
        } else {
          newCode = (keyCode - textCode + 26) % 26; // Symmetric
        }
        result += String.fromCharCode(newCode + 65);
        keyIndex++;
      } else {
        result += char;
      }
    }
    return result;
  },
};

export default beaufortCipher;