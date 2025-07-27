
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
using namespace std;

struct Expense {
    string name;
    string category;
    float amount;
    string date;
    string paymentMethod;
};

struct Recurringexpense {
    string name;
    string category;
    float amount;
    string frequency;
};

vector<Expense> expenses;
vector<Recurringexpense> Recurringexpenses;
vector<string> expenseAlerts;
float totalIncome = 0.0f;
float totalExpenses = 0.0f;
string currentCurrency = "RUPEES";
map<string, float> categoryBudget;

void Addcashexpense(string name, string category, float amount, string date) {
    expenses.push_back({name, category, amount, date, "cash"});
    totalExpenses += amount;
    cout << "Cash expense added.\n";
}

void Addcardexpense(string name, string category, float amount, string date) {
    expenses.push_back({name, category, amount, date, "card"});
    totalExpenses += amount;
    cout << "Card expense added.\n";
}

void viewtransactionhistory() {
    for (auto& e : expenses)
        cout << "Name=" << e.name << " Category=" << e.category << " Amount=" << e.amount << " Date=" << e.date << " Payment=" << e.paymentMethod << endl;
}

void setrecurringexpenses(string name, string category, float amount, string frequency) {
    Recurringexpenses.push_back({name, category, amount, frequency});
    cout << "Recurring expense set.\n";
}

void viewRecurringexpenses() {
    for (auto& r : Recurringexpenses)
        cout << "Name=" << r.name << " Category=" << r.category << " Amount=" << r.amount << " Frequency=" << r.frequency << endl;
}

void editRecurringexpense(const string& name, float newAmount) {
    for (auto& r : Recurringexpenses) {
        if (r.name == name) r.amount = newAmount;
    }
    cout << "Recurring expense edited.\n";
}

void removeRecurringexpense(const string& name) {
    for (auto it = Recurringexpenses.begin(); it != Recurringexpenses.end(); ++it) {
        if (it->name == name) {
            Recurringexpenses.erase(it);
            cout << "Recurring expense removed.\n";
            return;
        }
    }
}

void setexpensealert(string alert) {
    expenseAlerts.push_back(alert);
    cout << "Alert set.\n";
}

void viewexpensealerts() {
    for (auto& a : expenseAlerts) cout << a << endl;
}

void searchExpense(const string& keyword) {
    for (const auto& e : expenses) {
        if (e.name.find(keyword) != string::npos || e.category.find(keyword) != string::npos)
            cout << e.name << " " << e.category << " " << e.amount << " " << e.date << endl;
    }
}

void groupExpensesByCategory() {
    map<string, float> grouped;
    for (const auto& e : expenses)
        grouped[e.category] += e.amount;
    for (const auto& g : grouped)
        cout << g.first << ": " << g.second << endl;
}

void compareExpenses(float previous, float current) {
    cout << "Difference: " << (current - previous) << endl;
}

void getExpenseSummary() {
    cout << "Income: " << totalIncome << ", Expenses: " << totalExpenses << ", Balance: " << (totalIncome - totalExpenses) << endl;
}

void setCurrency(const string& currency) {
    currentCurrency = currency;
    cout << "Currency set to: " << currency << endl;
}

void convertCurrency(float rate) {
    for (auto& e : expenses) e.amount *= rate;
    totalIncome *= rate;
    totalExpenses *= rate;
    cout << "All values converted by rate " << rate << endl;
}

void viewExpenseByCategory(const string& category) {
    for (const auto& e : expenses) {
        if (e.category == category)
            cout << e.name << " " << e.amount << " " << e.date << endl;
    }
}

void viewExpenseByDate(const string& date) {
    for (const auto& e : expenses) {
        if (e.date == date)
            cout << e.name << " " << e.category << " " << e.amount << endl;
    }
}

void viewExpenseByPaymentMethod(const string& method) {
    for (auto& e : expenses) {
        if (e.paymentMethod == method)
            cout << e.name << " " << e.category << " " << e.amount << " " << e.date << endl;
    }
}

void clearAllExpenses() {
    expenses.clear();
    totalExpenses = 0;
    cout << "All expenses cleared.\n";
}

void clearAllIncome() {
    totalIncome = 0;
    cout << "All income cleared.\n";
}

void resetAllData() {
    expenses.clear();
    Recurringexpenses.clear();
    expenseAlerts.clear();
    totalIncome = 0;
    totalExpenses = 0;
    categoryBudget.clear();
    currentCurrency = "RUPEES";
    cout << "All data has been reset.\n";
}

