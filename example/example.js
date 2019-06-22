const filter = require('../index');
const fs = require('fs');
const path = require('path');
const decode = require('wav-decoder');
const encode = require('wav-encoder');

(async () => {
  const args = {
    freq: 1000,
    q: 3.0,
    gain: 10.0,
    samplerate: 44100
  };

  let inputBuffer = fs.readFileSync(path.join(__dirname, 'noise.wav'));
  inputBuffer = await decode.decode(inputBuffer);
  let L = inputBuffer.channelData[0];
  let R = inputBuffer.channelData[1];

  L = filter.peaking(L, args);
  R = filter.peaking(R, args);

  let output = {
    sampleRate: 44100,
    bitDepth: 32,
    float: true,
    channelData: [L, R]
  }
  outputBuffer = await encode.encode(output);

  fs.writeFileSync(path.join(__dirname, 'output.wav'), Buffer.from(outputBuffer));
})();
