import { Algorithm, Operation } from '../types';

const autoKeyCipher: Algorithm = {
  name: 'Auto Key',
  keyRequired: true,
  func: (text: string, operation: Operation, key?: string) => {
    if (!key) throw new Error('Key is required for Auto Key cipher');
    const keyUpper = key.toUpperCase().replace(/[^A-Z]/g, '');
    if (!keyUpper) throw new Error('Key must contain letters');

    let result = '';
    let runningKey = keyUpper;
    let keyIndex = 0;
    const cleanedText = text.toUpperCase().replace(/[^A-Z]/g, '');

    for (let i = 0; i < cleanedText.length; i++) {
      const char = cleanedText[i];
      const textCode = char.charCodeAt(0) - 65;
      const keyChar = runningKey[keyIndex];
      const keyCode = keyChar.charCodeAt(0) - 65;
      let newCode: number;

      if (operation === 'encrypt') {
        newCode = (textCode + keyCode) % 26;
        result += String.fromCharCode(newCode + 65);
        runningKey += char; // Append plaintext
      } else {
        newCode = (textCode - keyCode + 26) % 26;
        result += String.fromCharCode(newCode + 65);
        runningKey += String.fromCharCode(newCode + 65); // Append decrypted text
      }
      keyIndex++;
    }
    return result;
  },
};

export default autoKeyCipher;