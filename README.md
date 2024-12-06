# Vehicle Rental Business

## Description
The Vehicle Rental Business project is a system designed to manage the data and operations related to vehicles, clients, and parts for a vehicle rental business. It allows seamless management of data stored in CSV files while ensuring consistency and reliability.

## Features
1. Data Management:
   - Handles three CSV files:
     - Vehicles: Contains fields like model, brand, plate number, color, year, mileage, rented status, engine type, rental price, client ID, and return date.
     - Clients: Stores client-related information.
     - Parts: Tracks available vehicle parts.
2. CRUD Operations:
   - Supports Create, Read, Update, and Delete actions on each CSV file.
   - Maintains data consistency across all files.
3. Query Functionality:
   - Allows specific queries for a client, vehicle, or part.
4. Controlled File Updates:
   - Files are not modified until changes are explicitly confirmed by the user.
   - Generates a new file upon confirmation, replacing the previous one.

## Installation
Clone the repository using the following command:

```bash
git clone https://github.com/uwiwe/Cpp-UniversityProject-1
```

## Usage
Navigate to the project's binary directory and execute the program. 

For Windows Command Prompt or PowerShell:
```cmd
cd C:\root\to\the\project\rentaVehiculos\bin
main.exe
```

For Unix/Linux-based systems:
```bash
cd /path/to/the/project/rentaVehiculos/bin
./main
```

## Contribution
Contributions are welcome! Feel free to fork the repository, create a new branch for your changes, and submit a pull request.

## License
This project is licensed under the MIT License.
