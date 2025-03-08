#include <bits/stdc++.h>
using namespace std;

// Some useful functions
// Function to read an integer within a specified range [low, high]
int ReadInt(const int& low, const int& high) {
    int choice;
    cin >> choice;

    if (choice >= low && choice <= high)
        return choice;

    cerr << "\tError, please try again...\n\n";
    return ReadInt(low, high); // Recursive call for invalid input
}

// Function to display a menu and return the user's choice
int ShowMenu(const vector<string>& choices) {
    for (int i = 0; i < (int)choices.size(); i++) {
        cerr << "\t" << (i + 1) << ")" << choices[i] << "\n";
    }
    return ReadInt(1, (int)choices.size()); // Validate user choice
}




// Base class for bookable items (e.g., playgrounds)
class Bookable {
private:
    string id; // Unique identifier for the bookable item
    string category; // Category of the bookable item (e.g., Football)
    vector<int> bookable_periods; // Tracks availability of time slots (0 = free, 1 = reserved)

public:
    // Constructor initializes bookable_periods with 12 slots (all free by default)
    Bookable() {
        bookable_periods = vector<int>(12, 0);
    }

    // Setter and Getter for id
    void SetId(const string& id) {
        this->id = id;
    }
    const string& GetId() const {
        return id;
    }

    // Setter and Getter for category
    void SetCategory(const string& category) {
        this->category = category;
    }
    const string& GetCategory() const {
        return category;
    }

    // Check if a time period [from, to] is available
    bool CheckPeriod(const int& from, const int& to) {
        for (int i = from - 1; i < to; i++) {
            if (bookable_periods[i])
                return false; // Period is already reserved
        }
        return true; // Period is free
    }

    // Reserve a time period [from, to]
    void ReservePeriod(const int& from, const int& to) {
        for (int i = from - 1; i < to; i++)
            bookable_periods[i] = 1; // Mark as reserved
    }

    // Free a time period [from, to]
    void FreePeriod(const int& from, const int& to) {
        for (int i = from - 1; i < to; i++)
            bookable_periods[i] = 0; // Mark as free
    }

    // Pure virtual functions to be implemented by derived classes
    virtual string ToString() = 0; // Returns a string representation of the object
    virtual void Read(string id) = 0; // Reads input to initialize the object
    virtual ~Bookable() {} // Virtual destructor for proper cleanup
};

// Derived class for Football Playgrounds
class FootballPlayGround : public Bookable {
private:
    double morning_price; // Price for morning bookings
    double night_price; // Price for night bookings

public:
    FootballPlayGround() = default; // Default constructor

    // Setter and Getter for morning_price
    void SetMorningPrice(const double& morning_price) {
        this->morning_price = morning_price;
    }
    const double& GetMorningPrice() const {
        return morning_price;
    }

    // Setter and Getter for night_price
    void SetNightPrice(const double& night_price) {
        this->night_price = night_price;
    }
    const double& GetNightPrice() const {
        return night_price;
    }

    // Returns a string representation of the FootballPlayGround object
    string ToString() override {
        ostringstream oss;
        oss << "\tId: " << GetId() << ", Category: " << GetCategory() << "\n";
        oss << "\tMorning Price: " << GetMorningPrice() << ", Night Price: " << GetNightPrice();
        return oss.str();
    }

    // Reads input to initialize the FootballPlayGround object
    virtual void Read(string id) {
        SetId(id);
        SetCategory("Football");

        double morning_price, night_price;

        cerr << "Enter Morning Price: ";
        cin >> morning_price;
        SetMorningPrice(morning_price);

        cerr << "Enter Night Price: ";
        cin >> night_price;
        SetNightPrice(night_price);
    }

    virtual ~FootballPlayGround() {} // Virtual destructor
};




// Manages all bookable items
class BookableManager {
private:
    map<string, Bookable*> id_to_bookable_map; // Maps bookable IDs to Bookable objects

