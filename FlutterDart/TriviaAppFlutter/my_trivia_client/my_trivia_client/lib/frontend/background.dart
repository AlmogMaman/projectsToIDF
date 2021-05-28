import 'dart:core';
import 'package:flutter/material.dart';

Map<String,Background> backgrounds = {
  "Pig" : new Background("assets/images/homePageLandscape1.gif"),
  "Day" : new Background("assets/images/sunnyDay.gif"),
  "Sunset" : new Background("assets/images/sunset-on-a-beach.gif"),
  "Night" : new Background("assets/images/night.gif"),
  "SimpsonsTrivia" : new Background("assets/images/simpsonsTriviaGif.gif"),
  "Trivia" : new Background("assets/images/triviaBackgroundGif.gif"),
};

final Background DEFULT_HOME_BACKGROUND = backgrounds["Trivia"];
final Background DEFULT_SLASH_BACKGROUND = backgrounds["Trivia"];

class Background extends StatelessWidget {
  final String name;

  Background(this.name, {Key key}):super(key:key);
  @override
  Widget build(BuildContext context) {
    return Image(
      image: new AssetImage(
        name,
      ),
      fit: BoxFit.fill,
      height: MediaQuery.of(context).size.height,
      width: MediaQuery.of(context).size.width,
    );
  }
}