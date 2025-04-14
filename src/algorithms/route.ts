import { Algorithm, Operation } from '../types';

const routeCipher: Algorithm = {
  name: 'Route',
  keyRequired: true,
  func: (text: string, operation: Operation, key?: string) => {
    if (!key) throw new Error('Key is required for Route cipher');
    const rows = parseInt(key);
    if (isNaN(rows) || rows < 1) throw new Error('Key must be a number >= 1');

    const cleanedText = text.toUpperCase().replace(/[^A-Z]/g, '');
    const cols = Math.ceil(cleanedText.length / rows);
    let grid: string[][] = Array.from({ length: rows }, () => Array(cols).fill(''));

    if (operation === 'encrypt') {
      let idx = 0;
      for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols && idx < cleanedText.length; c++) {
          grid[r][c] = cleanedText[idx++];
        }
      }
      let result = '';
      for (let c = 0; c < cols; c++) {
        for (let r = 0; r < rows; r++) {
          if (grid[r][c]) result += grid[r][c];
        }
      }
      return result;
    } else {
      const len = cleanedText.length;
      let idx = 0;
      for (let c = 0; c < cols; c++) {
        for (let r = 0; r < rows && idx < len; r++) {
          grid[r][c] = cleanedText[idx++];
        }
      }
      let result = '';
      for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
          if (grid[r][c]) result += grid[r][c];
        }
      }
      return result;
    }
  },
};

export default routeCipher;