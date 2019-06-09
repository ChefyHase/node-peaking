#include <cmath>

using namespace std;

void peaking( float input[],
              float output[],
              float size,
              float freq,
              float q,
              float gain,
              float bw,
              float samplerate )
{
  float omega = 2.0f * 3.14159265f * freq / samplerate;
  float alpha = sin( omega ) * sinh( log( 2.0f ) / 2.0 * bw * omega / sin( omega ) );
  float A = pow( 10.0f, ( gain / 40.0f ) );

  float a0 = 1.0f + alpha / A;
  float a1 = -2.0f * cos( omega );
  float a2 = 1.0f - alpha / A;
  float b0 = 1.0f + alpha * A;
  float b1 = -2.0f * cos( omega );
  float b2 = 1.0f - alpha * A;

  /* buffers */
  float in1 = 0.0f;
  float in2 = 0.0f;
  float out1 = 0.0f;
  float out2 = 0.0f;

  /* apply filter */
  for( int i = 0; i < size; i++ )
  {
    output[ i ] = b0 / a0 * input[ i ] + b1 / a0 * in1 + b2 / a0 * in2 - a1 / a0 * out1 - a2 / a0 * out2;

    in2 = in1;
    in1 = input[ i ];

    out2 = out1;
    out1 = output[ i ];
  }
}