    // Frees memory allocated for bookable items
    void FreeLoadedData() {
        for (auto& pair : id_to_bookable_map) {
            delete pair.second; // Delete each Bookable object
        }
        id_to_bookable_map.clear(); // Clear the map
    }

    // Loads initial data (for demonstration purposes)
    void LoadData() {
        FootballPlayGround* venue = new FootballPlayGround;
        venue->SetId("001");
        venue->SetMorningPrice(150);
        venue->SetNightPrice(200);
        id_to_bookable_map["001"] = venue; // Add to the map
    }

public:
    // Constructor loads initial data
    BookableManager() {
        LoadData();
    }

    // Destructor frees allocated memory
    ~BookableManager() {
        FreeLoadedData();
    }

    // Adds a new bookable item to the manager
    void AddBookable(Bookable* new_bookable) {
        new_bookable->Read(new_bookable->GetId()); // Initialize the bookable
        id_to_bookable_map[new_bookable->GetId()] = new_bookable; // Add to the map
    }

    // Returns the map of bookable items
    const map<string, Bookable*> GetBookablesMap() const {
        return id_to_bookable_map;
    }

    // Checks if a bookable ID is unique
    bool CheckBookableId(const string& id) {
        return (id_to_bookable_map.count(id) == 0); // True if ID is not in use
    }
};





// Base class for reservations
class Reservation {
protected:
    string user_name; // Name of the user making the reservation
    string bookable_id; // ID of the bookable item being reserved

public:
    Reservation() {}

    // Setter and Getter for user_name
    void SetUserName(const string& user_name) {
        this->user_name = user_name;
    }
    const string& GetUserName() const {
        return user_name;
    }

    // Setter and Getter for bookable_id
    void SetBookableId(const string& bookable_id) {
        this->bookable_id = bookable_id;
    }
    const string& GetBookableId() const {
        return bookable_id;
    }

    // Pure virtual functions to be implemented by derived classes
    virtual string ToString() = 0; // Returns a string representation of the reservation
    virtual double TotalPrice() = 0; // Calculates the total price of the reservation
    virtual bool CompleteReservation(string user_name) = 0; // Completes the reservation process
    virtual ~Reservation() {} // Virtual destructor
};

// Derived class for Football Reservations
class FootballReservation : public Reservation {
private:
    int from; // Start time of the reservation
    int to; // End time of the reservation
    BookableManager& bookable_manager; // Reference to the BookableManager

public:
    // Constructor initializes the BookableManager reference
    FootballReservation(BookableManager& bookable_manager) :
        bookable_manager(bookable_manager) {
    }

    // Calculates the total price of the reservation
    virtual double TotalPrice() override {
        FootballPlayGround* venue = static_cast<FootballPlayGround*>(bookable_manager.GetBookablesMap().at(GetBookableId()));

        double total_price{ 0.0 };
        for (int i = from; i < to; i++)
            total_price += (i < 6) ? venue->GetMorningPrice() : venue->GetNightPrice(); // Morning or night price
        return total_price;
    }

    // Returns a string representation of the reservation
    virtual string ToString() override {
        ostringstream oss;
        oss << "\tVenue Id: " << GetBookableId() << "\n";
        oss << "\tFrom: " << from << ", To: " << to << "\n";
        oss << "\tFor Total Cost: " << TotalPrice() << "\n";
        return oss.str();
    }

    // Setter for reservation period
    void SetReservationPeriod(const int& from, const int& to) {
        this->from = from;
        this->to = to;
    }

    // Getter for reservation period
    pair<int, int> GetReservationPeriod() const {
        return make_pair(from, to);
    }

