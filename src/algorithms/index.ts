import atbashCipher from './atbash';
import caesarCipher from './caesar';
import augustCipher from './august';
import affineCipher from './affine';
import vigenereCipher from './vigenere';
import gronsfeldCipher from './gronsfeld';
import beaufortCipher from './beaufort';
import autoKeyCipher from './autokey';
import runningKeyCipher from './runningKey';
import hillCipher from './hillCipher';
import railFenceCipher from './railFence';
import routeCipher from './route';
import myszkowskiCipher from './myszkowski';

export const algorithms = [
  atbashCipher,
  caesarCipher,
  augustCipher,
  affineCipher,
  vigenereCipher,
  gronsfeldCipher,
  beaufortCipher,
  autoKeyCipher,
  runningKeyCipher,
  hillCipher,
  railFenceCipher,
  routeCipher,
  myszkowskiCipher,
];