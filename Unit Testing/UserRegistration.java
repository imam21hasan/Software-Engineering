import java.util.ArrayList;

public class UserRegistration {
	public ArrayList<User> users;

	public UserRegistration() {
		users = new ArrayList<>();
	}
	
	// add a new user
	public boolean addUser(User user)
	{
		if(user == null)
		{
			throw new IllegalArgumentException("User cannot be null");
		}
		if(user.getName() == null || user.getName().isEmpty())
		{
			throw new IllegalArgumentException("Name cannot be empty");
		}
		
		if(user.getEmail() == null || user.getEmail().isEmpty())
		{
			throw new IllegalArgumentException("Email cannot be empty");
		}
		
		if(user.getPassword() == null || user.getPassword().isEmpty())
		{
			throw new IllegalArgumentException("Password cannot be empty");
		}
		
		users.add(user);
		return true;
	}
	
	// Find user by email
	public User findUser(String email)
	{
		if(email == null || email.isEmpty())
		{
			throw new IllegalArgumentException("Email field is empty");
		}
		
		for(User user:users)
		{
			if(user.getEmail().equals(email))
			{
				return user;
			}
		}
		
		return null;
	}
	
	// Login verification 
	public boolean login(String email, String password)
	{
		if(email == null || email.isEmpty())
		{
			throw new IllegalArgumentException("Email cannot be empty");
		}
		
		if(password == null || password.isEmpty())
		{
			throw new IllegalArgumentException("Password cannot be empty");
		}
		
		// find the user by email then match the password
		User user = findUser(email);
		if(user == null)
		{
			return false;
		}
		
		if(!user.getPassword().equals(password))
		{
			return false;
		}
		
		return true;
		
	}
}

