import 'dart:core';
import 'dart:math';
import 'package:flutter/material.dart';
import 'package:my_trivia_client/frontend/buttons/buttons.dart' as btn;
import 'package:my_trivia_client/backend/my_navigator/my_navigator.dart' as nav;
import 'package:my_trivia_client/frontend/app_pages/score_page.dart' as scorePage;
import 'package:my_trivia_client/utils/utils.dart' as utils;


//Global variables.
final double BORDER_RADIUS = 10;
double globalSpVar = 0;
bool globalFinishGameFlagVar = false;
//Current trivia question - 
//includes question, answer and 3 wrong optiond.
dynamic globalCurrQVar = {'':''};
List<dynamic> globalQStorageVar = []; //For ask each question just one time.
TextStyle triviaTextStyle = new TextStyle(
  color: Colors.white,
  fontSize: 20,
);

final Color BACKGROUND_COLOR = Colors.blue.shade300;



class MyTriviaClientTriviaPage extends StatefulWidget {
  final List <dynamic> db;
  static final List<String> qKeys = ["q", "a", "f1", "f2", "f3"];
  static final int maxNum = 20;
  MyTriviaClientTriviaPage(
    {
      @required this.db,
      Key key, 
    }
  ): super(key:key);
   
  @override
  _MyTriviaClientTriviaPageState createState() => _MyTriviaClientTriviaPageState(db:this.db);
}

class _MyTriviaClientTriviaPageState extends State<MyTriviaClientTriviaPage> {
  int i = 0; //Real index.
  Random ran = new Random();//For random the question.
  List <dynamic> db;
  dynamic currQ;
  List<int> qIndexStorage = new List<int> (); //q stands for questions.
  double sWidth;
  double sHeight;
  String question;
  //bool finishGameFlag = false;
  int questionCounter = 1;

  
  _MyTriviaClientTriviaPageState(
    {
      @required this.db,
    }
  )
  {
    globalFinishGameFlagVar = false;
    globalSpVar = 0;
    _OptionalAnswerBtnState.indexStorage = [];
  }
  
  void _onAnswerBtnTapping()
  {
    setState(
      ()
      {
        if(i == 0) //The first question
          this.qIndexStorage.add(i);
        // if(i == 0) //The first question
        //   this.qIndexStorage.add(i);

        
        if(globalFinishGameFlagVar) //The game has finished.
        {
          nav.Nav.addPage(
            scorePage.MyTriviaClientScorePage(
              db: this.db,
              sp: globalSpVar,
            ),
            context,
          );
        }
        else //If the question is 1-15 (includes 1 and 15).
        {
          //print("after new page statement");
          this.i = ran.nextInt(MyTriviaClientTriviaPage.maxNum) % utils.OnObjectUtils.findLen(db);
          while(this.qIndexStorage.contains(i) && !globalFinishGameFlagVar)
          {
            this.i = ran.nextInt(MyTriviaClientTriviaPage.maxNum) % utils.OnObjectUtils.findLen(db);
          }
          if(i != 0) qIndexStorage.add(i);
          // if(i!=0) 
          //   qIndexStorage.add(i);
          this.questionCounter++;
          // this.currQ = db[this.i];

          globalCurrQVar = db[this.i];
          // this.question = this.currQ["q"];
          this.question = globalCurrQVar["q"];
          //print("counter: ${this.questionCounter}");
          if (this.questionCounter == utils.OnObjectUtils.findLen(this.db))
          {
            globalFinishGameFlagVar = true;
            //print(globalFinishGameFlagVar);
          } //If all the questions have been asked
          //print("that was: ${this.i} index");
          //print(this.qIndexStorage);
          // print("the current question counter: ${this.questionCounter}");
        }
      },
    );
  }

  
  @override
  Widget build(BuildContext context) {
    //this.i = ran.nextInt(MyTriviaClientTriviaPage.maxNum) % db.length;
    // this.currQ = db[i];
    globalCurrQVar = db[i];
    this.sWidth = MediaQuery.of(context).size.width;
    this.sHeight = MediaQuery.of(context).size.height;
    // this.question = this.currQ["q"];
    this.question = globalCurrQVar["q"];
    Scaffold triviaScaffold = new Scaffold(
      backgroundColor: BACKGROUND_COLOR,
      body: new Column(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        crossAxisAlignment: CrossAxisAlignment.center,

        children: <Widget>[


          //The question field
          new Container(
            decoration: new BoxDecoration(
              border: new Border.all(
                color: Colors.black,
                width: 1,
              ),
              borderRadius: new BorderRadius.circular(
                BORDER_RADIUS,
              ),
            ),
            child: new Text(
              this.question,
              style: triviaTextStyle,
            ),
            width: sWidth,
            height: sHeight/3,
            alignment: Alignment.center,
          ),

        //Current quwstion number
          new Text(
            "${this.questionCounter}/${utils.OnObjectUtils.findLen(this.db)}",
            style: triviaTextStyle,
          ),
          
          //A divider
          new Divider(
              color: Colors.black,
              thickness: 1,
          ),

          // Text(this.currQ["q"]),
          // new Text(this.currQ["a"]),


          //The answers place:
          new OptionalAnswerBtn(
            finishGameFlag: globalFinishGameFlagVar,
            currQ: this.currQ,
            onTapping: this._onAnswerBtnTapping,
            qKeys: MyTriviaClientTriviaPage.qKeys,
            dbLength: utils.OnObjectUtils.findLen(this.db),

          ),


          new OptionalAnswerBtn(
            finishGameFlag: globalFinishGameFlagVar,
            currQ: this.currQ,
            onTapping: this._onAnswerBtnTapping,
            qKeys: MyTriviaClientTriviaPage.qKeys,
            dbLength: utils.OnObjectUtils.findLen(this.db),
          ),


          new OptionalAnswerBtn(
            finishGameFlag: globalFinishGameFlagVar,
            currQ: this.currQ,
            onTapping: this._onAnswerBtnTapping,
            qKeys: MyTriviaClientTriviaPage.qKeys,
            dbLength: utils.OnObjectUtils.findLen(this.db),
          ),


          new OptionalAnswerBtn(
            finishGameFlag: globalFinishGameFlagVar,
            currQ: this.currQ,
            onTapping: this._onAnswerBtnTapping,
            qKeys: MyTriviaClientTriviaPage.qKeys,
            dbLength: utils.OnObjectUtils.findLen(this.db),
          ),
        ],
      ),
    );

    return WillPopScope(
      child: triviaScaffold, 
      onWillPop: () => new Future.value(false),
    );
    
  }
}

