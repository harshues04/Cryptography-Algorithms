import { Algorithm, Operation } from '../types';

const gronsfeldCipher: Algorithm = {
  name: 'Gronsfeld',
  keyRequired: true,
  func: (text: string, operation: Operation, key?: string) => {
    if (!key) throw new Error('Key is required for Gronsfeld cipher');
    const keyDigits = key.replace(/[^0-9]/g, '').split('').map(Number);
    if (!keyDigits.length) throw new Error('Key must contain digits');

    let result = '';
    let keyIndex = 0;
    const cleanedText = text.toUpperCase();

    for (let char of cleanedText) {
      if (/[A-Z]/.test(char)) {
        const textCode = char.charCodeAt(0) - 65;
        const shift = keyDigits[keyIndex % keyDigits.length];
        let newCode: number;
        if (operation === 'encrypt') {
          newCode = (textCode + shift) % 26;
        } else {
          newCode = (textCode - shift + 26) % 26;
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

export default gronsfeldCipher;