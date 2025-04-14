import React from 'react';

interface CryptoResultProps {
  result: string;
  error: string;
}

const CryptoResult: React.FC<CryptoResultProps> = ({ result, error }) => {
  return (
    <div className="result-container">
      {error && <p className="error">{error}</p>}
      {result && (
        <>
          <h2>Result</h2>
          <p>{result}</p>
        </>
      )}
    </div>
  );
};

export default CryptoResult;