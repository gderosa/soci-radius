#include "soci.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <exception>

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

        int count;
        string table = "radacct";
        // an useful query to get IP -> username mapping :
        // * ensure user is online
        // * in case of conflicts, take the most recent entry
        // "select username from radacct where acctstoptime is null and framedipaddress = '192.168.104.129' order by acctstarttime desc limit 1;"
        sql << "select count(*) from radacct", into(count);

        cout 
          << "We have " << count << " entries in the " << table << " table.\n";

        
        /*
        string name;
        while (getName(name))
        {
            string phone;
            indicator ind;
            sql << "select phone from phonebook where name = :name",
                into(phone, ind), use(name);

            if (ind == i_ok)
            {
                cout << "The phone number is " << phone << '\n';
            }
            else
            {
                cout << "There is no phone for " << name << '\n';
            }
        }
        */
    }
    catch (exception const &e)
    {
        cerr << "Error: " << e.what() << '\n';
    }
}