    // Completes the reservation process
    virtual bool CompleteReservation(string user_name) override {
        int from, to;
        while (true) {
            cerr << "Enter From: ";
            cin >> from;
            if (from < 1 || from > 11) {
                cerr << "\tInvalid input...\n";
                continue;
            }

            cerr << "Enter To: ";
            cin >> to;
            if (to < 2 || to > 12 || to <= from) {
                cerr << "\tInvalid input...\n";
                continue;
            }
            break;
        }

        bool reserved{ false };
        for (auto& pair : bookable_manager.GetBookablesMap()) {
            FootballPlayGround* venue = static_cast<FootballPlayGround*>(pair.second);
            if (venue->CheckPeriod(from, to - 1)) {
                venue->ReservePeriod(from, to - 1); // Reserve the period
                SetUserName(user_name);
                SetBookableId(venue->GetId());
                SetReservationPeriod(from, to);
                reserved = true;
                cerr << "\n" << ToString() << "\n";
                break;
            }
        }

        return reserved; // True if reservation was successful
    }

    virtual ~FootballReservation() {} // Virtual destructor
};





// Class representing a user
class User {
private:
    string name; // User's name
    string email; // User's email
    string password; // User's password
    bool is_admin; // True if the user is an admin
    vector<Reservation*> reservations; // List of user's reservations

public:
    User() {
        is_admin = false; // Default to non-admin
    }

    // Reads user details from input
    void Read(const string& name) {
        this->name = name;

        cerr << "Enter Email: ";
        cin >> email;

        cerr << "Enter password: ";
        cin >> password;
    }

    // Setter and Getter for name
    void SetName(const string& name) {
        this->name = name;
    }
    const string& GetName() const {
        return name;
    }

    // Setter and Getter for email
    void SetEmail(const string& email) {
        this->email = email;
    }
    const string& GetEmail() const {
        return email;
    }

    // Setter and Getter for password
    void SetPassword(const string& password) {
        this->password = password;
    }
    const string& GetPassword() const {
        return password;
    }

    // Returns whether the user is an admin
    const bool& IsAdmin() const {
        return is_admin;
    }

    // Sets the user as an admin
    void SetAsAdmin() {
        is_admin = true;
    }

    // Adds a reservation to the user's list
    void AddReservation(Reservation* reservation) {
        reservations.push_back(reservation);
    }

    // Deletes a reservation from the user's list
    void DeleteReservation(Reservation* reservation) {
        for (int i = 0; i < (int)reservations.size(); i++) {
            if (reservation == reservations[i]) {
                swap(reservations[i], reservations.back());
                break;
            }
        }

        delete reservation; // Free memory
        reservations.pop_back(); // Remove from the list
    }

    // Returns the list of reservations
    const vector<Reservation*>& GetReservations() const {
        return reservations;
    }

    // Returns a string representation of the user
    string ToString() const {
        ostringstream oss;
        oss << "Name: " << GetName() << ", Email: " << GetEmail();
        return oss.str();
    }
};

// Manages all users
class UserManager {
private:
    User* current_user; // Currently logged-in user
    map<string, User*> users_map; // Maps usernames to User objects

    // Frees memory allocated for users
    void FreeLoadedData() {
        for (auto& pair : users_map) {
            delete pair.second; // Delete each User object
        }
        users_map.clear(); // Clear the map
    }

    // Loads initial data (for demonstration purposes)
    void LoadData() {
        User* user_1 = new User;
        user_1->SetName("alaa");
        user_1->SetEmail("omranalaa754@gmail.com");
        user_1->SetPassword("alaa2004");
        user_1->SetAsAdmin();
        users_map["alaa"] = user_1;

        User* user_2 = new User;
        user_2->SetName("norhan");
        user_2->SetEmail("norhanalaa754@gmail.com");
        user_2->SetPassword("norhan2004");
        users_map["norhan"] = user_2;
    }

public:
    // Constructor initializes the current_user to nullptr and loads data
    UserManager() :
        current_user(nullptr) {
        LoadData();
    }

    // Destructor frees allocated memory
    ~UserManager() {
        FreeLoadedData();
    }

