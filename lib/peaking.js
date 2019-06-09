const addon = require('../build/Release/addon');

function peaking(input, args) {
  if (typeof input === 'undefined' || Object.keys(args).length !== 5 || Object.values(args).indexOf(null) !== -1) {
    throw new Error('Worng arguments.');
  }

  const { freq, q, gain, bw, samplerate } = args;
  const res = addon.filter(input, input.length, freq, q, gain, bw, samplerate);
  const float32Array = new Float32Array(Object.values(res));

  return float32Array;
}

module.exports = {
  peaking: peaking
}
