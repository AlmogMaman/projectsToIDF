import 'dart:core';
import 'package:flutter/material.dart';
import 'package:my_trivia_client/frontend/buttons/buttons.dart' as btn;
import "package:my_trivia_client/backend/my_navigator/my_navigator.dart" as nav;
import "package:my_trivia_client/frontend/app_pages/play_page.dart" as playPage;
import "package:my_trivia_client/frontend/app_pages/shop_page.dart" as shopPage;
import "package:my_trivia_client/frontend/app_pages/level_page.dart" as levelPage;
import 'package:my_trivia_client/frontend/background.dart' as background;



// final double ICON_SIZE = 50;
// final Color ICON_COLOR = Colors.red;




class MyTriviaClientHomePage extends StatelessWidget {

  final background.Background homeBackground;


  MyTriviaClientHomePage(
      {
        @required this.homeBackground,
        Key key,
      }
    ) : super(key:key);


  @override
  Widget build(BuildContext context) {
    final double DEFULT_BTN_WIDTH = MediaQuery.of(context).size.width/3.5;
    final double DEFULT_BTN_HEIGHT = MediaQuery.of(context).size.height/6;
    return WillPopScope(
      onWillPop: () => new Future.value(false),
      child: Scaffold(
        body: new Stack(
          alignment: Alignment.center,
          textDirection: TextDirection.ltr,
          children: <Widget>[


            //Background
            homeBackground,


            //Play button
            new btn.CustomButton(
              iconSign: Icons.play_arrow,
              btnWidth: DEFULT_BTN_WIDTH,
              btnHeight: DEFULT_BTN_HEIGHT,
              onTapping: () => nav.Nav.addPage(new playPage.MyTriviaClientPlayPage(), context),
              btnAlignment: Alignment.center,
            ),


            // //Shopping button
            // new btn.CustomButton(
            //   icon: Icon(
            //     Icons.shopping_cart,
            //     size: ICON_SIZE,
            //     color: ICON_COLOR,
            //   ),
            //   onTapping: () => nav.Nav.addPage(new shopPage.MyTriviaClientShopPage(), context),
            //   btnAlignment: Alignment.bottomLeft,
            // ),


            // //Level button
            // new btn.CustomButton(
            //   icon: Icon(
            //     Icons.all_inclusive,
            //     size: ICON_SIZE,
            //     color: ICON_COLOR,
            //   ),
            //   onTapping: () => nav.Nav.addPage(new levelPage.MyTriviaClientLevelPage(), context),
            //   btnAlignment: Alignment.bottomRight,
            // ),


            //Exit button
            //new CustomButton(icon: Icons.exit, alignment: alm),



          ],
        ),
      ),
    );
  }
}
