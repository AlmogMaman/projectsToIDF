import 'dart:core';
import 'dart:ui';
import 'package:flutter/material.dart';
import 'package:my_trivia_client/frontend/buttons/buttons.dart' as btn;
import "package:my_trivia_client/backend/my_navigator/my_navigator.dart" as nav;
import "package:my_trivia_client/frontend/background.dart" as background;
import 'package:my_trivia_client/frontend/app_pages/trivia_page.dart' as trivia;
import 'package:my_trivia_client/frontend/app_pages/home_page.dart' as home;
import 'package:my_trivia_client/backend/db_map/db_map.dart' as db_map_file;

final Color BACKGROUND_COLOR = Colors.blue.shade300;
final Color ICON_COLOR = Colors.white;


class MyTriviaClientPlayPage extends StatelessWidget{
 

  @override
  Widget build(BuildContext context) {
    final double DEFULT_BTN_WIDTH = MediaQuery.of(context).size.width/1.1;
    final double DEFULT_BTN_HEIGHT = MediaQuery.of(context).size.height/10;
    return WillPopScope(
      onWillPop: () => new Future.value(false),
      child: new Scaffold(
        backgroundColor: BACKGROUND_COLOR,
        appBar: new AppBar(
          leading: new IconButton(
            icon: new Icon(
              Icons.home,
            ),
            onPressed: () => nav.Nav.addPage(home.MyTriviaClientHomePage(
              homeBackground: background.DEFULT_HOME_BACKGROUND,
            ), context),
          ),
        ),
        body: new Column(
          mainAxisAlignment: MainAxisAlignment.spaceAround,
          children: <Widget>[

            //Tech room btn
            new btn.RoomOptionBtn(
              iconColor: ICON_COLOR,
              db: db_map_file.DB.db_map["tech"],
              iconSign: Icons.computer,
            ),


            //Food room btn
            new btn.RoomOptionBtn(
              iconColor: ICON_COLOR,
              db: db_map_file.DB.db_map["food"],
              iconSign: Icons.local_pizza,
            ),



            //Health room btn
            new btn.RoomOptionBtn(
              iconColor: ICON_COLOR,
              db: db_map_file.DB.db_map["health"],
              iconSign: Icons.directions_run,
            ),





          ],
        ),
      ),
    );
  }
}



