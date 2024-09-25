#include <iostream>
using namespace std;

class Account {
private:
    string name, gender;
    double amount;
    int acc_no;
    static int account_number_generator;

public:
    void create_account(string n, string g, double amt) {
        acc_no = ++account_number_generator;
        name = n;
        gender = g;
        amount = amt;
        cout << "\n" << name << " your account created with number: " << acc_no;
    }

    void deposit(double amt) {
        if (amt < 0)
            cout << "\nAmount cannot be negative: " << amt;
        else {
            amount += amt;
            check_balance();
        }
    }

    void withdraw(double amt) {
        if (amount - amt < 5000)
            cout << "\nInsufficient balance";
        else {
            amount -= amt;
            check_balance();
        }
    }

    void check_balance() {
        cout << "\nHi " << name << ", Your account number: " << acc_no << " balance: " << amount;
    }

    int get_account_no() {
        return acc_no;
    }

    void transfer(Account &receiver, double amt) {
        if (amount - amt < 5000) {
            cout << "\nInsufficient balance to transfer";
        } else {
            amount = amount-amt;
            receiver.amount =amount+amt;
            cout << "\nTransferred " << amt << " from account " << acc_no << " to account " << receiver.get_account_no();
            check_balance();
            receiver.check_balance();
        }
    }
};

int Account::account_number_generator = 202400;

int main() {
    Account bank[100]; // Create Account type bank array of 100
    int accounts = 0;
    int acc_no, flag;
    double amount;
    Account a;
    int ch;
    string n, g;
    double amt;
    do {
        cout << "\n---------------------------";
        cout << "\n---------ABC Bank---------";
        cout << "\n---------------------------";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit to Account";
        cout << "\n3. Withdraw from Account";
        cout << "\n4. Check Balance";
        cout << "\n5. Transfer Money";
        cout << "\n0. Exit";
        cout << "\n---------------------------";
        cout << "\n:";
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "\nEnter name: ";
                cin >> n;
                cout << "\nEnter gender: ";
                cin >> g;
                while (1) {
                    cout << "\nEnter amount >= 5000 to open account: ";
                    cin >> amt;
                    if (amt >= 5000) {
                        a.create_account(n, g, amt);
                        break;
                    }
                    cout << "\nMinimum amount to open account is 5000";
                }
                bank[accounts++] = a; // Account added to bank array
                break;

            case 2:
                cout << "\nEnter Account number: ";
                cin >> acc_no;
                flag = 0;
                for (int i = 0; i < accounts; i++) {
                    if (bank[i].get_account_no() == acc_no) {
                        cout << "\nAccount found:";
                        bank[i].check_balance();
                        cout << "\nEnter amount to deposit: ";
                        cin >> amount;
                        bank[i].deposit(amount);
                        flag = 1; // found
                        break;
                    }
                }
                if (flag == 0)
                    cout << "\nAccount " << acc_no << " not found";
                break;

            case 3:
                cout << "\nEnter Account number: ";
                cin >> acc_no;
                flag = 0;
                for (int i = 0; i < accounts; i++) {
                    if (bank[i].get_account_no() == acc_no) {
                        cout << "\nAccount found:";
                        bank[i].check_balance();
                        cout << "\nEnter amount to withdraw: ";
                        cin >> amount;
                        bank[i].withdraw(amount);
                        flag = 1; // found
                        break;
                    }
                }
                if (flag == 0)
                    cout << "\nAccount " << acc_no << " not found";
                break;

            case 4:
                cout << "\nEnter Account number: ";
                cin >> acc_no;
                flag = 0;
                for (int i = 0; i < accounts; i++) {
                    if (bank[i].get_account_no() == acc_no) {
                        cout << "\nAccount found:";
                        bank[i].check_balance();
                        flag = 1; // found
                        break;
                    }
                }
                if (flag == 0)
                    cout << "\nAccount " << acc_no << " not found";
                break;

            case 5: {
             //here i have made one sender and receiver variable
                int sender_acc_no, receiver_acc_no;
                double transfer_amt;
                cout << "\nEnter Sender's Account number: ";
                cin >> sender_acc_no;
                cout << "\nEnter Receiver's Account number: ";
                cin >> receiver_acc_no;
                flag = 0;
                int sender_index = -10, receiver_index = -10;

                for (int i = 0; i < accounts; i++) {
                    if (bank[i].get_account_no() == sender_acc_no) {
                        sender_index = i;
                        flag++;
                    }
                    if (bank[i].get_account_no() == receiver_acc_no) {
                        receiver_index = i;
                        flag++;
                    }
                    if (flag == 2) break; // it means both accounts found
                }
                
    //here sender_index and receiver_index is given -10 karan it because it not going in
    //the iterations
                if (sender_index != -10 && receiver_index != -10) {
                    cout << "\nEnter amount to transfer: ";
                    cin >> transfer_amt;
                    bank[sender_index].transfer(bank[receiver_index], transfer_amt);
                } else {
                    cout << "\nOne or both account numbers not found.";
                }
                break;
            }

            case 0:
                cout << "Thanks for banking with us.....";
                break;

            default:
                cout << "Wrong option selected";
                break;
        }
    } while (ch != 0);
    return 0;
}