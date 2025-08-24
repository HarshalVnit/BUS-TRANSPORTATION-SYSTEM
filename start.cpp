#include <iostream>
#include <map>
#include <vector>
#include <algorithm> // for std::transform
// #include <cctype>     // for ::tolower
// #include<bool>.....
#include <unordered_map>
#include <queue>      // required
#include <vector>     // for vector
#include <functional> // for greater<>

using namespace std;
class stop
{
private:
    int StopID;
    string StopName;

public:
    stop() : StopID(-1), StopName("Unknown") {} // 👈 default constructor//v.g.imp

    // constructor
    stop(int StopID, string StopName)
    {
        this->StopID = StopID;
        this->StopName = StopName;
    }
    // getter
    int getStopID() { return StopID; }
    string getStopName() { return StopName; }
    // setter
    void setStopName(string Name) { StopName = Name; }
    // display
    void DisplayStop()
    {
        cout << "StopID:" << StopID << endl
             << "StopName:" << StopName << endl;
    }
};
class Route
{
private:
    int RouteID;
    stop Source;
    stop Destination;
    int fare;
    float distance;

public:
    //  meaning of Source(Source)
    // Left side Source → member variable of class.
    // Right side Source → which is in the construcore parameter which is given as input
    // this means:
    // this->Source = parameter Source(this pevents extra copy of snstructor of stop also)
    Route(int RouteID, stop Source, stop Destination, int fare, float distance)
        : Source(Source), Destination(Destination) // Constructor Initializer List
    {
        this->RouteID = RouteID;
        this->fare = fare;
        this->distance = distance;
    }
    // getter
    float getDistance() { return distance; }
    int getFare() { return fare; }
    stop getSource() { return Source; }
    stop getDestination() { return Destination; }
    // display
    void DisplayRoute()
    {
        cout << "RouteID: " << RouteID << endl;

        cout << "Source stop: " << Source.getStopName() << endl;
        cout << "Destination stop: " << Destination.getStopName() << endl;
        cout << "distance:" << distance << " km ,\n fair is:" << fare << endl;
    }
};
class graph
{
private:
    map<int, stop> stops;
    map<int, vector<Route>> adjlist;
    unordered_map<int, float> dist;
    unordered_map<int, int> fare;
    unordered_map<int, int> parent;

public:
    // void ShortestPath(int StartID, int EndID);
    tuple<vector<int>, float, int> ShortestPath(int StartID, int EndID);

    void AddStop(stop s)
    {
        // stops[s.getStopID()] = s;//isse agar stops me stops does not exists t default constructor type something issue was there
        stops.insert({s.getStopID(), s});
    }
    void AddRoute(Route r)
    { // because getSource funtion only return stop obj then we have again to find
        int SourceID = r.getSource().getStopID();
        adjlist[SourceID].push_back(r);
    }
    void DisplayRoutefromStop(int StopID)
    {
        if (stops.find(StopID) == stops.end())
        {
            cout << "StopID " << StopID << " not found in stops map!" << endl;
            return;
        }
        if (adjlist.find(StopID) == adjlist.end())
        {
            cout << "No such stops available\n";
            return;
        }
        cout << "Routes from stop " << stops[StopID].getStopName() << ":" << endl;
        for (auto &r : adjlist[StopID])
        {
            cout << "To -> " << r.getDestination().getStopName() << endl;
            cout << "| Distance :" << r.getDistance() << "km" << endl;
            cout << "| Fare:" << r.getFare() << "rs" << endl;
        }
    }
    void DisplayallStops()
    {
        cout << "ALL STOPS :\n";
        for (auto &r : stops)
        {
            cout << "Stop id:" << r.first << " |Stop Name:" << r.second.getStopName() << endl;
        }
    }
    void DisplayallRoutes()
    {
        cout << "ALL Routes :\n";
        for (auto &r : adjlist)
        {
            cout << "Stop id:" << r.first << " |Stop Name:" << stops[r.first].getStopName() << endl;
            for (auto &p : adjlist[r.first])
            {
                cout << "To -> " << p.getDestination().getStopName() << endl;
                cout << "| Distance :" << p.getDistance() << "km" << endl;
                cout << "| Fare:" << p.getFare() << "rs" << endl;
            }
        }
    }
    stop *SearchStopbyID(int id)
    {
        for (auto &r : stops)
        {
            if (r.first == id)
                return &(r.second);
        }
        return nullptr;
    }
    string tolowercase(string s)
    {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }
    // transform(InputBegin, InputEnd, OutputBegin, Function);

