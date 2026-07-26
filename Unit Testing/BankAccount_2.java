public class BankAccount {

    private String accountHolder;
    private double balance;

    public BankAccount(String accountHolder, double balance) {
        if (balance < 0) {
            throw new IllegalArgumentException("Initial balance cannot be negative");
        }
        this.accountHolder = accountHolder;
        this.balance = balance;
    }

    public String getAccountHolder() {
        return accountHolder;
    }

    public double getBalance() {
        return balance;
    }

    // Deposit money
    public void deposit(double amount) {
        if (amount <= 0) {
            throw new IllegalArgumentException("Deposit amount must be greater than zero");
        }
        balance += amount;
    }

    // Withdraw money
    public void withdraw(double amount) {
        if (amount <= 0) {
            throw new IllegalArgumentException("Withdraw amount must be greater than zero");
        }

        if (amount > balance) {
            throw new IllegalArgumentException("Insufficient balance");
        }

        balance -= amount;
    }

    // Check minimum balance
    public boolean hasMinimumBalance() {
        return balance >= 1000;
    }

    // Find account type
    public String getAccountType(String code) {
        if (code == null) {
            return null;
        }

        if (code.equals("SAV")) {
            return "Savings";
        } else if (code.equals("CUR")) {
            return "Current";
        }

        return null;
    }
}