class OptionalAnswerBtn extends StatefulWidget {
  final void Function() onTapping;
  final bool finishGameFlag;
  static List<String> optionalAnswerKeys = [MyTriviaClientTriviaPage.qKeys[1], MyTriviaClientTriviaPage.qKeys[2], MyTriviaClientTriviaPage.qKeys[3], MyTriviaClientTriviaPage.qKeys[4]]; //The optional keys that we can use with them to get an optional answer.
  static Random ran = new Random(); //For random index.
  final dynamic currQ;
  final List<String> qKeys; //The valid keys of a question.
  static final int DURATION = 2000;
  final int dbLength;
  OptionalAnswerBtn(
    {
      @required this.finishGameFlag,
      @required this.dbLength,
      @required this.onTapping,
      @required this.currQ,
      @required this.qKeys,
      Key key,
    }
  ): super(key:key);
  @override
  _OptionalAnswerBtnState createState() => _OptionalAnswerBtnState(
    finishGameFlag: finishGameFlag,
    currQ: this.currQ,
    onTapping: this.onTapping,
    qKeys: this.qKeys,
    dbLength: this.dbLength,
  );
}

class _OptionalAnswerBtnState extends State<OptionalAnswerBtn> {
  bool finishGameFlag;
  static List<int> indexStorage = []; //Contains the indexes of the keys: a,f1,f2,f3 in our case.
  void Function() onTapping;
  dynamic currQ;
  List<String> qKeys; //The valid keys of a question.
  Color btnColor = Colors.transparent;
  Random ran = new Random();
  int i = 0; //Real index
  String currString = ""; //The current string in the btn display
  int dbLength;
  
  _OptionalAnswerBtnState(
    {
      @required this.finishGameFlag,
      @required this.dbLength,
      @required this.onTapping,
      @required this.currQ,
      @required this.qKeys,
    }
  );
  

  @override
  Widget build(BuildContext context) {
    // if(!globalFinishGameFlagVar)
    // {
    //   i = ran.nextInt(qKeys.length) % (OptionalAnswerBtn.optionalAnswerKeys.length);
    //   while(indexStorage.contains(i) && !globalFinishGameFlagVar)
    //   {
    //     i = ran.nextInt(qKeys.length) % (OptionalAnswerBtn.optionalAnswerKeys.length);
    //   }
    //   indexStorage.add(i);
    // }
    print(indexStorage);
    
    i = ran.nextInt(qKeys.length) % (OptionalAnswerBtn.optionalAnswerKeys.length);
    while(indexStorage.contains(i) && indexStorage.length <= OptionalAnswerBtn.optionalAnswerKeys.length && !globalFinishGameFlagVar)
    {
      i = ran.nextInt(qKeys.length) % (OptionalAnswerBtn.optionalAnswerKeys.length);
    }
    if(!globalFinishGameFlagVar) indexStorage.add(i);
    
    currString = globalCurrQVar[OptionalAnswerBtn.optionalAnswerKeys[i]];

    // print(this.currString);

    // currString = currQ[this.qKeys[i]];
    double sWidth = MediaQuery.of(context).size.width;
    double sHeight = MediaQuery.of(context).size.height * 1;
    return new btn.CustomButton(
      btnColor: this.btnColor,
      stringText: this.currString,
      
      // iconSign: Icons.access_alarm,
      textStyle: triviaTextStyle,
      onTapping: () => setState(
        ()
        {
          // if(currQ["a"] == this.currString)
          if(globalCurrQVar["a"] == this.currString)
          {
            SnackBar sb = new SnackBar(
              content: new Text("Right Answer"),
              backgroundColor: Colors.green,
              duration: new Duration(
                milliseconds: OptionalAnswerBtn.DURATION, //0.2 second
              ) 
            );  
            Scaffold.of(context).showSnackBar(sb);
            globalSpVar += (100 / this.dbLength); //Relative percent/
          }
          else
          {
            SnackBar sb = new SnackBar(
              content: new Text("Wrong Answer"),
              backgroundColor: Colors.red,
              duration: new Duration(
                milliseconds: OptionalAnswerBtn.DURATION, //0.2 second
              ) 
            );  
            Scaffold.of(context).showSnackBar(sb);
            // print("Hi");
            // btnColor = Colors.red;
          }
          
          // btnColor = Colors.transparent;
          this.onTapping();
          // this.currString = currQ[this.qKeys[i % qKeys.length]];
          this.currString = globalCurrQVar[this.qKeys[i % qKeys.length]];
          if(indexStorage.length == OptionalAnswerBtn.optionalAnswerKeys.length) //If the index storage is full.
          {
            indexStorage = []; //Preperation to the next question.
          }
        },
      ),
      btnWidth: sWidth/1.1,
      btnHeight: sHeight/14,
    );
  }
}






