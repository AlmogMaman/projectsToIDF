import 'dart:core';
import 'package:flutter/material.dart';
import 'package:my_trivia_client/frontend/app_pages/play_page.dart' as playPage;
import 'package:my_trivia_client/frontend/buttons/buttons.dart' as btn;
import 'package:my_trivia_client/backend/my_navigator/my_navigator.dart' as nav;
import 'package:my_trivia_client/frontend/app_pages/trivia_page.dart' as trivia;
import 'package:my_trivia_client/frontend/app_pages/home_page.dart' as home;
import 'package:my_trivia_client/frontend/background.dart' as background;

//Global vars
final background.Background DEFULT_HOME_BACKGROUND = background.backgrounds["Trivia"];


class MyTriviaClientScorePage extends StatelessWidget {

  final double sp; //Success percent - percent of right answers.
  final List<dynamic> db;
  final TextStyle textStyle = new TextStyle(
    fontSize: 30,
  );

  MyTriviaClientScorePage(
    {
      Key key,
      @required this.sp,
      @required this.db,
    }
  ) : super(key: key);

  @override
  Widget build(BuildContext context) {
    final double DEFULT_BTN_WIDTH = MediaQuery.of(context).size.width/3.5;
    final double DEFULT_BTN_HEIGHT = MediaQuery.of(context).size.height/6;
    return new WillPopScope(
      onWillPop: () => Future.value(false),
      child: new Scaffold(
        // backgroundColor: Colors.transparent,
        body: new Column(
          mainAxisAlignment: MainAxisAlignment.spaceAround,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: <Widget>[

            //The percent of success.
            new Text(
              "You answered ${sp.round().toStringAsFixed(0)}% right",
              style: this.textStyle,
            ),

            new Divider(
              color: Colors.black,
              thickness: 1,
            ),


            new Row(
              crossAxisAlignment: CrossAxisAlignment.center,
              mainAxisAlignment: MainAxisAlignment.spaceAround,
              children: <Widget>[

                
                //Return to menue Btn
                new btn.CustomButton(
                  iconSign: Icons.arrow_back,
                  btnWidth: DEFULT_BTN_WIDTH,
                  btnHeight: DEFULT_BTN_HEIGHT,
                  onTapping: () => nav.Nav.addPage(new playPage.MyTriviaClientPlayPage(), context),
                  btnAlignment: Alignment.center,
                ),


                //Play again btn.
                new btn.CustomButton( 
                  btnWidth: DEFULT_BTN_WIDTH,
                  btnHeight: DEFULT_BTN_HEIGHT,
                  iconSign: Icons.replay,
                  onTapping: () => nav.Nav.addPage(trivia.MyTriviaClientTriviaPage(db: this.db,), context),
                ),


                //Home btn
                new btn.CustomButton( 
                  btnWidth: DEFULT_BTN_WIDTH,
                  btnHeight: DEFULT_BTN_HEIGHT,
                  iconSign: Icons.home,
                  onTapping: () => nav.Nav.addPage(home.MyTriviaClientHomePage(
                    homeBackground: DEFULT_HOME_BACKGROUND,
                  ), context),
                ),


              ],
            ),
            
          ],
        ),
      ),
    );
  }
}