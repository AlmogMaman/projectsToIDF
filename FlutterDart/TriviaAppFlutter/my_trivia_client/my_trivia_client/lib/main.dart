import 'dart:io';
import 'dart:math';

import 'package:flutter/material.dart';
import 'package:synchronized/synchronized.dart';
import "frontend/app_pages/home_page.dart" as home_page_file;
import 'frontend/background.dart' as background;
import 'backend/db_map/db_map.dart' as db_map_file;
import 'package:my_trivia_client/backend/network/network.dart' as net;
import 'frontend/app_pages/dialog_page.dart' as dialog_page_file;

Widget homePage;


void restartProgram()
{
  print(""); // Change
  print("Restarting the program.");//Change
  main();
}

void main() 
{
  WidgetsFlutterBinding.ensureInitialized();


  
  net.Network.checkInternetConnectivity().then(
    (v)
    {
      if(v)
      {
        // //final result = InternetAddress.lookup('google.com');//check server connection
        // //if(internet && serverConnection)
        try{
          db_map_file.DB.initDB();
        }
        catch(e){
          print("the exeptions is: $e");
          throw (e);
        }
        homePage = home_page_file.MyTriviaClientHomePage(
          homeBackground: background.DEFULT_HOME_BACKGROUND,
        );
      }
      else
      {
        homePage = dialog_page_file.MyTriviaClientDialogPage(
          btnText: "Retry",
          dialogTitle: "Error",
          msg: "There is no Internet connection",
          onTapping: restartProgram,
          pageTitle: "My Trivia Client",
        );
      }
      runApp(MyTriviaClientApp());
    }
  );
  //Random rand = new Random();
  // //If the internet is on.
}
  

class MyTriviaClientApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      //debugShowCheckedModeBanner: false,
      // home: score.MyTriviaClientScorePage(
      //   sp: 0,
      //   db: tech.techRoomDb,
      // ),
      home: homePage,
    );
  }
}
//To run in more devices use "flutter run -d $deviceName" (deviceName -
//second device)










































































































// import 'dart:io';
// //import 'package:synchronized/synchronized.dart';
// import 'package:flutter/material.dart';
// import "frontend/app_pages/home_page.dart" as home_page_file;
// import 'frontend/background.dart' as background;
// import 'backend/db_map/db_map.dart' as db_map_file;
// import 'package:my_trivia_client/backend/network/network.dart' as net;
// import 'frontend/app_pages/dialog_page.dart' as dialog_page_file;

// Widget homePage;

// void restartProgram()
// {
//   print(""); // Change
//   print("Restarting the program.");//Change
//   main();
// }


// void main() 
// {
//   WidgetsFlutterBinding.ensureInitialized();
  

  
//   net.Network.checkInternetConnectivity().then(
//     (v)
//     {
//       if(v)
//       {
        
//         var result =  InternetAddress.lookup(net.Network.SERVER_IP);//check server connection
//         result.then(
//           (List<InternetAddress> res)
//           {
//             if(res[0].address.isNotEmpty && res[0].rawAddress.isNotEmpty)
//             {
//               homePage = home_page_file.MyTriviaClientHomePage(
//                   homeBackground: background.DEFULT_HOME_BACKGROUND,
//               );
//               do
//               {
//                 try{
//                   db_map_file.DB.initDB();
//                 }
//                 catch(e){
//                   print("the exeptions is: $e");
//                   throw (e);
//                 }
//               } while(!(db_map_file.DB.checkDbValidation()));
//             } //if - first then
//             else
//             {
//               print("The server is not connected");
//               homePage = dialog_page_file.MyTriviaClientDialogPage(
//                 btnText: "Retry",
//                 dialogTitle: "Error",
//                 msg: "The server is not connected.",
//                 onTapping: restartProgram,
//                 pageTitle: "My Trivia Client",          
//               );
//             } //else - first then
//           } //Then second function
//         );
//       }
//       else
//       {
//         homePage = dialog_page_file.MyTriviaClientDialogPage(
//           btnText: "Retry",
//           dialogTitle: "Error",
//           msg: "There is no Internet connection.",
//           onTapping: restartProgram,
//           pageTitle: "My Trivia Client",          
//         );
//       }
//       runApp(MyTriviaClientApp()); //Check if we have a problem with it.
//     }//First then function
//   );
//   //Random rand = new Random();
//   // //If the internet is on.
// }
  

// class MyTriviaClientApp extends StatelessWidget {
//   // This widget is the root of your application.
//   @override
//   Widget build(BuildContext context) {
//     return MaterialApp(
//       //debugShowCheckedModeBanner: false,
//       // home: score.MyTriviaClientScorePage(
//       //   sp: 0,
//       //   db: tech.techRoomDb,
//       // ),
//       home: homePage,
//     );
//   }
// }
// //To run in more devices use "flutter run -d $deviceName" (deviceName -
// //second device)

// //If android emulator is not working in windows:
// //Use the "bcdedit /set hypervisorlaunchtype off" cmd command.
