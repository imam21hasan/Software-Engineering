public class BankAccount {
	private int account;
	private int balance;

	public BankAccount(int account) {
		if(account<=0)
		{
			throw new IllegalArgumentException("Account Number must be positive");
		}
		this.account = account;
		balance = 0;
	}

	public int getAccount() {
		return account;
	}

	public void setAccount(int account) {
		if(account<=0)
		{
			throw new IllegalArgumentException("Account Number must be positive");
		}
		this.account = account;
		balance = 0;
	}
	
	public int getBalance()
	{
		return balance;
	}
	
	public void deposit(int amount)
	{
		if(amount<=0)
		{
			throw new IllegalArgumentException("Deposit amount must be greater than 0");
		}
		
		balance = balance + amount;
	}
	
	public void withdraw(int amount)
	{
		if(amount<=0)
		{
			throw new IllegalArgumentException("Withdraw amount must be greater than 0");
		}
		if(amount>balance)
		{
			throw new IllegalStateException("Insufficient Balance");
		}
		
		balance = balance - amount;
	}
}