import "dart:core";
import "package:flutter/material.dart";

 

class Nav{
  static void addPage(Widget page, BuildContext context, [bool removeStack = true])
  {
    if(!removeStack)
    {
      Navigator.push(
        context,
        new MaterialPageRoute(
          builder: (context) => page,
        ),
      );
    }
    else
    {
      Navigator.of(context).pushAndRemoveUntil(
        MaterialPageRoute(
          builder: (context) => page,
        ),
        (Route<dynamic> route) => false,
      );
    }
  }


  static void goBack(BuildContext context)
  {
    Navigator.pop(context);
  }
}
