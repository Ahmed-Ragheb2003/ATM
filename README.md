# 🏦 ATM Project in C++

![C++](https://img.shields.io/badge/Language-C++-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen.svg)

---

## 🚀 Project Overview
**ATM Project** is a **C++ console-based application** that simulates an **Automated Teller Machine (ATM)** system.  
It allows users to **login, withdraw, deposit, check balance, and view client information** through an interactive menu-driven interface.  
This project demonstrates **OOP principles, file handling, and modular programming**.

---

## 🌟 Key Features
- 🔑 **Secure Login**: Access your account using account number and PIN code.
- 💰 **Quick Withdraw**: Predefined withdrawal amounts for fast transactions.
- ✏️ **Normal Withdraw**: Withdraw a custom amount from your account.
- 🏦 **Deposit**: Add money to your account.
- 📊 **Check Balance**: View your current account balance.
- 🧾 **Show Client Data**: View full client information.
- 🕒 **Display Time & Date**: Shows current date and time for transactions.
- 🔄 **Interactive Console Interface**: Easy to navigate and user-friendly.

---

## 🛠️ Technologies Used
| Technology        | Purpose                                      |
|------------------|----------------------------------------------|
| **C++**           | Core programming language                    |
| **OOP Concepts**  | Structs, functions, modular design          |
| **File Handling** | Store and retrieve client information       |
| **Console UI**    | Menu-driven interactive screens             |

---

## 📂 Project Structure
```plaintext
ATM Project/
├── main.cpp                # Program entry point, contains main logic and menu
├── Clients.txt             # Data file storing client information
└── README.md               # Project documentation
```

---

## 🧩 How the Application Works

1. Run the program.
2. Login Screen appears:
```
---------------------------------
        Login Screen
---------------------------------
Enter Account Number? 
Enter Pin?
```

3. After successful login, the Main Menu appears:
```
==============================================
        ATM Main Menu Screen
==============================================
[1] Quick Withdraw
[2] Normal Withdraw
[3] Deposit
[4] Check Balance
[5] Show All Client Data
[6] Logout
==============================================
```

4. Select an option by entering a number from 1 to 6.

5. Follow instructions to perform the selected operation.

6. After each action, you can return to the Main Menu.

---

## 📈 Example Usage

- Login
```
Enter Account Number? 12345
Enter Pin? 54321
✅ Login Successful!
```

- Quick Withdraw
```
Choose amount:
[1] 100  [2] 250
[3] 300  [4] 450
...
[9] Exit
Your Total Balance is: 1500
```

- Normal Withdraw
```
Enter an amount Withdraw: 200
✅ Withdraw Successful. New Balance: 1300
```

- Deposit 
```
Enter an amount Deposit: 500
Are you sure you want to perform this transaction? y/n ? y
✅ Deposit Successful. New Balance: 1800
```

- Check Balance
```
Current Total Balance: 1800
```

- Show Client Data
```
| Account Number | Pin Code | Name          | Phone       | Balance |
| 12345          | 54321    | John Doe      | 0123456789 | 1800    |
```

---

## 🏗️ Code Highlights

- Struct sClient: Stores client information such as account number, PIN, name, phone, and balance.
- File Handling: Reads and writes client data to Clients.txt.
- Menu System: Enum enMainMenu handles different operations.
- Functions: Modular functions for each action (login, withdraw, deposit, check balance, display client data).
- Interactive Screens: Clear console outputs guide the user.

---

## 📝 Best Practices

- Input validation for menu options and amounts.
- Modular code with separate functions for each action.
- Confirmation prompts before sensitive transactions.
- File-based persistent storage for client data.
- User-friendly formatted output using setw and left

---

## 📜 License

This project is licensed under the MIT License.

You can freely use, modify, and distribute this software.

---

## 📫 Contact

If you want to reach me, you can contact me through:

- **GitHub:** [Ahmed-Ragheb2003](https://github.com/Ahmed-Ragheb2003)


Feel free to open issues or contribute to this project!
---
