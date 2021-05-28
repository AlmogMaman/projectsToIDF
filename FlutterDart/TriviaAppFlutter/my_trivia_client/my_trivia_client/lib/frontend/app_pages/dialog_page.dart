import 'package:flutter/material.dart';
import 'package:my_trivia_client/main.dart';

class MyTriviaClientDialogPage extends StatelessWidget {

  final String msg;
  final void Function () onTapping;
  final String btnText;
  final String dialogTitle;
  final String pageTitle;

  MyTriviaClientDialogPage(
    {
      @required this.msg,
      @required this.onTapping,
      @required this.btnText,
      @required this.dialogTitle,
      @required this.pageTitle,
      Key key,
    }
  ) : super(key: key);

  Widget dialogCreator(BuildContext context)
  {
    return AlertDialog(
      content: new Text(
        this.msg,
      ),
      title: new Text(
        this.dialogTitle,
      ),
      actions: <Widget>[
        new FlatButton(
          onPressed: this.onTapping,
          child: new Text(
            this.btnText,
          ),
        ),
      ],
    );
  }
  @override
  Widget build(BuildContext context) {
    return new Scaffold(
      appBar: new AppBar(
        title: new Text(
          this.pageTitle,
        ),
      ),
      body: this.dialogCreator(context),
    );
  }
}