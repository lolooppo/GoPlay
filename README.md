### GoPlay
# Playground Reservation System

This is a C++ implementation of a **Playground Reservation System** that allows users to reserve football playgrounds, manage reservations, and handle administrative tasks like adding new bookable items. The system is designed using **Object-Oriented Programming (OOP)** principles.

---

## Features

- **User Roles**:
  - **Regular Users**: Can view their profile, make reservations, and cancel reservations.
  - **Admins**: Can add new bookable items (e.g., football playgrounds) and manage system data.

- **Reservation Management**:
  - Users can reserve playgrounds for specific time slots.
  - Reservations are checked for availability before confirmation.
  - Users can cancel their reservations, freeing up the time slot.

- **Bookable Items**:
  - Supports football playgrounds with customizable pricing (morning and night rates).
  - Each bookable item has a unique ID and tracks reserved time slots.

- **Error Handling**:
  - Validates user input (e.g., time slots, IDs, and passwords).
  - Provides clear error messages for invalid inputs.

- **Data Persistence**:
  - Initial data (users and bookable items) is loaded at startup for demonstration purposes.

---

## How It Works

1. **User Authentication**:
   - Users can log in or sign up.
   - Admins have additional privileges to add new bookable items.

2. **Reservation Flow**:
   - Users select a time slot and check availability.
   - If available, the reservation is confirmed, and the total cost is calculated based on the time of day.

3. **Cancellation Flow**:
   - Users can view their reservations and cancel them if needed.
   - Cancelled time slots are freed up for other users.

4. **Admin Flow**:
   - Admins can add new football playgrounds with unique IDs and pricing.

---

## Code Structure

- **Classes**:
  - `Bookable`: Base class for bookable items.
  - `FootballPlayGround`: Derived class for football playgrounds.
  - `Reservation`: Base class for reservations.
  - `FootballReservation`: Derived class for football reservations.
  - `User`: Represents a user with reservations.
  - `UserManager`: Manages user authentication and data.
  - `BookableManager`: Manages bookable items and reservations.
  - `UserView`: Handles the user interface for regular users.
  - `AdminView`: Handles the user interface for admins.
  - `GoPlay`: Main class to run the application.

- **Key Functions**:
  - `ReadInt()`: Validates integer input within a range.
  - `ShowMenu()`: Displays a menu and returns the user's choice.
  - `CheckPeriod()`: Checks if a time slot is available.
  - `ReservePeriod()`: Reserves a time slot.
  - `FreePeriod()`: Frees a reserved time slot.

---

## How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/lolooppo/GoPlay.git
  
2. Compile the code using a C++ compiler (e.g., g++):
  ```bash
  g++ main.cpp -o GoPlay
  ``` 
3. Run the executable:
  ```bash
  ./GoPlay  
  ```


## Future Improvements
  1. Add support for more types of bookable items (e.g., basketball courts, tennis courts).

  2. Implement file-based data persistence to save and load user and bookable data.

  3. Enhance the UI with a graphical interface (e.g., using Qt or another framework).

  4. Add unit tests to ensure code reliability.