    // Handles user login or signup
    void AccessSystem() {
        int choice = ShowMenu({ "Log In", "Sign Up" });

        if (choice == 1)
            DoLogIn();
        else
            DoSignUp();
    }

    // Handles user login
    void DoLogIn() {
        string name;
        string password;
        while (true) {
            cerr << "Enter your name: ";
            cin >> name;

            if (users_map.count(name) == 0) {
                cerr << "\n\tOops, no such user name...\n";
                continue;
            }

            cerr << "Enter your password: ";
            cin >> password;

            if (users_map[name]->GetPassword() != password) {
                cerr << "\n\tOops, wrong password...\n";
                continue;
            }
            current_user = users_map[name];
            break;
        }
    }

    // Handles user signup
    void DoSignUp() {
        string name;

        while (true) {
            cerr << "Enter name(no spaces): ";
            cin >> name;

            if (users_map.count(name)) {
                cerr << "\n\tSorry, this user name is already in use...\n";
                continue;
            }
            else
                break;
        }

        User* new_user = new User;
        new_user->Read(name);
        users_map[name] = new_user;
        current_user = new_user;
    }

    // Adds a reservation to the current user
    void AddReservation(Reservation* reservation) {
        current_user->AddReservation(reservation);
    }

    // Deletes a reservation from the current user
    void DeleteReservation(Reservation* reservation) {
        current_user->DeleteReservation(reservation);
    }

    // Returns the currently logged-in user
    User* GetCurrentUser() const {
        return current_user;
    }

    // Returns the map of users
    const map<string, User*> GetUsersMap() const {
        return users_map;
    }
};





// Handles the user interface for regular users
class UserView {
private:
    BookableManager& bookable_manager; // Reference to the BookableManager
    UserManager& user_manager; // Reference to the UserManager

public:
    // Constructor initializes references
    UserView(BookableManager& bookable_manager, UserManager& user_manager) :
        bookable_manager(bookable_manager), user_manager(user_manager) {
    }

    // Displays the user interface
    void Display() {
        const User* user = user_manager.GetCurrentUser();
        cerr << "\n\tName: " << user->GetName() << " || " << "User View\n";

        vector<string> menu;
        menu.push_back("View profile");
        menu.push_back("List my Reservations");
        menu.push_back("Reserve");
        menu.push_back("Cancel Reservation");
        menu.push_back("Log out");

        while (true) {
            int choice = ShowMenu(menu);
            if (choice == 1) {
                ViewProfile();
            }
            else if (choice == 2) {
                ListMyReservations();
            }
            else if (choice == 3) {
                DoReserve();
            }
            else if (choice == 4) {
                DoCanceling();
            }
            else {
                break;
            }
        }
    }

    // Displays the current user's profile
    void ViewProfile() const {
        User* current_user = user_manager.GetCurrentUser();
        cerr << current_user->ToString() << "\n";
    }

    // Lists the current user's reservations
    bool ListMyReservations() const {
        string current_user_name = user_manager.GetCurrentUser()->GetName();
        vector<Reservation*> current_user_reservations = user_manager.GetUsersMap().at(current_user_name)->GetReservations();

        if (current_user_reservations.empty()) {
            cerr << "Sorry, you have not any reservations yet...\n";
            return false;
        }
        else
            for (auto& reservation : current_user_reservations)
                cerr << reservation->ToString() << "\n";
        cerr << "\n";
        return true;
    }

    // Handles the reservation process
    void DoReserve() {
        FootballReservation* reservation = new FootballReservation(bookable_manager);
        if (!reservation->CompleteReservation(user_manager.GetCurrentUser()->GetName())) {
            cerr << "\n\tSorry, no available bookable at this period...\n\n";
            delete reservation;
            return;
        }
        cerr << "\tCongratulations, Reservation has done successfully...\n\n";
        user_manager.AddReservation(reservation);
    }

