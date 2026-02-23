from datetime import datetime

# Prompt user for date of birth
dob_input = input("Enter your date of birth (YYYY-MM-DD): ")

try:
    # Convert input string to date object
    dob = datetime.strptime(dob_input, "%Y-%m-%d")
    today = datetime.today()

    # Calculate age
    age = today.year - dob.year - ((today.month, today.day) < (dob.month, dob.day))

    print(f"You are {age} years old.")

except ValueError:
    print("Invalid date format. Please enter the date in YYYY-MM-DD format.")
sum = 32


