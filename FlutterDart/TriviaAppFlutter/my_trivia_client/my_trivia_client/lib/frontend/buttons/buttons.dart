import 'package:flutter/material.dart';
import 'dart:core';
import 'package:my_trivia_client/backend/my_navigator/my_navigator.dart' as nav;
import 'package:my_trivia_client/frontend/app_pages/trivia_page.dart' as trivia;

final double BORDER_RADIUS = 100;
const double ICON_SIZE = 50;
const Color ICON_COLOR = Colors.red;


// class CustomButton extends StatefulWidget {
//   final Alignment rowAlignment;
//   final double iconSize;
//   final Color iconColor;
//   final IconData iconSign;
//   final void Function() onTapping;
//   final Color btnColor;
//   final Alignment btnAlignment;
//   final double btnWidth;
//   final double btnHeight;
//   final String stringText;
//   final TextStyle textStyle;

//   CustomButton(
//     {
//       this.textStyle = null,
//       this.iconSign = null,
//       this.iconSize = ICON_SIZE,
//       this.iconColor = ICON_COLOR,
//       this.rowAlignment = Alignment.center,
//       @required this.onTapping,
//       this.btnColor = Colors.transparent,
//       this.btnAlignment = Alignment.center,
//       @required this.btnWidth,
//       @required this.btnHeight,
//       this.stringText = "",
//       Key key,
//     }
//   ):super(key:key);

//   @override
//   _CustomButtonState createState() => _CustomButtonState(
//     rowAlignment: this.rowAlignment,
//     iconSize: this.iconSize,
//     iconColor: this.iconColor,
//     iconSign: this.iconSign,
//     onTapping: this.onTapping,
//     btnColor: this.btnColor,
//     btnAlignment: this.btnAlignment,
//     btnWidth: this.btnWidth,
//     btnHeight: this.btnHeight,
//     stringText: this.stringText,
//     textStyle: this.textStyle,
//   );
// }

// class _CustomButtonState extends State<CustomButton> {

//   Alignment rowAlignment;
//   double iconSize;
//   Color iconColor;
//   IconData iconSign;
//   void Function() onTapping;
//   Color btnColor;
//   Alignment btnAlignment;
//   double btnWidth;
//   double btnHeight;
//   String stringText;
//   TextStyle textStyle;

//   _CustomButtonState(
//     {
//       @required this.textStyle,
//       @required this.iconSign,
//       @required this.iconSize,
//       @required this.iconColor,
//       @required this.rowAlignment,
//       @required this.onTapping,
//       @required this.btnColor,
//       @required this.btnAlignment,
//       @required this.btnWidth,
//       @required this.btnHeight,
//       @required this.stringText,
//     }
//   );

//   @override
//   Widget build(BuildContext context)
//   {
//     return new Align(
//       alignment: this.btnAlignment,
//       child: new GestureDetector(
//         child: Container(
//           child: new Row(
//             mainAxisAlignment: MainAxisAlignment.center,
//             crossAxisAlignment: CrossAxisAlignment.center,
//             children: <Widget>[
//               new Icon(
//                 this.iconSign,
//                 color: this.iconColor,
//                 size: this.iconSize,
//               ),
//               new Text(
//                 this.stringText,
//                 style: this.textStyle,
//               ),
//             ],
//           ),
//           decoration: new BoxDecoration(
//             border: new Border.all(
//               width: 1
//             ),
//             borderRadius: new BorderRadius.circular(BORDER_RADIUS),
//             color: this.btnColor,
//           ),
//           alignment: this.rowAlignment,
//           padding: new EdgeInsets.all(0),
//           width: this.btnWidth,
//           height: this.btnHeight,
//         ),
//         onTap: this.onTapping,
//       ),
//     );
//   }

// }


class CustomButton extends StatelessWidget
{
  final Alignment rowAlignment;
  final double iconSize;
  final Color iconColor;
  final IconData iconSign;
  final void Function() onTapping;
  final Color btnColor;
  final Alignment btnAlignment;
  final double btnWidth;
  final double btnHeight;
  final String stringText;
  final TextStyle textStyle;

  CustomButton(
    {
      this.textStyle = null,
      this.iconSign = null,
      this.iconSize = ICON_SIZE,
      this.iconColor = ICON_COLOR,
      this.rowAlignment = Alignment.center,
      @required this.onTapping,
      this.btnColor = Colors.transparent,
      this.btnAlignment = Alignment.center,
      @required this.btnWidth,
      @required this.btnHeight,
      this.stringText = "",
      Key key,
    }
  ):super(key:key);
  
  @override
  Widget build(BuildContext context)
  {
    return new Align(
      alignment: this.btnAlignment,
      child: new GestureDetector(
        child: Container(
          child: new Row(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: <Widget>[
              new Icon(
                this.iconSign,
                color: this.iconColor,
                size: this.iconSize,
              ),
              new Flexible(
                child: new Text(
                  this.stringText,
                  style: this.textStyle,
                ),
              ),
            ],
          ),
          decoration: new BoxDecoration(
            border: new Border.all(
              width: 1
            ),
            borderRadius: new BorderRadius.circular(BORDER_RADIUS),
            color: this.btnColor,
          ),
          alignment: this.rowAlignment,
          padding: new EdgeInsets.all(0),
          width: this.btnWidth,
          height: this.btnHeight,
        ),
        onTap: this.onTapping,
      ),
    );
  }
}

class RoomOptionBtn extends StatelessWidget {
  final Color iconColor;
  final IconData iconSign;
  final List<dynamic> db;
  RoomOptionBtn(
    {
      this.iconColor = Colors.red,
      @required this.db,
      @required this.iconSign,
      Key key
    }
  ): super(key:key);
  @override
  Widget build(BuildContext context) {
    final double DEFULT_BTN_WIDTH = MediaQuery.of(context).size.width/1.1;
    final double DEFULT_BTN_HEIGHT = MediaQuery.of(context).size.height/10;
    return CustomButton(
      btnAlignment: Alignment(0,0),
      btnWidth: DEFULT_BTN_WIDTH,
      btnHeight: DEFULT_BTN_HEIGHT,
      iconSign: this.iconSign,
      iconColor: this.iconColor,
      onTapping: () => nav.Nav.addPage(trivia.MyTriviaClientTriviaPage(db: this.db,), context),
    );
  }
}