    stop *SearchStopbyName(string name)
    {
        string searchname = tolowercase(name);
        for (auto &r : stops)
        {
            if (tolowercase(r.second.getStopName()) == searchname)
                return &(r.second);
        }
        return nullptr;
    }
    void Allroutesfromstop(string name)
    {
        string searchname = tolowercase(name);
        for (auto &r : stops)
        {
            if (tolowercase(r.second.getStopName()) == searchname)
            {
                cout << " Routes are as follows from " << searchname;
                for (auto &p : adjlist[r.first])
                {
                    cout << "To -> " << p.getDestination().getStopName() << endl;
                    cout << "| Distance :" << p.getDistance() << "km" << endl;
                    cout << "| Fare:" << p.getFare() << "rs" << endl;
                }
            }
        }
    }
};
tuple<vector<int>, float, int> graph::ShortestPath(int StartID, int EndID)
{
    bool startidfound = false, endidfound = false;
    for (auto &a : stops)
    {
        if (a.first == StartID)
            startidfound = true;
        if (a.first == EndID)
            endidfound = true;
    }
    if (!startidfound || !endidfound)
    {
        cout << "One f the ID's not found retry again with available stop ids\n";
        return {{}, -1, -1};
    }
    else
    {

        for (auto &b : stops)
        {
            dist[b.first] = INT_MAX;
            fare[b.first] = INT_MAX;
        }
        dist[StartID] = 0;
        fare[StartID] = 0;

        for (auto &c : stops)
            parent[c.first] = -1;

        priority_queue<
            pair<float, int>,         // what type we store? {distance, stopID}
            vector<pair<float, int>>, // underlying container (default is vector)
            greater<pair<float, int>> // comparator → makes it min-heap
            >
            pq;
        pq.push({0, StartID}); // {distance, stopID}
                               // This means: "Start exploring from StartID with distance 0."

        while (!pq.empty())
        {
            auto [CurrDist, u] = pq.top();
            pq.pop();
            if (CurrDist > dist[u])
                continue;
            for (auto &edge : adjlist[u])
            {
                int v = edge.getDestination().getStopID();
                float weight = edge.getDistance();
                int farex = edge.getFare();
                if (weight + dist[u] < dist[v])
                {
                    dist[v] = weight + dist[u];
                    fare[v] = farex + fare[u];
                    pq.push({dist[v], v});
                    parent[v] = u;
                }
            }
        }
        vector<int> path;
        for (int i = EndID; i != -1; i = parent[i])
        {
            path.push_back(i);
        }
        reverse(path.begin(), path.end());

        return {path, dist[EndID], fare[EndID]};
    }
}
// void graph::ShortestPath(int StartID, int EndID)
// {
//     bool startidfound = false, endidfound = false;
//     for (auto &a : stops)
//     {
//         if (a.first == StartID)
//             startidfound = true;
//         if (a.first == EndID)
//             endidfound = true;
//     }
//     if (!startidfound || !endidfound)
//     {
//         cout << "One f the ID's not found retry again with available stop ids\n";
//         return;
//     }
//     else
//     {

//         for (auto &b : stops)
//         {
//             dist[b.first] = INT_MAX;
//         }
//         dist[StartID] = 0;

//         for (auto &c : stops)
//             parent[c.first] = -1;

//         priority_queue<
//             pair<int, int>,         // what type we store? {distance, stopID}
//             vector<pair<int, int>>, // underlying container (default is vector)
//             greater<pair<int, int>> // comparator → makes it min-heap
//             >
//             pq;
//         pq.push({0, StartID}); // {distance, stopID}
//                                // This means: "Start exploring from StartID with distance 0."
//         while (!pq.empty())
//         {
//             auto [currDist, u] = pq.top(); // get the node with the smallest distance
//             pq.pop();

//             // If we already found a shorter distance before, skip this entry
//             if (currDist > dist[u])
//                 continue;

//             // Explore neighbors of u
//             for (auto &edge : adjlist[u])
//             {
//                 int v = edge.getDestination().getStopID();
//                 int weight = edge.getDistance();

