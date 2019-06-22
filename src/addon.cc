#include <nan.h>
#include "peaking.hpp"
#include <iostream>

namespace demo {
NAN_METHOD(filter)
{
  if(info.Length() < 2)
  {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  // args
  auto input = Nan::To<v8::Object>(info[0]).ToLocalChecked();
  auto size = Nan::To<v8::Uint32>(info[1]).ToLocalChecked();
  auto freq = Nan::To<v8::Number>(info[2]).ToLocalChecked();
  auto q = Nan::To<v8::Number>(info[3]).ToLocalChecked();
  auto gain = Nan::To<v8::Number>(info[4]).ToLocalChecked();
  auto samplerate = Nan::To<v8::Uint32>(info[5]).ToLocalChecked();
  const int length = size->Value();

  // native float array factory
  float inputArray[length];
  for (int i = 0; i < length; i++) {
    auto num = Nan::To<v8::Number>(Nan::Get(input, i).ToLocalChecked()).ToLocalChecked();
    inputArray[i] = num->Value();
  }

  // apply filter
  float outputArray[length];
  peaking(inputArray,
          outputArray,
          length,
          freq->Value(),
          q->Value(),
          gain->Value(),
          samplerate->Value());

  // output array factory
  auto outputObj = Nan::New<v8::Object>();
  for (int i = 0; i < length; i++) {
    auto num = Nan::New<v8::Number>(outputArray[i]);
    Nan::Set(outputObj, i, num);
  }

  // return
  info.GetReturnValue().Set(outputObj);
}

NAN_MODULE_INIT( init )
{
  Nan::SetMethod(target, "filter", filter);
}

NODE_MODULE(addon, init)
}
