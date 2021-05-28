import 'package:flutter/material.dart';
import 'package:my_trivia_client/frontend/buttons/buttons.dart' as btn;
import "package:my_trivia_client/backend/my_navigator/my_navigator.dart" as nav;
import "package:my_trivia_client/frontend/background.dart" as background;


class MyTriviaClientShopPage extends StatefulWidget {
  @override
  _MyTriviaClientShopPageState createState() => _MyTriviaClientShopPageState();
}

class _MyTriviaClientShopPageState extends State<MyTriviaClientShopPage> {
  @override
  Widget build(BuildContext context) {
    return WillPopScope(
      child: new Scaffold(
        appBar: new AppBar(
          leading: new IconButton(
            icon: new Icon(
              Icons.arrow_back,
            ),
            onPressed: () =>  nav.Nav.goBack(context),
          ),
        ),
      ),
      onWillPop: () => new Future.value(false),
    );
  }
}