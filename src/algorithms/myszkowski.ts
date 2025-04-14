import { Algorithm, Operation } from '../types';

const myszkowskiCipher: Algorithm = {
  name: 'Myszkowski',
  keyRequired: true,
  func: (text: string, operation: Operation, key?: string) => {
    if (!key) throw new Error('Key is required for Myszkowski cipher');
    const keyUpper = key.toUpperCase().replace(/[^A-Z]/g, '');
    if (!keyUpper) throw new Error('Key must contain letters');

    const cleanedText = text.toUpperCase().replace(/[^A-Z]/g, '');
    const cols = keyUpper.length;
    const rows = Math.ceil(cleanedText.length / cols);
    let grid: string[][] = Array.from({ length: rows }, () => Array(cols).fill(''));

    if (operation === 'encrypt') {
      let idx = 0;
      for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols && idx < cleanedText.length; c++) {
          grid[r][c] = cleanedText[idx++];
        }
      }
      const keyOrder = keyUpper
        .split('')
        .map((char, i) => ({ char, index: i }))
        .sort((a, b) => a.char.localeCompare(b.char));
      const groups: number[][] = [];
      let currentGroup: number[] = [keyOrder[0].index];
      for (let i = 1; i < keyOrder.length; i++) {
        if (keyOrder[i].char === keyOrder[i - 1].char) {
          currentGroup.push(keyOrder[i].index);
        } else {
          groups.push(currentGroup);
          currentGroup = [keyOrder[i].index];
        }
      }
      groups.push(currentGroup);
      let result = '';
      for (let group of groups) {
        for (let r = 0; r < rows; r++) {
          for (let c of group) {
            if (grid[r][c]) result += grid[r][c];
          }
        }
      }
      return result;
    } else {
      const keyOrder = keyUpper
        .split('')
        .map((char, i) => ({ char, i }))
        .sort((a, b) => a.char.localeCompare(b.char));
      const groups: number[][] = [];
      let currentGroup: number[] = [keyOrder[0].i];
      for (let i = 1; i < keyOrder.length; i++) {
        if (keyOrder[i].char === keyOrder[i - 1].char) {
          currentGroup.push(keyOrder[i].i);
        } else {
          groups.push(currentGroup);
          currentGroup = [keyOrder[i].i];
        }
      }
      groups.push(currentGroup);

      // Calculate lengths for each group
      const len = cleanedText.length;
      let pos = 0;
      for (let group of groups) {
        for (let r = 0; r < rows; r++) {
          for (let c of group) {
            if (pos < len && r < rows && c < cols) {
              grid[r][c] = cleanedText[pos++];
            }
          }
        }
      }
      // Read off row by row
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

export default myszkowskiCipher;