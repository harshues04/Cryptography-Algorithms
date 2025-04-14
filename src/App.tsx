import React, { useState } from 'react';
import CryptoForm from './components/CryptoForm';
import CryptoResult from './components/CryptoResult';
import { AlgorithmType, Operation } from './types';

const App: React.FC = () => {
  const [result, setResult] = useState<string>('');
  const [error, setError] = useState<string>('');

  const handleProcess = (
    text: string,
    operation: Operation,
    algorithm: AlgorithmType,
    key?: string
  ) => {
    try {
      const processedText = algorithm.func(text, operation, key);
      setResult(processedText);
      setError('');
    } catch (err) {
      setError((err as Error).message);
      setResult('');
    }
  };

  return (
    <div className="app">
      <h1>Crypto Algorithms</h1>
      <CryptoForm onProcess={handleProcess} />
      <CryptoResult result={result} error={error} />
    </div>
  );
};

export default App;