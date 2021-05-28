import 'dart:convert';
import 'package:http/http.dart' as http;
import 'package:connectivity/connectivity.dart';

// import 'package:json_serializable/json_serializable.dart';

const int OK_STATUS_CODE = 200;

class Network
{
  static const String SERVER_IP = "10.0.2.2"; //Instead of 127.0.0.1 cus its on emulator.
  static const String SERVER_PORT = "1234";
  static const String BASIC_URL = "http://$SERVER_IP:$SERVER_PORT/";

  static const Map<String, String> URLS_MAP = 
  {
    "tech": Network.BASIC_URL + "tech",
    "food":  Network.BASIC_URL + "food",
    "health":  Network.BASIC_URL + "health",
  };


  static Future getData(String url) async
  { 
    try{
      http.Response res = await http.get(Uri.encodeFull(url));
      if(res.statusCode == OK_STATUS_CODE) return json.decode(res.body);
      else
      {
        throw Exception("An error has accured, the server returned ${res.statusCode} status code");
      }
    }
    catch(e){
      print("The exception was: $e");
      //print("The program should stop here...");
      throw Exception(e);
    }
  }

  static Future<bool> checkInternetConnectivity() async
  {
    bool connected = false;
    ConnectivityResult result = await Connectivity().checkConnectivity();
    print(result); //Change
    if(result == ConnectivityResult.mobile || result == ConnectivityResult.wifi){
      connected = true;
    }
    print("The connections is : $connected according to first"); //Change
    return connected;
  }
  static bool fetchCheckInternetConnectivity()
  {
    bool answer = false;
    Future<bool> futureAnswer = Network.checkInternetConnectivity();
    futureAnswer.then(
      (bool v)
      {
        print("The v var is: $v"); //Change
        answer = v;
      }
    );
    print("The fetch answer: $answer");//Change
    return answer;
  }
  
  static Future<bool> checkServerConnection() async
  {
    bool connected = false;
    


    return connected;
  }

}


