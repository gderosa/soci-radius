#include "soci.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <exception>
#include <vector>

using namespace soci;
using namespace std;

bool getName(string &name)
{
    cout << "Enter name: ";
    return cin >> name;
}

int main()
{
    try
    {
        session sql("mysql", "db=radius user=radius password=radius");

        string username;
        indicator ind;
        // an useful query to get IP -> username mapping :
        // * ensure user is online
        // * in case of conflicts, take the most recent entry
        string ip = "192.168.104.129";
        string query = "SELECT username FROM radacct WHERE acctstoptime IS NULL AND framedipaddress = '" + ip + "' order by acctstarttime desc limit 1";
        sql << query, into(username, ind);
      
        if ( ind == i_ok ) {
          cout 
            << "online user with ip = " << ip << " is '" << username << "'\n";
        } else {
          cout 
            << "there's no online user with ip = " << ip << "\n";
        }

        // part 2: multiple rows, use std::vector
        vector<int>     ids(100);
        vector<string>  usernames(100);
        vector<tm>      starttimes(100);
        string query2 = "SELECT radacctid, username, acctstarttime FROM radacct";
        sql << query2, into(ids), into(usernames), into(starttimes);
        unsigned int i;        
        for (i=0; i<ids.size(); i++) {
          cout << 
            ids[i]                  << "\t" << 
            usernames[i]            << "\t" << 
            asctime(&starttimes[i]) ;
        }

    }
    catch (exception const &e)
    {
        cerr << "Error: " << e.what() << '\n';
    }
}