//                 // Relaxation step: check if going via u gives a shorter path
//                 if (dist[u] + weight < dist[v])
//                 {
//                     dist[v] = dist[u] + weight;
//                     parent[v] = u;         // record the path
//                     pq.push({dist[v], v}); // push the updated distance
//                 }
//             }
//         }
//         while (!pq.empty())
//         {
//             auto [CurrDist, u] = pq.top();
//             pq.pop();
//             if (CurrDist > dist[u])
//                 continue;
//             for (auto &edge : adjlist[u])
//             {
//                 int v = edge.getDestination().getStopID();
//                 float weight = edge.getDistance();
//                 if (weight + dist[u] < dist[v])
//                 {
//                     dist[v] = weight + dist[u];
//                     pq.push({dist[v], v});
//                     parent[v] = u;
//                 }
//             }
//         }
//         vector<int> path;
//         for (int i = EndID; i != -1; i = parent[i])
//         {
//             path.push_back(i);
//         }
//         reverse(path.begin(), path.end());

//         cout << "Shortest path from " << stops[StartID].getStopName() << " to " << stops[EndID].getStopName() << "is:\n";
//         for (int i = 0; i < path.size() - 1; i++)
//         {
//             cout << path[i] << " -> ";
//         }
//         cout << path[path.size() - 1] << endl;
//         cout << "total distance is " << dist[EndID];
//     }
// }
class Ticket
{
    // private://in sab to private nahi rakhna ham ticket ke map to to prvate rakhre ne

public:
    int ticketid;
    string PassengerName;
    int sourceid;
    int destid;
    int fare;
    float dist;
    map<int, Ticket> Tickets;
    graph g1;
    Ticket(int id, string name, int id1, int id2, int f, float d)
        : ticketid(id), PassengerName(name), sourceid(id1), destid(id2), fare(f), dist(d) {}
};