void addIncome(float income) {
    totalIncome += income;
}

void removeIncome(float amount) {
    totalIncome -= amount;
    cout << "Income removed.\n";
}

void updateIncome(float oldAmount, float newAmount) {
    totalIncome = totalIncome - oldAmount + newAmount;
    cout << "Income updated.\n";
}

void calculateAvgexpense() {
    if (expenses.empty()) {
        cout << "No expenses recorded.\n";
        return;
    }
    float sum = 0;
    for (const auto& e : expenses) sum += e.amount;
    cout << "Average Expense: " << (sum / expenses.size()) << endl;
}

void caltotalbycat(const string& category) {
    float total = 0;
    for (const auto& e : expenses) {
        if (e.category == category)
            total += e.amount;
    }
    cout << "Total spent on " << category << ": " << total << endl;
}

void exportexpensestoCSV(const string& path) {
    ofstream file(path);
    file << "Name,Category,Amount,Date,PaymentMethod\n";
    for (const auto& e : expenses) {
        file << e.name << "," << e.category << "," << e.amount << "," << e.date << "," << e.paymentMethod << "\n";
    }
    file.close();
    cout << "Expenses exported to CSV: " << path << endl;
}

void importexpensesfromCSV(const string& path) {
    ifstream file(path);
    string line;
    getline(file, line);
    while (getline(file, line)) {
        string name, category, date, method;
        float amount;
        size_t pos = 0;
        vector<string> fields;
        while ((pos = line.find(',')) != string::npos) {
            fields.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        fields.push_back(line);
        if (fields.size() == 5) {
            name = fields[0];
            category = fields[1];
            amount = stof(fields[2]);
            date = fields[3];
            method = fields[4];
            expenses.push_back({name, category, amount, date, method});
            totalExpenses += amount;
        }
    }
    file.close();
    cout << "Expenses imported from CSV: " << path << endl;
}

int main() {
    int choice;
    string name, category, date, frequency;
    float amount, oldAmount, newAmount;
    do {
        cout << "\n--- Expenditure Management Menu ---\n";
        cout << "1. Add Cash Expense\n";
        cout << "2. Add Card Expense\n";
        cout << "3. View Transaction History\n";
        cout << "4. Set Recurring Expense\n";
        cout << "5. View Recurring Expenses\n";
        cout << "6. Set Expense Alert\n";
        cout << "7. View Alerts\n";
        cout << "8. Group Expenses by Category\n";
        cout << "9. Get Expense Summary\n";
        cout << "10. Reset All Data\n";
        cout << "11. Add Income\n";
        cout << "12. Remove Income\n";
        cout << "13. Update Income\n";
        cout << "14. Export Expenses to CSV\n";
        cout << "15. Import Expenses from CSV\n";
        cout << "16. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter name, category, amount, date: ";
                cin >> name >> category >> amount >> date;
                Addcashexpense(name, category, amount, date);
                break;
            case 2:
                cout << "Enter name, category, amount, date: ";
                cin >> name >> category >> amount >> date;
                Addcardexpense(name, category, amount, date);
                break;
            case 3:
                viewtransactionhistory();
                break;
            case 4:
                cout << "Enter name, category, amount, frequency: ";
                cin >> name >> category >> amount >> frequency;
                setrecurringexpenses(name, category, amount, frequency);
                break;
            case 5:
                viewRecurringexpenses();
                break;
            case 6:
                cout << "Enter alert message: ";
                cin.ignore();
                getline(cin, name);
                setexpensealert(name);
                break;
            case 7:
                viewexpensealerts();
                break;
            case 8:
                groupExpensesByCategory();
                break;
            case 9:
                getExpenseSummary();
                break;
            case 10:
                resetAllData();
                break;
            case 11:
                cout << "Enter income amount: ";
                cin >> amount;
                addIncome(amount);
                break;
            case 12:
                cout << "Enter income amount to remove: ";
                cin >> amount;
                removeIncome(amount);
                break;
            case 13:
                cout << "Enter old income and new income: ";
                cin >> oldAmount >> newAmount;
                updateIncome(oldAmount, newAmount);
                break;
            case 14:
                cout << "Enter file path to export: ";
                cin >> name;
                exportexpensestoCSV(name);
                break;
            case 15:
                cout << "Enter file path to import: ";
                cin >> name;
                importexpensesfromCSV(name);
                break;
            case 16:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 16);
    return 0;
}
