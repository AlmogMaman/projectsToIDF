import 'package:flutter/material.dart';


class OnObjectUtils
{
  //Find a len of an iteratable object.
  static int findLen(dynamic v)
  {
    int len = 0;
    for(dynamic i in v)
    {
      len++;
    }
    return len;
  }
}