    // Handles the cancellation process
    void DoCanceling() {
        if (!ListMyReservations())
            return;

        pair<int, int> period;  // {from,to}
        cerr << "\n\tEnter the reserved period you want to cancel\n";

        cerr << "\tEnter From: ";
        cin >> period.first;
        if (period.first < 1 || period.first > 11) {
            cerr << "\tInvalid input...\n";
            return;
        }

        cerr << "\tEnter To: ";
        cin >> period.second;
        if (period.second < 2 || period.first > 12 || period.second <= period.first) {
            cerr << "\tInvalid input...\n";
            return;
        }

        vector<Reservation*> current_user_reservations = user_manager.GetCurrentUser()->GetReservations();
        FootballPlayGround* venue{ nullptr };

        for (int i = 0; i < (int)current_user_reservations.size(); ++i) {
            FootballReservation* football_reservation = static_cast<FootballReservation*>(current_user_reservations[i]);
            if (football_reservation->GetReservationPeriod() == period) {
                string bookable_id = football_reservation->GetBookableId();
                venue = static_cast<FootballPlayGround*>(bookable_manager.GetBookablesMap().at(bookable_id));
                user_manager.DeleteReservation(football_reservation);
                break;
            }
        }

        if (venue == nullptr) {
            cerr << "\n\tSorry, no such reservation done by you at this period\n";
            return;
        }

        // Free the reserved period from the reserved venue (football play ground)
        venue->FreePeriod(period.first, period.second);
        cerr << "\n\tReservation has been canceled successfully\n\n";
    }
};





// Handles the user interface for admins
class AdminView {
private:
    BookableManager& bookable_manager; // Reference to the BookableManager
    UserManager& user_manager; // Reference to the UserManager

public:
    // Constructor initializes references
    AdminView(BookableManager& bookable_manager, UserManager& user_manager) :
        bookable_manager(bookable_manager), user_manager(user_manager) {
    }

    // Displays the admin interface
    void Display() {
        User* current_user = user_manager.GetCurrentUser();
        cerr << "\n\tName: " << current_user->GetName() << " | " << "Admin view\n";

        vector<string> menu;
        menu.push_back("View Profile");
        menu.push_back("Add Bookable");
        menu.push_back("Log Out");

        while (true) {
            int choice = ShowMenu(menu);
            if (choice == 1) {
                ViewProfile();
            }
            else if (choice == 2) {
                AddBookable();
            }
            else {
                break;
            }
        }
    }

    // Displays the current admin's profile
    void ViewProfile() {
        User* current_user = user_manager.GetCurrentUser();
        cerr << current_user->ToString() << "\n";
    }

    // Handles adding a new bookable item
    void AddBookable() {
        FootballPlayGround* venue = new FootballPlayGround;

        string id;
        while (true) {
            cerr << "Enter new Bookable Id: ";
            cin >> id;

            if (bookable_manager.CheckBookableId(id) == false) {
                cerr << "Sorry, this id is already in use...\n";
                continue;
            }
            else {
                break;
            }
        }
        bookable_manager.AddBookable(venue);
    }
};





// Main class to run the application
class GoPlay {
    BookableManager* bookable_manager; // Manages bookable items
    UserManager* user_manager; // Manages users

public:
    // Constructor initializes managers
    GoPlay() :
        bookable_manager(new BookableManager), user_manager(new UserManager) {
    }

    // Destructor frees allocated memory
    ~GoPlay() {
        delete bookable_manager;
        delete user_manager;
    }

    // Runs the application
    void run() {
        while (true) {
            user_manager->AccessSystem();

            if (user_manager->GetCurrentUser()->IsAdmin()) {
                AdminView view(*bookable_manager, *user_manager);
                view.Display();
            }
            else {
                UserView view(*bookable_manager, *user_manager);
                view.Display();
            }
        }
    }
};


// Entry point of the program
int main() {
    GoPlay site;
    site.run();
}