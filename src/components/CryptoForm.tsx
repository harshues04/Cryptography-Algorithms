import React, { useState } from 'react';
import { Operation, AlgorithmType } from '../types';
import { algorithms } from '../algorithms';

interface CryptoFormProps {
  onProcess: (
    text: string,
    operation: Operation,
    algorithm: AlgorithmType,
    key?: string
  ) => void;
}

const CryptoForm: React.FC<CryptoFormProps> = ({ onProcess }) => {
  const [text, setText] = useState('');
  const [operation, setOperation] = useState<Operation>('encrypt');
  const [algorithmName, setAlgorithmName] = useState(algorithms[0].name);
  const [key, setKey] = useState('');

  const selectedAlgorithm = algorithms.find((alg) => alg.name === algorithmName);

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    if (!text || !selectedAlgorithm) return;
    onProcess(text, operation, selectedAlgorithm, key || undefined);
  };

  return (
    <div className="form-container">
      <form onSubmit={handleSubmit}>
        <div className="form-group">
          <label htmlFor="algorithm">Algorithm</label>
          <select
            id="algorithm"
            value={algorithmName}
            onChange={(e) => setAlgorithmName(e.target.value)}
          >
            {algorithms.map((alg) => (
              <option key={alg.name} value={alg.name}>
                {alg.name}
              </option>
            ))}
          </select>
        </div>
        <div className="form-group">
          <label htmlFor="operation">Operation</label>
          <select
            id="operation"
            value={operation}
            onChange={(e) => setOperation(e.target.value as Operation)}
          >
            <option value="encrypt">Encrypt</option>
            <option value="decrypt">Decrypt</option>
          </select>
        </div>
        <div className="form-group">
          <label htmlFor="text">Text</label>
          <textarea
            id="text"
            value={text}
            onChange={(e) => setText(e.target.value)}
            rows={4}
            placeholder="Enter text to encrypt/decrypt"
          />
        </div>
        {selectedAlgorithm?.keyRequired && (
          <div className="form-group">
            <label htmlFor="key">Key</label>
            <input
              id="key"
              type="text"
              value={key}
              onChange={(e) => setKey(e.target.value)}
              placeholder="Enter key"
            />
          </div>
        )}
        <button type="submit">Process</button>
      </form>
    </div>
  );
};

export default CryptoForm;