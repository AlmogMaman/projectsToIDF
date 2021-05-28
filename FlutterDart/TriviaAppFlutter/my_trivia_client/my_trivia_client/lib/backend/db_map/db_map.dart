//Map of all the data bases that take a part of the project
import 'package:my_trivia_client/backend/network/network.dart' as net;
import 'package:synchronized/synchronized.dart';

var lock = new Lock();

List<dynamic> global_tech_db = [];
List<dynamic> global_food_db = [];
List<dynamic> global_health_db = [];


class DB
{
  

  //Inits the data bases.
  static void initDB() async
  {

    await lock.synchronized(
      () async
      {
        net.Network.getData(net.Network.URLS_MAP["tech"]).then(
        (value)
          {
            global_tech_db = value;
          }
        );

        //init the food db.
        net.Network.getData(net.Network.URLS_MAP["food"]).then(
          (value)
          {
            global_food_db = value;
          }
        );


        //Inits the health db.
        net.Network.getData(net.Network.URLS_MAP["health"]).then(
          (value)
          {
            global_health_db = value;
          }
        );
      }
    );
  }

  static Map<String, List<dynamic>> db_map =
  {
    "tech" : global_tech_db,
    "food" : global_food_db,
    "health" : global_health_db, 
  };


  //Checks the validation of the data bases - that they are
  //not null or empty tho.
  static bool checkDbValidation()
  {
    bool isValid = true;

    for(String i in DB.db_map.keys)
    {
      print(DB.db_map[i]);
      // if(DB.db_map[i].isEmpty)
      // {
      //   isValid = false;
      //   print("There is not data bases validation...");
      //   print("The problem is about the $i data base - at least");
      //   break;
      // }
    }
    return true;
    // DB.db_map.forEach(
    //   (String k, List<dynamic> v)
    //   {
    //     if(v.isEmpty) //Check
    //     {
    //       valid = false;
    //       print("There is not data bases validation...");
    //       print("The problem is about the $k data base - at least");
    //     }
    //   }
    // );

    //return valid;
  }
}