class TicketSystemm
{
private:
    map<int, Ticket> Tickets;
    graph g1;
    int counter = 1;

public:
    void BookTicket()
    {
        int sid, did;
        cout << "enter source id:\n";
        cin >> sid;
        cout << "enter destination id\n";
        cin >> did;
        string Pname;
        cin.ignore();
        getline(cin, Pname);
        stop *s = g1.SearchStopbyID(sid);
        stop *d = g1.SearchStopbyID(did);
        if (s && d)
        {
            auto [path, totaldist, totalfare] = g1.ShortestPath(sid, did);
            // cout << "total shortest distance is:" << totaldist << endl;
            // cout << "total fare will be:" << totalfare << endl;
            // this->fare = totalfare;
            // this->dist = totaldist;
            // this->destid = did;
            // this->sourceid = sid;
            // this->PassengerName = Pname;
            Ticket t(counter, Pname, sid, did, totalfare, totaldist);
            // Tickets.push_back(counte++, t);my wrong interpretation
            Tickets[t.ticketid] = t;
            cout << "\nTicket booked successfully!\n";
            cout << "Ticket ID: " << t.ticketid << endl;
            cout << "Passenger: " << t.PassengerName << endl;
            cout << "From " << sid << " to " << did << endl;
            cout << "Distance: " << t.dist << " km\n";
            cout << "Fare: " << t.fare << " Rs\n";
        }
        else
            cout << "invalid ids found\n";
    }
    void Showticket(int id)
    {
        if (Tickets.find(id) != Tickets.end())
        {
            Ticket t = Tickets[id];
            cout << "\n Ticket Details\n";
            cout << "ID: " << t.ticketid << " | Passenger: " << t.PassengerName
                 << " | Fare: " << t.fare << " | Distance: " << t.dist << endl;
        }
        else
        {
            cout << " Ticket not found!\n";
        }
    }
    void cancelticket(int id)
    {
        auto it = Tickets.find(id);
        if(it !=Tickets.end())
        {
            Tickets.erase(id);
            cout << "Ticket with id " << id << "is cancelled\n";
        }
        else
            cout << "no such ticket id is found\n";
    }
};
int main()
{
    graph g1;
    TicketSystemm t1;
    int choice;
    int flag = 1;
    while (flag == 1)
    {
        cout << "\n==========BUS NETWORK MENU==========\n";
        cout << "1.Add Stop\n";
        cout << "2.Add Route\n";
        cout << "3.Display all Stops\n";
        cout << "4.Display all Routes\n";
        cout << "5.Search Stop by ID\n";
        cout << "6.Search Stop by Name\n";
        cout << "7.Display Routes from Stops\n";
        cout << "8.Shortest Path\n";
        cout << "9.Book ticket\n";
        cout << "10.show ticket\n";
        cout << "11.cancel ticket\n";
        cout << "12.Exit\n";
        cout << "Enter choice:\n";
        cin >> choice;

        if (choice == 1)
        {
            int id;
            cout << "Enter Stop ID:\n";
            cin >> id;
            string name;
            cout << "Enter Stop Name:\n";
            cin.ignore();
            getline(cin, name);
            g1.AddStop(stop(id, name));
            // used stop to initialize that stop here as it was not pre existed
            // function to add[search if stop is aleady present]
        }
        else if (choice == 2)
        {
            int sid, did, rid, tfare;
            float dist;
            string sname, dname;
            cout << "Enter Route id:\n";
            cin >> rid;

            cout << "Enter Start stop id:\n";
            cin >> sid;
            cout << "Enter Destination id:\n";
            cin >> did;
            cout << "Enter Distance between these two routes:\n";
            cin >> dist;
            cout << "Enter Total fare:\n";
            cin >> tfare;
            stop *s = g1.SearchStopbyID(sid);
            stop *d = g1.SearchStopbyID(did);
            if (s && d)
                g1.AddRoute(Route(rid, *s, *d, tfare, dist));
            else
                cout << "invalid stop id's";
        }
        else if (choice == 3)
        {
            g1.DisplayallStops();
        }
        else if (choice == 4)
        {
            g1.DisplayallRoutes();
        }
        else if (choice == 5)
        {
            int rid1;
            cout << "enter stop id:\n";
            stop *s1 = g1.SearchStopbyID(rid1);
            if (s1)
                s1->DisplayStop();
            else
                cout << "no stop found";
        }
        else if (choice == 6)
        {
            string rname;
            cin.ignore();
            getline(cin, rname);
            stop *s2 = g1.SearchStopbyName(rname);
            if (s2)
            {
                s2->DisplayStop();
            }
            else
                cout << "no stop found\n";
        }
        else if (choice == 7)
        {
            int rid2;
            cout << "enter source id:\n";
            cin >> rid2;
            g1.DisplayRoutefromStop(rid2);
        }
        else if (choice == 8)
        {
            int rid3, rid4;
            cout << "enter source id:\n";
            cin >> rid3;
            cout << "enter destination id:\n";
            cin >> rid4;
            g1.ShortestPath(rid3, rid4);
        }
        else if (choice == 9)
        {
            t1.BookTicket();
        }
        else if (choice == 10)
        {
            flag = 0;
        }
    }

    // stop s1(1, "nagpur");
    // stop s2(2, "jalgaon");
    // stop s3(3, "mumbai");
    // s1.DisplayStop();
    // Route s1_s2(11, s1, s2, 700, 350);
    // Route s1_s3(12, s1, s3, 2000, 800);
    // Route s2_s3(23, s2, s3, 650, 300);

    // s1_s2.DisplayRoute();
    // graph g1;
    // g1.AddStop(s1);
    // g1.AddStop(s2);
    // g1.AddStop(s3);

    // g1.AddRoute(s1_s3);
    // g1.AddRoute(s1_s2);
    // g1.AddRoute(s2_s3);
    // g1.DisplayRoutefromStop(s1.getStopID());
    // g1.DisplayallStops();
    // g1.DisplayallRoutes();

    // stop *s = g1.SearchStopbyID(1);
    // if (s != nullptr)
    // {
    //     cout << "Found Stop: " << s->getStopName() << endl;
    // }
    // else
    // {
    //     cout << "Stop not found!" << endl;
    // }
    // stop *ss = g1.SearchStopbyName("Nagpur");
    // if (s != nullptr)
    // {
    //     cout << "Found Stop: " << s->getStopID() << endl;
    // }
    // else
    // {
    //     cout << "Stop not found!" << endl;
    // }
    // g1.Allroutesfromstop("nagpur");
    // g1.ShortestPath(1, 3);
    return 0;
}