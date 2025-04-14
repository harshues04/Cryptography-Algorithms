import { Algorithm, Operation } from '../types';

const vigenereCipher: Algorithm = {
  name: 'Vigenère',
  keyRequired: true,
  func: (text: string, operation: Operation, key?: string) => {
    if (!key) throw new Error('Key is required for Vigenère cipher');
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
          newCode = (textCode + keyCode) % 26;
        } else {
          newCode = (textCode - keyCode + 26) % 26;
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

export default vigenereCipher;