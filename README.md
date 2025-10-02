# Bus Network Management System

This is a C++ console application for managing a bus network. It models bus stops and routes as a graph and uses Dijkstra's algorithm to find the shortest path between two stops based on distance. The system allows both administrators and passengers to interact with the bus network. Data for stops, routes, and tickets is stored in CSV files, ensuring data persistence between program executions.

### Features

  * **Graph Representation:** The bus network is modeled as a graph where stops are nodes and routes are weighted edges.
  * **Shortest Path Calculation:** Uses a min-priority queue with **Dijkstra's algorithm** to find the shortest path and associated total fare between any two bus stops.
  * **Data Persistence:** All stops, routes, and tickets are loaded from and saved to CSV files (`Stops.csv`, `Routes.csv`, and `Tickets.csv`).
  * **User Roles:** The system has two main user types:
      * **Admin:** Can add new stops and routes to the network. Admin access is protected by a simple login.
      * **Passenger:** Can view all stops and routes, search for stops, find the shortest path, book tickets, and view or cancel existing tickets.

### Getting Started

#### Prerequisites

  * A C++ compiler that supports C++11 or newer (for features like `std::tuple` and `auto`).
  * A basic text editor to view or edit the CSV files.

#### How to Compile and Run

1.  Save the provided code as a `.cpp` file (e.g., `main.cpp`).
2.  Compile the code using a C++ compiler. For example, with g++:
    ```sh
    g++ main.cpp -o bus_system
    ```
3.  Run the executable:
    ```sh
    ./bus_system
    ```
    The program will automatically create the necessary CSV files if they don't already exist.

### Usage

When you run the program, you will be presented with a main menu to choose your role as either an **Admin** or a **Passenger**.

#### Admin Menu

The admin menu allows you to manage the bus network.

1.  **Add Stop:** Prompts for a new stop ID and name to add to the network and save to `Stops.csv`.
2.  **Add Route:** Prompts for a route ID, a starting stop ID, a destination stop ID, the distance, and the fare. The new route is added to the network and saved to `Routes.csv`.

#### Passenger Menu

The passenger menu provides options for searching and booking.

1.  **Display all Stops:** Shows a list of all bus stops with their IDs and names.
2.  **Display all Routes:** Lists all available routes, including source, destination, distance, and fare.
3.  **Search Stop by ID:** Finds and displays information for a stop using its ID.
4.  **Search Stop by Name:** Finds and displays information for a stop using its name (case-insensitive).
5.  **Display Routes from Stop:** Shows all routes starting from a specified stop ID.
6.  **Display Shortest Path:** Calculates and displays the shortest route between two stops, along with the total distance and fare.
7.  **Book Ticket:** Books a ticket between two stops, calculates the fare, and saves the ticket to `Tickets.csv`.
8.  **Show Ticket:** Displays the details of a booked ticket using its ID.
9.  **Cancel Ticket:** Deletes a ticket by its ID from both the program's data and the `Tickets.csv` file.
