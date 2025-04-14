import { Algorithm, Operation } from '../types';

const railFenceCipher: Algorithm = {
  name: 'Rail Fence',
  keyRequired: true,
  func: (text: string, operation: Operation, key?: string) => {
    if (!key) throw new Error('Key is required for Rail Fence cipher');
    const rails = parseInt(key);
    if (isNaN(rails) || rails < 2) throw new Error('Key must be a number >= 2');

    if (operation === 'encrypt') {
      let fence: string[][] = Array.from({ length: rails }, () => []);
      let row = 0;
      let dir = 1;

      for (let char of text.toUpperCase().replace(/[^A-Z]/g, '')) {
        fence[row].push(char);
        row += dir;
        if (row === rails - 1 || row === 0) dir = -dir;
      }

      return fence.map((row) => row.join('')).join('');
    } else {
      const len = text.length;
      let fence: (string | null)[][] = Array.from({ length: rails }, () =>
        Array(len).fill(null)
      );
      let row = 0;
      let dir = 1;
      let pos = 0;

      for (let i = 0; i < len; i++) {
        fence[row][pos] = '*';
        pos++;
        row += dir;
        if (row === rails - 1 || row === 0) dir = -dir;
      }

      let idx = 0;
      for (let r = 0; r < rails; r++) {
        for (let c = 0; c < len; c++) {
          if (fence[r][c] === '*' && idx < len) {
            fence[r][c] = text[idx++];
          }
        }
      }

      let result = '';
      row = 0;
      dir = 1;
      pos = 0;
      for (let i = 0; i < len; i++) {
        if (fence[row][pos]) result += fence[row][pos];
        pos++;
        row += dir;
        if (row === rails - 1 || row === 0) dir = -dir;
      }
      return result;
    }
  },
};

export default railFenceCipher;