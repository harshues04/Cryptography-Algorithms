import { Algorithm, Operation } from '../types';

const runningKeyCipher: Algorithm = {
  name: 'Running Key',
  keyRequired: true,
  func: (text: string, operation: Operation, key?: string) => {
    if (!key) throw new Error('Key is required for Running Key cipher');
    const keyUpper = key.toUpperCase().replace(/[^A-Z]/g, '');
    const cleanedText = text.toUpperCase().replace(/[^A-Z]/g, '');
    if (keyUpper.length < cleanedText.length) {
      throw new Error('Key must be at least as long as the text');
    }

    let result = '';
    for (let i = 0; i < cleanedText.length; i++) {
      const textCode = cleanedText.charCodeAt(i) - 65;
      const keyCode = keyUpper.charCodeAt(i) - 65;
      let newCode: number;
      if (operation === 'encrypt') {
        newCode = (textCode + keyCode) % 26;
      } else {
        newCode = (textCode - keyCode + 26) % 26;
      }
      result += String.fromCharCode(newCode + 65);
    }
    return result;
  },
};

export default runningKeyCipher;