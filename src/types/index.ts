export type Operation = 'encrypt' | 'decrypt';

export interface Algorithm {
  name: string;
  keyRequired: boolean;
  func: (text: string, operation: Operation, key?: string) => string;
}

export type AlgorithmType = Algorithm;